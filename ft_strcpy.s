global ft_strcpy

ft_strcpy:
    mov     rax, rdi

.copy_loop:
    mov     al, [rsi]
    mov     [rdi], al
    cmp     al, 0
    je      .done
    inc     rsi
    inc     rdi
    jmp     .copy_loop

.done:
    ret
