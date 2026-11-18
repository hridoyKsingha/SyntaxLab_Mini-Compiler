
#ifndef SEMANTIC_H
#define SEMANTIC_H

#include "../ast/ast.h"

void semantic_declare(const char *name, const char *type);

void semantic_check_identifier(const char *name);

void semantic_check_assignment(
    const char *name,
    const char *declared_type,
    ASTNode *expression
);

void semantic_check_variable_assignment(
    const char *name,
    ASTNode *expression
);

void semantic_check_condition(ASTNode *condition);

int semantic_error_count(void);

#endif
