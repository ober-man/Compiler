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
	printGraph("open scope ");
	for(auto&& stmt : stmts)
	{
		if(stmt->getNodeType() == nodeType::RET)
			return stmt->visit();
		else
		{
			double retval = stmt->visit();
			if(!std::isnan(retval))
				return retval;
		}
	}
	printGraph("close scope\n");
	return NAN;
}

//////////////////////////////////////////////////////////////////_IFNODE_//////////////////////////////////////////////////////////////////

double IfNode::visit() const
{
	printGraph("start if-stmt");
	if(scope->getNodeType() != nodeType::SCOPE)
		throw std::runtime_error("Error: wrong action\n");
	if(cond->visit())
		return scope->visit();
    else if(else_scope != nullptr)
        return else_scope->visit();
    return NAN;
}

//////////////////////////////////////////////////////////////////_WHILENODE_//////////////////////////////////////////////////////////////////

double WhileNode::visit() const
{
	double retval;
	printGraph("start while-stmt ");
	if(scope->getNodeType() != nodeType::SCOPE)
		throw std::runtime_error("Error: wrong action\n");
	while(cond->visit())
		retval = scope->visit();
	printGraph("end while-stmt ");
	return retval;
}

//////////////////////////////////////////////////////////////////_BINOPNODE_//////////////////////////////////////////////////////////////////

double BinOpNode::visit() const
{
	if(left == nullptr || right == nullptr)
		throw std::runtime_error("Error: too less arguments\n");

	switch(op)
	{
		case binOpType::ADD:
			printGraph("ADD ");
			return left->visit() + right->visit();

		case binOpType::SUB:
			printGraph("SUB ");
			return left->visit() - right->visit();

		case binOpType::MUL:
			printGraph("MUL ");
			return left->visit() * right->visit();

		case binOpType::DIV:
		{
			double val = right->visit();
			if(val == 0)
				throw std::runtime_error("Error: division by zero\n");
			printGraph("DIV ");
			return left->visit() / val;
		}

		case binOpType::MOD:
		{
			int val = static_cast<int>(right->visit());
			if(val == 0)
				throw std::runtime_error("Error: division by zero\n");
			printGraph("MOD ");
			return static_cast<int>(left->visit()) % val;
		}

		case binOpType::ASSIGN:
		{
			if(left->getNodeType() != nodeType::ID)
				throw std::runtime_error("Error: assigning not to the variable\n");
			printGraph("ASSIGN ");
			auto var = std::static_pointer_cast<VarNode>(left);
			double value = right->visit();
			var->setValue(value);
			return NAN;
		}

		case binOpType::NOT_EQUAL:
			printGraph("NOT_EQUAL ");
			return static_cast<double>(left->visit() != right->visit());

		case binOpType::EQUAL:
			printGraph("EQUAL ");
			return static_cast<double>(left->visit() == right->visit());

		case binOpType::LESS:
			printGraph("LESS ");
			return static_cast<double>(left->visit() < right->visit());

		case binOpType::GREATER:
			printGraph("GREATER ");
			return static_cast<double>(left->visit() > right->visit());

		case binOpType::LESS_EQ:
			printGraph("LESS_EQ ");
			return static_cast<double>(left->visit() <= right->visit());

		case binOpType::GREATER_EQ:
			printGraph("GREATER_EQ ");
			return static_cast<double>(left->visit() >= right->visit());

		case binOpType::AND:
			printGraph("AND ");
			return left->visit() && right->visit();

		case binOpType::OR:
			printGraph("OR ");
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
			printGraph("NOT ");
			return !(expr->visit());

		case unOpType::PRINT:
		{
			double val = expr->visit();
			printGraph("PRINT ");
			std::cout << val << std::endl;
			return NAN;
		}

		case unOpType::SCAN:
		{
			if(expr->getNodeType() != nodeType::ID)
				throw std::runtime_error("Error: scanning not to the variable\n");
			printGraph("SCAN ");

			double value;
			std::cin >> value;

			auto var = std::static_pointer_cast<VarNode>(expr);
			var->setValue(value);
			return NAN;
		}

		default:
			throw std::runtime_error("Error: unknown operand\n");
	}
}

//////////////////////////////////////////////////////////////////_FUNC_NODE_//////////////////////////////////////////////////////////////////

std::string FuncNode::getFuncName() const 					
{ 
	return decl.lock()->getName(); 
}

auto FuncNode::getFuncParams() const
{ 
	return decl.lock()->getFuncParams();
}

bool FuncNode::isDefined() const
{ 
	return decl.lock()->isDefined(); 
}

//////////////////////////////////////////////////////////////////_CALL_NODE_//////////////////////////////////////////////////////////////////

std::shared_ptr<FuncNode> createNewFuncInstance(const std::shared_ptr<FuncNode>& old_func)
{
	auto&& old_scope = old_func->getScope();
	auto&& old_table = old_scope->getTable();
	ScopeNode new_scope{*old_scope};
	auto&& new_table = new_scope.getTable();
	auto new_scope_ptr = std::make_shared<ScopeNode>(new_scope);

	FuncNode new_func{*old_func};
	new_func.setScope(new_scope_ptr);
	return std::make_shared<FuncNode>(new_func);
}

double CallNode::visit() const 
{
	printGraph("call func %s ", name);
    if(isRecursive)
    {
    	// func is not defined yet
    	auto decl = curScope->find(name);
	    if(decl == nullptr || decl->getExprType() != exprType::FUNC)
	        throw std::runtime_error("Error: called unknown function");

	    auto func_decl = std::static_pointer_cast<DeclFuncNode>(decl);
	    func = createNewFuncInstance(func_decl->getFuncNode());
    }

    auto&& func_scope = func->getScope();
    auto&& table = func_scope->getTable();
    auto&& params = func->getFuncParams();
    int arg_num = 0;

    if(args.size() != params.size())
    {
    	std::cout << "args" << std::endl;
    	std::for_each(args.begin(), args.end(), [](auto&& arg){ std::cout << arg->visit() << std::endl; });
    	std::cout << "params" << std::endl;
    	std::for_each(params.begin(), params.end(), [](auto&& param){ std::cout << param << std::endl; });
    	throw std::runtime_error("Error: incorrect number of function parameters");
    }

    if(args.size() == 0)
    	return func_scope->visit();

    for(auto&& param_name : params)
    {
    	double arg_val = args[arg_num]->visit();

    	auto cur_param = func_scope->findInThisScope(param_name);
    	if(cur_param == nullptr)
    		throw std::runtime_error("Error: incorrect function parameter\n");

    	auto param_decl = std::static_pointer_cast<DeclVarNode>(cur_param);
    	param_decl->setValue(arg_val);
        ++arg_num;
    }

    printGraph("call func %s end ", func->getFuncName());
    return func_scope->visit();
}

//////////////////////////////////////////////////////////////////_RET_NODE_//////////////////////////////////////////////////////////////////

double RetNode::visit() const
{
	printGraph("return expr ");
	auto type = expr->getNodeType();
	if(type != nodeType::BINOP && type != nodeType::UNOP && type != nodeType::CONST &&
	   type != nodeType::ID && type != nodeType::CALL)
		throw std::runtime_error("Error: bad type of return expression\n");

	else if(type == nodeType::BINOP)
	{
		auto oper_type = static_pointer_cast<BinOpNode>(expr)->getOperType();
		if(oper_type == binOpType::ASSIGN)
			throw std::runtime_error("Error: bad binop type of return expression\n");
	}
	else if(type == nodeType::UNOP)
	{
		auto oper_type = static_pointer_cast<UnOpNode>(expr)->getOperType();
		if(oper_type != unOpType::NOT)
			throw std::runtime_error("Error: bad unop type of return expression\n");
	}

    return expr->visit();
}
