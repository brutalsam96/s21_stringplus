#include <check.h>
#include <stdio.h>
#include <stdlib.h>
#include "../../s21_sprintf.h"

#define BUFF_SIZE 1024

/* Original tests using the '+' flag */
START_TEST(test_sprtinf_c) {
  char s21_buff[BUFF_SIZE], std_buff[BUFF_SIZE];
  char value = 'A';
  s21_sprintf(s21_buff, "ab %+10c cd", value);
  sprintf(std_buff, "ab %+10c cd", value);
  ck_assert_str_eq(s21_buff, std_buff);
}
END_TEST

START_TEST(test_sprtinf_d) {
  char s21_buff[BUFF_SIZE], std_buff[BUFF_SIZE];
  int value = -5;
  s21_sprintf(s21_buff, "ab %+010d cd", value);
  sprintf(std_buff, "ab %+010d cd", value);
  ck_assert_str_eq(s21_buff, std_buff);
}
END_TEST

START_TEST(test_sprtinf_i) {
  char s21_buff[BUFF_SIZE], std_buff[BUFF_SIZE];
  int value = 0;
  s21_sprintf(s21_buff, "ab %+010i cd", value);
  sprintf(std_buff, "ab %+010i cd", value);
  ck_assert_str_eq(s21_buff, std_buff);
}
END_TEST

START_TEST(test_sprtinf_e) {
  char s21_buff[BUFF_SIZE], std_buff[BUFF_SIZE];
  double value = -0.0;
  s21_sprintf(s21_buff, "ab %+010e cd", value);
  sprintf(std_buff, "ab %+010e cd", value);
  ck_assert_str_eq(s21_buff, std_buff);
}
END_TEST

START_TEST(test_sprtinf_E) {
  char s21_buff[BUFF_SIZE], std_buff[BUFF_SIZE];
  double value = -1.0;
  s21_sprintf(s21_buff, "ab %+08E cd", value);
  sprintf(std_buff, "ab %+08E cd", value);
  ck_assert_str_eq(s21_buff, std_buff);
}
END_TEST

START_TEST(test_sprtinf_f) {
  char s21_buff[BUFF_SIZE], std_buff[BUFF_SIZE];
  double value = -5.0;
  s21_sprintf(s21_buff, "ab %+010f cd", value);
  sprintf(std_buff, "ab %+010f cd", value);
  ck_assert_str_eq(s21_buff, std_buff);
}
END_TEST

START_TEST(test_sprtinf_g) {
  char s21_buff[BUFF_SIZE], std_buff[BUFF_SIZE];
  double value = -5.0;
  s21_sprintf(s21_buff, "ab %+010g cd", value);
  sprintf(std_buff, "ab %+010g cd", value);
  ck_assert_str_eq(s21_buff, std_buff);
}
END_TEST

START_TEST(test_sprtinf_G) {
  char s21_buff[BUFF_SIZE], std_buff[BUFF_SIZE];
  double value = 0.0;
  s21_sprintf(s21_buff, "ab %+.8G cd", value);
  sprintf(std_buff, "ab %+.8G cd", value);
  ck_assert_str_eq(s21_buff, std_buff);
}
END_TEST

START_TEST(test_sprtinf_o) {
  char s21_buff[BUFF_SIZE], std_buff[BUFF_SIZE];
  unsigned int value = 0;
  s21_sprintf(s21_buff, "ab %+8o cd", value);
  sprintf(std_buff, "ab %+8o cd", value);
  ck_assert_str_eq(s21_buff, std_buff);
}
END_TEST

START_TEST(test_sprtinf_s) {
  char s21_buff[BUFF_SIZE], std_buff[BUFF_SIZE];
  char *value = "Hello";
  s21_sprintf(s21_buff, "ab %015s cd", value);
  sprintf(std_buff, "ab %015s cd", value);
  ck_assert_str_eq(s21_buff, std_buff);
}
END_TEST

START_TEST(test_sprtinf_u) {
  char s21_buff[BUFF_SIZE], std_buff[BUFF_SIZE];
  unsigned int value = 0;
  s21_sprintf(s21_buff, "ab %+015u cd", value);
  sprintf(std_buff, "ab %+015u cd", value);
  ck_assert_str_eq(s21_buff, std_buff);
}
END_TEST

START_TEST(test_sprtinf_x) {
  char s21_buff[BUFF_SIZE], std_buff[BUFF_SIZE];
  unsigned int value = 0;
  s21_sprintf(s21_buff, "ab %+011x cd", value);
  sprintf(std_buff, "ab %+011x cd", value);
  ck_assert_str_eq(s21_buff, std_buff);
}
END_TEST

START_TEST(test_sprtinf_X) {
  char s21_buff[BUFF_SIZE], std_buff[BUFF_SIZE];
  unsigned int value = 0;
  s21_sprintf(s21_buff, "ab %+11X cd", value);
  sprintf(std_buff, "ab %+11X cd", value);
  ck_assert_str_eq(s21_buff, std_buff);
}
END_TEST

START_TEST(test_sprtinf_p) {
  char s21_buff[BUFF_SIZE], std_buff[BUFF_SIZE];
  int value = 0;
  s21_sprintf(s21_buff, "ab %+11p cd", &value);
  sprintf(std_buff, "ab %+11p cd", &value);
  ck_assert_str_eq(s21_buff, std_buff);
}
END_TEST

START_TEST(test_sprtinf_n) {
  char s21_buff[BUFF_SIZE], std_buff[BUFF_SIZE];
  int value = 0, value2 = 0;
  s21_sprintf(s21_buff, "ab %+11n cd", &value);
  sprintf(std_buff, "ab %+11n cd", &value2);
  ck_assert_str_eq(s21_buff, std_buff);
  ck_assert_int_eq(value, value2);
}
END_TEST

START_TEST(test_sprtinf_percent) {
  char s21_buff[BUFF_SIZE], std_buff[BUFF_SIZE];
  s21_sprintf(s21_buff, "ab %+10% cd");
  sprintf(std_buff, "ab %+10% cd");
  ck_assert_str_eq(s21_buff, std_buff);
}
END_TEST

/* New tests for additional flag functions and edge cases */

/* '-' flag (left-justify) */
START_TEST(test_sprtinf_minus_d) {
  char s21_buff[BUFF_SIZE], std_buff[BUFF_SIZE];
  int value = 123;
  s21_sprintf(s21_buff, "ab %-10d cd", value);
  sprintf(std_buff, "ab %-10d cd", value);
  ck_assert_str_eq(s21_buff, std_buff);
}
END_TEST

START_TEST(test_sprtinf_minus_f) {
  char s21_buff[BUFF_SIZE], std_buff[BUFF_SIZE];
  double value = 123.456;
  s21_sprintf(s21_buff, "ab %-10f cd", value);
  sprintf(std_buff, "ab %-10f cd", value);
  ck_assert_str_eq(s21_buff, std_buff);
}
END_TEST

START_TEST(test_sprtinf_minus_s) {
  char s21_buff[BUFF_SIZE], std_buff[BUFF_SIZE];
  char *value = "Hello";
  s21_sprintf(s21_buff, "ab %-10s cd", value);
  sprintf(std_buff, "ab %-10s cd", value);
  ck_assert_str_eq(s21_buff, std_buff);
}
END_TEST

/* ' ' (space) flag */
START_TEST(test_sprtinf_space_d_positive) {
  char s21_buff[BUFF_SIZE], std_buff[BUFF_SIZE];
  int value = 123;
  s21_sprintf(s21_buff, "ab % 10d cd", value);
  sprintf(std_buff, "ab % 10d cd", value);
  ck_assert_str_eq(s21_buff, std_buff);
}
END_TEST

START_TEST(test_sprtinf_space_d_negative) {
  char s21_buff[BUFF_SIZE], std_buff[BUFF_SIZE];
  int value = -123;
  s21_sprintf(s21_buff, "ab % 10d cd", value);
  sprintf(std_buff, "ab % 10d cd", value);
  ck_assert_str_eq(s21_buff, std_buff);
}
END_TEST

/* '#' flag (alternative form) */
START_TEST(test_sprtinf_hash_o) {
  char s21_buff[BUFF_SIZE], std_buff[BUFF_SIZE];
  unsigned int value = 123;
  s21_sprintf(s21_buff, "ab %#10o cd", value);
  sprintf(std_buff, "ab %#10o cd", value);
  ck_assert_str_eq(s21_buff, std_buff);
}
END_TEST

START_TEST(test_sprtinf_hash_x) {
  char s21_buff[BUFF_SIZE], std_buff[BUFF_SIZE];
  unsigned int value = 255;
  s21_sprintf(s21_buff, "ab %#10x cd", value);
  sprintf(std_buff, "ab %#10x cd", value);
  ck_assert_str_eq(s21_buff, std_buff);
}
END_TEST

START_TEST(test_sprtinf_hash_X) {
  char s21_buff[BUFF_SIZE], std_buff[BUFF_SIZE];
  unsigned int value = 255;
  s21_sprintf(s21_buff, "ab %#10X cd", value);
  sprintf(std_buff, "ab %#10X cd", value);
  ck_assert_str_eq(s21_buff, std_buff);
}
END_TEST

START_TEST(test_sprtinf_hash_f) {
  char s21_buff[BUFF_SIZE], std_buff[BUFF_SIZE];
  double value = 123.0;
  s21_sprintf(s21_buff, "ab %#10f cd", value);
  sprintf(std_buff, "ab %#10f cd", value);
  ck_assert_str_eq(s21_buff, std_buff);
}
END_TEST

START_TEST(test_sprtinf_hash_e) {
  char s21_buff[BUFF_SIZE], std_buff[BUFF_SIZE];
  double value = 123.0;
  s21_sprintf(s21_buff, "ab %#10e cd", value);
  sprintf(std_buff, "ab %#10e cd", value);
  ck_assert_str_eq(s21_buff, std_buff);
}
END_TEST

START_TEST(test_sprtinf_hash_g) {
  char s21_buff[BUFF_SIZE], std_buff[BUFF_SIZE];
  double value = 123.0;
  s21_sprintf(s21_buff, "ab %#10g cd", value);
  sprintf(std_buff, "ab %#10g cd", value);
  ck_assert_str_eq(s21_buff, std_buff);
}
END_TEST

/* '0' flag (zero padding) */
START_TEST(test_sprtinf_zero_d_positive) {
  char s21_buff[BUFF_SIZE], std_buff[BUFF_SIZE];
  int value = 123;
  s21_sprintf(s21_buff, "ab %010d cd", value);
  sprintf(std_buff, "ab %010d cd", value);
  ck_assert_str_eq(s21_buff, std_buff);
}
END_TEST

START_TEST(test_sprtinf_zero_d_negative) {
  char s21_buff[BUFF_SIZE], std_buff[BUFF_SIZE];
  int value = -123;
  s21_sprintf(s21_buff, "ab %010d cd", value);
  sprintf(std_buff, "ab %010d cd", value);
  ck_assert_str_eq(s21_buff, std_buff);
}
END_TEST

START_TEST(test_sprtinf_zero_f) {
  char s21_buff[BUFF_SIZE], std_buff[BUFF_SIZE];
  double value = 123.456;
  s21_sprintf(s21_buff, "ab %010f cd", value);
  sprintf(std_buff, "ab %010f cd", value);
  ck_assert_str_eq(s21_buff, std_buff);
}
END_TEST

/* Combined '-' and '0' flags (left-justify overrides zero padding) */
START_TEST(test_sprtinf_minus_zero_d) {
  char s21_buff[BUFF_SIZE], std_buff[BUFF_SIZE];
  int value = 123;
  s21_sprintf(s21_buff, "ab %-010d cd", value);
  sprintf(std_buff, "ab %-010d cd", value);
  ck_assert_str_eq(s21_buff, std_buff);
}
END_TEST

Suite *sprintf_suite(void) {
  Suite *s = suite_create("s21_sprintf");
  TCase *tc = tcase_create("Core");

  /* Add original '+' flag tests */
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
  tcase_add_test(tc, test_sprtinf_percent);

  /* Add new flag tests */
  tcase_add_test(tc, test_sprtinf_minus_d);
  tcase_add_test(tc, test_sprtinf_minus_f);
  tcase_add_test(tc, test_sprtinf_minus_s);
  tcase_add_test(tc, test_sprtinf_space_d_positive);
  tcase_add_test(tc, test_sprtinf_space_d_negative);
  tcase_add_test(tc, test_sprtinf_hash_o);
  tcase_add_test(tc, test_sprtinf_hash_x);
  tcase_add_test(tc, test_sprtinf_hash_X);
  tcase_add_test(tc, test_sprtinf_hash_f);
  tcase_add_test(tc, test_sprtinf_hash_e);
  tcase_add_test(tc, test_sprtinf_hash_g);
  tcase_add_test(tc, test_sprtinf_zero_d_positive);
  tcase_add_test(tc, test_sprtinf_zero_d_negative);
  tcase_add_test(tc, test_sprtinf_zero_f);
  tcase_add_test(tc, test_sprtinf_minus_zero_d);

  suite_add_tcase(s, tc);
  return s;
}

int main(void) {
  int fails;
  Suite *s = sprintf_suite();
  SRunner *sr = srunner_create(s);

  srunner_run_all(sr, CK_VERBOSE);
  fails = srunner_ntests_failed(sr);
  srunner_free(sr);

  return (fails == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
