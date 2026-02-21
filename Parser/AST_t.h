typedef enum {
    AST_NUMBER,
    AST_BINARY_OP,
    AST_FUNCTION_DEF,
    AST_FUNCTION_CALL,
    AST_IDENTIFIER
} AST_types;

typedef struct AST AST;

typedef struct {
    char* name;
    TokenType func_type;
    AST** args;
    size_t arg_count;
    AST* body;
} AST_FunctionDef;

typedef struct {
    char name[64];
    AST** args;
    size_t arg_count;
} AST_FunctionCall;

typedef struct {
    char value[64];
} AST_Number;

typedef struct {
    char* op;
    AST* left;
    AST* right;
} AST_BinaryOp;

struct AST {
    AST_types type;
    union {
        AST_Number number;
        AST_BinaryOp binary;
        AST_FunctionDef func_def;
        AST_FunctionCall func_call;
    };
};
