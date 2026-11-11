
%{
#include <stdio.h>
int yylex(void);
void yyerror(const char *s);
%}

%token INT FLOAT BOOL NUMBER IDENTIFIER

%%

program:
    statement_list
    ;

statement_list:
    statement
    | statement_list statement
    ;

statement:
    INT IDENTIFIER '=' expression ';'
    {
        printf("Valid Integer Declaration!\n");
    }
    | FLOAT IDENTIFIER '=' expression ';'
    {
        printf("Valid Float Declaration!\n");
    }
    | BOOL IDENTIFIER '=' expression ';'
    {
        printf("Valid Boolean Declaration!\n");
    }
    ;

expression:
    expression '+' term
    | expression '-' term
    | term
    ;

term:
    term '*' factor
    | term '/' factor
    | factor
    ;

factor:
    NUMBER
    | IDENTIFIER
    | '(' expression ')'
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
