#include "driver.hpp"
#include <algorithm>

Driver::Driver(const char* file_name)
{
	input_file.open(file_name);
    curScope = std::make_shared<ScopeNode>();
    globalScope = curScope;
    lex = std::make_unique<Lexer>();
    curFunc = "global";

    // Set new input stream
    lex->switch_streams(input_file, std::cout);

    // Push all program lines to the vector
    std::string str;
    while(std::getline(input_file, str))
    {
        str.erase(remove(str.begin(), str.end(), '\t'), str.end());
        stmts.push_back(str);
    }

    // do not delete this is crutial!!!
    input_file.clear();
    input_file.seekg(0);
}

void Driver::addStmt(std::shared_ptr<BaseNode>& node)
{
	if(node != nullptr)
		curScope->addStmt(node);
}

void Driver::start() const
{
    auto&& symbolTable = globalScope->getTable();
    auto&& stmts = globalScope->getStmts();

    // for visiting all global variables
    for(auto&& stmt : stmts)
        stmt->visit();

    for(auto&& [string, decl] : symbolTable)
        if(decl->getName() == "main")
        {
            auto&& main = std::static_pointer_cast<DeclFuncNode>(decl);
            auto&& scope = main->getScope();
            scope->visit();
        }
}

bool Driver::parse()
{
    // create a parser, give a driver to it
    yy::parser parser(this);

    // start parsing with using lexer from this driver
    bool res = parser.parse();
    return !res;
}

// The main function: it takes a token from lexer and return its type to grammar parser
yy::parser::token_type Driver::yylex(yy::parser::location_type* loc, yy::parser::semantic_type* yylval)
{
    // take a token from lexer
	yy::parser::token_type type = static_cast<yy::parser::token_type>(lex->yylex());

    // if its type is a NUMBER, parse it as string->double
    if(type == yy::parser::token_type::NUMBER)
        yylval->as<double>() = std::stof(lex->YYText());

    // if its type is ID, parse it as a string
    if(type == yy::parser::token_type::ID)
    {
        std::string name(lex->YYText());
        yy::parser::semantic_type tmp;
        tmp.as<std::string>() = name;
        yylval->swap<std::string>(tmp);
    }

    *loc = lex->getCurrentLocation();
    return type;
}
