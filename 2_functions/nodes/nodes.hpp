#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <exception>
#include <memory>
#include <optional>

//#define PRINT_GRAPH

#ifdef PRINT_GRAPH
#define printGraph(...) \
do \
{ \
    printf(__VA_ARGS__); \
} while (0)
#else
#define printGraph(...)
#endif // PRINT_GRAPH

enum class nodeType
{
	SCOPE, IF, WHILE,
	BINOP, UNOP, CONST, ID,
	BREAK, CONTINUE,
    DECL, CALL, RET,
    FUNC
};

class BaseNode
{
	private:
		nodeType node_type;

	public:
		BaseNode(nodeType type_) : node_type(type_) {}
		virtual ~BaseNode() = default;

		nodeType getNodeType() const { return node_type; }
		virtual double visit() const = 0;
};

// forward declarations
class DeclNode;
class DeclFuncNode;

enum class varType
{
    INT, DOUBLE, CHAR, STRING, BOOL, VOID
};

/// TODO: make semantic
/// decl can be taken from the driver
class VarNode final : public BaseNode
{
    private:
		std::string name;
		double value;
		//std::weak_ptr<DeclNode> decl;

	public:
		VarNode(const std::string& name_, const double value_ = 0.0) : //, std::weak_ptr<DeclNode>& decl_) :
			BaseNode(nodeType::ID), name(name_), value(value_) {}
		~VarNode() = default;

		double getValue() const       { return value; }
		void setValue(double value_)  { value = value_; }
		double visit() const override { printGraph("Var %s", name); return value; }
};

/// TODO: fix some bugs with tables
class ScopeNode final: public BaseNode
{
	private:
		std::vector<std::shared_ptr<BaseNode>> stmts;
		std::shared_ptr<ScopeNode> prev = nullptr;
		std::unordered_map<std::string, std::shared_ptr<DeclNode>> table;

	public:
		ScopeNode(const std::shared_ptr<ScopeNode> prev_ = nullptr) :
			BaseNode(nodeType::SCOPE), prev(prev_) {}
		~ScopeNode() = default;

		void insert(const std::string& name, const std::shared_ptr<DeclNode>& node)  { table[name] = node; }
		std::shared_ptr<DeclNode> find(const std::string& name) const;
		std::shared_ptr<DeclNode> findInThisScope(const std::string& name) const;
		void addStmt(std::shared_ptr<BaseNode>& stmt)                          { stmts.push_back(stmt); }
		auto getPrev() const					                               { return prev; }
		auto getTable() const 												   { return table; }
		double visit() const override;
};

/// TODO: make else with std::optional
class IfNode final : public BaseNode
{
	private:
		std::shared_ptr<BaseNode> cond = nullptr;
		std::shared_ptr<BaseNode> scope = nullptr;
		std::shared_ptr<BaseNode> else_scope = nullptr;

	public:
		IfNode(const std::shared_ptr<BaseNode>& cond_,
               const std::shared_ptr<BaseNode>& scope_,
               const std::shared_ptr<BaseNode>& else_scope_) :
            BaseNode(nodeType::IF), cond(cond_), scope(scope_), else_scope(else_scope_) {}

		IfNode(std::shared_ptr<BaseNode>& cond_,
               std::shared_ptr<BaseNode>& scope_) :
            BaseNode(nodeType::IF), cond(cond_), scope(scope_) {}
		~IfNode() = default;
		double visit() const override;
};

class WhileNode final : public BaseNode
{
	private:
		std::shared_ptr<BaseNode> cond = nullptr;
		std::shared_ptr<BaseNode> scope = nullptr;

	public:
		WhileNode(const std::shared_ptr<BaseNode>& cond_, const std::shared_ptr<BaseNode>& scope_) :
			BaseNode(nodeType::WHILE), cond(cond_), scope(scope_) {}
		~WhileNode() = default;
		double visit() const override;
};

enum class binOpType
{
	ADD, SUB, MUL, DIV, MOD, ASSIGN,
  	NOT_EQUAL, EQUAL, LESS, GREATER,
  	LESS_EQ, GREATER_EQ, AND, OR
};

class BinOpNode final : public BaseNode
{
	private:
		std::shared_ptr<BaseNode> left = nullptr;
		binOpType op;
		std::shared_ptr<BaseNode> right = nullptr;

	public:
		BinOpNode(const std::shared_ptr<BaseNode>& left_, const binOpType op_, const std::shared_ptr<BaseNode>& right_) :
			BaseNode(nodeType::BINOP), left(left_), op(op_), right(right_) {}
		~BinOpNode() = default;

		std::shared_ptr<BaseNode> getLeft() const  { return left; }
		binOpType getOperType() const 			   { return op; }
		std::shared_ptr<BaseNode> getRight() const { return right; }
		double visit() const override;
};

enum class unOpType
{
	NOT, PRINT, SCAN
};

class UnOpNode final : public BaseNode
{
	private:
		std::shared_ptr<BaseNode> expr = nullptr;
		unOpType op;

	public:
		UnOpNode(const std::shared_ptr<BaseNode>& expr_, const unOpType op_) :
			BaseNode(nodeType::UNOP), expr(expr_), op(op_) {}
		~UnOpNode() = default;

		std::shared_ptr<BaseNode> getExpr() const { return expr; }
		unOpType getOperType() const              { return op; }
		double visit() const override;
};

/// TODO: make a template and rename to ConstNode
class ConstNode final : public BaseNode
{
	private:
		double num;

	public:
		ConstNode(const int num_) :
			BaseNode(nodeType::CONST), num(num_) {}
		~ConstNode() = default;

		double getNum() const         { return num; }
		double visit() const override { printGraph("const %lg\n", num); return num; }
};

enum class exprType
{
    VAR, ARR, FUNC
};

class DeclNode : public BaseNode
{
    private:
        exprType expr_type;

    public:
        DeclNode(const exprType type) : BaseNode(nodeType::DECL), expr_type(type) {}
        virtual ~DeclNode() = default;

        virtual std::string getName() const = 0;
        exprType getExprType() const { return expr_type; }
        double visit() const override = 0;
};

class DeclVarNode final : public DeclNode
{
    private:
        std::string name;
        std::shared_ptr<VarNode> node;
        varType var_type;

	public:
		DeclVarNode(const std::string& name_,
                    const std::shared_ptr<VarNode> node_,
                    const varType var_type_ = varType::VOID) :
		    DeclNode(exprType::VAR), name(name_), node(node_), var_type(var_type_) {}
		~DeclVarNode() = default;

        std::string getName() const override { return name; }
        auto getVarNode() const      		 { return node; }
        auto getValue() const 				 { return node->getValue(); }
        void setValue(double value)			 { node->setValue(value); }
        varType getVarType() const    		 { return var_type; }
		double visit() const override 		 { printGraph("decl var %s\n", name); return 0; }
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
		double visit() const override;
};

class ArrAccess final : public BaseNode
{
    private:
		// ...

	public:
		ArrAccess( ... ) : BaseNode(exprType::ACCESS) {}
		~ArrAccess() = default;

		double visit() const override;
};
#endif // ARRAY_SUPPORTED


class FuncNode final : public BaseNode
{
    private:
		std::weak_ptr<DeclFuncNode> decl;
		std::shared_ptr<ScopeNode> scope = nullptr;

	public:
		FuncNode(const std::weak_ptr<DeclFuncNode>& decl_, 
				 const std::shared_ptr<ScopeNode>& scope_) :
			BaseNode(nodeType::FUNC), decl(decl_), scope(scope_) {}
		~FuncNode() = default;

		std::string getFuncName() const;
		auto getFuncArgs() const;
		auto getScope() const 						{ return scope; }
		double visit() const override				{ printGraph("func %s\n", getFuncName()); return 0; }
};

/// TODO: bool ret <- types
class DeclFuncNode final : public DeclNode
{
    private:
		std::string funcname;
		std::vector<std::string> args;
		std::shared_ptr<FuncNode> func = nullptr;
		bool defined = false;

	public:
		DeclFuncNode(const std::string& funcname_, 
					 const std::vector<std::string>& args_ = {}) :
            DeclNode(exprType::FUNC), funcname(funcname_), args(args_) {}
		~DeclFuncNode() = default;

        std::string getName() const override               { return funcname; }
        auto getFuncArgs() const       					   { return args; }
        auto getFuncNode() const                           { return func; }
        auto getScope() const 							   { return func->getScope(); }
        bool isDefined() const                             { return defined; }

        void defineFunc()                                  { defined = true; }
        void setFuncNode(std::shared_ptr<FuncNode>& func_) { func = func_; }
		double visit() const override					   { printGraph("decl func %s\n", funcname); return 0; }
};

/// TODO: make string_view
/// TODO: think may be change FuncNode to DeclFuncNode
class CallNode final : public BaseNode
{
    private:
		std::string name;
		std::shared_ptr<FuncNode> func;
		std::shared_ptr<ScopeNode> curScope;
		std::vector<double> args;

	public:
		CallNode(const std::string& name_, 
				 const std::shared_ptr<FuncNode>& func_, 
				 const std::shared_ptr<ScopeNode>& curScope_, 
				 const std::vector<double>& args_) :
			BaseNode(nodeType::CALL), name(name_), func(func_), curScope(curScope_), args(args_) {}

		CallNode(const std::string& name_, 
				 const std::shared_ptr<FuncNode>& func_, 
				 const std::shared_ptr<ScopeNode>& curScope_) :
			BaseNode(nodeType::CALL), name(name_), func(func_), curScope(curScope_) {}
		~CallNode() = default;

        std::shared_ptr<FuncNode> getFunc() const { return func; }
        std::string getFuncName() const           { return name; }
		double visit() const override;
};

class RetNode final : public BaseNode
{
    private:
		std::shared_ptr<BaseNode> expr = nullptr;

	public:
		RetNode(const std::shared_ptr<BaseNode>& expr_) :
			BaseNode(nodeType::RET), expr(expr_) {}
		~RetNode() = default;

		double visit() const override;
};


#ifdef CYCLE_MODIFIERS_SUPPORTED
// to the light future...
class BreakNode final : public BaseNode
{
    public:
		BreakNode() : BaseNode(nodeType::BREAK) {}
		~BreakNode() = default;

		double visit() const override;
};

class ContinueNode final : public BaseNode
{
    public:
		ContinueNode() : BaseNode(nodeType::CONTINUE) {}
		~ContinueNode() = default;

		double visit() const override;
};
#endif //CYCLE_MODIFIERS_SUPPORTED
