section .text
    global ft_write
    extern __errno_location

ft_write:
    mov     rax, 1        ; syscall: write
    syscall               ; вызов ядра: write(fd, buf, count)
    cmp     rax, 0
    jl      .error        ; если rax < 0 → ошибка
    ret

.error:
    neg     rax           ; rax = -rax (теперь в rax положительный errno)
    mov     rdi, rax      ; положительный код ошибки → rdi
    call    __errno_location
    mov     [rax], rdi    ; *errno = код ошибки
    mov     rax, -1       ; вернуть -1
    ret

section .note.GNU-stack noalloc noexec nowrite progbits




;В ft_write ты не вызываешь другую функцию, ты делаешь прямой вызов ядра Linux через syscall.
;🧠 Как работает системный вызов (x86_64 Linux)
;Регистр	Значение
;rax	номер системного вызова
;rdi	1-й аргумент (fd)
;rsi	2-й аргумент (buf)
;rdx	3-й аргумент (count)
;Для write, системный вызов имеет номер 1.
;
; Почему нужен __errno_location
;
;    errno — глобальная переменная, но в многопоточных программах у каждого потока — своя.
;
;    __errno_location возвращает указатель на текущий errno, с которым можно безопасно работать.