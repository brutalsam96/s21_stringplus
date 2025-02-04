#include "string_functions.h"

#include <errno.h>  // for strerror
#include <stdio.h>

#define MAX_CHAR 100

s21_size_t s21_strlen(const char *str) {
    s21_size_t length = 0;
    while (str[length] != '\0') {
        length++;
    }
    return length;
}

void *s21_memchr(const void *str, int c, s21_size_t n) {
    char *string = (char *)str;
    char target = (char)c;

    s21_size_t i = 0;
    while (i < n) {
        if (string[i] == target) {
            return (void *)(string + i);
        }
        i++;
    }

    return S21_NULL;
}

int s21_memcmp(const void *str1, const void *str2, s21_size_t n) {
    int value = 0;

    char *string1 = (char *)str1;
    char *string2 = (char *)str2;

    s21_size_t i = 0;
    while (i < n) {
        if (string1[i] == string2[i]) {
            i++;
            continue;
        }

        value = string1[i] - string2[i];
        break;
    }

    return value;
}

void *s21_memcpy(void *dest, const void *src, s21_size_t n) {
    char *destination = (char *)dest;
    char *sourceText = (char *)src;

    for (s21_size_t i = 0; i < n; i++) {
        destination[i] = sourceText[i];
    }

    return dest;
}

void *s21_memset(void *str, int c, s21_size_t n) {
    char *string = (char *)str;

    for (s21_size_t i = 0; i < n; i++) {
        string[i] = c;
    }

    return str;
}

char *s21_strncat(char *dest, const char *src, s21_size_t n) {
    s21_size_t dest_len = s21_strlen(dest);
    s21_size_t i = 0;

    while (src[i] != '\0' && i < n) {
        dest[dest_len + i] = src[i];
        i++;
    }

    dest[dest_len + i] = '\0';
    return dest;
}

char *s21_strchr(const char *str, int c) {
    int i = 0;

    while (str[i] != '\0') {
        if (str[i] == c) {
            return (char *)str + i;
        }
        i++;
    }
    return S21_NULL;
}

int s21_strncmp(const char *str1, const char *str2, s21_size_t n) {
    for (s21_size_t i = 0; i < n; i++) {
        if (str1[i] != str2[i]) {
            return str1[i] - str2[i];
        }
        if (str1[i] == '\0' || str2[i] == '\0') {
            break;
        }
    }
    return 0;
}

char *s21_strncpy(char *dest, const char *src, s21_size_t n) {
    s21_size_t i = 0;

    while (i < n && src[i] != '\0') {
        dest[i] = src[i];
        i++;
    }

    while (i < n) {
        dest[i] = '\0';
        i++;
    }
    return dest;
}

s21_size_t s21_strcspn(const char *str1, const char *str2) {
    s21_size_t i = 0;

    while (str1[i] != '\0') {
        const char *p = str2;
        while (*p != '\0') {
            if (str1[i] == *p) {
                return i;
            }
            p++;
        }
        i++;
    }

    return i;
}

char *s21_strerror(int errnum) {
    ErrorCode error_codes[] = {{1, "Operation not permitted"},            // EPERM
                               {2, "No such file or directory"},          // ENOENT
                               {3, "No such process"},                    // ESRCH
                               {4, "Interrupted system call"},            // EINTR
                               {5, "I/O error"},                          // EIO
                               {6, "No such device or address"},          // ENXIO
                               {7, "Argument list too long"},             // E2BIG
                               {8, "Exec format error"},                  // ENOEXEC
                               {9, "Bad file descriptor"},                // EBADF
                               {10, "No child processes"},                // ECHILD
                               {11, "Resource temporarily unavailable"},  // EAGAIN
                               {12, "Out of memory"},                     // ENOMEM
                               {13, "Permission denied"},                 // EACCES
                               {14, "Bad address"},                       // EFAULT
                               {15, "Block device required"},             // ENOTBLK
                               {16, "Device or resource busy"},           // EBUSY
                               {17, "File exists"},                       // EEXIST
                               {18, "Cross-device link"},                 // EXDEV
                               {19, "No such device"},                    // ENODEV
                               {20, "Not a directory"},                   // ENOTDIR
                               {21, "Is a directory"},                    // EISDIR
                               {22, "Invalid argument"},                  // EINVAL
                               {23, "Too many open files in system"},     // ENFILE
                               {24, "Too many open files"},               // EMFILE
                               {25, "Inappropriate ioctl for device"},    // ENOTTY
                               {26, "Text file busy"},                    // ETXTBSY
                               {27, "File too large"},                    // EFBIG
                               {28, "No space left on device"},           // ENOSPC
                               {29, "Illegal seek"},                      // ESPIPE
                               {30, "Read-only file system"},             // EROFS
                               {31, "Too many links"},                    // EMLINK
                               {32, "Broken pipe"},                       // EPIPE
                               {33, "Numerical argument out of domain"},  // EDOM
                               {34, "Result too large"},                  // ERANGE
                               {0, ""}};

    int i = 0;
    while (error_codes[i].error_code != 0) {
        if (error_codes[i].error_code == errnum) {
            return (char *)error_codes[i].message;
        }
        i++;
    }
    return S21_NULL;
}

char *s21_strpbrk(const char *str1, const char *str2) {
    if (str1 == S21_NULL || str2 == S21_NULL) {
        return S21_NULL;
    }

    for (int i = 0; str2[i] != '\0'; i++) {
        for (int j = 0; str1[j] != '\0'; j++) {
            if (str2[i] == str1[j]) {
                return (char *)&str1[j];
            }
        }
    }
    return S21_NULL;
}

char *s21_strrchr(const char *str, int c) {
    if (str == S21_NULL) {
        return S21_NULL;
    }

    const char *last_occurrence = S21_NULL;
    for (; *str != '\0'; str++) {
        if (*str == (char)c) {
            last_occurrence = str;
        }
    }

    return (char *)last_occurrence;
}

char *s21_strstr(const char *haystack, const char *needle) {
    if (!haystack || !needle) {
        return S21_NULL;
    }

    if (*needle == '\0') {
        return (char *)haystack;
    }

    while (*haystack != '\0') {
        const char *h = haystack;
        const char *n = needle;

        while (*n != '\0' && *h == *n) {
            h++;
            n++;
        }

        if (*n == '\0') {
            return (char *)haystack;
        }

        haystack++;
    }

    return S21_NULL;
}

char *s21_strtok(char *str, const char *delim) {
    static char *next;

    if (str != S21_NULL) {
        next = str;
    }

    if (next == S21_NULL) {
        return S21_NULL;
    }

    char *start = next;
    while (*start && s21_strchr(delim, *start)) {
        start++;
    }

    if (*start == '\0') {
        next = S21_NULL;
        return S21_NULL;
    }

    char *end = start;
    while (*end && !s21_strchr(delim, *end)) {
        end++;
    }

    if (*end) {
        *end = '\0';
        next = end + 1;
    } else {
        next = S21_NULL;
    }

    return start;
}
