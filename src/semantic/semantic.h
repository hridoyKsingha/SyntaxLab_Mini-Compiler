#ifndef SEMANTIC_H
#define SEMANTIC_H

void semantic_declare(const char *name, const char *type);
void semantic_check_identifier(const char *name);
int semantic_error_count(void);

#endif