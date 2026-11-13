#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symbol_table.h"

static Symbol *symbol_table = NULL;

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

Symbol *symbol_table_lookup(const char *name)
{
    Symbol *current = symbol_table;

    while (current != NULL) {
        if (strcmp(current->name, name) == 0) {
            return current;
        }

        current = current->next;
    }

    return NULL;
}

int symbol_table_insert(const char *name, const char *type)
{
    if (symbol_table_lookup(name) != NULL) {
        return 0;
    }

    Symbol *new_symbol = malloc(sizeof(Symbol));

    if (new_symbol == NULL) {
        fprintf(stderr, "Memory allocation failed!\n");
        exit(1);
    }

    new_symbol->name = copy_text(name);
    new_symbol->type = copy_text(type);
    new_symbol->next = symbol_table;

    symbol_table = new_symbol;

    return 1;
}

void symbol_table_print(void)
{
    Symbol *current = symbol_table;

    printf("\n========== SYMBOL TABLE ==========\n");

    printf("%-15s %-10s\n", "Variable", "Data Type");

    while (current != NULL) {
        printf("%-15s %-10s\n",
               current->name, current->type);

        current = current->next;
    }

    printf("==================================\n");
}