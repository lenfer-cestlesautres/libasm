section .text
    global ft_strdup
    extern malloc
    extern __errno_location

ft_strdup:
    ; rdi — const char *s
    ; Нужно: вызвать malloc(strlen(s) + 1), потом скопировать s в новую память

    push rdi            ; сохраняем rdi = s (на стеке)

; ----------------------
; Вызываем ft_strlen вручную
; ----------------------
    xor     rax, rax    ; длина = 0
.strlen_loop:
    cmp     byte [rdi + rax], 0
    je      .strlen_done
    inc     rax
    jmp     .strlen_loop
.strlen_done:
    inc     rax         ; +1 для \0

; ----------------------
; Вызов malloc
; ----------------------
    mov     rdi, rax    ; rdi = длина + 1
    call    malloc      ; malloc(len)

    test    rax, rax
    je      .malloc_fail    ; если malloc вернул 0 → ошибка

    mov     rsi, rax    ; rsi = куда копировать (dst)
    pop     rdi         ; rdi = s (src)
    mov     rax, rsi    ; вернуть dst

; ----------------------
; Копируем строку (встроенный ft_strcpy)
; ----------------------
.copy_loop:
    mov     dl, [rdi]
    mov     [rsi], dl
    inc     rdi
    inc     rsi
    test    dl, dl
    jne     .copy_loop

    ret

; ----------------------
; Обработка malloc ошибки
; ----------------------
.malloc_fail:
    call    __errno_location
    mov     dword [rax], 12      ; ENOMEM = 12
    xor     rax, rax             ; вернуть NULL
    ret

section .note.GNU-stack noalloc noexec nowrite progbits


;Что делает:
;
;    Выделяет память под копию строки s
;
;    Копирует строку (включая \0) в новую память
;
;    Возвращает указатель на копию
;
;    Возвращает NULL и устанавливает errno, если malloc не удался
;
;    🧠 План действий
;
;    Посчитать длину строки → ft_strlen (можно встроить)
;
;    Добавить +1 байт под \0
;
;    Вызвать malloc
;
;    Если malloc вернул NULL, установить errno = 12 (ENOMEM)
;
;    Иначе — скопировать строку (можно встроить ft_strcpy)
;
;    Вернуть указатель