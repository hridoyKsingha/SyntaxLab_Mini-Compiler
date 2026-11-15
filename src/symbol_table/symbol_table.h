
#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

typedef struct Symbol {
    char *name;
    char *type;
    int scope_level;
    struct Symbol *next;
} Symbol;

int symbol_table_insert(const char *name, const char *type);
Symbol *symbol_table_lookup(const char *name);

void symbol_table_enter_scope(void);
void symbol_table_exit_scope(void);

void symbol_table_print(void);

#endif
