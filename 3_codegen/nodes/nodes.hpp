#pragma once

#include <iostream>
#include <vector>
#include <unordered_map>
#include <exception>
#include <optional>
#include <cmath>
#include <cassert>
#include <string>
#include <memory>

#include "llvm/IR/Constants.h"
#include "INode.hpp"
#include "../codegen/codegen.hpp"

class VarNode final : public BaseNode
{
	private:
   		std::string name;
   		int value;
   		std::weak_ptr<DeclVarNode> decl;

    public:
		VarNode(const std::string& name_, 
				const int value_ = 0.0) :
			BaseNode(nodeType::ID), name(name_), value(value_) {}
		~VarNode() = default;

		int getValue() const   	  						 { return value; }
		void setValue(int value_)  						 { value = value_; }
		auto getDecl() const 	   						 { return decl.lock(); }
		void setDecl(std::shared_ptr<DeclVarNode> decl_) { decl = std::weak_ptr(decl_); }
		llvm::Value* codegen() const override;
};

class ScopeNode final: public BaseNode
{
    private:
   		std::vector<std::shared_ptr<BaseNode>> stmts;
   		std::shared_ptr<ScopeNode> prev = nullptr;
   		std::unordered_map<std::string, std::shared_ptr<DeclNode>> table;

    public:
   		ScopeNode(std::shared_ptr<ScopeNode> prev_ = nullptr) :
   			BaseNode(nodeType::SCOPE), prev(prev_) {}
   	 	~ScopeNode() = default;

		void insert(const std::string& name, const std::shared_ptr<DeclNode>& node) { table[name] = node; }
		void addStmt(std::shared_ptr<BaseNode>& stmt)                     			{ stmts.push_back(stmt); }
		std::shared_ptr<DeclNode> find(const std::string& name) const;
		std::shared_ptr<DeclNode> findInThisScope(const std::string& name) const;
		auto getPrev() const   				                           			    { return prev; }
		auto getTable() const    											   		{ return table; }
		auto getStmts() const    											   		{ return stmts; }
		llvm::Value* codegen() const override;
};

class IfNode final : public BaseNode
{
    private:
		std::shared_ptr<BaseNode> cond = nullptr;
		std::shared_ptr<BaseNode> scope = nullptr;
		std::shared_ptr<BaseNode> else_scope = nullptr;

    public:
		IfNode(std::shared_ptr<BaseNode> cond_,
			   std::shared_ptr<BaseNode> scope_,
			   std::shared_ptr<BaseNode> else_scope_) :
			BaseNode(nodeType::IF), cond(cond_), scope(scope_), else_scope(else_scope_) {}

		IfNode(std::shared_ptr<BaseNode>& cond_,
			   std::shared_ptr<BaseNode>& scope_) :
			BaseNode(nodeType::IF), cond(cond_), scope(scope_) {}
		~IfNode() = default;
		llvm::Value* codegen() const override;
};

class WhileNode final : public BaseNode
{
    private:
		std::shared_ptr<BaseNode> cond = nullptr;
		std::shared_ptr<BaseNode> scope = nullptr;

    public:
	WhileNode(std::shared_ptr<BaseNode> cond_, std::shared_ptr<BaseNode> scope_) :
		BaseNode(nodeType::WHILE), cond(cond_), scope(scope_) {}
	~WhileNode() = default;
	llvm::Value* codegen() const override;
};

class BinOpNode final : public BaseNode
{
    private:
		std::shared_ptr<BaseNode> left = nullptr;
		binOpType op;
		std::shared_ptr<BaseNode> right = nullptr;

    public:
		BinOpNode(std::shared_ptr<BaseNode> left_, binOpType op_, std::shared_ptr<BaseNode> right_) :
			BaseNode(nodeType::BINOP), left(left_), op(op_), right(right_) {}
		~BinOpNode() = default;

		std::shared_ptr<BaseNode> getLeft() const  { return left; }
		binOpType getOperType() const    		   { return op; }
		std::shared_ptr<BaseNode> getRight() const { return right; }
		llvm::Value* codegen() const override;
};

class UnOpNode final : public BaseNode
{
    private:
		std::shared_ptr<BaseNode> expr = nullptr;
		unOpType op;

    public:
		UnOpNode(std::shared_ptr<BaseNode> expr_, const unOpType op_) :
			BaseNode(nodeType::UNOP), expr(expr_), op(op_) {}
		~UnOpNode() = default;

		std::shared_ptr<BaseNode> getExpr() const { return expr; }
		unOpType getOperType() const          	{ return op; }
		llvm::Value* codegen() const override;
};

class ConstNode final : public BaseNode
{
    private:
   		int num;

    public:
   		ConstNode(const int num_) : BaseNode(nodeType::CONST), num(num_) {}
   		~ConstNode() = default;

   		int getNum() const { return num; }
   		llvm::Value* codegen() const override;
};

class DeclNode : public BaseNode
{
	private:
    	exprType expr_type;

	public:
    	DeclNode(const exprType type) : BaseNode(nodeType::DECL), expr_type(type) {}
    	virtual ~DeclNode() = default;

    	virtual std::string getName() const = 0;
    	exprType getExprType() const 		  { return expr_type; }
    	llvm::Value* codegen() const override = 0;
};

class DeclVarNode final : public DeclNode
{
	private:
    	std::string name;
    	std::shared_ptr<VarNode> varNode;
    	mutable llvm::Value* alloca = nullptr;
    	varType var_type;

    public:
		DeclVarNode(std::string& name_, 
					std::shared_ptr<VarNode> varNode_,
		    		varType var_type_ = varType::VOID) :
			DeclNode(exprType::VAR), name(name_), varNode(varNode_), var_type(var_type_) {}
		~DeclVarNode() = default;

		std::string getName() const override  { return name; }
		varType getVarType() const   		  { return var_type; }
		auto getVarNode() const 			  { return varNode; }
		llvm::Value* codegen() const override;
};


#ifdef ARRAY_SUPPORTED
class DeclArrNode final : public DeclNode
{
	private:
   	 // ...

    public:
   		DeclArrNode( ... ) : DeclNode(exprType::ARR) {}
    	~DeclArrNode() = default;

   	 	std::string getName() const override;
   	 	llvm::Value* codegen() const override;
};

class ArrAccess final : public BaseNode
{
	private:
   		// ...

    public:
   		ArrAccess( ... ) : BaseNode(exprType::ACCESS) {}
   		~ArrAccess() = default;

   		llvm::Value* codegen() const override;
};
#endif // ARRAY_SUPPORTED


class DeclFuncNode final : public DeclNode
{
	private:
		std::string funcname;
		std::vector<std::string> params;
		mutable llvm::Function* func = nullptr;
		bool defined = false;

    public:
		DeclFuncNode(const std::string& funcname_,
				  	 const std::vector<std::string>& params_ = {}) :
			DeclNode(exprType::FUNC), funcname(funcname_), params(params_) {}
		~DeclFuncNode() = default;

    	std::string getName() const override           	{ return funcname; }
    	auto getFuncParams() const  				    { return params; }
    	bool isDefined() const                         	{ return defined; }
    	void setFunc(llvm::Function* func_)   			{ func = func_; }
    	void defineFunc()                              	{ defined = true; }
   		llvm::Value* codegen() const override;
};

class FuncNode final : public BaseNode
{
	private:
		std::shared_ptr<DeclFuncNode> decl = nullptr;
		std::shared_ptr<ScopeNode> scope = nullptr;

    public:
		FuncNode(std::shared_ptr<DeclFuncNode>&decl_,
			  	 std::shared_ptr<ScopeNode> scope_) :
			BaseNode(nodeType::FUNC), decl(decl_), scope(scope_) {}
		~FuncNode() = default;

		std::string getFuncName() const    			   	  { return decl->getName(); }
		auto getScope() const    						  { return scope; }
		void setScope(std::shared_ptr<ScopeNode>& scope_) { scope = scope_; }
		llvm::Value* codegen() const override;
};

class CallNode final : public BaseNode
{
	private:
		std::string name;
		std::shared_ptr<DeclFuncNode> func;
		std::vector<std::shared_ptr<BaseNode>> args;

    public:
		CallNode(const std::string& name_,
			     std::shared_ptr<DeclFuncNode> func_,
			     const std::vector<std::shared_ptr<BaseNode>>& args_ = {}) :
		 	BaseNode(nodeType::CALL), name(name_), func(func_), args(args_) {}
		~CallNode() = default;

		std::shared_ptr<DeclFuncNode> getFunc() const    		  	  { return func; }
		std::string getFuncName() const      					  	  { return name; }
		void setFuncNode(const std::shared_ptr<DeclFuncNode>& func_)  { func = func_; }
		llvm::Value* codegen() const override;
};

class RetNode final : public BaseNode
{
	private:
   		std::shared_ptr<BaseNode> expr = nullptr;

    public:
   		RetNode(const std::shared_ptr<BaseNode> expr_) :
   			BaseNode(nodeType::RET), expr(expr_) {}
   		~RetNode() = default;

   		llvm::Value* codegen() const override;
};


#ifdef CYCLE_MODIFIERS_SUPPORTED
// to the light future...
class BreakNode final : public BaseNode
{
	public:
   		BreakNode() : BaseNode(nodeType::BREAK) {}
   		~BreakNode() = default;

   		llvm::Value* codegen() const override;
};

class ContinueNode final : public BaseNode
{
	public:
   		ContinueNode() : BaseNode(nodeType::CONTINUE) {}
   		~ContinueNode() = default;

   		llvm::Value* codegen() const override;
};
#endif //CYCLE_MODIFIERS_SUPPORTED