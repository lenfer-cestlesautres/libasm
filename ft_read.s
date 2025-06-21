section .text
    global ft_read
    extern __errno_location

ft_read:
    mov     rax, 0         ; syscall: read
    syscall
    cmp     rax, 0
    jl      .error
    ret

.error:
    neg     rax
    mov     rdi, rax
    call    __errno_location
    mov     [rax], rdi
    mov     rax, -1
    ret

section .note.GNU-stack noalloc noexec nowrite progbits