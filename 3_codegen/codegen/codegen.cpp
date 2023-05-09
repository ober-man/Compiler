#include "codegen.hpp"

using blocksPairTy = std::pair<llvm::BasicBlock*, llvm::BasicBlock*>;

CodeGen::CodeGen()
{
	context = std::make_unique<llvm::LLVMContext>();
	module = std::make_unique<llvm::Module>("main", *context);
	builder = std::make_unique<llvm::IRBuilder<>>(*context);

	// insert print function
	llvm::FunctionType* funcTy = llvm::FunctionType::get(getVoidTy(), {getInt32Ty()}, false);
	llvm::Function::Create(funcTy, llvm::Function::ExternalLinkage, "__pcl_print", *module);

	// insert scan function
	funcTy = llvm::FunctionType::get(getInt32Ty(), false);
	llvm::Function::Create(funcTy, llvm::Function::ExternalLinkage, "__pcl_scan", *module);

/*
	// insert start function
	funcTy = llvm::FunctionType::get(getVoidTy(), false);
	llvm::Function::Create(funcTy, llvm::Function::ExternalLinkage, "__pcl_start", *module);
*/
}

llvm::Value* CodeGen::addBinOp(llvm::Value* left, binOpType op, llvm::Value* right)
{
    if(left == nullptr)
   		throw std::runtime_error("Error: left argument is not correct");
    if(right == nullptr)
   		throw std::runtime_error("Error: right argument is not correct");

    switch(op)
    {
    	case binOpType::ADD:
        	return builder->CreateAdd(left, right);

    	case binOpType::SUB:
        	return builder->CreateSub(left, right);

    	case binOpType::MUL:
        	return builder->CreateMul(left, right);

    	case binOpType::DIV:
        	return builder->CreateSDiv(left, right);

    	case binOpType::MOD:
        	return builder->CreateSRem(left, right);

    	case binOpType::ASSIGN:
			return builder->CreateStore(/*val =*/ right, /*alloca =*/ left);

    	case binOpType::NOT_EQUAL:
        	return builder->CreateICmpNE(left, right);

    	case binOpType::EQUAL:
        	return builder->CreateICmpEQ(left, right);

    	case binOpType::LESS:
        	return builder->CreateICmpSLT(left, right);

    	case binOpType::GREATER:
        	return builder->CreateICmpSGT(left, right);

    	case binOpType::LESS_EQ:
        	return builder->CreateICmpSLE(left, right);

    	case binOpType::GREATER_EQ:
        	return builder->CreateICmpSGE(left, right);

    	case binOpType::AND:
        	return builder->CreateAnd(left, right);

    	case binOpType::OR:
        	return builder->CreateOr(left, right);

    	default:
   		 throw std::runtime_error("Error: unknown binary operation");
	}
}

llvm::Value* CodeGen::addUnOp(llvm::Value* expr, unOpType op)
{
    if(expr == nullptr)
   		throw std::runtime_error("Error: argument is not correct");

    switch(op)
    {
		case unOpType::NOT:
			return builder->CreateNot(expr);

		case unOpType::PRINT:
		{
			auto *print_func = module->getFunction("__pcl_print");
			if(print_func == nullptr)
				throw std::runtime_error("Error: func __pcl_print was not instantiated");
			llvm::Value *args[] = {expr};
			return builder->CreateCall(print_func, args);
		}

		case unOpType::SCAN:
		{
		 	auto *scan_func = module->getFunction("__pcl_scan");
			if(scan_func == nullptr)
				throw std::runtime_error("Error: func __pcl_scan was not instantiated");
			auto* val = builder->CreateCall(scan_func);
			return builder->CreateStore(val, expr);
		}

		default:
			throw std::runtime_error("Error: unknown unary operation\n");
    }
}

llvm::Value* CodeGen::addVarDecl()
{
	return builder->CreateAlloca(getInt32Ty());
}

llvm::Value* CodeGen::addVarLoad(llvm::Value* alloca)
{
	return builder->CreateLoad(getInt32Ty(), alloca);
}

blocksPairTy CodeGen::addWhileStart(llvm::Value* condValue)
{
	llvm::BasicBlock* bodyBB = llvm::BasicBlock::Create(*context, "while_body", curFunction);
	llvm::BasicBlock* endBB  = llvm::BasicBlock::Create(*context, "while_end", curFunction);
	builder->CreateCondBr(condValue, bodyBB, endBB);
	builder->SetInsertPoint(bodyBB);
	return std::make_pair(bodyBB, endBB);
}

void CodeGen::addWhileEnd(llvm::Value* condValue, blocksPairTy BBs)
{
	builder->CreateCondBr(condValue, BBs.first, BBs.second);
	builder->SetInsertPoint(BBs.second);
}

blocksPairTy CodeGen::addIfStart(llvm::Value* condValue)
{
	llvm::BasicBlock* thenBB = llvm::BasicBlock::Create(*context, "then_branch", curFunction);
	llvm::BasicBlock* elseBB = llvm::BasicBlock::Create(*context, "else_branch", curFunction);
	llvm::BasicBlock* endBB  = llvm::BasicBlock::Create(*context, "if_end", curFunction);
	builder->CreateCondBr(condValue, thenBB, elseBB);
	builder->SetInsertPoint(thenBB);
	return std::make_pair(endBB, elseBB);
}

void CodeGen::addIfBranch(blocksPairTy BBs)
{
    builder->CreateBr(BBs.first);
    builder->SetInsertPoint(BBs.second);
}

llvm::Function* CodeGen::addFuncDecl(unsigned size, const std::string& name)
{/*
	if(name == "main")
	{
		auto* func = module->getFunction("__pcl_start");
		llvm::BasicBlock *BB = llvm::BasicBlock::Create(*context, "main", func);
		builder->SetInsertPoint(BB);
		return func;
	}
*/
	std::vector<llvm::Type*> argTypes;
	for(int i = 0; i < size; ++i)
		argTypes.push_back(getInt32Ty());

	llvm::FunctionType* funcTy = llvm::FunctionType::get(getInt32Ty(), argTypes, false);
	return llvm::Function::Create(funcTy, llvm::Function::ExternalLinkage, name, *module);
}

llvm::Value* CodeGen::addFuncBody(llvm::Function* func)
{
	curFunction = func;
	llvm::BasicBlock* bodyBB = llvm::BasicBlock::Create(*context, "func_start", func);
	builder->SetInsertPoint(bodyBB);
	return nullptr;
}

llvm::Value* CodeGen::addCall(llvm::FunctionType* funcTy, llvm::Function* func, std::vector<llvm::Value*>& args)
{
    return builder->CreateCall(funcTy, func, args);
}

llvm::Value* CodeGen::addRet(llvm::Value* expr)
{
	return builder->CreateRet(expr);
}

llvm::Type* CodeGen::getInt32Ty()
{
    return llvm::Type::getInt32Ty(*context);
}

llvm::Type* CodeGen::getVoidTy()
{
    return llvm::Type::getVoidTy(*context);
}

void CodeGen::printIR(std::string out)
{
    std::error_code EC;
	llvm::raw_fd_ostream os{out, EC};
	if (EC)
		llvm::errs() << EC.message().c_str() << "\n";
    module->print(os, nullptr);
    os.close();
}