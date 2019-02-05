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

class cIfNode : public cStmtNode
{
public:
    // param is first stmt in the list of statements
cIfNode(cExprNode *expr, cStmtsNode *stmts, cStmtsNode *els) : cStmtNode()
    {
        AddChild(expr);
        AddChild(stmts);
        AddChild(els);        
    }

    virtual string NodeType() { return string("if"); }
    virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }
};
