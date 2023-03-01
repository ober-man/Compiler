#pragma once

#ifndef yyFlexLexer
#include <FlexLexer.h>
#endif

#include "grammar.tab.hh" // contains definition of class yy::parser

class Lexer final: public yyFlexLexer
{
    private:
        yy::parser::location_type curLoc;
        std::size_t curLine;

    public:
        Lexer() : curLoc(0), curLine(1) {}

        yy::parser::location_type getCurrentLocation() const { return curLoc; }
        std::size_t getCurrentLine() const { return curLine; }
        void updateLocation()
        {
            std::size_t line = lineno();
            curLoc.lines(line - curLine);
            curLoc.step();
            if (line - curLine == 0)
                curLoc.columns(YYLeng());
            curLine = line;
        }
        int yylex() override; // defined in lex.yy.cc by flex
        virtual ~Lexer() = default;
};
