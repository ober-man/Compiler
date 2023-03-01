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

        LPARENTHESIS    "("
        RPARENTHESIS    ")"
        LBRACE          "{"
        RBRACE          "}"
        LBRACKET        "["
        RBRACKET        "]"

        QUEST_MARK      "?"
        COLON           ":"

        IF              "if"
        THEN            "then"
        ELSE            "else"
        WHILE           "while"
        PRINT           "print"
        SCAN            "scan"

        FUNC            "func"
        RETURN          "return"
        
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
%nterm <std::shared_ptr<BaseNode>> stmts
%nterm <std::shared_ptr<BaseNode>> stmt
%nterm <std::shared_ptr<BaseNode>> scope
%nterm <std::shared_ptr<BaseNode>> open_sc
%nterm <std::shared_ptr<BaseNode>> close_sc
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

program: stmts                                      { driver->start(); }
;

stmts:    stmt                                      { driver->addStmt($1); }
        | stmts stmt                                { driver->addStmt($2); }                                 
;

stmt:     scope                                     { $$ = $1; }
        | assign                                    { $$ = $1; }
        | if_stmt                                   { $$ = $1; }
        | while_stmt                                { $$ = $1; }
        | input                                     { $$ = $1; }
        | output                                    { $$ = $1; }
;

scope: open_sc stmts close_sc                       { $$ = $3; }
;

open_sc: LBRACE                                     { driver->setScope(std::make_shared<ScopeNode>(driver->getScope())); }
;

close_sc: RBRACE                                    { $$ = driver->getScope(); driver->setPrevScope(); }
;

assign: name ASSIGN exprs SEMICOLON                 { $$ = std::make_shared<BinOpNode>($1, binOpType::ASSIGN, $3); }
;
 
name: ID                                            {
                                                      auto node = driver->find($1);
                                                      if(node == nullptr)
                                                      {
                                                          node = std::make_shared<IdentNode>($1);
                                                          driver->insert($1, node);
                                                      }
                                                      $$ = node;
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
                                                         $$ = node;
                                                    }
       | NUMBER                                     { $$ = std::make_shared<NumNode>($1); }
       | LPARENTHESIS expr RPARENTHESIS             { $$ = $2; }
;


if_stmt: IF LPARENTHESIS cond RPARENTHESIS scope        { $$ = std::make_shared<IfNode>($3, $5); }
;

while_stmt: WHILE LPARENTHESIS cond RPARENTHESIS scope  { $$ = std::make_shared<WhileNode>($3, $5); }
;

cond:     cond AND cond                             { $$ = std::make_shared<BinOpNode>($1, binOpType::AND, $3); }
        | cond OR cond                              { $$ = std::make_shared<BinOpNode>($1, binOpType::OR, $3); }
        | NOT cond                                  { $$ = std::make_shared<UnOpNode>($2, unOpType::NOT); }
        | LPARENTHESIS cond RPARENTHESIS            { $$ = $2; } // make a shift-reduce conflict
        | expr                                      { $$ = $1; }
        | expr EQUAL expr                           { $$ = std::make_shared<BinOpNode>($1, binOpType::EQUAL, $3); }
        | expr NOT_EQUAL expr                       { $$ = std::make_shared<BinOpNode>($1, binOpType::NOT_EQUAL, $3); }
        | expr LESS expr                            { $$ = std::make_shared<BinOpNode>($1, binOpType::LESS, $3); }
        | expr GREATER expr                         { $$ = std::make_shared<BinOpNode>($1, binOpType::GREATER, $3); }
        | expr LESS_EQ expr                         { $$ = std::make_shared<BinOpNode>($1, binOpType::LESS_EQ, $3); }
        | expr GREATER_EQ expr                      { $$ = std::make_shared<BinOpNode>($1, binOpType::GREATER_EQ, $3); }
;

input: SCAN LPARENTHESIS name RPARENTHESIS SEMICOLON    { $$ = std::make_shared<UnOpNode>($3, unOpType::SCAN); }
;

output: PRINT LPARENTHESIS exprs RPARENTHESIS SEMICOLON { $$ = std::make_shared<UnOpNode>($3, unOpType::PRINT); }
;

%%

// Main parsing function: just delegate driver's parser
yy::parser::token_type yylex (yy::parser::semantic_type* yylval, yy::parser::location_type* l, Driver* driver) 
{
        return driver->yylex (l, yylval);
}

void yy::parser::error(const yy::parser::location_type& loc, const std::string& message)
{
        std::cerr << message << " in line " << loc.begin.line << std::endl;
}

