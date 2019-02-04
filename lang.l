%{
//**************************************
// lang.l
//
// scanner definition file. flex uses this file to create the scanner
//
// Author: <<<< Samuel Bishop  >>>>
//

#include "lex.h"
#include "cSymbolTable.h"
#include "langparse.h"
#include <list>
using std::list;
// Macros that can be used to create debug output from the scanner
// The first one does NOT create debug output, the second does.
// Uncomment one or the other then use DO_RETURN(val) for all your return 
// statements
//#define DO_RETURN(a) { return (a); }
#define DO_RETURN(a) { return Return(a); }

int Return(int val);
cSymbolTable *IncreaseScope();
cSymbolTable *DecreaseScope();
int identifier();
int increaseScope();
int decreaseScope();

symbolTable_t *currentTable;
extern list<symbolTable_t*> g_list;
extern cSymbolTable g_symbolTable;

%}

%option noyywrap
%option noinput
%option nounput
%option yylineno

%%
"("                         DO_RETURN('(');
")"                         DO_RETURN(')');
"{"                         DO_RETURN('{');
"}"                         DO_RETURN('}');
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
"struct"                    DO_RETURN(STRUCT);
"array"                     DO_RETURN(ARRAY);
"return"                    DO_RETURN(RETURN);
[0-9]+                      {
                               yylval.int_val = atoi(yytext);
                               DO_RETURN(INT_VAL);
                            }
[0-9]+[.][0-9]+             {
                                yylval.float_val = atof(yytext);
                                DO_RETURN(FLOAT_VAL);
                            }
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

int identifier() {
    cSymbol * sym = g_symbolTable.Find(yytext);
    if (sym == nullptr) {
        cSymbol * temp = new cSymbol(yytext);
        yylval.symbol = temp;        
    }
    else
    {
        yylval.symbol = sym;
    }
    if(yylval.symbol->IsType()) { return TYPE_ID; }
    else { return IDENTIFIER; }
}
