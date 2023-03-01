#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <exception>
#include <memory>

enum class nodeType
{
	SCOPE = 1, IF = 2, WHILE = 3, BINOP = 4, UNOP = 5, NUM = 6, ID = 7
};

class BaseNode 
{
	private:
		nodeType type;

	public:
		BaseNode(nodeType type_) : type(type_) {}
		virtual ~BaseNode() = default;

		nodeType getType() const      { return type; }
		virtual double visit() const = 0;
};

class IdentNode final : public BaseNode
{ 
	public:
		std::string name;
		double value;

	public:
		IdentNode(const std::string& name_, double value_ = 0.0) : 
			BaseNode(nodeType::ID), name(name_), value(value_) {}
		~IdentNode() = default;

		double getValue() const       { return value; }
		void setValue(double value_)  { value = value_; }
		double visit() const override { std::cout << name << std::endl; return value; }
};

class ScopeNode final: public BaseNode
{
	private:
		std::vector<std::shared_ptr<BaseNode>> stmts;
		std::shared_ptr<ScopeNode> prev = nullptr;
		std::unordered_map<std::string, std::shared_ptr<IdentNode>> table;

	public:
		ScopeNode(std::shared_ptr<ScopeNode> prev_ = nullptr) : 
			BaseNode(nodeType::SCOPE), prev(prev_) {}
		~ScopeNode() = default;

		void insert(const std::string& name, std::shared_ptr<IdentNode> node) { table[name] = node; }
		std::shared_ptr<IdentNode> find(const std::string& name) const;
		void addStmt(std::shared_ptr<BaseNode>& stmt)                         { stmts.push_back(stmt); }
		std::shared_ptr<ScopeNode> getPrev() const                            { return prev; }
		double visit() const override;
};

class IfNode final : public BaseNode
{
	private:
		std::shared_ptr<BaseNode> cond = nullptr;
		std::shared_ptr<BaseNode> scope = nullptr;

	public:
		IfNode(std::shared_ptr<BaseNode>& cond_, std::shared_ptr<BaseNode>& scope_) : 
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
		WhileNode(std::shared_ptr<BaseNode>& cond_, std::shared_ptr<BaseNode>& scope_) : 
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
		BinOpNode(std::shared_ptr<BaseNode>& left_, binOpType op_, std::shared_ptr<BaseNode>& right_) : 
			BaseNode(nodeType::BINOP), left(left_), op(op_), right(right_) {}
		~BinOpNode() = default;

		std::shared_ptr<BaseNode> getLeft() const  { return left; }
		binOpType getOp() const { return op; }
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
		UnOpNode(std::shared_ptr<BaseNode>& expr_, unOpType op_) : 
			BaseNode(nodeType::UNOP), expr(expr_), op(op_) {}
		~UnOpNode() = default;

		std::shared_ptr<BaseNode> getExpr() const { return expr; }
		unOpType getOp() const                    { return op; }
		double visit() const override;
};

class NumNode final : public BaseNode
{ 
	private:
		double num;

	public:
		NumNode(int num_) : 
			BaseNode(nodeType::NUM), num(num_) {}
		~NumNode() = default;

		double getNum() const         { return num; }
		double visit() const override { std::cout << num << std::endl; return num; }
};
