char* compile_asm(char* fsrc)
{
    return "section .text\n\tglobal _start\n\n_start:\n\tmov rax, 1\n\tmov rdi, 1\n\tpush byte 'A'\n\tmov rsi, rsp\n\tmov rdx, 1\n\tsyscall\n\n\tmov rax, 60\n\tmov rdi, 0\n\tsyscall";
}