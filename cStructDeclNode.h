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

class cStructDeclNode : public cDeclNode
{
public:
    // param is first stmt in the list of statements
cStructDeclNode(cDeclsNode* decls, cSymbol* sym) : cDeclNode()
    {
        AddChild(decls);

        if(!(g_symbolTable.Find(sym->GetName())))
        {
            sym->SetType(true);
            g_symbolTable.Insert(sym);
            AddChild(sym);
        }
        else
        {
            cSymbol *newSym = new cSymbol(sym->GetName());
            newSym->SetType(true);
            g_symbolTable.Insert(newSym);
            AddChild(newSym);
        }
                
    }

    virtual string NodeType() { return string("struct_decl"); }
    virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }
};
