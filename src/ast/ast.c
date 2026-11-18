
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"

static char *copy_text(const char *text)
{
    if (text == NULL)
        return NULL;

    char *copy = malloc(strlen(text) + 1);

    if (copy == NULL) {
        fprintf(stderr, "Memory allocation failed!\n");
        exit(1);
    }

    strcpy(copy, text);
    return copy;
}

static ASTNode *ast_create(ASTNodeType type, const char *value)
{
    ASTNode *node = malloc(sizeof(ASTNode));

    if (node == NULL) {
        fprintf(stderr, "Memory allocation failed!\n");
        exit(1);
    }

    node->type = type;
    node->value = copy_text(value);
    node->data_type = NULL;
    node->left = NULL;
    node->right = NULL;
    node->third = NULL;
    node->next = NULL;

    return node;
}

ASTNode *ast_number(const char *value)
{
    return ast_create(AST_NUMBER, value);
}

ASTNode *ast_identifier(const char *value)
{
    return ast_create(AST_IDENTIFIER, value);
}

ASTNode *ast_boolean(const char *value)
{
    return ast_create(AST_BOOLEAN, value);
}

ASTNode *ast_binary(const char *op, ASTNode *left, ASTNode *right)
{
    ASTNode *node = ast_create(AST_BINARY, op);
    node->left = left;
    node->right = right;
    return node;
}

ASTNode *ast_unary(const char *op, ASTNode *operand)
{
    ASTNode *node = ast_create(AST_UNARY, op);
    node->left = operand;
    return node;
}

ASTNode *ast_declaration(const char *type, const char *name, ASTNode *value)
{
    ASTNode *node = ast_create(AST_DECLARATION, name);
    node->data_type = copy_text(type);
    node->left = value;
    return node;
}

ASTNode *ast_append(ASTNode *list, ASTNode *node)
{
    if (node == NULL)
        return list;

    if (list == NULL)
        return node;

    ASTNode *current = list;

    while (current->next != NULL)
        current = current->next;

    current->next = node;
    return list;
}

ASTNode *ast_block(ASTNode *statements)
{
    ASTNode *node = ast_create(AST_BLOCK, NULL);
    node->left = statements;
    return node;
}

ASTNode *ast_if(ASTNode *condition, ASTNode *then_branch,
                ASTNode *else_branch)
{
    ASTNode *node = ast_create(AST_IF, NULL);
    node->left = condition;
    node->right = then_branch;
    node->third = else_branch;
    return node;
}

ASTNode *ast_while(ASTNode *condition, ASTNode *body)
{
    ASTNode *node = ast_create(AST_WHILE, NULL);
    node->left = condition;
    node->right = body;
    return node;
}

ASTNode *ast_assignment(const char *name, ASTNode *expression)
{
    ASTNode *node = ast_create(AST_ASSIGNMENT, name);
    node->left = expression;
    return node;
}


ASTNode *ast_print_statement(ASTNode *expression)
{
    ASTNode *node = ast_create(AST_PRINT, NULL);
    node->left = expression;
    return node;
}


static void print_tree(ASTNode *node, int level)
{
    while (node != NULL) {

        for (int i = 0; i < level; i++)
            printf("  ");

        switch (node->type) {

            case AST_DECLARATION:
                printf("DECLARATION: %s %s\n",
                       node->data_type, node->value);
                break;

            case AST_NUMBER:
                printf("NUMBER: %s\n", node->value);
                break;

            case AST_IDENTIFIER:
                printf("IDENTIFIER: %s\n", node->value);
                break;

            case AST_BOOLEAN:
                printf("BOOLEAN: %s\n", node->value);
                break;

            case AST_BINARY:
                printf("BINARY OPERATOR: %s\n", node->value);
                break;

            case AST_UNARY:
                printf("UNARY OPERATOR: %s\n", node->value);
                break;

            case AST_BLOCK:
                printf("BLOCK\n");
                break;

            case AST_IF:
                printf("IF STATEMENT\n");
                break;

            case AST_WHILE:
                printf("WHILE STATEMENT\n");
                break;

            case AST_PRINT:
                printf("PRINT STATEMENT\n");
                break;

            case AST_ASSIGNMENT:
                printf("ASSIGNMENT: %s\n", node->value);
                break;
        }

        if (node->left != NULL)
            print_tree(node->left, level + 1);

        if (node->right != NULL)
            print_tree(node->right, level + 1);

        if (node->third != NULL)
            print_tree(node->third, level + 1);

        node = node->next;
    }
}

void ast_print(ASTNode *node)
{
    print_tree(node, 0);
}
