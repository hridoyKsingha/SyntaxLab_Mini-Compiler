
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"

static char *copy_text(const char *text)
{
    char *copy = malloc(strlen(text) + 1);

    if (copy != NULL) {
        strcpy(copy, text);
    }

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
    node->value = value ? copy_text(value) : NULL;
    node->data_type = NULL;
    node->left = NULL;
    node->right = NULL;
    node->next = NULL;

    return node;
}

ASTNode *ast_number(const char *value)
{
    return ast_create(AST_NUMBER, value);
}

ASTNode *ast_identifier(const char *name)
{
    return ast_create(AST_IDENTIFIER, name);
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
    if (list == NULL) {
        return node;
    }

    ASTNode *current = list;

    while (current->next != NULL) {
        current = current->next;
    }

    current->next = node;
    return list;
}

static void print_tree(ASTNode *node, int level)
{
    while (node != NULL) {

        for (int i = 0; i < level; i++) {
            printf("  ");
        }

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
        }

        if (node->left != NULL) {
            print_tree(node->left, level + 1);
        }

        if (node->right != NULL) {
            print_tree(node->right, level + 1);
        }

        node = node->next;
    }
}

void ast_print(ASTNode *node)
{
    print_tree(node, 0);
}
