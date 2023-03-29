#pragma once

#include "../compiler/lexer.hpp"
#include <fstream>
#include <memory>

class Driver final
{
	private:
		std::ifstream input_file;
		std::vector<std::string> stmts; 
		std::shared_ptr<ScopeNode> curScope = nullptr;
		std::unique_ptr<Lexer> lex = nullptr;

	public:
		Driver(const char* file_name);
		~Driver();

		void addStmt(std::shared_ptr<BaseNode>& node);
		void setScope(std::shared_ptr<ScopeNode> scope)                        { curScope = scope; }
		void setPrevScope()                                                    { curScope = curScope->getPrev(); }
		std::shared_ptr<ScopeNode> getScope() const                            { return curScope; }
		void insert(const std::string& name, std::shared_ptr<IdentNode>& node) { curScope->insert(name, node); }
		std::shared_ptr<IdentNode> find(const std::string& name) const         { return curScope->find(name); }
		void start() const;
		bool parse();
		yy::parser::token_type yylex(yy::parser::location_type* loc, yy::parser::semantic_type* yylval);
};




