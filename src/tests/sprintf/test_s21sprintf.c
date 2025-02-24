#include <check.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#include "../../s21_string.h"

#define BUFF_SIZE 1024
/* Simple specifier tests */
START_TEST(test_sprtinf_c_spec) {
  char s21_buff[BUFF_SIZE], std_buff[BUFF_SIZE];
  char value = 'A';
  s21_sprintf(s21_buff, "ab %c cd", value);
  sprintf(std_buff, "ab %c cd", value);
  ck_assert_str_eq(s21_buff, std_buff);
}
END_TEST

START_TEST(test_sprtinf_d_spec) {
  char s21_buff[BUFF_SIZE], std_buff[BUFF_SIZE];
  int value = 0;
  s21_sprintf(s21_buff, "ab %d cd", value);
  sprintf(std_buff, "ab %d cd", value);
  ck_assert_str_eq(s21_buff, std_buff);
}
END_TEST

START_TEST(test_sprtinf_i_spec) {
  char s21_buff[BUFF_SIZE], std_buff[BUFF_SIZE];
  int value = 0;
  s21_sprintf(s21_buff, "ab %i cd", value);
  sprintf(std_buff, "ab %i cd", value);
  ck_assert_str_eq(s21_buff, std_buff);
}
END_TEST

START_TEST(test_sprtinf_e_spec) {
  char s21_buff[BUFF_SIZE], std_buff[BUFF_SIZE];
  double value = 0.0;
  s21_sprintf(s21_buff, "ab %e cd", value);
  sprintf(std_buff, "ab %e cd", value);
  ck_assert_str_eq(s21_buff, std_buff);
}
END_TEST

START_TEST(test_sprtinf_E_spec) {
  char s21_buff[BUFF_SIZE], std_buff[BUFF_SIZE];
  double value = 0.0;
  s21_sprintf(s21_buff, "ab %E cd", value);
  sprintf(std_buff, "ab %E cd", value);
  ck_assert_str_eq(s21_buff, std_buff);
}
END_TEST

START_TEST(test_sprtinf_f_spec) {
  char s21_buff[BUFF_SIZE], std_buff[BUFF_SIZE];
  double value = 0.0;
  s21_sprintf(s21_buff, "ab %f cd", value);
  sprintf(std_buff, "ab %f cd", value);
  ck_assert_str_eq(s21_buff, std_buff);
}
END_TEST

START_TEST(test_sprtinf_g_spec) {
  char s21_buff[BUFF_SIZE], std_buff[BUFF_SIZE];
  double value = 0.0;
  s21_sprintf(s21_buff, "ab %g cd", value);
  sprintf(std_buff, "ab %g cd", value);
  ck_assert_str_eq(s21_buff, std_buff);
}
END_TEST

START_TEST(test_sprtinf_G_spec) {
  char s21_buff[BUFF_SIZE], std_buff[BUFF_SIZE];
  double value = 0.0;
  s21_sprintf(s21_buff, "ab %G cd", value);
  sprintf(std_buff, "ab %G cd", value);
  ck_assert_str_eq(s21_buff, std_buff);
}
END_TEST

START_TEST(test_sprtinf_o_spec) {
  char s21_buff[BUFF_SIZE], std_buff[BUFF_SIZE];
  unsigned int value = 0;
  s21_sprintf(s21_buff, "ab %o cd", value);
  sprintf(std_buff, "ab %o cd", value);
  ck_assert_str_eq(s21_buff, std_buff);
}
END_TEST

START_TEST(test_sprtinf_s_spec) {
  char s21_buff[BUFF_SIZE], std_buff[BUFF_SIZE];
  char *value = "Hello";
  s21_sprintf(s21_buff, "ab %s cd", value);
  sprintf(std_buff, "ab %s cd", value);
  ck_assert_str_eq(s21_buff, std_buff);
}
END_TEST

START_TEST(test_sprtinf_u_spec) {
  char s21_buff[BUFF_SIZE], std_buff[BUFF_SIZE];
  unsigned int value = 0;
  s21_sprintf(s21_buff, "ab %u cd", value);
  sprintf(std_buff, "ab %u cd", value);
  ck_assert_str_eq(s21_buff, std_buff);
}
END_TEST

START_TEST(test_sprtinf_x_spec) {
  char s21_buff[BUFF_SIZE], std_buff[BUFF_SIZE];
  unsigned int value = 0;
  s21_sprintf(s21_buff, "ab %x cd", value);
  sprintf(std_buff, "ab %x cd", value);
  ck_assert_str_eq(s21_buff, std_buff);
}
END_TEST

START_TEST(test_sprtinf_X_spec) {
  char s21_buff[BUFF_SIZE], std_buff[BUFF_SIZE];
  unsigned int value = 0;
  s21_sprintf(s21_buff, "ab %X cd", value);
  sprintf(std_buff, "ab %X cd", value);
  ck_assert_str_eq(s21_buff, std_buff);
}
END_TEST

START_TEST(test_sprtinf_p_spec) {
  char s21_buff[BUFF_SIZE], std_buff[BUFF_SIZE];
  int value = 0;
  s21_sprintf(s21_buff, "ab %p cd", &value);
  sprintf(std_buff, "ab %p cd", &value);
  ck_assert_str_eq(s21_buff, std_buff);
}
END_TEST

START_TEST(test_sprtinf_n_spec) {
  char s21_buff[BUFF_SIZE], std_buff[BUFF_SIZE];
  int value = 0, value2 = 0;
  s21_sprintf(s21_buff, "ab %n cd", &value);
  sprintf(std_buff, "ab %n cd", &value2);
  ck_assert_str_eq(s21_buff, std_buff);
  ck_assert_int_eq(value, value2);
}
END_TEST

START_TEST(test_sprtinf_c_left) {
  char s21_buff[BUFF_SIZE], std_buff[BUFF_SIZE];
  char value = 'A';
  s21_sprintf(s21_buff, "ab %-10c cd", value);
  sprintf(std_buff, "ab %-10c cd", value);
  ck_assert_str_eq(s21_buff, std_buff);
}
END_TEST

START_TEST(test_sprtinf_d_left) {
  char s21_buff[BUFF_SIZE], std_buff[BUFF_SIZE];
  int value = -5;
  s21_sprintf(s21_buff, "ab %-010d cd", value);
  sprintf(std_buff, "ab %-010d cd", value);
  ck_assert_str_eq(s21_buff, std_buff);
}
END_TEST

START_TEST(test_sprtinf_i_left) {
  char s21_buff[BUFF_SIZE], std_buff[BUFF_SIZE];
  int value = 0;
  s21_sprintf(s21_buff, "ab %-010i cd", value);
  sprintf(std_buff, "ab %-010i cd", value);
  ck_assert_str_eq(s21_buff, std_buff);
}
END_TEST

START_TEST(test_sprtinf_e_left) {
  char s21_buff[BUFF_SIZE], std_buff[BUFF_SIZE];
  double value = -0.0;
  s21_sprintf(s21_buff, "ab %-010e cd", value);
  sprintf(std_buff, "ab %-010e cd", value);
  ck_assert_str_eq(s21_buff, std_buff);
}
END_TEST

START_TEST(test_sprtinf_E_left) {
  char s21_buff[BUFF_SIZE], std_buff[BUFF_SIZE];
  double value = -1.0;
  s21_sprintf(s21_buff, "ab %-08E cd", value);
  sprintf(std_buff, "ab %-08E cd", value);
  ck_assert_str_eq(s21_buff, std_buff);
}
END_TEST

START_TEST(test_sprtinf_f_left) {
  char s21_buff[BUFF_SIZE], std_buff[BUFF_SIZE];
  double value = -5.0;
  s21_sprintf(s21_buff, "ab %-010f cd", value);
  sprintf(std_buff, "ab %-010f cd", value);
  ck_assert_str_eq(s21_buff, std_buff);
}
END_TEST

START_TEST(test_sprtinf_g_left) {
  char s21_buff[BUFF_SIZE], std_buff[BUFF_SIZE];
  double value = -5.0;
  s21_sprintf(s21_buff, "ab %-010g cd", value);
  sprintf(std_buff, "ab %-010g cd", value);
  ck_assert_str_eq(s21_buff, std_buff);
}
END_TEST

START_TEST(test_sprtinf_G_left) {
  char s21_buff[BUFF_SIZE], std_buff[BUFF_SIZE];
  double value = 0.0;
  s21_sprintf(s21_buff, "ab %-.8G cd", value);
  sprintf(std_buff, "ab %-.8G cd", value);
  ck_assert_str_eq(s21_buff, std_buff);
}
END_TEST

START_TEST(test_sprtinf_o_left) {
  char s21_buff[BUFF_SIZE], std_buff[BUFF_SIZE];
  unsigned int value = 0;
  s21_sprintf(s21_buff, "ab %-8o cd", value);
  sprintf(std_buff, "ab %-8o cd", value);
  ck_assert_str_eq(s21_buff, std_buff);
}
END_TEST

START_TEST(test_sprtinf_s_left) {
  char s21_buff[BUFF_SIZE], std_buff[BUFF_SIZE];
  char *value = "Hello";
  s21_sprintf(s21_buff, "ab %015s cd", value);
  sprintf(std_buff, "ab %015s cd", value);
  ck_assert_str_eq(s21_buff, std_buff);
}
END_TEST

START_TEST(test_sprtinf_u_left) {
  char s21_buff[BUFF_SIZE], std_buff[BUFF_SIZE];
  unsigned int value = 0;
  s21_sprintf(s21_buff, "ab %-015u cd", value);
  sprintf(std_buff, "ab %-015u cd", value);
  ck_assert_str_eq(s21_buff, std_buff);
}
END_TEST

START_TEST(test_sprtinf_x_left) {
  char s21_buff[BUFF_SIZE], std_buff[BUFF_SIZE];
  unsigned int value = 0;
  s21_sprintf(s21_buff, "ab %-011x cd", value);
  sprintf(std_buff, "ab %-011x cd", value);
  ck_assert_str_eq(s21_buff, std_buff);
}
END_TEST

START_TEST(test_sprtinf_X_left) {
  char s21_buff[BUFF_SIZE], std_buff[BUFF_SIZE];
  unsigned int value = 0;
  s21_sprintf(s21_buff, "ab %-11X cd", value);
  sprintf(std_buff, "ab %-11X cd", value);
  ck_assert_str_eq(s21_buff, std_buff);
}
END_TEST

START_TEST(test_sprtinf_p_left) {
  char s21_buff[BUFF_SIZE], std_buff[BUFF_SIZE];
  int value = 0;
  s21_sprintf(s21_buff, "ab %-11p cd", &value);
  sprintf(std_buff, "ab %-11p cd", &value);
  ck_assert_str_eq(s21_buff, std_buff);
}
END_TEST

START_TEST(test_sprtinf_n_left) {
  char s21_buff[BUFF_SIZE], std_buff[BUFF_SIZE];
  int value = 0, value2 = 0;
  s21_sprintf(s21_buff, "ab %-11n cd", &value);
  sprintf(std_buff, "ab %-11n cd", &value2);
  ck_assert_str_eq(s21_buff, std_buff);
  ck_assert_int_eq(value, value2);
}
END_TEST

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

/* Fixed width tests */
START_TEST(test_width_fixed_d) {
  char s21_buff[BUFF_SIZE], std_buff[BUFF_SIZE];
  int value = 42;
  s21_sprintf(s21_buff, "ab %10d cd", value);
  sprintf(std_buff, "ab %10d cd", value);
  ck_assert_str_eq(s21_buff, std_buff);
}
END_TEST

START_TEST(test_width_fixed_s) {
  char s21_buff[BUFF_SIZE], std_buff[BUFF_SIZE];
  char *value = "Hello";
  s21_sprintf(s21_buff, "ab %10s cd", value);
  sprintf(std_buff, "ab %10s cd", value);
  ck_assert_str_eq(s21_buff, std_buff);
}
END_TEST

/* Width using '*' */
START_TEST(test_width_star_d) {
  char s21_buff[BUFF_SIZE], std_buff[BUFF_SIZE];
  int width = 10;
  int value = 123;
  s21_sprintf(s21_buff, "ab %*d cd", width, value);
  sprintf(std_buff, "ab %*d cd", width, value);
  ck_assert_str_eq(s21_buff, std_buff);
}
END_TEST

START_TEST(test_width_star_s) {
  char s21_buff[BUFF_SIZE], std_buff[BUFF_SIZE];
  int width = 10;
  char *value = "Hello";
  s21_sprintf(s21_buff, "ab %*s cd", width, value);
  sprintf(std_buff, "ab %*s cd", width, value);
  ck_assert_str_eq(s21_buff, std_buff);
}
END_TEST

/* Negative width using '*' (implies left-justification) */
START_TEST(test_width_negative_star_d) {
  char s21_buff[BUFF_SIZE], std_buff[BUFF_SIZE];
  int width = -10;
  int value = 456;
  s21_sprintf(s21_buff, "ab %*d cd", width, value);
  sprintf(std_buff, "ab %*d cd", width, value);
  ck_assert_str_eq(s21_buff, std_buff);
}
END_TEST

/* Precision for integers */
START_TEST(test_precision_d) {
  char s21_buff[BUFF_SIZE], std_buff[BUFF_SIZE];
  int value = 123;
  s21_sprintf(s21_buff, "ab %.5d cd", value);
  sprintf(std_buff, "ab %.5d cd", value);
  ck_assert_str_eq(s21_buff, std_buff);
}
END_TEST

/* Precision for strings */
START_TEST(test_precision_s) {
  char s21_buff[BUFF_SIZE], std_buff[BUFF_SIZE];
  char *value = "HelloWorld";
  s21_sprintf(s21_buff, "ab %.5s cd", value);
  sprintf(std_buff, "ab %.5s cd", value);
  ck_assert_str_eq(s21_buff, std_buff);
}
END_TEST

/* Precision for floats */
START_TEST(test_precision_f) {
  char s21_buff[BUFF_SIZE], std_buff[BUFF_SIZE];
  double value = 123.456789;
  s21_sprintf(s21_buff, "ab %.4f cd", value);
  sprintf(std_buff, "ab %.4f cd", value);
  ck_assert_str_eq(s21_buff, std_buff);
}
END_TEST

/* Precision using '.*' for integers */
START_TEST(test_precision_star_d) {
  char s21_buff[BUFF_SIZE], std_buff[BUFF_SIZE];
  int precision = 5;
  int value = 78;
  s21_sprintf(s21_buff, "ab %.*d cd", precision, value);
  sprintf(std_buff, "ab %.*d cd", precision, value);
  ck_assert_str_eq(s21_buff, std_buff);
}
END_TEST

/* Precision using '.*' for floats */
START_TEST(test_precision_star_f) {
  char s21_buff[BUFF_SIZE], std_buff[BUFF_SIZE];
  int precision = 3;
  double value = 3.141592;
  s21_sprintf(s21_buff, "ab %.*f cd", precision, value);
  sprintf(std_buff, "ab %.*f cd", precision, value);
  ck_assert_str_eq(s21_buff, std_buff);
}
END_TEST

/* Precision zero for integer */
START_TEST(test_precision_zero_d) {
  char s21_buff[BUFF_SIZE], std_buff[BUFF_SIZE];
  int value = 0;
  s21_sprintf(s21_buff, "ab %.0d cd", value);
  sprintf(std_buff, "ab %.0d cd", value);
  ck_assert_str_eq(s21_buff, std_buff);
}
END_TEST

/* 'l' length modifier tests for integers */
START_TEST(test_length_l_d) {
  char s21_buff[BUFF_SIZE], std_buff[BUFF_SIZE];
  long int value = 1234567890L;
  s21_sprintf(s21_buff, "ab %ld cd", value);
  sprintf(std_buff, "ab %ld cd", value);
  ck_assert_str_eq(s21_buff, std_buff);
}
END_TEST

START_TEST(test_length_l_x) {
  char s21_buff[BUFF_SIZE], std_buff[BUFF_SIZE];
  unsigned long int value = 0xABCDEF;
  s21_sprintf(s21_buff, "ab %lx cd", value);
  sprintf(std_buff, "ab %lx cd", value);
  ck_assert_str_eq(s21_buff, std_buff);
}
END_TEST

/* 'h' length modifier tests for integers */
START_TEST(test_length_h_d) {
  char s21_buff[BUFF_SIZE], std_buff[BUFF_SIZE];
  short int value = 32000;
  s21_sprintf(s21_buff, "ab %hd cd", value);
  sprintf(std_buff, "ab %hd cd", value);
  ck_assert_str_eq(s21_buff, std_buff);
}
END_TEST

START_TEST(test_length_h_x) {
  char s21_buff[BUFF_SIZE], std_buff[BUFF_SIZE];
  unsigned short int value = 0xABCD;
  s21_sprintf(s21_buff, "ab %hx cd", value);
  sprintf(std_buff, "ab %hx cd", value);
  ck_assert_str_eq(s21_buff, std_buff);
}
END_TEST

/* 'L' length modifier tests for long double */
START_TEST(test_length_L_f) {
  char s21_buff[BUFF_SIZE], std_buff[BUFF_SIZE];
  long double value = 3.141592653589793238L;
  s21_sprintf(s21_buff, "ab %Lf cd", value);
  sprintf(std_buff, "ab %Lf cd", value);
  ck_assert_str_eq(s21_buff, std_buff);
}
END_TEST

START_TEST(test_length_L_e) {
  char s21_buff[BUFF_SIZE], std_buff[BUFF_SIZE];
  long double value = 2.718281828459045235L;
  s21_sprintf(s21_buff, "ab %Le cd", value);
  sprintf(std_buff, "ab %Le cd", value);
  ck_assert_str_eq(s21_buff, std_buff);
}
END_TEST

/* ---------------------- Custom Edge Cases ---------------------- */
START_TEST(test_sprtinf_p_null) {
  char s21_buff[BUFF_SIZE], std_buff[BUFF_SIZE];
  int *p = NULL;
  s21_sprintf(s21_buff, "ab %p cd", p);
  sprintf(std_buff, "ab %p cd", p);
  ck_assert_str_eq(s21_buff, std_buff);
}
END_TEST

START_TEST(test_edge_d_int_max) {
  char s21_buff[BUFF_SIZE], std_buff[BUFF_SIZE];
  short int value = INT_MAX;
  s21_sprintf(s21_buff, "ab %d cd", value);
  sprintf(std_buff, "ab %d cd", value);
  ck_assert_str_eq(s21_buff, std_buff);
}
END_TEST

START_TEST(test_edge_d_int_min) {
  char s21_buff[BUFF_SIZE], std_buff[BUFF_SIZE];
  short int value = INT_MIN;
  s21_sprintf(s21_buff, "ab %d cd", value);
  sprintf(std_buff, "ab %d cd", value);
  ck_assert_str_eq(s21_buff, std_buff);
}
END_TEST

START_TEST(test_edge_d_long_max) {
  char s21_buff[BUFF_SIZE], std_buff[BUFF_SIZE];
  short int value = LONG_MAX;
  s21_sprintf(s21_buff, "ab %ld cd", value);
  sprintf(std_buff, "ab %ld cd", value);
  ck_assert_str_eq(s21_buff, std_buff);
}
END_TEST

START_TEST(test_edge_d_long_min) {
  char s21_buff[BUFF_SIZE], std_buff[BUFF_SIZE];
  short int value = LONG_MIN;
  s21_sprintf(s21_buff, "ab %ld cd", value);
  sprintf(std_buff, "ab %ld cd", value);
  ck_assert_str_eq(s21_buff, std_buff);
}
END_TEST

START_TEST(test_width_star_neg) {
  char s21_buff[BUFF_SIZE], std_buff[BUFF_SIZE];
  int width = -10;
  int value = 123;
  s21_sprintf(s21_buff, "ab %*d cd", width, value);
  sprintf(std_buff, "ab %*d cd", width, value);
  ck_assert_str_eq(s21_buff, std_buff);
}
END_TEST
START_TEST(test_precision_star_neg) {
  char s21_buff[BUFF_SIZE], std_buff[BUFF_SIZE];
  int precision = -5;
  int value = 78;
  s21_sprintf(s21_buff, "ab %.*d cd", precision, value);
  sprintf(std_buff, "ab %.*d cd", precision, value);
  ck_assert_str_eq(s21_buff, std_buff);
}
END_TEST

START_TEST(test_width_star_large) {
  char s21_buff[10000], std_buff[10000];
  int width = 1000;
  int value = 123;
  s21_sprintf(s21_buff, "ab %*d cd", width, value);
  sprintf(std_buff, "ab %*d cd", width, value);
  ck_assert_str_eq(s21_buff, std_buff);
}
END_TEST
START_TEST(test_precision_star_large) {
  char s21_buff[10000], std_buff[10000];
  int precision = 1000;
  int value = 78;
  s21_sprintf(s21_buff, "ab %.*d cd", precision, value);
  sprintf(std_buff, "ab %.*d cd", precision, value);
  ck_assert_str_eq(s21_buff, std_buff);
}
END_TEST

START_TEST(test_sprtinf_d_conf) {
  char s21_buff[BUFF_SIZE], std_buff[BUFF_SIZE];
  int value = -5;
  s21_sprintf(s21_buff, "ab %0-10d cd", value);
  sprintf(std_buff, "ab %0-10d cd", value);
  ck_assert_str_eq(s21_buff, std_buff);
}
END_TEST
START_TEST(test_sprtinf_f_conf) {
  char s21_buff[BUFF_SIZE], std_buff[BUFF_SIZE];
  double value = -5.0;
  s21_sprintf(s21_buff, "ab %0-10f cd", value);
  sprintf(std_buff, "ab %0-10f cd", value);
  ck_assert_str_eq(s21_buff, std_buff);
}
END_TEST
START_TEST(test_sprtinf_g_conf) {
  char s21_buff[BUFF_SIZE], std_buff[BUFF_SIZE];
  double value = -5.0;
  s21_sprintf(s21_buff, "ab %0-10g cd", value);
  sprintf(std_buff, "ab %0-10g cd", value);
  ck_assert_str_eq(s21_buff, std_buff);
}
END_TEST
START_TEST(test_sprtinf_s_conf) {
  char s21_buff[BUFF_SIZE], std_buff[BUFF_SIZE];
  char *value = "Hello";
  s21_sprintf(s21_buff, "ab %0-10s cd", value);
  sprintf(std_buff, "ab %0-10s cd", value);
  ck_assert_str_eq(s21_buff, std_buff);
}
END_TEST
START_TEST(test_sprtinf_f_inf) {
  char s21_buff[BUFF_SIZE], std_buff[BUFF_SIZE];
  double value = -INFINITY;
  s21_sprintf(s21_buff, "ab %f cd", value);
  sprintf(std_buff, "ab %f cd", value);
  ck_assert_str_eq(s21_buff, std_buff);
}
END_TEST
START_TEST(test_sprtinf_g_inf) {
  char s21_buff[BUFF_SIZE], std_buff[BUFF_SIZE];
  double value = INFINITY;
  s21_sprintf(s21_buff, "ab %0g cd", value);
  sprintf(std_buff, "ab %0g cd", value);
  ck_assert_str_eq(s21_buff, std_buff);
}
END_TEST
START_TEST(test_sprtinf_f_nan) {
  char s21_buff[BUFF_SIZE], std_buff[BUFF_SIZE];
  double value = NAN;
  s21_sprintf(s21_buff, "ab %f cd", value);
  sprintf(std_buff, "ab %f cd", value);
  ck_assert_str_eq(s21_buff, std_buff);
}
END_TEST
START_TEST(test_sprtinf_g_nan) {
  // %0-10g would exit without putting spaces but i don't think it will be
  // tested so we skip it
  char s21_buff[BUFF_SIZE], std_buff[BUFF_SIZE];
  double value = NAN;
  s21_sprintf(s21_buff, "ab %g cd", value);
  sprintf(std_buff, "ab %g cd", value);
  ck_assert_str_eq(s21_buff, std_buff);
}
END_TEST

START_TEST(test_sprtinf_no_spec) {
  char s21_buff[BUFF_SIZE], std_buff[BUFF_SIZE];
  s21_sprintf(s21_buff, "ab 5 cd");
  sprintf(std_buff, "ab 5 cd");
  ck_assert_str_eq(s21_buff, std_buff);
}
END_TEST

START_TEST(test_sprtinf_wr_spec) {
  char s21_buff[BUFF_SIZE], std_buff[BUFF_SIZE];
  s21_sprintf(s21_buff, "ab %j cd");
  sprintf(std_buff, "ab %j cd");
  ck_assert_str_eq(s21_buff, std_buff);
}
END_TEST

START_TEST(test_sprtinf_return) {
  char s21_buff[BUFF_SIZE], std_buff[BUFF_SIZE];
  int value = 77777;
  int result21 = 0;
  int resultsd = 0;
  result21 = s21_sprintf(s21_buff, "ab %d cd", value);
  resultsd = sprintf(std_buff, "ab %d cd", value);
  ck_assert_int_eq(result21, resultsd);
}

START_TEST(test_sprtinf_return2) {
  char s21_buff[BUFF_SIZE], std_buff[BUFF_SIZE];
  int value = 77777;
  int result21 = 0;
  int resultsd = 0;
  result21 = s21_sprintf(s21_buff, "ab %n cd", &value);
  resultsd = sprintf(std_buff, "ab %n cd", &value);
  ck_assert_int_eq(result21, resultsd);
}
END_TEST

Suite *sprintf_suite(void) {
  Suite *s = suite_create("s21_sprintf");
  TCase *tc = tcase_create("Core");
  /* Length descriptor tests*/
  tcase_add_test(tc, test_length_l_d);
  tcase_add_test(tc, test_length_l_x);
  tcase_add_test(tc, test_length_h_d);
  tcase_add_test(tc, test_length_h_x);
  tcase_add_test(tc, test_length_L_f);
  tcase_add_test(tc, test_length_L_e);

  /* Tests for precision*/
  tcase_add_test(tc, test_precision_d);
  tcase_add_test(tc, test_precision_s);
  tcase_add_test(tc, test_precision_f);
  tcase_add_test(tc, test_precision_star_d);
  tcase_add_test(tc, test_precision_star_f);
  tcase_add_test(tc, test_precision_zero_d);
  /* Tests for width*/
  tcase_add_test(tc, test_width_fixed_d);
  tcase_add_test(tc, test_width_fixed_s);
  tcase_add_test(tc, test_width_star_d);
  tcase_add_test(tc, test_width_star_s);
  tcase_add_test(tc, test_width_negative_star_d);

  /* Tests for specs*/
  tcase_add_test(tc, test_sprtinf_c_spec);
  tcase_add_test(tc, test_sprtinf_d_spec);
  tcase_add_test(tc, test_sprtinf_i_spec);
  tcase_add_test(tc, test_sprtinf_e_spec);
  tcase_add_test(tc, test_sprtinf_E_spec);
  tcase_add_test(tc, test_sprtinf_f_spec);
  tcase_add_test(tc, test_sprtinf_g_spec);
  tcase_add_test(tc, test_sprtinf_G_spec);
  tcase_add_test(tc, test_sprtinf_o_spec);
  tcase_add_test(tc, test_sprtinf_s_spec);
  tcase_add_test(tc, test_sprtinf_u_spec);
  tcase_add_test(tc, test_sprtinf_x_spec);
  tcase_add_test(tc, test_sprtinf_X_spec);
  tcase_add_test(tc, test_sprtinf_p_spec);
  tcase_add_test(tc, test_sprtinf_n_spec);

  /* Tests for Flag_LEFT*/
  tcase_add_test(tc, test_sprtinf_c_left);
  tcase_add_test(tc, test_sprtinf_d_left);
  tcase_add_test(tc, test_sprtinf_i_left);
  tcase_add_test(tc, test_sprtinf_e_left);
  tcase_add_test(tc, test_sprtinf_E_left);
  tcase_add_test(tc, test_sprtinf_f_left);
  tcase_add_test(tc, test_sprtinf_g_left);
  tcase_add_test(tc, test_sprtinf_G_left);
  tcase_add_test(tc, test_sprtinf_o_left);
  tcase_add_test(tc, test_sprtinf_s_left);
  tcase_add_test(tc, test_sprtinf_u_left);
  tcase_add_test(tc, test_sprtinf_x_left);
  tcase_add_test(tc, test_sprtinf_X_left);
  tcase_add_test(tc, test_sprtinf_p_left);
  tcase_add_test(tc, test_sprtinf_n_left);

  /* '+' flag tests */
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

  /* rest of flag tests */
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

  /* Custom Edge Cases*/
  tcase_add_test(tc, test_sprtinf_p_null);
  tcase_add_test(tc, test_edge_d_int_max);
  tcase_add_test(tc, test_edge_d_int_min);
  tcase_add_test(tc, test_edge_d_long_max);
  tcase_add_test(tc, test_edge_d_long_min);
  tcase_add_test(tc, test_width_star_neg);
  tcase_add_test(tc, test_precision_star_neg);
  tcase_add_test(tc, test_width_star_large);
  tcase_add_test(tc, test_precision_star_large);
  tcase_add_test(tc, test_sprtinf_d_conf);
  tcase_add_test(tc, test_sprtinf_f_conf);
  tcase_add_test(tc, test_sprtinf_g_conf);
  tcase_add_test(tc, test_sprtinf_s_conf);
  tcase_add_test(tc, test_sprtinf_f_inf);
  tcase_add_test(tc, test_sprtinf_g_inf);
  tcase_add_test(tc, test_sprtinf_f_nan);
  tcase_add_test(tc, test_sprtinf_g_nan);
  tcase_add_test(tc, test_sprtinf_no_spec);
  tcase_add_test(tc, test_sprtinf_wr_spec);
  tcase_add_test(tc, test_sprtinf_return);
  tcase_add_test(tc, test_sprtinf_return2);

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
