global ft_strcmp

ft_strcmp:
    xor rax, rax
    xor rcx, rcx

.loop:
    mov al, [rdi]
    mov cl, [rsi]
    cmp al, cl
    jne .diff
    cmp al, 0
    je .done
    inc rdi
    inc rsi
    jmp .loop

.diff:
    movzx eax, al
    movzx ecx, cl
    sub eax, ecx
    ret

.done:
    xor eax, eax
    ret
