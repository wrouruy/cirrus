typedef enum {
    AST_NUMBER,
    AST_BINARY_OP
} AST_types;

typedef struct AST {
    AST_types type;
    char valueStr[64];   // for num or operation 
    struct AST* left;    // for exercise
    struct AST* right;
} AST;