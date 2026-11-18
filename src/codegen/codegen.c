
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "codegen.h"

static int temp_count = 0;
static int label_count = 0;

static char *copy_text(const char *text)
{
    char *copy = malloc(strlen(text) + 1);

    if (copy == NULL) {
        fprintf(stderr, "Memory allocation failed!\n");
        exit(1);
    }

    strcpy(copy, text);
    return copy;
}

static char *new_temp(void)
{
    char buffer[32];

    sprintf(buffer, "t%d", ++temp_count);

    return copy_text(buffer);
}

static char *new_label(void)
{
    char buffer[32];

    sprintf(buffer, "L%d", ++label_count);

    return copy_text(buffer);
}

static char *generate_expression(ASTNode *node)
{
    if (node == NULL)
        return copy_text("");

    switch (node->type) {

        case AST_NUMBER:
        case AST_IDENTIFIER:
        case AST_BOOLEAN:
            return copy_text(node->value);

        case AST_BINARY:
        {
            char *left = generate_expression(node->left);
            char *right = generate_expression(node->right);
            char *temp = new_temp();

            printf("%s = %s %s %s\n",
                   temp, left, node->value, right);

            free(left);
            free(right);

            return temp;
        }

        case AST_UNARY:
        {
            char *operand = generate_expression(node->left);
            char *temp = new_temp();

            printf("%s = %s%s\n",
                   temp, node->value, operand);

            free(operand);

            return temp;
        }

        default:
            return copy_text("");
    }
}

static void generate_statements(ASTNode *node);

static void generate_statement(ASTNode *node)
{
    if (node == NULL)
        return;

    switch (node->type) {

        case AST_DECLARATION:
        case AST_ASSIGNMENT:
        {
            char *result = generate_expression(node->left);

            printf("%s = %s\n", node->value, result);

            free(result);
            break;
        }

        case AST_PRINT:
        {
            char *result = generate_expression(node->left);

            printf("print %s\n", result);

            free(result);
            break;
        }

        case AST_BLOCK:
            generate_statements(node->left);
            break;

        case AST_IF:
        {
            char *condition = generate_expression(node->left);
            char *else_label = new_label();

            printf("ifFalse %s goto %s\n",
                   condition, else_label);

            free(condition);

            generate_statement(node->right);

            if (node->third != NULL) {
                char *end_label = new_label();

                printf("goto %s\n", end_label);
                printf("%s:\n", else_label);

                generate_statement(node->third);

                printf("%s:\n", end_label);

                free(end_label);
            }
            else {
                printf("%s:\n", else_label);
            }

            free(else_label);
            break;
        }

        case AST_WHILE:
        {
            char *start_label = new_label();
            char *end_label = new_label();

            printf("%s:\n", start_label);

            char *condition = generate_expression(node->left);

            printf("ifFalse %s goto %s\n",
                   condition, end_label);

            free(condition);

            generate_statement(node->right);

            printf("goto %s\n", start_label);
            printf("%s:\n", end_label);

            free(start_label);
            free(end_label);
            break;
        }

        default:
            break;
    }
}

static void generate_statements(ASTNode *node)
{
    while (node != NULL) {
        generate_statement(node);
        node = node->next;
    }
}

void codegen_generate(ASTNode *root)
{
    temp_count = 0;
    label_count = 0;

    printf("\n========== THREE ADDRESS CODE ==========\n");

    generate_statements(root);

    printf("========================================\n");
}
