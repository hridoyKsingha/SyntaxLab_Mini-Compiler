
#include <stdio.h>
#include <string.h>
#include "semantic.h"
#include "../symbol_table/symbol_table.h"

static int errors = 0;

static int is_numeric(const char *type)
{
    return strcmp(type, "int") == 0 ||
           strcmp(type, "float") == 0;
}

void semantic_declare(const char *name, const char *type)
{
    if (!symbol_table_insert(name, type)) {
        printf("Semantic Error: Variable '%s' already declared!\n", name);
        errors++;
    }
}

void semantic_check_identifier(const char *name)
{
    if (symbol_table_lookup(name) == NULL) {
        printf("Semantic Error: Undeclared variable '%s'!\n", name);
        errors++;
    }
}

static const char *expression_type(ASTNode *node)
{
    if (node == NULL)
        return "error";

    switch (node->type) {

        case AST_NUMBER:
            return strchr(node->value, '.') ? "float" : "int";

        case AST_BOOLEAN:
            return "bool";

        case AST_IDENTIFIER:
        {
            Symbol *symbol = symbol_table_lookup(node->value);

            return symbol ? symbol->type : "error";
        }

        case AST_UNARY:
        {
            const char *type = expression_type(node->left);

            if (strcmp(type, "error") == 0)
                return "error";

            if (strcmp(node->value, "!") == 0 &&
                strcmp(type, "bool") == 0)
                return "bool";

            printf("Semantic Error: Invalid operand for '%s'!\n",
                   node->value);
            errors++;
            return "error";
        }

        case AST_BINARY:
        {
            const char *left = expression_type(node->left);
            const char *right = expression_type(node->right);
            const char *op = node->value;

            if (strcmp(left, "error") == 0 ||
                strcmp(right, "error") == 0)
                return "error";

            if (strcmp(op, "&&") == 0 || strcmp(op, "||") == 0) {
                if (strcmp(left, "bool") == 0 &&
                    strcmp(right, "bool") == 0)
                    return "bool";
            }
            else if (strcmp(op, "+") == 0 ||
                     strcmp(op, "-") == 0 ||
                     strcmp(op, "*") == 0 ||
                     strcmp(op, "/") == 0) {

                if (is_numeric(left) && is_numeric(right)) {
                    if (strcmp(left, "float") == 0 ||
                        strcmp(right, "float") == 0)
                        return "float";

                    return "int";
                }
            }
            else if (strcmp(op, "==") == 0 ||
                     strcmp(op, "!=") == 0) {

                if ((is_numeric(left) && is_numeric(right)) ||
                    (strcmp(left, "bool") == 0 &&
                     strcmp(right, "bool") == 0))
                    return "bool";
            }
            else if (strcmp(op, ">") == 0 ||
                     strcmp(op, "<") == 0 ||
                     strcmp(op, ">=") == 0 ||
                     strcmp(op, "<=") == 0) {

                if (is_numeric(left) && is_numeric(right))
                    return "bool";
            }

            printf("Semantic Error: Invalid operand types for '%s'!\n",
                   op);
            errors++;
            return "error";
        }

        default:
            return "error";
    }
}

void semantic_check_assignment(
    const char *name,
    const char *declared_type,
    ASTNode *expression)
{
    const char *actual_type = expression_type(expression);

    if (strcmp(actual_type, "error") == 0)
        return;

    if (strcmp(declared_type, actual_type) == 0 ||
        (strcmp(declared_type, "float") == 0 &&
         strcmp(actual_type, "int") == 0))
        return;

    printf("Semantic Error: Type mismatch for variable '%s'! "
           "Expected %s, got %s.\n",
           name, declared_type, actual_type);

    errors++;
}

void semantic_check_variable_assignment(
    const char *name,
    ASTNode *expression)
{
    Symbol *symbol = symbol_table_lookup(name);

    if (symbol == NULL) {
        printf("Semantic Error: Undeclared variable '%s'!\n", name);
        errors++;
        return;
    }

    semantic_check_assignment(name, symbol->type, expression);
}

void semantic_check_condition(ASTNode *condition)
{
    const char *type = expression_type(condition);

    if (strcmp(type, "error") == 0)
        return;

    if (strcmp(type, "bool") != 0) {
        printf("Semantic Error: Condition must be bool, got %s!\n",
               type);
        errors++;
    }
}

int semantic_error_count(void)
{
    return errors;
}
