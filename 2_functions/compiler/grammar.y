%language "c++"
%skeleton "lalr1.cc"
%require "3.5"

%defines
%define api.value.type variant // can work with C++ objects
%define parse.error verbose // for generation errors

%locations

%code requires
{
    #include "../nodes/nodes.hpp"
    class Driver; // forward declararion
}

%param {Driver* driver}

%code
{
    #include "../driver/driver.hpp"
    yy::parser::token_type yylex(yy::parser::semantic_type* yylval, yy::parser::location_type* l, Driver* driver);
}

%token  SEMICOLON       ";"
        COMMA           ","

        ADD             "+"
        SUB             "-"
        MUL             "*"
        DIV             "/"
        MOD             "%"
        ASSIGN          "="
        INCR            "++"
        DECR            "--"

        NOT_EQUAL       "!="
        EQUAL           "=="
        LESS            "<"
        GREATER         ">"
        LESS_EQ         "<="
        GREATER_EQ      ">="

        AND             "&&"
        OR              "||"
        NOT             "!"

        LPAR            "("
        RPAR            ")"
        LBRACE          "{"
        RBRACE          "}"
        LBRACKET        "["
        RBRACKET        "]"

        QUEST_MARK      "?"
        COLON           ":"

        IF              "if"
        ELSE            "else"
        WHILE           "while"
        PRINT           "print"
        SCAN            "scan"

        BREAK           "break"
        CONTINUE        "continue"

        FUNC            "func"
        RETURN          "return"

        VAR             "var"
        ARRAY           "array"
;

%token <std::string> ID;
%token <double> NUMBER;

// lower priority
%right "="
%left "||"
%left "&&"
%left "==" "!="
%left "<" ">" "<=" ">="
%left "+" "-"
%left "*" "/" "%"
%right "++" "--" "!"
%left "[" "]" "(" ")"
// upper priority

// return types
%nterm <std::shared_ptr<BaseNode>> program
%nterm <std::shared_ptr<BaseNode>> global_scope
%nterm <std::shared_ptr<BaseNode>> global_decl
%nterm <std::shared_ptr<BaseNode>> decl_func
%nterm <std::shared_ptr<BaseNode>> func_sign
%nterm <std::shared_ptr<BaseNode>> args
%nterm <std::string>               arg
%nterm <std::shared_ptr<BaseNode>> func_scope
%nterm <std::shared_ptr<BaseNode>> open_func_scope
%nterm <std::shared_ptr<BaseNode>> close_func_scope
%nterm <std::shared_ptr<BaseNode>> return
%nterm <std::shared_ptr<BaseNode>> stmts
%nterm <std::shared_ptr<BaseNode>> stmt
%nterm <std::shared_ptr<BaseNode>> scope
%nterm <std::shared_ptr<BaseNode>> open_sc
%nterm <std::shared_ptr<BaseNode>> close_sc
%nterm <std::shared_ptr<BaseNode>> decl
%nterm <std::shared_ptr<BaseNode>> decl_var
%nterm <std::shared_ptr<BaseNode>> call
%nterm <std::shared_ptr<BaseNode>> assign
%nterm <std::shared_ptr<BaseNode>> name
%nterm <std::shared_ptr<BaseNode>> exprs
%nterm <std::shared_ptr<BaseNode>> expr
%nterm <std::shared_ptr<BaseNode>> if_stmt
%nterm <std::shared_ptr<BaseNode>> while_stmt
%nterm <std::shared_ptr<BaseNode>> cond
%nterm <std::shared_ptr<BaseNode>> input
%nterm <std::shared_ptr<BaseNode>> output

%start program // start symbol

%%

program: global_scope                               { driver->start(); } // driver starts visiting AST after parser makes it
;

global_scope:   global_decl                         { $$ = $1; }
              | global_scope global_decl            { $$ = $2; }
;

global_decl:   decl_func                            { $$ = $1; }
             | decl_var                             { $$ = $1; }
;

decl_func :   func_sign func_scope                  {
                                                        // both definition and declaration
                                                        std::weak_ptr<DeclFuncNode> decl = $1;
                                                        auto func_node = std::make_shared<FuncNode>(decl, $2);
                                                        $1->setFuncNode(func_node);
                                                        $1->defineFunc();
                                                        $$ = $1;
                                                    }
           | func_sign SEMICOLON                    {
                                                        // just declaration without definition
                                                        $$ = $1;
                                                    }
;

func_sign: FUNC ID LPAR args RPAR                   {
                                                        auto node = driver->find($2);
                                                        if(node != nullptr && node->expr_type == FUNC)
                                                        {
                                                            auto func_node = static_pointer_cast<DeclFuncNode>(node);
                                                            if(func_node->isDefined) // ODR violation
                                                                throw std::runtime_error("Error: redeclaration of function\n");
                                                        } // TODO: handle case var name = func name

                                                        auto new_node = std::make_shared<DeclFuncNode>($2, driver->getFuncArgs());
                                                        driver->insertName($2, new_node);
                                                        args.clear();
                                                        $$ = new_node;
                                                    }
;

args:  args                                         { driver->insertFuncArg($1); }
     | args COMMA arg                               { driver->insertFuncArg($3); }
     | /* eps */                                    {} // void
;

arg: ID                                             { $$ = $1; }
;

func_scope: open_func_scope stmts close_func_scope  { $$ = $3; }
;

open_func_scope: LBRACE                             { driver->setScope(std::make_shared<ScopeNode>(driver->getGlobalScope())); }
;

close_func_scope: return RBRACE                     { 
                                                        driver->addStmt($1);
                                                        $$ = driver->getScope();
                                                        driver->setScope(driver->getGlobalScope()); 
                                                    }
;

return : RETURN expr SEMICOLON                      { $$ = std::make_shared<RetNode>($2); }
;

stmts:    stmt                                      { driver->addStmt($1); }
        | stmts stmt                                { driver->addStmt($2); }
;


stmt:   scope                                       { $$ = $1; }
      | decl                                        { $$ = $1; }
      | call                                        { $$ = $1; }
      | assign                                      { $$ = $1; }
      | if_stmt                                     { $$ = $1; }
      | while_stmt                                  { $$ = $1; }
      | input                                       { $$ = $1; }
      | output                                      { $$ = $1; }
      //| break                                       { $$ = $1; }
      //| continue                                    { $$ = $1; }
;

scope: open_scope stmts close_scope                 { $$ = $3; }
;

open_scope: LBRACE                                  { driver->setScope(std::make_shared<ScopeNode>(driver->getScope())); }
;

close_scope: RBRACE                                 {
                                                        $$ = driver->getScope();
                                                        driver->setPrevScope();
                                                    }
;

decl:   decl_var                                    { $$ = $1; }
; // TODO: decl arr

decl_var:   VAR ID SEMICOLON                        {
                                                        auto node = driver->findInCurrentScope($2);
                                                        if(node != nullptr) // ODR violation
                                                        {
                                                            // TODO: correct text if func name = var name
                                                            throw std::runtime_error("Error: redeclaration of variable\n");
                                                        }

                                                        auto var_node = std::make_shared<VarNode>($2);
                                                        auto decl_node = std::make_shared<DeclVarNode>($2, var_node);
                                                        driver->insertName($2, decl_node);
                                                        $$ = decl_node;
                                                    }
          | VAR ID ASSIGN NUMBER SEMICOLON          {
                                                        auto node = driver->findInCurrentScope($2);
                                                        if(node != nullptr) // ODR violation
                                                        {
                                                            // TODO: correct text if func name = var name
                                                            throw std::runtime_error("Error: redeclaration of variable\n");
                                                        }

                                                        auto var_node = std::make_shared<VarNode>($2, $4);
                                                        auto decl_node = std::make_shared<DeclVarNode>($2, var_node);
                                                        driver->insertName($2, decl_node);
                                                        $$ = decl_node;
                                                    }
;

call: ID LPAR args RPAR SEMICOLON                   {
                                                        auto node = driver->findInCurrentScope($2);
                                                        if(node == nullptr || node->getExprType() != FUNC)
                                                            throw std::runtime_error("Error: calling unknown function\n");

                                                        auto func_decl = static_pointer_cast<DeclFuncNode>(node);
                                                        auto&& func_args = driver->getFuncArgs();

                                                        $$ = std::make_shared<CallNode>($1, func_decl->getFuncNode(), 
                                                                                        driver->getCurScope(), func_args);
                                                        func_args.clear();
                                                    }
;

assign: name ASSIGN exprs SEMICOLON                 { $$ = std::make_shared<BinOpNode>($1, binOpType::ASSIGN, $3); }
;

name: ID                                            {
                                                        auto node = driver->find($1);
                                                        if(node == nullptr)
                                                            throw std::runtime_error("Error: variable was not declared\n");
                                                        $$ = node->getVarNode();
                                                    }
;

exprs:   expr                                       { $$ = $1; }
       | expr exprs                                 { $$ = $2; }
;

expr:    expr ADD expr                              { $$ = std::make_shared<BinOpNode>($1, binOpType::ADD, $3); }
       | expr SUB expr                              { $$ = std::make_shared<BinOpNode>($1, binOpType::SUB, $3); }
       | expr MUL expr                              { $$ = std::make_shared<BinOpNode>($1, binOpType::MUL, $3); }
       | expr DIV expr                              { $$ = std::make_shared<BinOpNode>($1, binOpType::DIV, $3); }
       | expr MOD expr                              { $$ = std::make_shared<BinOpNode>($1, binOpType::MOD, $3); }
       | ID                                         {
                                                         auto node = driver->find($1);
                                                         if(node == nullptr)
                                                             throw std::runtime_error("Error: unknown variable\n");
                                                         $$ = node->getVarNode();
                                                    }
       | NUMBER                                     { $$ = std::make_shared<ConstNode>($1); }
       | LPAR expr RPAR                             { $$ = $2; }
       | call                                       { $$ = $1; }
;

if_stmt:   IF LPAR cond RPAR scope                  { $$ = std::make_shared<IfNode>($3, $5); }
         | IF LPAR cond RPAR scope ELSE scope       { $$ = std::make_shared<IfNode>($3, $5, $7); }
;

while_stmt: WHILE LPAR cond RPAR scope              { $$ = std::make_shared<WhileNode>($3, $5); }
;

cond:     cond AND cond                             { $$ = std::make_shared<BinOpNode>($1, binOpType::AND, $3); }
        | cond OR cond                              { $$ = std::make_shared<BinOpNode>($1, binOpType::OR, $3); }
        | NOT cond                                  { $$ = std::make_shared<UnOpNode>($2, unOpType::NOT); }
        | LPAR cond RPAR                            { $$ = $2; } // make a shift-reduce conflict but not critical
        | expr                                      { $$ = $1; }
        | expr EQUAL expr                           { $$ = std::make_shared<BinOpNode>($1, binOpType::EQUAL, $3); }
        | expr NOT_EQUAL expr                       { $$ = std::make_shared<BinOpNode>($1, binOpType::NOT_EQUAL, $3); }
        | expr LESS expr                            { $$ = std::make_shared<BinOpNode>($1, binOpType::LESS, $3); }
        | expr GREATER expr                         { $$ = std::make_shared<BinOpNode>($1, binOpType::GREATER, $3); }
        | expr LESS_EQ expr                         { $$ = std::make_shared<BinOpNode>($1, binOpType::LESS_EQ, $3); }
        | expr GREATER_EQ expr                      { $$ = std::make_shared<BinOpNode>($1, binOpType::GREATER_EQ, $3); }
;

input: SCAN LPAR name RPAR SEMICOLON                { $$ = std::make_shared<UnOpNode>($3, unOpType::SCAN); }
;

output: PRINT LPAR exprs RPAR SEMICOLON             { $$ = std::make_shared<UnOpNode>($3, unOpType::PRINT); }
;


%%

// Main parsing function: just delegate driver's parser
yy::parser::token_type yylex (yy::parser::semantic_type* yylval, yy::parser::location_type* l, Driver* driver)
{
        return driver->yylex(l, yylval);
}

void yy::parser::error(const yy::parser::location_type& loc, const std::string& message)
{
        std::cerr << message << " in line " << loc.begin.line << std::endl;
}

