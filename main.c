#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>

// declarations
ssize_t ft_write(int fd, const void *buf, size_t count);
ssize_t ft_read(int fd, void *buf, size_t count);
size_t ft_strlen(const char *s);
char   *ft_strcpy(char *dst, const char *src);
int     ft_strcmp(const char *s1, const char *s2);
char   *ft_strdup(const char *s);

void test_strlen() {
    printf("\n--- ft_strlen ---\n");

    const char *cases[] = {"", "a", "Hello, libasm!", "123", "2147483647",
        "lorem\tipsum\tdolor\nsit\namet\n",
        "\n\n\f\r\t",
        "   ",
        "Lorem ipsum dolor sit amet, consectetur adipiscing elit. "
    "Sed do eiusmod tempor incididunt utrem\tipsum\tdolor\nsit\namet\n labore et dolore magna aliqua. "
    "Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi "
    "ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit "
    "in voluptate velit esse cillum dolore eu fugiat nulla pariatur. "
    "Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia "
    "deserunt mollit anim id est laborum. "
    "1234567890ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"
    " — repeated multiple times. "
    "Lorem ipsum dolor sit amet, consectetur adipiscing elit. "
    "Sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. "
    "Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi "
    "ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit "
    "in voluptate velit esse cillum dolore eu fugiat nulla pariatur. "
    "Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia "
    "deserunt mollit anim id est laborum. ", NULL};

        for (int i = 0; cases[i]; i++) {
            printf("[%d] ft_strlen: %lu | strlen: %lu\n",
            i, ft_strlen(cases[i]), strlen(cases[i]));
        }
}

void test_strcpy() {
    printf("\n--- ft_strcpy ---\n");
    const char *cases[] = {"", "a", "Test string", "Long string with multiple words and characters!", NULL};
    char dst1[1024], dst2[1024];
    for (int i = 0; cases[i]; i++) {
        memset(dst1, 0, sizeof(dst1));
        memset(dst2, 0, sizeof(dst2));
        ft_strcpy(dst1, cases[i]);
        strcpy(dst2, cases[i]);
        printf("[%d] Test result: %s\n", i, strcmp(dst1, dst2) == 0 ? "✅" : "❌");
    }
}

void test_strcmp() {
 printf("\n--- ft_strcmp ---\n");
    const char *pairs[][2] = {
        {"", ""},
        {"", "a"},
        {"a", ""},
        {"abc", "abc"},
        {"abc", "abcd"},
        {"abcd", "abc"},
        {"xyz", "xya"},
        {"same", "same"},
        {"short", "shorter"},
        {"shorter", "short"},
        {"Hello", "hello"},
        {"different", "DIFFERENT"},
        {"123", "123"},
        {"123", "124"},
        // {"", NULL},        // segfault
        // {NULL, ""},        // segfault
        {NULL, NULL} 
    };
    for (int i = 0; pairs[i][0]; i++) {
        int res1 = ft_strcmp(pairs[i][0], pairs[i][1]);
        int res2 = strcmp(pairs[i][0], pairs[i][1]);
        printf("[%d] ft: %d | std: %d %s\n",
               i, res1, res2, res1 == res2 ? "✅" : "❌");
    }
}

void test_write() {
    printf("\n--- ft_write ---\n");
    const char *cases[] = {"", "Hello\n", "Another test line\n", NULL};
    for (int i = 0; cases[i]; i++) {
        errno = 0;
        ssize_t ret1 = write(1, cases[i], strlen(cases[i]));
        int e1 = errno;
        errno = 0;
        ssize_t ret2 = ft_write(1, cases[i], strlen(cases[i]));
        int e2 = errno;
        printf("\n[%d] write: %zd (%d), ft_write: %zd (%d) %s\n",
               i, ret1, e1, ret2, e2, (ret1 == ret2 && e1 == e2) ? "✅" : "❌");
        }

    // err case
    errno = 0;
    ssize_t ret1 = write(-1, "bad fd\n", 7);
    int e1 = errno;
    errno = 0;
    ssize_t ret2 = ft_write(-1, "bad fd\n", 7);
    int e2 = errno;
    printf("\n[error] write: %zd (%d), ft_write: %zd (%d) %s\n",
           ret1, e1, ret2, e2, (ret1 == ret2 && e1 == e2) ? "✅" : "❌");
}

void test_read() {
    printf("\n--- ft_read ---\n");

    char buf1[64] = {0};
    char buf2[64] = {0};
    ssize_t r1, r2;
    int e1, e2;

    // stdin
    printf("Type something (up to 63 chars): ");
    fflush(stdout);
    errno = 0;
    r1 = read(0, buf1, 63);
    e1 = errno;
    buf1[(r1 >= 0 && r1 < 64) ? r1 : 0] = '\0';

    printf("Now repeat same for ft_read: ");
    fflush(stdout);
    errno = 0;
    r2 = ft_read(0, buf2, 63);
    e2 = errno;
    buf2[(r2 >= 0 && r2 < 64) ? r2 : 0] = '\0';

    printf("read:    \"%s\" (%zd, errno: %d)\n", buf1, r1, e1);
    printf("ft_read: \"%s\" (%zd, errno: %d)\n", buf2, r2, e2);

    // file
    int fd = open("test_read.txt", O_CREAT | O_RDWR | O_TRUNC, 0644);
    write(fd, "Read this line\n", 15);
    lseek(fd, 0, SEEK_SET);

    memset(buf1, 0, sizeof(buf1));
    memset(buf2, 0, sizeof(buf2));

    errno = 0;
    r1 = read(fd, buf1, 15);
    e1 = errno;
    lseek(fd, 0, SEEK_SET);
    errno = 0;
    r2 = ft_read(fd, buf2, 15);
    e2 = errno;
    close(fd);
    remove("test_read.txt");

    printf("\nread:    \"%s\" (%zd, errno: %d)\n", buf1, r1, e1);
    printf("ft_read: \"%s\" (%zd, errno: %d)\n", buf2, r2, e2);
    printf("%s\n", (r1 == r2 && memcmp(buf1, buf2, 15) == 0) ? "✅" : "❌");

    // invalid fd
    errno = 0;
    r1 = read(-1, buf1, 10);
    e1 = errno;
    errno = 0;
    r2 = ft_read(-1, buf2, 10);
    e2 = errno;

    printf("\n[ERR] read:    %zd (errno: %d)\n", r1, e1);
    printf("[ERR] ft_read: %zd (errno: %d)\n", r2, e2);
    printf("[ERR]%s\n", (r1 == r2 && e1 == e2) ? "✅" : "❌");
}

void test_strdup() {
    printf("\n--- ft_strdup ---\n");
    const char *cases[] = {"", "duplicate", "long duplicated string test case with symbols !@#"   
    "Sed o eiusmod tempor incididunt utrem\tipsum\tdolor\nsit\namet\n labore et dolore magna aliqua. "
    "Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi "
    "ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit "
    "in voluptate velit esse cillum dolore eu fugiat nulla pariatur. "
    "Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia "
    "deserunt mollit anim id est laborum. "
    "1234567890ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz", NULL};

    for (int i = 0; cases[i]; i++) {
        char *dup1 = ft_strdup(cases[i]);
        char *dup2 = strdup(cases[i]);

        if (!dup1 || !dup2) {
            printf("[%d] ❌ malloc failed: dup1 = %p, dup2 = %p\n", i, (void*)dup1, (void*)dup2);
        } else {
            int match = strcmp(dup1, dup2) == 0;
            printf("[%d]%s\n", i, match ? "✅" : "❌");
        }
        if (dup1)
            free(dup1);
        if (dup2)
        free(dup2);
    }
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
