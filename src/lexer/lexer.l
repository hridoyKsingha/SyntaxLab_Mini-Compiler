
%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../ast/ast.h"
#include "../parser/parser.tab.h"
%}

%option noyywrap

%%

"int" {
    return INT;
}

"float" {
    return FLOAT;
}

"bool" {
    return BOOL;
}

"true" {
    return TRUE;
}

"false" {
    return FALSE;
}

"==" {
    return EQ;
}

"!=" {
    return NE;
}

">=" {
    return GE;
}

"<=" {
    return LE;
}

"&&" {
    return AND;
}

"||" {
    return OR;
}

"!" {
    return NOT;
}

[0-9]+\.[0-9]+ {
    yylval.text = strdup(yytext);
    return NUMBER;
}

[0-9]+ {
    yylval.text = strdup(yytext);
    return NUMBER;
}

[a-zA-Z_][a-zA-Z0-9_]* {
    yylval.text = strdup(yytext);
    return IDENTIFIER;
}

"+"|"-"|"*"|"/" {
    return yytext[0];
}

">"|"<"|"="|"("|")"|";" {
    return yytext[0];
}

"//".* {
    /* Ignore single-line comments */
}

[ \t\n]+ {
    /* Ignore whitespace */
}

. {
    printf("UNKNOWN: %s\n", yytext);
}

%%
