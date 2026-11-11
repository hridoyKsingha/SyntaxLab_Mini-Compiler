%{
#include <stdio.h>
int yylex(void);
void yyerror(const char *s);
%}

%token INT NUMBER IDENTIFIER

%%

program:
    statement
    ;

statement:
    INT IDENTIFIER '=' NUMBER ';'
    {
        printf("Valid Declaration!\n");
    }
    ;

%%

void yyerror(const char *s)
{
    printf("Syntax Error: %s\n", s);
}

int main()
{
    printf("SyntaxLab Parser Started\n");
    yyparse();
    return 0;
}
