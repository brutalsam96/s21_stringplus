#include <check.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "../../s21_string.h"

START_TEST(test_memchr) {
    const char str1[] = "Tutorialspoint";
    const char ch1 = '.';
    char *string1 = (char *)s21_memchr(str1, ch1, s21_strlen(str1));
    char *string2 = (char *)memchr(str1, ch1, strlen(str1));
    ck_assert_ptr_eq(string1, string2);
}

START_TEST(test_memchr2) {
    const char str1[] = "abcdef";
    const char ch1 = 'd';
    char *string1 = (char *)s21_memchr(str1, ch1, s21_strlen(str1));
    char *string2 = (char *)memchr(str1, ch1, strlen(str1));
    ck_assert_ptr_eq(string1, string2);
}

START_TEST(test_memchr3) {
    const char str1[] = "Welcome to\n India";
    const char ch1 = '\n';
    char *string1 = (char *)s21_memchr(str1, ch1, s21_strlen(str1));
    char *string2 = (char *)memchr(str1, ch1, strlen(str1));
    ck_assert_ptr_eq(string1, string2);
}

START_TEST(test_memcmp) {
    int s21_res;
    int res;
    const char *str1 = "abcdef";
    const char *str2 = "ABCDEF";
    s21_res = s21_memcmp(str1, str2, 6);
    res = memcmp(str1, str2, 6);
    ck_assert_int_eq(s21_res, res);
}

START_TEST(test_memcmp2) {
    int s21_res;
    int res;

    int arr1[] = {1, 2, 3, 4, 5};
    int arr2[] = {1, 2, 3, 4, 6};
    s21_res = s21_memcmp(arr1, arr2, sizeof(arr1));
    res = memcmp(arr1, arr2, sizeof(arr1));
    ck_assert_int_eq(s21_res, res);
}

START_TEST(test_memcmp3) {
    int s21_res;
    int res;

    const char *str1 = "12345678901400345678";
    const char *str2 = "1234567";

    s21_res = s21_memcmp(str1, str2, 7);
    res = memcmp(str1, str2, 7);
    ck_assert_int_eq(s21_res, res);
}

START_TEST(test_memcpy) {
    const char src1[50] = "Tutorialspoint";
    char s21_dest1[50] = {0};
    char dest1[50] = {0};
    s21_memcpy(s21_dest1, src1, strlen(src1) + 1);
    memcpy(dest1, src1, strlen(src1) + 1);
    ck_assert_str_eq(s21_dest1, dest1);
}

START_TEST(test_memcpy2) {
    const char src1[50] = "Point";
    char s21_dest1[50] = {0};
    char dest1[50] = {0};
    s21_memcpy(s21_dest1, src1, strlen(src1) + 1);
    memcpy(dest1, src1, strlen(src1) + 1);
    ck_assert_str_eq(s21_dest1, dest1);
}

START_TEST(test_memcpy3) {
    const char src1[50] = "Valgrind safe test";
    char s21_dest1[50] = {0};
    char dest1[50] = {0};
    s21_memcpy(s21_dest1, src1, strlen(src1) + 1);
    memcpy(dest1, src1, strlen(src1) + 1);
    ck_assert_str_eq(s21_dest1, dest1);
}

START_TEST(test_strlen) {
    int s21_len, len;
    const char *word1 = "Tutorialspoint";
    s21_len = s21_strlen(word1);
    len = strlen(word1);
    ck_assert_int_eq(s21_len, len);
}

START_TEST(test_strlen2) {
    int s21_len, len;
    const char *word1 = "";
    s21_len = s21_strlen(word1);
    len = strlen(word1);
    ck_assert_int_eq(s21_len, len);
}

START_TEST(test_strlen3) {
    int s21_len, len;
    const char *word1 = "\n";
    s21_len = s21_strlen(word1);
    len = strlen(word1);
    ck_assert_int_eq(s21_len, len);
}

START_TEST(test_memset) {
    char str1[20] = "Hello World";
    char s21_str1[20] = "Hello World";
    memset(str1, 'Z', 10);
    s21_memset(s21_str1, 'Z', 10);
    ck_assert_str_eq(str1, s21_str1);
}

START_TEST(test_memset2) {
    int arr[10];
    int s21_arr[10];
    memset(arr, 0, sizeof(arr));
    s21_memset(s21_arr, 0, sizeof(s21_arr));
    ck_assert_mem_eq(arr, s21_arr, sizeof(arr));
}

START_TEST(test_strncat) {
    char dest1[20] = "Hello, ";
    char s21_dest1[20] = "Hello, ";
    char src1[] = "Beautiful World!";
    strncat(dest1, src1 + 10, 5);
    s21_strncat(s21_dest1, src1 + 10, 5);
    ck_assert_str_eq(dest1, s21_dest1);
}

START_TEST(test_strncat2) {
    char dest1[20] = "";
    char s21_dest1[20] = "";
    char src1[] = "World!";
    strncat(dest1, src1, 5);
    s21_strncat(s21_dest1, src1, 5);
    ck_assert_str_eq(dest1, s21_dest1);
}

START_TEST(test_strchr) {
    char *s21_res;
    char *res;
    const char *str1 = "TutorialsPoint";
    const char ch1 = '.';
    res = strchr(str1, ch1);
    s21_res = s21_strchr(str1, ch1);
    ck_assert_ptr_eq(res, s21_res);
}

START_TEST(test_strchr2) {
    char *s21_res;
    char *res;
    const char *str1 = "Welcome to Tutorialspoint";
    const char ch1 = 'u';
    res = strchr(str1, ch1);
    s21_res = s21_strchr(str1, ch1);
    ck_assert_ptr_eq(res, s21_res);
}

START_TEST(test_strchr3) {
    char *s21_res;
    char *res;
    const char *str1 = "This is simple string";
    const char ch1 = 's';
    res = strchr(str1, ch1);
    s21_res = s21_strchr(str1, ch1);
    ck_assert_ptr_eq(res, s21_res);
}

START_TEST(test_strncmp) {
    int res;
    int s21_res;
    const char str_1[] = "java";
    const char str_2[] = "java";
    res = strncmp(str_1, str_2, strlen(str_2));
    s21_res = s21_strncmp(str_1, str_2, strlen(str_2));
    ck_assert_int_eq(res, s21_res);
}

START_TEST(test_strncmp2) {
    int res;
    int s21_res;
    const char str_1[] = "abcdef";
    const char str_2[] = "ABCDEF";
    res = strncmp(str_1, str_2, strlen(str_2));
    s21_res = s21_strncmp(str_1, str_2, strlen(str_2));
    ck_assert_int_eq(res, s21_res);
}

START_TEST(test_strncpy) {
    const char *src1 = "TutorialsPoint.com";
    char dest1[12] = {0};
    char s21_dest1[12] = {0};
    strncpy(dest1, src1, 10);
    s21_strncpy(s21_dest1, src1, 10);
    ck_assert_str_eq(dest1, s21_dest1);
}
START_TEST(test_strncpy2) {
    const char *src1 = "Hello, Note!";
    char dest1[12] = {0};
    char s21_dest1[12] = {0};
    strncpy(dest1, src1, 10);
    s21_strncpy(s21_dest1, src1, 10);
    ck_assert_str_eq(dest1, s21_dest1);
}
START_TEST(test_strcspn) {
    int res, s21_res;
    const char *str1 = "Tutorialspoint";
    const char *str2 = "Textbook";
    res = strcspn(str1, str2);
    s21_res = s21_strcspn(str1, str2);
    ck_assert_int_eq(res, s21_res);
}

START_TEST(test_strcspn2) {
    int res, s21_res;
    const char *str1 = "tutorialspoint";
    const char *str2 = "tutorial";
    res = strcspn(str1, str2);
    s21_res = s21_strcspn(str1, str2);
    ck_assert_int_eq(res, s21_res);
}

START_TEST(test_strcspn3) {
    int res, s21_res;
    const char *str1 = "Welcome to Tutorialspoint Community";
    const char *str2 = "point";
    res = strcspn(str1, str2);
    s21_res = s21_strcspn(str1, str2);
    ck_assert_int_eq(res, s21_res);
}

START_TEST(test_strerror) {
    FILE *res;
    res = fopen("file.txt", "r");
    int err_code = errno;
    ck_assert_str_eq(strerror(err_code), s21_strerror(err_code));
    
}
START_TEST(test_strpbrk) {
    char *res, *s21_res;
    const char str1[] = "abcde2fghi3jk4l";
    const char str2[] = "34";
    res = strpbrk(str1, str2);
    s21_res = s21_strpbrk(str1, str2);
    ck_assert_pstr_eq(res, s21_res);
}

START_TEST(test_strpbrk2) {
    char *res, *s21_res;
    const char str1[] = "Hello, World!";
    const char str2[] = "oW";
    res = strpbrk(str1, str2);
    s21_res = s21_strpbrk(str1, str2);
    ck_assert_pstr_eq(res, s21_res);
}

START_TEST(test_strpbrk3) {
    char *res, *s21_res;
    const char str1[] = "Our Tutorials";
    const char str2[] = "rT";
    res = strpbrk(str1, str2);
    s21_res = s21_strpbrk(str1, str2);
    ck_assert_pstr_eq(res, s21_res);
}

START_TEST(test_strrchr) {
    char *res, *s21_res;
    const char str[] = "Tutorialspoint";
    const char ch = '.';
    res = strchr(str, ch);
    s21_res = s21_strchr(str, ch);
    ck_assert_pstr_eq(res, s21_res);
}

START_TEST(test_strrchr2) {
    char *res, *s21_res;
    const char str[] = "Welcome to Tutorialspoint";
    const char ch = 'u';
    res = strchr(str, ch);
    s21_res = s21_strchr(str, ch);
    ck_assert_pstr_eq(res, s21_res);
}

START_TEST(test_strstr) {
    char *res, *s21_res;
    const char str[20] = "TutorialsPoint";
    const char substr[10] = "Point";
    res = strstr(str, substr);
    s21_res = s21_strstr(str, substr);
    ck_assert_ptr_eq(res, s21_res);
}

START_TEST(test_strstr2) {
    char *res, *s21_res;
    char str_1[100] = "Welcome to Tutorialspoint";
    res = strstr(str_1, "ials");
    s21_res = s21_strstr(str_1, "ials");
    ck_assert_ptr_eq(res, s21_res);
}

START_TEST(test_strtok) {
    char *token, *s21_token;
    char str[80] = "This is - www.tutorialspoint.com - website";
    const char s[2] = "-";
    token = strtok(str, s);
    s21_token = s21_strtok(str, s);
    ck_assert_ptr_eq(token, s21_token);
}

START_TEST(test_strtok2) {
    char *token, *s21_token;
    char str_1[] = "ttttt";
    char *str_2 = "tp";
    token = strtok(str_1, str_2);
    s21_token = s21_strtok(str_1, str_2);
    ck_assert_ptr_eq(token, s21_token);
}





Suite *s21_string_suite(void) {
    Suite *s = suite_create("s21_string");
    TCase *tc = tcase_create("Core");

    tcase_add_test(tc, test_memchr);
    tcase_add_test(tc, test_memchr2);
    tcase_add_test(tc, test_memchr3);
    tcase_add_test(tc, test_memcmp);
    tcase_add_test(tc, test_memcmp2);
    tcase_add_test(tc, test_memcmp3);
    tcase_add_test(tc, test_memcpy);
    tcase_add_test(tc, test_memcpy2);
    tcase_add_test(tc, test_memcpy3);
    tcase_add_test(tc, test_strlen);
    tcase_add_test(tc, test_strlen2);
    tcase_add_test(tc, test_strlen3);
    tcase_add_test(tc, test_memset);
    tcase_add_test(tc, test_memset2);
    tcase_add_test(tc, test_strncat);
    tcase_add_test(tc, test_strncat2);
    tcase_add_test(tc, test_strchr);
    tcase_add_test(tc, test_strchr2);
    tcase_add_test(tc, test_strncmp);
    tcase_add_test(tc, test_strncmp2);
    tcase_add_test(tc, test_strncpy);
    tcase_add_test(tc, test_strncpy2);
    tcase_add_test(tc, test_strcspn);
    tcase_add_test(tc, test_strcspn2);
    tcase_add_test(tc, test_strerror);
    tcase_add_test(tc, test_strpbrk);
    tcase_add_test(tc, test_strpbrk2);
    tcase_add_test(tc, test_strpbrk3);
    tcase_add_test(tc, test_strrchr);
    tcase_add_test(tc, test_strrchr2);
    tcase_add_test(tc, test_strstr);
    tcase_add_test(tc, test_strstr2);
    tcase_add_test(tc, test_strtok);
    tcase_add_test(tc, test_strtok2);
    suite_add_tcase(s, tc);
    return s;
}

int main (void) {
    int fails;
    Suite *s = s21_string_suite();
    SRunner *sr = srunner_create(s);

    srunner_run_all(sr, CK_VERBOSE);
    fails = srunner_ntests_failed(sr);
    srunner_free(sr);
    return (fails == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}