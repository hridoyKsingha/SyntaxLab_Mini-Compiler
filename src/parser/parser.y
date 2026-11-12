
%{
#include <stdio.h>
int yylex(void);
void yyerror(const char *s);
%}

%token INT FLOAT BOOL NUMBER IDENTIFIER TRUE FALSE
%token EQ NE GE LE AND OR NOT

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
    logical_expression
    ;

logical_expression:
    logical_expression OR logical_term
    | logical_term
    ;

logical_term:
    logical_term AND unary_expression
    | unary_expression
    ;

unary_expression:
    NOT unary_expression
    | relational_expression
    ;

relational_expression:
    arithmetic_expression relational_operator arithmetic_expression
    | arithmetic_expression
    ;

relational_operator:
    EQ
    | NE
    | GE
    | LE
    | '>'
    | '<'
    ;

arithmetic_expression:
    arithmetic_expression '+' term
    | arithmetic_expression '-' term
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
    | TRUE
    | FALSE
    | '(' arithmetic_expression ')'
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
