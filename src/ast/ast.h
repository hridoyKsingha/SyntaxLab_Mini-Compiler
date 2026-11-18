
#ifndef AST_H
#define AST_H

typedef enum {
    AST_DECLARATION,
    AST_NUMBER,
    AST_IDENTIFIER,
    AST_BOOLEAN,
    AST_BINARY,
    AST_UNARY,
    AST_BLOCK,
    AST_IF,
    AST_WHILE,
    AST_PRINT,
    AST_ASSIGNMENT
} ASTNodeType;

typedef struct ASTNode {
    ASTNodeType type;
    char *value;
    char *data_type;

    struct ASTNode *left;
    struct ASTNode *right;
    struct ASTNode *third;
    struct ASTNode *next;
} ASTNode;

ASTNode *ast_number(const char *value);
ASTNode *ast_identifier(const char *value);
ASTNode *ast_boolean(const char *value);
ASTNode *ast_binary(const char *op, ASTNode *left, ASTNode *right);
ASTNode *ast_unary(const char *op, ASTNode *operand);
ASTNode *ast_declaration(const char *type, const char *name, ASTNode *value);
ASTNode *ast_append(ASTNode *list, ASTNode *node);

ASTNode *ast_block(ASTNode *statements);
ASTNode *ast_if(ASTNode *condition, ASTNode *then_branch, ASTNode *else_branch);
ASTNode *ast_while(ASTNode *condition, ASTNode *body);
ASTNode *ast_print_statement(ASTNode *expression);
ASTNode *ast_assignment(const char *name, ASTNode *expression);
void ast_print(ASTNode *root);

#endif
