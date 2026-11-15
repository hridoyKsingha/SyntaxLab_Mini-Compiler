
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symbol_table.h"

static Symbol *symbol_table = NULL;
static int current_scope = 0;

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
    Symbol *current = symbol_table;

    while (current != NULL) {
        if (strcmp(current->name, name) == 0 &&
            current->scope_level == current_scope) {
            return 0;
        }

        current = current->next;
    }

    Symbol *new_symbol = malloc(sizeof(Symbol));

    if (new_symbol == NULL) {
        fprintf(stderr, "Memory allocation failed!\n");
        exit(1);
    }

    new_symbol->name = copy_text(name);
    new_symbol->type = copy_text(type);
    new_symbol->scope_level = current_scope;
    new_symbol->next = symbol_table;

    symbol_table = new_symbol;

    return 1;
}

void symbol_table_enter_scope(void)
{
    current_scope++;
}

void symbol_table_exit_scope(void)
{
    if (current_scope == 0) {
        return;
    }

    while (symbol_table != NULL &&
           symbol_table->scope_level == current_scope) {

        Symbol *temp = symbol_table;
        symbol_table = symbol_table->next;

        free(temp->name);
        free(temp->type);
        free(temp);
    }

    current_scope--;
}

void symbol_table_print(void)
{
    Symbol *current = symbol_table;

    printf("\n========== SYMBOL TABLE ==========\n");
    printf("%-15s %-10s %-10s\n",
           "Variable", "Data Type", "Scope");

    while (current != NULL) {
        printf("%-15s %-10s %-10d\n",
               current->name,
               current->type,
               current->scope_level);

        current = current->next;
    }

    printf("==================================\n");
}
