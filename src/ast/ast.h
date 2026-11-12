
#ifndef AST_H
#define AST_H

typedef enum {
    AST_DECLARATION,
    AST_NUMBER,
    AST_IDENTIFIER,
    AST_BOOLEAN,
    AST_BINARY,
    AST_UNARY
} ASTNodeType;

typedef struct ASTNode {
    ASTNodeType type;
    char *value;
    char *data_type;
    struct ASTNode *left;
    struct ASTNode *right;
    struct ASTNode *next;
} ASTNode;

ASTNode *ast_number(const char *value);
ASTNode *ast_identifier(const char *name);
ASTNode *ast_boolean(const char *value);
ASTNode *ast_binary(const char *op, ASTNode *left, ASTNode *right);
ASTNode *ast_unary(const char *op, ASTNode *operand);
ASTNode *ast_declaration(const char *type, const char *name, ASTNode *value);
ASTNode *ast_append(ASTNode *list, ASTNode *node);
void ast_print(ASTNode *node);

#endif
