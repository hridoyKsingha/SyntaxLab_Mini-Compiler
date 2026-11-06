%{
#include <stdio.h>
%}

%option noyywrap

%%

"int"|"float"|"bool"|"if"|"else"|"while"|"print" {
    printf("KEYWORD: %s\n", yytext);
}

[0-9]+\.[0-9]+ {
    printf("FLOAT: %s\n", yytext);
}

[0-9]+ {
    printf("NUMBER: %s\n", yytext);
}

[a-zA-Z_][a-zA-Z0-9_]* {
    printf("IDENTIFIER: %s\n", yytext);
}

"=="|"!="|"<="|">="|"="|"<"|">" {
    printf("RELATIONAL_OPERATOR: %s\n", yytext);
}

"&&"|"||"|"!" {
    printf("LOGICAL_OPERATOR: %s\n", yytext);
}

"+"|"-"|"*"|"/" {
    printf("ARITHMETIC_OPERATOR: %s\n", yytext);
}

"//".* {
    /* Ignore single-line comments */
}

"("|")"|"{"|"}" {
    printf("BRACKET: %s\n", yytext);
}

";"|"," {
    printf("SEPARATOR: %s\n", yytext);
}

[ \t\n]+ {
    /* Ignore whitespace */
}

. {
    printf("UNKNOWN: %s\n", yytext);
}

%%

int main()
{
    printf("SyntaxLab Lexer Started\n");
    yylex();
    return 0;
}
