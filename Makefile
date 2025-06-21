NAME = libasm.a

ASM_SRC = \
	ft_strlen.s \
	ft_strcpy.s \
	ft_strcmp.s \
	ft_write.s \
	ft_read.s \
	ft_strdup.s

ASM_OBJ = $(ASM_SRC:.s=.o)

C_TEST = main.c
C_OBJ = $(C_TEST:.c=.o)

CC = gcc
ASM = nasm
ASM_FLAGS = -f elf64
CFLAGS = -Wall -Wextra -Werror
AR = ar rcs

# Правило по умолчанию
all: $(NAME)

# Создание библиотеки из объектных файлов
$(NAME): $(ASM_OBJ)
	$(AR) $(NAME) $(ASM_OBJ)

# Компиляция .s в .o
%.o: %.s
	$(ASM) $(ASM_FLAGS) $< -o $@

# Компиляция теста
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

test: $(NAME) $(C_OBJ)
	$(CC) $(CFLAGS) -o test $(C_OBJ) -L. -lasm

clean:
	rm -f $(ASM_OBJ) $(C_OBJ)

fclean: clean
	rm -f $(NAME) test

re: fclean all






# NAME = libasm.a
# NASM = nasm
# NASMFLAGS = -f elf64

# SRCS = ft_strcpy.s
# OBJS = $(SRCS:.s=.o)

# all: $(NAME)

# $(NAME): $(OBJS)
# 	ar rcs $(NAME) $(OBJS)

# %.o: %.s
# 	$(NASM) $(NASMFLAGS) $< -o $@

# clean:
# 	rm -f $(OBJS)

# fclean: clean
# 	rm -f $(NAME) test

# re: fclean all

# test: all main.c
# 	cc -no-pie -Wall -Wextra -Werror main.c -L. -lasm -o test

# bonus:
# 	@echo "No bonus yet"