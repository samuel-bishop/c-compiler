%{
//**************************************
// lang.l
//
// scanner definition file. flex uses this file to create the scanner
//
// Author: <<<< Samuel Bishop  >>>>
//

#include "lex.h"
#include "tokens.h"
#include "cSymbolTable.h"
#include <list>
using std::list;
// Macros that can be used to create debug output from the scanner
// The first one does NOT create debug output, the second does.
// Uncomment one or the other then use DO_RETURN(val) for all your return 
// statements
#define DO_RETURN(a) { return (a); }
//#define DO_RETURN(a) { return Return(a); }

int Return(int val);
cSymbolTable *IncreaseScope();
cSymbolTable *DecreaseScope();
int identifier();
int increaseScope();
int decreaseScope();

typedef unordered_map<string, cSymbol*> map;
map *currentTable;
extern list<cSymbolTable> g_list;
extern cSymbolTable g_symbolTable;

%}

%option noyywrap
%option noinput
%option nounput
%option yylineno

%%
"("                         DO_RETURN('(');
")"                         DO_RETURN(')');
"{"                         DO_RETURN(increaseScope());
"}"                         DO_RETURN(decreaseScope());
"["                         DO_RETURN('[');
"]"                         DO_RETURN(']');
";"                         DO_RETURN(';');
","                         DO_RETURN(',');
"."                         DO_RETURN('.');
"+"                         DO_RETURN('+');
"-"                         DO_RETURN('-');
"*"                         DO_RETURN('*');
"/"                         DO_RETURN('/');
"%"                         DO_RETURN('%');
"="                         DO_RETURN('=');

"!="                        DO_RETURN(NOT_EQUALS);
"=="                        DO_RETURN(EQUALS);
"&&"                        DO_RETURN(AND);
"||"                        DO_RETURN(OR);

"program"                   DO_RETURN(PROGRAM);
"if"                        DO_RETURN(IF);
"else"                      DO_RETURN(ELSE);
"endif"                     DO_RETURN(ENDIF);
"while"                     DO_RETURN(WHILE);
"print"                     DO_RETURN(PRINT);
"int"                       DO_RETURN(INT);
"float"                     DO_RETURN(FLOAT);
"char"                      DO_RETURN(CHAR);
"struct"                    DO_RETURN(STRUCT);
"array"                     DO_RETURN(ARRAY);
"return"                    DO_RETURN(RETURN);

[0-9]+                      DO_RETURN(INT_VAL);
[0-9]+[.][0-9]+             DO_RETURN(FLOAT_VAL);
[_a-zA-Z][_a-zA-Z0-9]*      DO_RETURN(identifier());

[ \n\t\r\f]+                {} 
[/][/].*                    {}

.                           DO_RETURN(JUNK_TOKEN);
%%

// This function allows us to do extra processing on each token
// It is used to generate lexer debug info
int Return(int val)
{
    printf("Scanned '%s': %d\n", yytext, val);
    return val;
}

int increaseScope() {
    currentTable = g_symbolTable.IncreaseScope();
    return '{';
}

int identifier() {
    cSymbol * sym = g_symbolTable.FindLocal(yytext);
    if (sym == nullptr) {
        cSymbol * temp = new cSymbol(yytext);
        g_symbolTable.Insert(temp);
        yylval.symbol = temp;
    }
    else
    {
        yylval.symbol = sym;
    }
    return IDENTIFIER;
    
}

int decreaseScope()
{
    currentTable = g_symbolTable.DecreaseScope();
    return '}';
}
