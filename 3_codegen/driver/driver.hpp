#pragma once

#include "../compiler/lexer.hpp"
#include <fstream>
#include <memory>

class Driver final
{
	private:
		std::ifstream input_file;
		std::unique_ptr<Lexer> lex = nullptr;

		std::vector<std::string> stmts;
		std::shared_ptr<ScopeNode> curScope = nullptr;
		std::shared_ptr<ScopeNode> globalScope = nullptr;

		std::vector<std::string> funcParams;
		std::vector<std::shared_ptr<BaseNode>> funcArgs;

	public:
		Driver(const char* file_name);
		~Driver() = default;

		void setScope(const std::shared_ptr<ScopeNode> scope)                       { curScope = scope; }
		void setPrevScope()                                                         { curScope = curScope->getPrev(); }

		auto getScope() const                                                       { return curScope; }
		auto getGlobalScope() const                                                 { return globalScope; }
		auto getFuncArgs() const 													{ return funcArgs; }
		auto getFuncParams() const													{ return funcParams; }

		void insertName(const std::string& name, 
						const std::shared_ptr<DeclNode>& node)   					{ curScope->insert(name, node); }
		void insertFuncArg(const std::shared_ptr<BaseNode>& expr)					{ funcArgs.push_back(expr); }
		void insertFuncParam(const std::string& name)								{ funcParams.push_back(name); }

		void clearArgs()															{ funcArgs.clear(); }
		void clearParams()															{ funcParams.clear(); }

		std::shared_ptr<DeclNode> find(const std::string& name) const               { return curScope->find(name); }
		std::shared_ptr<DeclNode> findInCurrentScope(const std::string& name) const { return curScope->findInThisScope(name); }
		std::shared_ptr<DeclNode> findInGlobalScope(const std::string& name) const  { return globalScope->findInThisScope(name); }

		void start() const;
		bool parse();
		void addStmt(std::shared_ptr<BaseNode>& node);
		yy::parser::token_type yylex(yy::parser::location_type* loc, yy::parser::semantic_type* yylval);
};