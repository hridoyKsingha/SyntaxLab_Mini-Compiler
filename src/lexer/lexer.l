%{
#include <stdio.h>
#include "../parser/parser.tab.h"
%}

%option noyywrap

%%

"int" {
    return INT;
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
