#pragma once

#include <iostream>
#include "../nodes/INode.hpp"

#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/GlobalValue.h"
#include "llvm/IR/Verifier.h"
#include "llvm/Support/TargetSelect.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Support/raw_ostream.h"

class CodeGen
{
	private:
		std::unique_ptr<llvm::LLVMContext> context = nullptr;
		std::unique_ptr<llvm::Module> module = nullptr;
		std::unique_ptr<llvm::IRBuilder<>> builder = nullptr;
		llvm::Function* curFunction = nullptr;

	public:
		CodeGen();
		~CodeGen() = default;	

		using blocksPairTy = std::pair<llvm::BasicBlock*, llvm::BasicBlock*>;

		llvm::Value* addBinOp(llvm::Value* left, binOpType op, llvm::Value* right);
		llvm::Value* addUnOp(llvm::Value* expr, unOpType op);

		llvm::Value* addVarLoad(llvm::Value* alloca);
	    llvm::Value* addVarDecl();

		blocksPairTy addWhileStart(llvm::Value* condValue);
		void addWhileEnd(llvm::Value* condValue, blocksPairTy BBs);
		blocksPairTy addIfStart(llvm::Value* condValue);
		void addIfBranch(blocksPairTy BBs);

		llvm::Function* addFuncDecl(unsigned size, const std::string& name);
		llvm::Value* addFuncBody(llvm::Function* func);
		llvm::Value* addCall(llvm::FunctionType* funcTy, llvm::Function* func, std::vector<llvm::Value*>& args);
		llvm::Value* addRet(llvm::Value* expr);

		llvm::Type* getInt32Ty();
		llvm::Type* getVoidTy();

		void printIR(std::string out = {});
};

extern std::unique_ptr<CodeGen> globalCodeGen;