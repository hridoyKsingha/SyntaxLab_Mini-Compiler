
%{
#include <stdio.h>
#include <stdlib.h>
#include "ast.h"

int yylex(void);
void yyerror(const char *s);
%}

%union {
    char *text;
    ASTNode *node;
}

%token INT FLOAT BOOL TRUE FALSE
%token <text> NUMBER IDENTIFIER
%token EQ NE GE LE AND OR NOT

%type <node> program statement_list statement
%type <node> expression logical_expression logical_term
%type <node> unary_expression relational_expression
%type <node> arithmetic_expression term factor

%type <text> relational_operator

%%

program:
    statement_list
    {
        printf("\n========== ABSTRACT SYNTAX TREE ==========\n");
        ast_print($1);
        printf("==========================================\n");
    }
    ;

statement_list:
    statement
    {
        $$ = $1;
    }
    | statement_list statement
    {
        $$ = ast_append($1, $2);
    }
    ;

statement:
    INT IDENTIFIER '=' expression ';'
    {
        $$ = ast_declaration("int", $2, $4);
        free($2);
    }
    | FLOAT IDENTIFIER '=' expression ';'
    {
        $$ = ast_declaration("float", $2, $4);
        free($2);
    }
    | BOOL IDENTIFIER '=' expression ';'
    {
        $$ = ast_declaration("bool", $2, $4);
        free($2);
    }
    ;

expression:
    logical_expression
    {
        $$ = $1;
    }
    ;

logical_expression:
    logical_expression OR logical_term
    {
        $$ = ast_binary("||", $1, $3);
    }
    | logical_term
    {
        $$ = $1;
    }
    ;

logical_term:
    logical_term AND unary_expression
    {
        $$ = ast_binary("&&", $1, $3);
    }
    | unary_expression
    {
        $$ = $1;
    }
    ;

unary_expression:
    NOT unary_expression
    {
        $$ = ast_unary("!", $2);
    }
    | relational_expression
    {
        $$ = $1;
    }
    ;

relational_expression:
    arithmetic_expression relational_operator arithmetic_expression
    {
        $$ = ast_binary($2, $1, $3);
    }
    | arithmetic_expression
    {
        $$ = $1;
    }
    ;

relational_operator:
    EQ { $$ = "=="; }
    | NE { $$ = "!="; }
    | GE { $$ = ">="; }
    | LE { $$ = "<="; }
    | '>' { $$ = ">"; }
    | '<' { $$ = "<"; }
    ;

arithmetic_expression:
    arithmetic_expression '+' term
    {
        $$ = ast_binary("+", $1, $3);
    }
    | arithmetic_expression '-' term
    {
        $$ = ast_binary("-", $1, $3);
    }
    | term
    {
        $$ = $1;
    }
    ;

term:
    term '*' factor
    {
        $$ = ast_binary("*", $1, $3);
    }
    | term '/' factor
    {
        $$ = ast_binary("/", $1, $3);
    }
    | factor
    {
        $$ = $1;
    }
    ;

factor:
    NUMBER
    {
        $$ = ast_number($1);
        free($1);
    }
    | IDENTIFIER
    {
        $$ = ast_identifier($1);
        free($1);
    }
    | TRUE
    {
        $$ = ast_boolean("true");
    }
    | FALSE
    {
        $$ = ast_boolean("false");
    }
    | '(' expression ')'
    {
        $$ = $2;
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
