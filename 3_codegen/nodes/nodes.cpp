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

llvm::Value* ScopeNode::codegen() const
{
    for(auto&& stmt : stmts)
   		stmt->codegen();
    return nullptr;
}

//////////////////////////////////////////////////////////////////_IFNODE_//////////////////////////////////////////////////////////////////

llvm::Value* IfNode::codegen() const
{
    if(scope->getNodeType() != nodeType::SCOPE)
   		throw std::runtime_error("Error: wrong action\n");

	llvm::Value *condValue = cond->codegen();
	auto BBs = globalCodeGen->addIfStart(condValue);

	scope->codegen();
	globalCodeGen->addThenBranch(BBs); // then else end

	else_scope->codegen();
	globalCodeGen->addElseBranch(BBs.second); // else end end

	return nullptr;
}

//////////////////////////////////////////////////////////////////_WHILENODE_//////////////////////////////////////////////////////////////////

llvm::Value* WhileNode::codegen() const
{
   	 if(scope->getNodeType() != nodeType::SCOPE)
   		 throw std::runtime_error("Error: wrong action\n");

	llvm::Value* condValue = cond->codegen();
	auto BBs = globalCodeGen->addWhileStart(condValue);

	scope->codegen();

	llvm::Value* newCondValue = cond->codegen(); // for SSA-form
	globalCodeGen->addWhileEnd(newCondValue, BBs);

	return nullptr;
}

//////////////////////////////////////////////////////////////////_BINOPNODE_//////////////////////////////////////////////////////////////////

llvm::Value* BinOpNode::codegen() const
{
	if(left == nullptr || right == nullptr)
  		throw std::runtime_error("Error: too less arguments\n");

    llvm::Value* leftValue = nullptr;
    llvm::Value* rightValue = right->codegen();

	if(op == binOpType::ASSIGN)
	{
		if(left->getNodeType() != nodeType::ID) // TODO: for arrays
  			throw std::runtime_error("Error: assigning not to the variable\n");
		else
			leftValue = std::static_pointer_cast<VarNode>(left)->getDecl()->codegen();
	}
	else
		leftValue = left->codegen();

	return globalCodeGen->addBinOp(leftValue, op, rightValue);
}

//////////////////////////////////////////////////////////////////_UNOPNODE_//////////////////////////////////////////////////////////////////

llvm::Value* UnOpNode::codegen() const
{
    if(expr == nullptr)
   		throw std::runtime_error("Error: too less arguments\n");

    if(op == unOpType::SCAN && expr->getNodeType() != nodeType::ID)
   		throw std::runtime_error("Error: scanning not to the variable\n");
   	
   	llvm::Value* exprValue = nullptr;
   	if(op == unOpType::SCAN)
   	{
   		auto exprNode = std::static_pointer_cast<VarNode>(expr);
   		exprValue = exprNode->getDecl()->codegen();
   	}
   	else
    	exprValue = expr->codegen();

	return globalCodeGen->addUnOp(exprValue, op);
}

//////////////////////////////////////////////////////////////////_CONSTNODE_/////////////////////////////////////////////////////////////////

llvm::Value* ConstNode::codegen() const
{
    auto* type = globalCodeGen->getInt32Ty();
	return llvm::ConstantInt::get(type, num);
}

//////////////////////////////////////////////////////////////////_VARNODE_///////////////////////////////////////////////////////////////////

llvm::Value* VarNode::codegen() const
{
	return globalCodeGen->addVarLoad(decl.lock()->codegen());
}

//////////////////////////////////////////////////////////////////_DECLVARNODE_///////////////////////////////////////////////////////////////

llvm::Value* DeclVarNode::codegen() const
{
	if(!alloca)
		alloca = globalCodeGen->addVarDecl();
	return alloca;
}

//////////////////////////////////////////////////////////////////_DECLFUNCNODE_//////////////////////////////////////////////////////////////

llvm::Value* DeclFuncNode::codegen() const
{
	if(!defined)
		return nullptr;
	if(!func)
		func = globalCodeGen->addFuncDecl(params.size(), funcname);
	return static_cast<llvm::Value*>(func);
}

//////////////////////////////////////////////////////////////////_FUNCNODE_//////////////////////////////////////////////////////////////////

llvm::Value* FuncNode::codegen() const
{
	llvm::Function* func = static_cast<llvm::Function*>(decl->codegen());
	globalCodeGen->addFuncBody(func);

	auto&& params = decl->getFuncParams();

	for(int i = 0; i < params.size(); ++i) 
	{
    	auto&& node = scope->find(params[i]);
    	if(node != nullptr)
		{
	        auto&& declNode = std::static_pointer_cast<DeclVarNode>(node);
	        auto* alloca = declNode->codegen(); 						// create alloca for param
	        llvm::Argument* argVal = func->getArg(i); 					// take generated llvm value for it
	        globalCodeGen->addBinOp(alloca, binOpType::ASSIGN, argVal); // create assign to it
	   	}
	   	else
	   		throw std::runtime_error("Error: incorrect argument");
	}

	scope->codegen();
	return nullptr;
}

//////////////////////////////////////////////////////////////////_CALLNODE_//////////////////////////////////////////////////////////////////

llvm::Value* CallNode::codegen() const
{
	auto&& params = func->getFuncParams();
	if(params.size() != args.size())
		throw std::runtime_error("Error: incorrect number of function parameters");

	auto* funcdecl = static_cast<llvm::Function*>(func->codegen());
    auto* funcTy = funcdecl->getFunctionType();

    std::vector<llvm::Value*> argsValue;
    for(auto&& arg : args)
    {
    	llvm::Value* argValue = arg->codegen();
        argsValue.push_back(argValue);
    }

    return globalCodeGen->addCall(funcTy, funcdecl, argsValue);
}

//////////////////////////////////////////////////////////////////_RET_NODE_//////////////////////////////////////////////////////////////////

llvm::Value* RetNode::codegen() const
{
	nodeType type = expr->getNodeType();
	if(type != nodeType::BINOP && type != nodeType::UNOP && type != nodeType::CONST &&
   	   type != nodeType::ID    && type != nodeType::CALL)
	{
   		throw std::runtime_error("Error: bad type of return expression");
	}
    else if(type == nodeType::BINOP)
    {
   		auto operType = static_pointer_cast<BinOpNode>(expr)->getOperType();
   		if(operType == binOpType::ASSIGN)
   			throw std::runtime_error("Error: bad binOp type of return expression");
    }
    else if(type == nodeType::UNOP)
	{
		auto operType = static_pointer_cast<UnOpNode>(expr)->getOperType();
		if(operType != unOpType::NOT)
			throw std::runtime_error("Error: bad unOp type of return expression");
    }

	llvm::Value* exprValue = expr->codegen();
	return globalCodeGen->addRet(exprValue);
}