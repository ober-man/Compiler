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
%nterm <std::shared_ptr<BaseNode>> params
%nterm <std::string>               param
%nterm <std::shared_ptr<BaseNode>> args
%nterm <std::shared_ptr<BaseNode>> arg
%nterm <std::shared_ptr<BaseNode>> func_scope
%nterm <std::shared_ptr<BaseNode>> open_func
%nterm <std::shared_ptr<BaseNode>> func_stmts
%nterm <std::shared_ptr<BaseNode>> close_func
%nterm <std::shared_ptr<BaseNode>> return
%nterm <std::shared_ptr<BaseNode>> stmts
%nterm <std::shared_ptr<BaseNode>> stmt
%nterm <std::shared_ptr<BaseNode>> scope
%nterm <std::shared_ptr<BaseNode>> open_scope
%nterm <std::shared_ptr<BaseNode>> close_scope
%nterm <std::shared_ptr<BaseNode>> decl
%nterm <std::shared_ptr<BaseNode>> decl_var
%nterm <std::shared_ptr<BaseNode>> call
%nterm <std::shared_ptr<BaseNode>> assign
%nterm <std::shared_ptr<BaseNode>> name
//%nterm <std::shared_ptr<BaseNode>> exprs
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
                                                        auto decl_node = std::static_pointer_cast<DeclFuncNode>($1);
                                                        std::weak_ptr<DeclFuncNode> decl = decl_node;

                                                        auto scope = std::static_pointer_cast<ScopeNode>($2);
                                                        auto func_node = std::make_shared<FuncNode>(decl, scope);

                                                        decl_node->setFuncNode(func_node);
                                                        decl_node->defineFunc();
                                                        $$ = decl_node;
                                                    }
           | func_sign SEMICOLON                    {
                                                        // just declaration without definition
                                                        $$ = $1;
                                                    }
;

func_sign: FUNC ID LPAR params RPAR                 {
                                                        auto node = driver->find($2);
                                                        if(node != nullptr && node->getExprType() == exprType::FUNC)
                                                        {
                                                            auto func_node = std::static_pointer_cast<DeclFuncNode>(node);
                                                            if(func_node->isDefined()) // ODR violation
                                                                throw std::runtime_error("Error: redeclaration of function\n");
                                                        } // TODO: handle case var name = func name

                                                        auto new_node = std::make_shared<DeclFuncNode>($2, driver->getFuncArgs());
                                                        driver->insertName($2, new_node);
                                                        $$ = new_node;
                                                    }
;

params:  param                                      { driver->insertFuncArg($1); }
       | params COMMA param                         { driver->insertFuncArg($3); }
       | /* eps */                                  {} // void
;

param: ID                                           { $$ = $1; }
;

func_scope: open_func func_stmts close_func         { $$ = $3; }
;

open_func: LBRACE                                   { 
                                                        auto scope = std::make_shared<ScopeNode>(driver->getGlobalScope());
                                                        driver->setScope(scope);

                                                        auto&& args = driver->getFuncArgs();
                                                        for(auto&& arg : args)
                                                        {
                                                            auto var_node = std::make_shared<VarNode>(arg);
                                                            auto param = std::make_shared<DeclVarNode>(arg, var_node);
                                                            scope->insert(arg, param);
                                                        }
                                                        driver->clearArgs();
                                                    }
;

func_stmts:   stmts                                 { $$ = $1; }   
            | /* eps */                             {}

close_func: RBRACE                                  { 
                                                        $$ = driver->getScope();
                                                        driver->setScope(driver->getGlobalScope()); 
                                                    }
;

return : RETURN expr SEMICOLON                      { $$ = std::make_shared<RetNode>($2); }
;

stmts:   stmt                                       { driver->addStmt($1); }
       | stmts stmt                                 { driver->addStmt($2); }
;


stmt:   scope                                       { $$ = $1; }
      | decl                                        { $$ = $1; }
      | call SEMICOLON                              { $$ = $1; }
      | assign                                      { $$ = $1; }
      | if_stmt                                     { $$ = $1; }
      | while_stmt                                  { $$ = $1; }
      | input                                       { $$ = $1; }
      | output                                      { $$ = $1; }
      | return                                      { $$ = $1; }
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
          | VAR ID ASSIGN expr SEMICOLON            {
                                                        auto node = driver->findInCurrentScope($2);
                                                        if(node != nullptr) // ODR violation
                                                        {
                                                            // TODO: correct text if func name = var name
                                                            throw std::runtime_error("Error: redeclaration of variable\n");
                                                        }

                                                        auto var_node = std::make_shared<VarNode>($2);
                                                        auto decl_node = std::make_shared<DeclVarNode>($2, var_node);
                                                        driver->insertName($2, decl_node);

                                                        $$ = std::make_shared<BinOpNode>(var_node, binOpType::ASSIGN, $4);
                                                    }
;

call: ID LPAR args RPAR                             {
                                                        auto node = driver->findInGlobalScope($1);
                                                        if(node == nullptr || node->getExprType() != exprType::FUNC)
                                                            throw std::runtime_error("Error: calling unknown function\n");

                                                        auto func_decl = static_pointer_cast<DeclFuncNode>(node);
                                                        auto&& func_args = driver->getFuncArgs();

                                                        $$ = std::make_shared<CallNode>($1, func_decl->getFuncNode(), 
                                                                                        driver->getScope(), func_args);
                                                        driver->clearArgs();    
                                                    }
     | ID LPAR RPAR                                 {
                                                        auto node = driver->findInGlobalScope($1);
                                                        if(node == nullptr || node->getExprType() != exprType::FUNC)
                                                            throw std::runtime_error("Error: calling unknown function\n");

                                                        auto func_decl = static_pointer_cast<DeclFuncNode>(node);
                                                        $$ = std::make_shared<CallNode>($1, func_decl->getFuncNode(), 
                                                                                        driver->getScope());
                                                    }
;

args:  arg                                          { driver->insertFuncArg($1); }
     | arg COMMA args                               { driver->insertFuncArg($1); }
;

arg:  expr                                          { $$ = $1; }
;

assign: name ASSIGN expr SEMICOLON                 { $$ = std::make_shared<BinOpNode>($1, binOpType::ASSIGN, $3); }
;

name: ID                                            {
                                                        auto node = driver->find($1);
                                                        if(node == nullptr)
                                                            throw std::runtime_error("Error: variable was not declared\n");
                                                        else if(node->getExprType() != exprType::VAR)
                                                            throw std::runtime_error("Error: name is not a variable\n");
                                                        $$ = std::static_pointer_cast<DeclVarNode>(node)->getVarNode();
                                                    }
;

/*exprs:   expr                                       { $$ = $1; }
       | expr exprs                                 { $$ = $2; }
;*/

expr:    expr ADD expr                              { $$ = std::make_shared<BinOpNode>($1, binOpType::ADD, $3); }
       | expr SUB expr                              { $$ = std::make_shared<BinOpNode>($1, binOpType::SUB, $3); }
       | expr MUL expr                              { $$ = std::make_shared<BinOpNode>($1, binOpType::MUL, $3); }
       | expr DIV expr                              { $$ = std::make_shared<BinOpNode>($1, binOpType::DIV, $3); }
       | expr MOD expr                              { $$ = std::make_shared<BinOpNode>($1, binOpType::MOD, $3); }
       | ID                                         {
                                                        auto decl_node = driver->find($1);
                                                        if(decl_node == nullptr)
                                                        {
                                                            std::cout << $1 << std::endl;
                                                            throw std::runtime_error("Error: unknown variable\n");
                                                        }
                                                        auto var_node = std::static_pointer_cast<DeclVarNode>(decl_node);
                                                        $$ = var_node->getVarNode();
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

output: PRINT LPAR expr RPAR SEMICOLON             { $$ = std::make_shared<UnOpNode>($3, unOpType::PRINT); }
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

