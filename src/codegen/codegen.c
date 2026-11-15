
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "codegen.h"

static int temp_count = 0;

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

    temp_count++;
    sprintf(buffer, "t%d", temp_count);

    return copy_text(buffer);
}

static char *generate_expression(ASTNode *node)
{
    if (node == NULL) {
        return copy_text("");
    }

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

void codegen_generate(ASTNode *root)
{
    ASTNode *current = root;

    temp_count = 0;

    printf("\n========== THREE ADDRESS CODE ==========\n");

    while (current != NULL) {

        if (current->type == AST_DECLARATION) {

            char *result = generate_expression(current->left);

            printf("%s = %s\n", current->value, result);

            free(result);
        }

        current = current->next;
    }

    printf("========================================\n");
}
