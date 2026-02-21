char* compile_asm(AST* ast)
{
    return "section .text:\n\tglobal _start\n_start:\n\t";
}