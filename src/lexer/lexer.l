
%{
#include <stdio.h>
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

"&&" {
    return AND;
}

"||" {
    return OR;
}

"!" {
    return NOT;
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

">" {
    return '>';
}

"<" {
    return '<';
}


[0-9]+\.[0-9]+ {
    return NUMBER;
}

[0-9]+ {
    return NUMBER;
}

[a-zA-Z_][a-zA-Z0-9_]* {
    return IDENTIFIER;
}

[ \t\n]+ {
    /* Ignore whitespace */
}

. {
    return yytext[0];
}

%%
