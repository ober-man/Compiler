%option c++
%option noyywrap nounput noinput batch
%option yyclass="Lexer"

%{
    #include "lexer.hpp" // contains definition of class Lexer and can reach class yy::parser
%}

WS                  [ \t\n]+
LETTER              [A-Za-z_]
DIGIT               [0-9]
SYMBOL              [a-zA-Z0-9_]
ID                  {LETTER}{SYMBOL}*
NUMBER              [+-]?{DIGIT}*(\.{DIGIT}+)?([eE][+-]?{DIGIT}+)?

%%

{WS}        /* skip space symbols */
"//".*      /* skip comments */
";"         return yy::parser::token_type::SEMICOLON;
","         return yy::parser::token_type::COMMA;

"+"         return yy::parser::token_type::ADD;
"-"         return yy::parser::token_type::SUB;
"*"         return yy::parser::token_type::MUL;
"/"         return yy::parser::token_type::DIV;
"%"         return yy::parser::token_type::MOD;
"="         return yy::parser::token_type::ASSIGN;

"!="        return yy::parser::token_type::NOT_EQUAL;
"=="        return yy::parser::token_type::EQUAL;
"<"         return yy::parser::token_type::LESS;
">"         return yy::parser::token_type::GREATER;
"<="        return yy::parser::token_type::LESS_EQ;
">="        return yy::parser::token_type::GREATER_EQ;

"&&"        return yy::parser::token_type::AND;
"||"        return yy::parser::token_type::OR;
"!"         return yy::parser::token_type::NOT;

"("         return yy::parser::token_type::LPAR;
")"         return yy::parser::token_type::RPAR;
"{"         return yy::parser::token_type::LBRACE;
"}"         return yy::parser::token_type::RBRACE;
"["         return yy::parser::token_type::LBRACKET;
"]"         return yy::parser::token_type::RBRACKET;

"?"         return yy::parser::token_type::QUEST_MARK;
":"         return yy::parser::token_type::COLON;

"if"        return yy::parser::token_type::IF;
"else"      return yy::parser::token_type::ELSE;
"while"     return yy::parser::token_type::WHILE;
"print"     return yy::parser::token_type::PRINT;
"scan"      return yy::parser::token_type::SCAN;

"break"     return yy::parser::token_type::BREAK;
"continue"  return yy::parser::token_type::CONTINUE;

"func"      return yy::parser::token_type::FUNC;
"return"    return yy::parser::token_type::RETURN;

"var"       return yy::parser::token_type::VAR;
"array"     return yy::parser::token_type::ARRAY;

{ID}        return yy::parser::token_type::ID;
{NUMBER}    return yy::parser::token_type::NUMBER;

%%
