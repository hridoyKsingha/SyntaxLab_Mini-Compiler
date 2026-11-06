%{
#include <stdio.h>
%}

%option noyywrap

%%

"int"               { printf("KEYWORD: %s\n", yytext); }
"float"             { printf("KEYWORD: %s\n", yytext); }
"bool"              { printf("KEYWORD: %s\n", yytext); }

[0-9]+              { printf("NUMBER: %s\n", yytext); }

[a-zA-Z_][a-zA-Z0-9_]* {
                        printf("IDENTIFIER: %s\n", yytext);
                     }

"="                 { printf("OPERATOR: %s\n", yytext); }
"+"                 { printf("OPERATOR: %s\n", yytext); }
"-"                 { printf("OPERATOR: %s\n", yytext); }
"*"                 { printf("OPERATOR: %s\n", yytext); }
"/"                 { printf("OPERATOR: %s\n", yytext); }

";"                 { printf("SEMICOLON: %s\n", yytext); }

[ \t\n]+            { /* Ignore whitespace */ }

.                   { printf("UNKNOWN: %s\n", yytext); }

%%

int main()
{
    printf("SyntaxLab Lexer Started\n");
    yylex();
    return 0;
}
