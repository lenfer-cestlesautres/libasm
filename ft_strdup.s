global ft_strdup
extern malloc
extern __errno_location

ft_strdup:
    push    rdi

    xor     rax, rax
.strlen_loop:
    cmp     byte [rdi + rax], 0
    je      .strlen_done
    inc     rax
    jmp     .strlen_loop

.strlen_done:
    inc     rax
    mov     rdi, rax
    call    malloc wrt ..plt

    test    rax, rax
    je      .malloc_fail

    mov     rsi, rax
    pop     rdi
    mov     rax, rsi

.copy_loop:
    mov     dl, [rdi]
    mov     [rsi], dl
    inc     rdi
    inc     rsi
    test    dl, dl
    jne     .copy_loop

    ret

.malloc_fail:
    pop     rdi
    call    __errno_location wrt ..plt
    mov     dword [rax], 12
    xor     rax, rax
    ret
