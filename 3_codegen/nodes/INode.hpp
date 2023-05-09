#pragma once

#include "llvm/IR/Value.h"

enum class nodeType
{
    SCOPE, IF,    WHILE,
    BINOP, UNOP,  CONST,
    ID,    BREAK, CONTINUE,
    DECL,  CALL,  RET,
    FUNC,  ARR,   ACCESS
};

class BaseNode
{
    private:
   		nodeType node_type;

    public:
   		BaseNode(nodeType type_) : node_type(type_) {}
   		virtual ~BaseNode() = default;

   		nodeType getNodeType() const { return node_type; }
   		virtual llvm::Value* codegen() const = 0;
};

enum class varType
{
    INT, DOUBLE, CHAR, STRING, BOOL, VOID
};

enum class binOpType
{
    ADD, SUB, MUL, DIV, MOD, ASSIGN,
    NOT_EQUAL, EQUAL, LESS, GREATER,
    LESS_EQ, GREATER_EQ, AND, OR
};

enum class unOpType
{
    NOT, PRINT, SCAN
};

enum class exprType
{
    VAR, ARR, FUNC
};

// forward declarations
class DeclNode;
class DeclFuncNode;
class DeclVarNode;
