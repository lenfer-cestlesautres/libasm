section .text
    global ft_strlen

ft_strlen:
    ; rdi — указатель на строку
    ; возвращает длину в rax

    xor rax, rax          ; обнуляем счётчик длины
.loop:
    cmp byte [rdi + rax], 0   ; сравниваем текущий символ с 0
    je .end                   ; если конец строки — выходим
    inc rax                   ; увеличиваем счётчик
    jmp .loop
.end:
    ret

section .note.GNU-stack noalloc noexec nowrite progbits
