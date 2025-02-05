#ifndef TEST_FUNCTION

#define TEST_FUNCTION

#include <errno.h>
#include <stdio.h>
#include <string.h>

#include "../string_functions.h"

void compareTwoString(char *string1, char *string2);
void compareTwoInteger(int a, int b);

void test_memchr(int *test);
void test_memcmp(int *test);
void test_memcpy(int *test);
void test_strlen(int *test);
void test_memset(int *test);
void test_strncat(int *test);
void test_strchr(int *test);
void test_strncmp(int *test);
void test_strncpy(int *test);
void test_strcspn(int *test);
void test_strerror(int *test);
void test_strpbrk(int *test);
void test_strrchr(int *test);
void test_strstr(int *test);
void test_strtok(int *test);

#endif
