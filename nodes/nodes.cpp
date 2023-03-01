#include "nodes.hpp"

//////////////////////////////////////////////////////////////////_SCOPENODE_//////////////////////////////////////////////////////////////////

std::shared_ptr<IdentNode> ScopeNode::find(const std::string& name) const
{
	auto res = table.find(name);
	if(res != table.end())
		return res->second;

	if(prev != nullptr)
		return prev->find(name);

	return nullptr;
}

double ScopeNode::visit() const
{
	std::cout << "open scope" << std::endl;
	for(auto&& stmt: stmts)
		stmt->visit();
	std::cout << "close scope" << std::endl;
	return 0;
}

//////////////////////////////////////////////////////////////////_IFNODE_//////////////////////////////////////////////////////////////////

double IfNode::visit() const
{
	std::cout << "start if-stmt" << std::endl;
	if(scope->getType() != nodeType::SCOPE)
		throw std::runtime_error("Error: wrong action\n");
	if(cond->visit())
		scope->visit();
	std::cout << "end if-stmt" << std::endl;
	return 0;
}

//////////////////////////////////////////////////////////////////_WHILENODE_//////////////////////////////////////////////////////////////////

double WhileNode::visit() const
{
	std::cout << "start while-stmt" << std::endl;
	if(scope->getType() != nodeType::SCOPE)
		throw std::runtime_error("Error: wrong action\n");
	while(cond->visit())
		scope->visit();
	std::cout << "end while-stmt" << std::endl;
	return 0;
}

//////////////////////////////////////////////////////////////////_BINOPNODE_//////////////////////////////////////////////////////////////////

double BinOpNode::visit() const
{
	if(left == nullptr || right == nullptr)
		throw std::runtime_error("Error: too less arguments\n");

	switch(op)
	{
		case binOpType::ADD:
			std::cout << "ADD" << std::endl;
			return left->visit() + right->visit();

		case binOpType::SUB:
			std::cout << "SUB" << std::endl;
			return left->visit() - right->visit();

		case binOpType::MUL:
			std::cout << "MUL" << std::endl;
			return left->visit() * right->visit();

		case binOpType::DIV:
		{
			double val = right->visit();
			if(val == 0)
				throw std::runtime_error("Error: division by zero\n");
			std::cout << "DIV" << std::endl;
			return left->visit() / val;
		}

		case binOpType::MOD:
		{
			int val = static_cast<int>(right->visit());
			if(val == 0)
				throw std::runtime_error("Error: division by zero\n");
			std::cout << "MOD" << std::endl;
			return static_cast<int>(left->visit()) % val;
		}

		case binOpType::ASSIGN:
		{
			if(left->getType() != nodeType::ID)
				throw std::runtime_error("Error: assigning not to the variable\n");
			std::cout << "ASSIGN" << std::endl;
			auto var = std::static_pointer_cast<IdentNode>(left);
			double value = right->visit();
			var->setValue(value);
			return value;
		}

		case binOpType::NOT_EQUAL:
			std::cout << "NOT_EQUAL" << std::endl;
			return static_cast<double>(left->visit() != right->visit());

		case binOpType::EQUAL:
			std::cout << "EQUAL" << std::endl;
			return static_cast<double>(left->visit() == right->visit());

		case binOpType::LESS:
			std::cout << "LESS" << std::endl;
			return static_cast<double>(left->visit() < right->visit());

		case binOpType::GREATER:
			std::cout << "GREATER" << std::endl;
			return static_cast<double>(left->visit() > right->visit());

		case binOpType::LESS_EQ:
			std::cout << "LESS_EQ" << std::endl;
			return static_cast<double>(left->visit() <= right->visit());

		case binOpType::GREATER_EQ:
			std::cout << "GREATER_EQ" << std::endl;
			return static_cast<double>(left->visit() >= right->visit());

		case binOpType::AND:
			std::cout << "AND" << std::endl;
			return left->visit() && right->visit();
			
		case binOpType::OR:
			std::cout << "OR" << std::endl;
			return left->visit() || right->visit();
			
		default:
			throw std::runtime_error("Error: unknown operand\n");
	}
}

//////////////////////////////////////////////////////////////////_UNOPNODE_//////////////////////////////////////////////////////////////////

double UnOpNode::visit() const
{
	if(expr == nullptr)
		throw std::runtime_error("Error: too less arguments\n");

	switch(op)
	{
		case unOpType::NOT:
			std::cout << "NOT" << std::endl;
			return !(expr->visit());

		case unOpType::PRINT:
		{
			double val = expr->visit();
			std::cout << "PRINT" << std::endl;
			std::cout << val << std::endl;
			return val;
		}

		case unOpType::SCAN:
		{
			if(expr->getType() != nodeType::ID)
				throw std::runtime_error("Error: scanning not to the variable\n");
			std::cout << "SCAN" << std::endl;

			double value;
			std::cin >> value;

			auto var = std::static_pointer_cast<IdentNode>(expr);
			var->setValue(value);
			return value;			
		}

		default:
			throw std::runtime_error("Error: unknown operand\n");
	}
}
