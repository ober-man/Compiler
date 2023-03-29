#include "nodes.hpp"

//////////////////////////////////////////////////////////////////_SCOPENODE_//////////////////////////////////////////////////////////////////

std::shared_ptr<DeclNode> ScopeNode::find(const std::string& name) const
{
	auto res = table.find(name);
	if(res != table.end())
		return res->second;

	if(prev != nullptr)
		return prev->find(name);

	return nullptr;
}

std::shared_ptr<DeclNode> ScopeNode::findInThisScope(const std::string& name) const
{
	auto res = table.find(name);
	if(res != table.end())
		return res->second;
	else return nullptr;
}

double ScopeNode::visit() const
{
	printGraph("open scope");
	double retval;
	for(auto&& stmt : stmts)
		retval = stmt->visit();
	printGraph("close scope");
	return retval;
}

//////////////////////////////////////////////////////////////////_IFNODE_//////////////////////////////////////////////////////////////////

double IfNode::visit() const
{
	printGraph("start if-stmt");
	if(scope->getType() != nodeType::SCOPE)
		throw std::runtime_error("Error: wrong action\n");
	if(cond->visit())
		scope->visit();
    else if(else_scope != nullptr)
        else_scope->visit();
	printGraph("end if-stmt");
	return 0;
}

//////////////////////////////////////////////////////////////////_WHILENODE_//////////////////////////////////////////////////////////////////

double WhileNode::visit() const
{
	printGraph("start while-stmt");
	if(scope->getType() != nodeType::SCOPE)
		throw std::runtime_error("Error: wrong action\n");
	while(cond->visit())
		scope->visit();
	printGraph("end while-stmt");
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
			printGraph("ADD");
			return left->visit() + right->visit();

		case binOpType::SUB:
			printGraph("SUB" << std::endl;
			return left->visit() - right->visit();

		case binOpType::MUL:
			printGraph("MUL" << std::endl;
			return left->visit() * right->visit();

		case binOpType::DIV:
		{
			double val = right->visit();
			if(val == 0)
				throw std::runtime_error("Error: division by zero\n");
			printGraph("DIV");
			return left->visit() / val;
		}

		case binOpType::MOD:
		{
			int val = static_cast<int>(right->visit());
			if(val == 0)
				throw std::runtime_error("Error: division by zero\n");
			printGraph("MOD");
			return static_cast<int>(left->visit()) % val;
		}

		case binOpType::ASSIGN:
		{
			if(left->getType() != nodeType::ID)
				throw std::runtime_error("Error: assigning not to the variable\n");
			printGraph("ASSIGN");
			auto var = std::static_pointer_cast<VarNode>(left);
			double value = right->visit();
			var->setValue(value);
			return value;
		}

		case binOpType::NOT_EQUAL:
			printGraph("NOT_EQUAL");
			return static_cast<double>(left->visit() != right->visit());

		case binOpType::EQUAL:
			printGraph("EQUAL");
			return static_cast<double>(left->visit() == right->visit());

		case binOpType::LESS:
			printGraph("LESS");
			return static_cast<double>(left->visit() < right->visit());

		case binOpType::GREATER:
			printGraph("GREATER");
			return static_cast<double>(left->visit() > right->visit());

		case binOpType::LESS_EQ:
			printGraph("LESS_EQ");
			return static_cast<double>(left->visit() <= right->visit());

		case binOpType::GREATER_EQ:
			printGraph("GREATER_EQ");
			return static_cast<double>(left->visit() >= right->visit());

		case binOpType::AND:
			printGraph("AND");
			return left->visit() && right->visit();

		case binOpType::OR:
			printGraph("OR");
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
			printGraph("NOT");
			return !(expr->visit());

		case unOpType::PRINT:
		{
			double val = expr->visit();
			printGraph("PRINT");
			std::cout << val << std::endl;
			return val;
		}

		case unOpType::SCAN:
		{
			if(expr->getType() != nodeType::ID)
				throw std::runtime_error("Error: scanning not to the variable\n");
			printGraph("SCAN");

			double value;
			std::cin >> value;

			auto var = std::static_pointer_cast<VarNode>(expr);
			var->setValue(value);
			return value;
		}

		default:
			throw std::runtime_error("Error: unknown operand\n");
	}
}

//////////////////////////////////////////////////////////////////_CALL_NODE_//////////////////////////////////////////////////////////////////

double CallNode::visit() const
{
    auto&& func_scope = func->getScope();
    auto&& params = func->getFuncArgs();

    if(args.size() != params.size())
    	throw std::runtime_error("Error: incorrect number of function parameters\n");

    for(auto&& arg : args)
    {
    	auto var_decl = static_pointer_cast<DeclVarNode>(curScope->find(arg));
    	double val = decl->getValue();

    	auto var_node = std::make_shared<VarNode>(arg, val);
        auto param = std::make_shared<DeclVarNode>(arg, var_node);
        func_scope->insertName(arg, param);
    }

    return scope->visit();
}

//////////////////////////////////////////////////////////////////_RET_NODE_//////////////////////////////////////////////////////////////////

double RetNode::visit() const
{
	auto type = expr->getNodeType();
	if(type != BINOP || type != UNOP || type != CONST || type != ID || type != CALL)
		throw std::runtime_error("Error: bad return expression\n");
	else if(type == BINOP)
	{
		auto oper_type = static_pointer_cast<BinOpNode>(expr)->getOperType();
		if(oper_type == ASSIGN)
			throw std::runtime_error("Error: bad return expression\n");
	}
	else if(type == UNOP)
	{
		auto oper_type = static_pointer_cast<BinOpNode>(expr)->getOperType();
		if(oper_type != NOT)
			throw std::runtime_error("Error: bad return expression\n");
	}
    return expr->visit();
}
