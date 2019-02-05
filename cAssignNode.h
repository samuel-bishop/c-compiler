#pragma once
//**************************************
// cStmtsNode.h
//
// Defines AST node that represents a list of statements
//
// Author: Samuel Bishop
// samuel.bishop@oit.edu
//

#include "cStmtNode.h"

class cAssignNode : public cStmtNode
{
public:
    // param is first stmt in the list of statements
cAssignNode(cVarExprNode *varExpr, cExprNode *expr) : cStmtNode()
    {
        AddChild(varExpr);
        AddChild(expr);
    }

    virtual string NodeType() { return string("assign"); }
    virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }
};
