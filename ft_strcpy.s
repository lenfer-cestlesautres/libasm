section .text
    global ft_strcpy

ft_strcpy:
    mov     rax, rdi           ; сохранить dst, это return-значение

.copy_loop:
    mov     al, [rsi]          ; al = *src загрузить байт из src в al
    mov     [rdi], al          ; *dst = al  записать этот байт в dst
    cmp     al, 0              ; конец строки?
    je      .done              ; если да — выходим
    inc     rsi                ; src++
    inc     rdi                ; dst++
    jmp     .copy_loop         ; повторяем

.done:
    ret

section .note.GNU-stack noalloc noexec nowrite progbits
