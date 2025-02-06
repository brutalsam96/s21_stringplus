#include <check.h>
#include <stdio.h>
#include <stdlib.h>
#include "../../s21_sprintf.h"

#define BUFF_SIZE 1024

START_TEST(test_sprtinf_c) {
    char s21_buff[BUFF_SIZE], std_buff[BUFF_SIZE]; char value = 'A';
    s21_sprintf(s21_buff,"ab %c cd", value);
    sprintf(std_buff,"ab %c cd", value);
    ck_assert_str_eq(s21_buff, std_buff);
} END_TEST

START_TEST(test_sprtinf_d) {
    char s21_buff[BUFF_SIZE], std_buff[BUFF_SIZE]; int value = 123;
    s21_sprintf(s21_buff,"ab %d cd", value);
    sprintf(std_buff,"ab %d cd", value);
    ck_assert_str_eq(s21_buff, std_buff);
} END_TEST

START_TEST(test_sprtinf_i) {
    char s21_buff[BUFF_SIZE], std_buff[BUFF_SIZE]; int value = 321;
    s21_sprintf(s21_buff,"ab %i cd", value);
    sprintf(std_buff,"ab %i cd", value);
    ck_assert_str_eq(s21_buff, std_buff);
} END_TEST

START_TEST(test_sprtinf_e) {
    char s21_buff[BUFF_SIZE], std_buff[BUFF_SIZE]; double value = 123.0;
    s21_sprintf(s21_buff,"ab %e cd", value);
    sprintf(std_buff,"ab %e cd", value);
    ck_assert_str_eq(s21_buff, std_buff);
} END_TEST

START_TEST(test_sprtinf_E) {
    char s21_buff[BUFF_SIZE], std_buff[BUFF_SIZE]; double value = 123.456;
    s21_sprintf(s21_buff,"ab %E cd", value);
    sprintf(std_buff,"ab %E cd", value);
    ck_assert_str_eq(s21_buff, std_buff);
} END_TEST

START_TEST(test_sprtinf_f) {
    char s21_buff[BUFF_SIZE], std_buff[BUFF_SIZE]; double value = 1.234567;
    s21_sprintf(s21_buff,"ab %f cd", value);
    sprintf(std_buff,"ab %f cd", value);
    ck_assert_str_eq(s21_buff, std_buff);
} END_TEST

START_TEST(test_sprtinf_g) {
    char s21_buff[BUFF_SIZE], std_buff[BUFF_SIZE]; double value = 123.0;
    s21_sprintf(s21_buff,"ab %g cd", value);
    sprintf(std_buff,"ab %g cd", value);
    ck_assert_str_eq(s21_buff, std_buff);
} END_TEST

START_TEST(test_sprtinf_G) {
    char s21_buff[BUFF_SIZE], std_buff[BUFF_SIZE]; double value = 123.456;
    s21_sprintf(s21_buff,"ab %G cd", value);
    sprintf(std_buff,"ab %G cd", value);
    ck_assert_str_eq(s21_buff, std_buff);
} END_TEST

START_TEST(test_sprtinf_o) {
    char s21_buff[BUFF_SIZE], std_buff[BUFF_SIZE]; unsigned int value = 2559;
    s21_sprintf(s21_buff,"ab %o cd", value);
    sprintf(std_buff,"ab %o cd", value);
    ck_assert_str_eq(s21_buff, std_buff);
} END_TEST

START_TEST(test_sprtinf_s) {
    char s21_buff[BUFF_SIZE], std_buff[BUFF_SIZE]; char *value = "Hello";
    s21_sprintf(s21_buff,"ab %s cd", value);
    sprintf(std_buff,"ab %s cd", value);
    ck_assert_str_eq(s21_buff, std_buff);
} END_TEST

START_TEST(test_sprtinf_u) {
    char s21_buff[BUFF_SIZE], std_buff[BUFF_SIZE]; unsigned int value = 555777;
    s21_sprintf(s21_buff,"ab %u cd", value);
    sprintf(std_buff,"ab %u cd", value);
    ck_assert_str_eq(s21_buff, std_buff);
} END_TEST

START_TEST(test_sprtinf_x) {
    char s21_buff[BUFF_SIZE], std_buff[BUFF_SIZE]; unsigned int value = 915;
    s21_sprintf(s21_buff,"ab %x cd", value);
    sprintf(std_buff,"ab %x cd", value);
    ck_assert_str_eq(s21_buff, std_buff);
} END_TEST

START_TEST(test_sprtinf_X) {
    char s21_buff[BUFF_SIZE], std_buff[BUFF_SIZE]; unsigned int value = 519;
    s21_sprintf(s21_buff,"ab %X cd", value);
    sprintf(std_buff,"ab %X cd", value);
    ck_assert_str_eq(s21_buff, std_buff);
} END_TEST

START_TEST(test_sprtinf_p) {
    char s21_buff[BUFF_SIZE], std_buff[BUFF_SIZE]; int value = 5;
    s21_sprintf(s21_buff,"ab %p cd", &value);
    sprintf(std_buff,"ab %p cd", &value);
    ck_assert_str_eq(s21_buff, std_buff);
} END_TEST

START_TEST(test_sprtinf_n) {
    char s21_buff[BUFF_SIZE], std_buff[BUFF_SIZE]; int value = 0, value2 = 0;
    s21_sprintf(s21_buff,"ab %n cd", &value);
    sprintf(std_buff,"ab %n cd", &value2);
    ck_assert_str_eq(s21_buff, std_buff);
    ck_assert_int_eq(value, value2);
} END_TEST

START_TEST(test_sprtinf_percent) {
    char s21_buff[BUFF_SIZE], std_buff[BUFF_SIZE];
    s21_sprintf(s21_buff,"ab %% cd");
    sprintf(std_buff,"ab %% cd");
    ck_assert_str_eq(s21_buff, std_buff);
} END_TEST






Suite *sprintf_suite(void) {
    Suite *s = suite_create("s21_sprintf");
    TCase *tc = tcase_create("Core");

    tcase_add_test(tc, test_sprtinf_c);
    tcase_add_test(tc, test_sprtinf_d);
    tcase_add_test(tc, test_sprtinf_i);
    tcase_add_test(tc, test_sprtinf_e);
    tcase_add_test(tc, test_sprtinf_E);
    tcase_add_test(tc, test_sprtinf_f);
    tcase_add_test(tc, test_sprtinf_g);
    tcase_add_test(tc, test_sprtinf_G);
    tcase_add_test(tc, test_sprtinf_o);
    tcase_add_test(tc, test_sprtinf_s);
    tcase_add_test(tc, test_sprtinf_u);
    tcase_add_test(tc, test_sprtinf_x);
    tcase_add_test(tc, test_sprtinf_X);
    tcase_add_test(tc, test_sprtinf_p);
    tcase_add_test(tc, test_sprtinf_n);
    tcase_add_test(tc, test_sprtinf_g);

    suite_add_tcase(s, tc);
    return s;
}

int main(void){
    int fails;
    Suite *s = sprintf_suite();
    SRunner *sr = srunner_create(s);

    srunner_run_all(sr, CK_VERBOSE);
    fails = srunner_ntests_failed(sr);
    srunner_free(sr);

    // char buff1[256];
    // char buff2[256];
    // int value=0, value2=0;
    // s21_sprintf(buff1,"ab %n cd", &value);
    // sprintf(buff2,"ab %n cd", &value2);
    // printf("s21:%s\n std:%s\n s21:%d\n std:%d\n", buff1, buff2, value, value2);

    return (fails == 0) ? EXIT_SUCCESS : EXIT_FAILURE;

}