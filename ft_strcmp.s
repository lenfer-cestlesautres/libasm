section .text
    global ft_strcmp

ft_strcmp:
    xor rax, rax        ; обнуляем al
    xor rcx, rcx        ; обнуляем cl

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

section .note.GNU-stack noalloc noexec nowrite progbits





















;ft_strcmp:
;    xor rax, rax ; обнуляем rax в нем будет а1 s1[i]
;    xor rbx, rbx ; обнуляем rbx в нем будет b1 s2[i]
;
;    .loop:
;        mov al, [rdi]      ; al = s1[i]
;        mov bl, [rsi]      ; bl = s2[i]
;        cmp al, bl         ; сравнить текущие символы
;        jne .diff          ; если не равны — переход к разнице
;        cmp al, 0          ; если символ == '\0'
;        je .done           ; значит строки равны, конец
;        inc rdi            ; s1++
;        inc rsi            ; s2++
;        jmp .loop          ; повторить
;        ret
;    .diff:
;    ; al = s1[i], bl = s2[i]
;    movzx eax, al      ; расширить al до eax (32-бита, без знака)
;    movzx ebx, bl      ; тоже самое для bl
;    sub eax, ebx       ; eax = al - bl
;    ret
;
;    .done:
;    xor eax, eax       ; вернуть 0 — строки равны
;    ret


;rdi	указатель на s1
;rsi	указатель на s2
;al	байт из s1[i]
;bl	байт из s2[i]
;rax	результат (s1[i] - s2[i]) и возвращаемое значение
;
;🔍 Что здесь происходит:
;
;    mov al, [rdi] — загрузить 1 байт из памяти по адресу rdi (то есть *s1)
;
;    cmp al, bl — сравниваем байты
;
;    jne — "jump if not equal" — прыжок, если байты не равны
;
;    cmp al, 0 — проверяем, не конец ли строки (строки в C заканчиваются нулём)
;
;    inc rdi — двигаемся к следующему символу
;
;    Повторяем