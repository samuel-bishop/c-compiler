#pragma once
//**************************************
// cStmtsNode.h
//
// Defines AST node that represents a list of statements
//
// Author: Phil Howard
// phil.howard@oit.edu
//

#include "cSymbolTable.h"
#include "cExprNode.h"

class cVarExprNode : public cExprNode
{
public:
    // param is first stmt in the list of statements
cVarExprNode(cSymbol *sym) : cExprNode()
    {
        AddChild(sym);
    }

    // Add a statement to the list
    void Insert(cSymbol *sym)
    {
        AddChild(sym);
    }

    virtual string NodeType() { return string("varref"); }
    virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }
};
