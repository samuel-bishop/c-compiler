#pragma once
//**************************************
// cIntExprNode.h
//
// Defines an AST node for an integer constant (literals).
//
// Inherits from cExprNode so that integer constants can be used anywhere
// expressions are used.
//
// Author: Phil Howard
// phil.howard@oit.edu
//

#include "cAstNode.h"
#include "cExprNode.h"

class cBinaryExprNode : public cExprNode
{
public:
    // param is the value of the integer constant
cBinaryExprNode(cExprNode* LHS, cOpNode* OP, cExprNode* RHS) : cExprNode()
    {
        AddChild(LHS);
        AddChild(OP);
        AddChild(RHS);
    }

    virtual string NodeType() { return string("expr"); }
    virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }
};
