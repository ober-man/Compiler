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
		std::shared_ptr<ScopeNode> globalScope = nullptr;
		std::shared_ptr<FuncNode> curFunc = nullptr;
		std::unique_ptr<Lexer> lex = nullptr;
		std::vector<std::string> funcArgs;

	public:
		Driver(const char* file_name);
		~Driver() = default;

		void addStmt(std::shared_ptr<BaseNode>& node);
		void setScope(std::shared_ptr<ScopeNode> scope)                             { curScope = scope; }
		void setPrevScope()                                                         { curScope = curScope->getPrev(); }
		auto getScope() const                                                       { return curScope; }
		auto getGlobalScope() const                                                 { return globalScope; }
		auto getFuncArgs() const 													{ return funcArgs; }
		void insertName(const std::string& name, std::shared_ptr<DeclNode>& node)   { curScope->insert(name, node); }
		void insertFuncArg(const std::string& name)									{ args.push_back(name); }
		std::shared_ptr<DeclNode> findId(const std::string& name) const             { return curScope->find(name); }
		std::shared_ptr<DeclNode> findInCurrentScope(const std::string& name) const { return curScope->findInThisScope(name); }
		void start() const;
		bool parse();
		yy::parser::token_type yylex(yy::parser::location_type* loc, yy::parser::semantic_type* yylval);
};




