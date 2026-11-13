#include <stdio.h>
#include "semantic.h"
#include "../symbol_table/symbol_table.h"

static int errors = 0;

void semantic_declare(const char *name, const char *type)
{
    if (!symbol_table_insert(name, type)) {
        printf("Semantic Error: Variable '%s' already declared!\n",
               name);

        errors++;
    }
}

void semantic_check_identifier(const char *name)
{
    if (symbol_table_lookup(name) == NULL) {
        printf("Semantic Error: Undeclared variable '%s'!\n",
               name);

        errors++;
    }
}

int semantic_error_count(void)
{
    return errors;
}