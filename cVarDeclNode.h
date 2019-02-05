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
#include "cDeclNode.h"

class cVarDeclNode : public cDeclNode
{
public:
    // param is first stmt in the list of statements
cVarDeclNode(cSymbol* type, cSymbol* name) : cDeclNode()
    {
        AddChild(type);

        if(!(g_symbolTable.Find(name->GetName())))
        {
            g_symbolTable.Insert(name);
            AddChild(name);
        }
        else
        {
            cSymbol *newSym = new cSymbol(name->GetName());
            g_symbolTable.Insert(newSym);
            AddChild(newSym);
        }
    }

    virtual string NodeType() { return string("var_decl"); }
    virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }
};
