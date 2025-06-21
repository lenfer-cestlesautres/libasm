// #include <stdio.h>
// #include <string.h>
// #include "libasm.h"

// int main(void) {
//     char src[] = "Hello, world?";
//     char dst[50];

//     ft_strcpy(dst, src);
//     printf("src: %s\n", src);
//     printf("dst: %s\n", dst);

//     return 0;
// }
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>

// Объявления функций из libasm
ssize_t ft_write(int fd, const void *buf, size_t count);
ssize_t ft_read(int fd, void *buf, size_t count);
size_t ft_strlen(const char *s);
char   *ft_strcpy(char *dst, const char *src);
int     ft_strcmp(const char *s1, const char *s2);
char   *ft_strdup(const char *s);

void test_strlen() {
    printf("\n--- ft_strlen ---\n");
    const char *s = "Hello, libasm!";
    printf("ft_strlen(\"%s\") = %lu\n", s, ft_strlen(s));
    printf("strlen(\"%s\")     = %lu\n", s, strlen(s));
}

void test_strcpy() {
    printf("\n--- ft_strcpy ---\n");
    char src[] = "libasm is cool";
    char dst[100] = {0};
    printf("Исходная строка: %s\n", src);
    ft_strcpy(dst, src);
    printf("Копия: %s\n", dst);
}

void test_strcmp() {
    printf("\n--- ft_strcmp ---\n");
    const char *a = "abc";
    const char *b = "abc";
    const char *c = "abcd";
    const char *d = "abb";

    printf("ft_strcmp(\"%s\", \"%s\") = %d\n", a, b, ft_strcmp(a, b));
    printf("ft_strcmp(\"%s\", \"%s\") = %d\n", a, c, ft_strcmp(a, c));
    printf("ft_strcmp(\"%s\", \"%s\") = %d\n", a, d, ft_strcmp(a, d));
}

void test_write() {
    printf("\n--- ft_write ---\n");
    const char *msg = "Hello from ft_write\n";
    ssize_t ret = ft_write(1, msg, strlen(msg));
    printf("\nВозвращено байт: %zd, errno: %d (%s)\n", ret, errno, strerror(errno));
}

void test_read() {
    printf("\n--- ft_read ---\n");
    char buf[100] = {0};
    printf("Введите строку: ");
    ssize_t ret = ft_read(0, buf, sizeof(buf)-1);
    if (ret >= 0)
        buf[ret] = '\0';
    printf("\nft_read возвратил: %zd байт, строка: \"%s\", errno: %d (%s)\n", ret, buf, errno, strerror(errno));
}

void test_strdup() {
    printf("\n--- ft_strdup ---\n");
    const char *src = "duplicate this!";
    char *dup = ft_strdup(src);
    if (dup)
        printf("Оригинал: \"%s\"\nКопия:    \"%s\"\n", src, dup);
    else
        printf("Ошибка: ft_strdup вернул NULL (errno = %d: %s)\n", errno, strerror(errno));
    free(dup);
}

int main(void) {
    test_strlen();
    test_strcpy();
    test_strcmp();
    test_write();
    test_read();
    test_strdup();
    return 0;
}
