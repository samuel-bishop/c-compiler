#pragma once
//**************************************
// cSymbolTable.h
//
// Defines a nested symbol table.
// Individual levels of the symbol table use a std::unordered_map from the STL
//
// Author: Samuel Bishop 
// samuel.bishop@oit.edu
//
//

#include "cSymbol.h"
#include <unordered_map>
#include <list>

using std::unordered_map;
using std::list;
typedef unordered_map<string, cSymbol*> map;

class cSymbolTable
{
    public:
        // CREATE A SYMBOL TABLE
        cSymbolTable()
        {
            
        }

        // INCREASE THE SCOPE: ADD A LEVEL TO THE NESTED SYMBOL TABLE
        // RETURN VALUE IS THE NEWLY CREATED SCOPE        
        map *IncreaseScope()
        {
            map * temp = new map();
            g_list.push_front(temp);
            return temp;
        }

        // DECREASE THE SCOPE: REMOVE THE OUTER-MOST SCOPE.
        // RETURNED VALUE IS THE OUTER-MOST SCOPE AFTER THE POP.
        //
        // NOTE: DO NOT CLEAN UP MEMORY AFTER POPING THE TABLE. PARTS OF THE
        // AST WILL PROBABLY CONTAIN POINTERS TO SYMBOLS IN THE POPPED TABLE.
        map *DecreaseScope()
        {
            g_list.pop_front();
            return g_list.front();
        }

        // INSERT A SYMBOL INTO THE TABLE
        // ASSUMES THE SYMBOL IS NOT ALREADY IN THE TABLE
        void Insert(cSymbol *sym)
        {
            (*g_list.front())[sym->GetName()] = sym;
        }

        // DO A LOOKUP IN THE NESTED TABLE. 
        // RETURN THE SYMBOL FOR THE OUTER-MOST MATCH. 
        // RETURNS NULLPTR IF NO MATCH IS FOUND.
        cSymbol *Find(string name)
        {
            cSymbol * sym;
            for(map* scope : g_list)
            {
                sym = (*scope)[name];
                if(sym != nullptr)
                {
                    return sym;
                }
            }
            return nullptr;
        }

        // FIND A SYMBOL IN THE OUTER-MOST SCOPE.
        // NOTE: DOES NOT SEARCH NESTED SCOPES, ONLY THE OUTERMOST SCOPE.
        // RETURN THE SYMBOL IF FOUND.
        // RETURNS NULLPTR IF THE SYMBOL IS NOT FOUND.
        cSymbol *FindLocal(string name)
        {
            return (*g_list.front())[name];
        }
protected:
        list<map*> g_list;
};

// DECLARATION FOR THE GLOBAL SYMBOL TABLE.
// DEFINITION IS IN MAIN.CPP
extern cSymbolTable g_symbolTable;
