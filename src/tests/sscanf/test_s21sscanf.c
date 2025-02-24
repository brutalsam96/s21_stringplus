#include <check.h>
#include <stdio.h>
#include <stdlib.h>
#include "../../s21_sscanf.h"

#define BUFF_SIZE 1024

// %c specifer
START_TEST(test_sscanf_c_spec) {
    char input[] = "ab A cd";
    char s21_value = 0, std_value = 0;

    s21_sscanf(input, "ab %c cd", &s21_value);
    sscanf(input, "ab %c cd", &std_value);

    ck_assert_int_eq(s21_value, std_value);
}
END_TEST

START_TEST(test_sscanf_c_single_char) {
    char input[] = "X";
    char s21_value = 0, std_value = 0;

    s21_sscanf(input, "%c", &s21_value);
    sscanf(input, "%c", &std_value);

    ck_assert_int_eq(s21_value, std_value);
}
END_TEST

START_TEST(test_sscanf_c_with_leading_spaces) {
    char input[] = "   A";
    char s21_value = 0, std_value = 0;

    s21_sscanf(input, " %c", &s21_value);
    sscanf(input, " %c", &std_value);

    ck_assert_int_eq(s21_value, std_value);
}
END_TEST

START_TEST(test_sscanf_c_with_trailing_spaces) {
    char input[] = "A   ";
    char s21_value = 0, std_value = 0;

    s21_sscanf(input, "%c ", &s21_value);
    sscanf(input, "%c ", &std_value);

    ck_assert_int_eq(s21_value, std_value);
}
END_TEST

START_TEST(test_sscanf_c_multiple_chars) {
    char input[] = "X Y Z";
    char s21_value1 = 0, s21_value2 = 0, s21_value3 = 0;
    char std_value1 = 0, std_value2 = 0, std_value3 = 0;

    s21_sscanf(input, "%c %c %c", &s21_value1, &s21_value2, &s21_value3);
    sscanf(input, "%c %c %c", &std_value1, &std_value2, &std_value3);

    ck_assert_int_eq(s21_value1, std_value1);
    ck_assert_int_eq(s21_value2, std_value2);
    ck_assert_int_eq(s21_value3, std_value3);
}
END_TEST

START_TEST(test_sscanf_c_newline_character) {
    char input[] = "\n";
    char s21_value = 0, std_value = 0;

    s21_sscanf(input, "%c", &s21_value);
    sscanf(input, "%c", &std_value);

    ck_assert_int_eq(s21_value, std_value);
}
END_TEST

START_TEST(test_sscanf_c_tab_character) {
    char input[] = "\t";
    char s21_value = 0, std_value = 0;

    s21_sscanf(input, "%c", &s21_value);
    sscanf(input, "%c", &std_value);

    ck_assert_int_eq(s21_value, std_value);
}
END_TEST

START_TEST(test_sscanf_c_special_character) {
    char input[] = "@";
    char s21_value = 0, std_value = 0;

    s21_sscanf(input, "%c", &s21_value);
    sscanf(input, "%c", &std_value);

    ck_assert_int_eq(s21_value, std_value);
}
END_TEST

START_TEST(test_sscanf_c_numeric_character) {
    char input[] = "9";
    char s21_value = 0, std_value = 0;

    s21_sscanf(input, "%c", &s21_value);
    sscanf(input, "%c", &std_value);

    ck_assert_int_eq(s21_value, std_value);
}
END_TEST

START_TEST(test_sscanf_c_with_format_string) {
    char input[] = "abXcd";
    char s21_value = 0, std_value = 0;

    s21_sscanf(input, "ab%ccd", &s21_value);
    sscanf(input, "ab%ccd", &std_value);

    ck_assert_int_eq(s21_value, std_value);
}
END_TEST

// %d specifier

START_TEST(test_sscanf_d_positive_number) {
    char input[] = "123";
    int s21_value = 0, std_value = 0;

    s21_sscanf(input, "%d", &s21_value);
    sscanf(input, "%d", &std_value);

    ck_assert_int_eq(s21_value, std_value);
}
END_TEST

START_TEST(test_sscanf_d_negative_number) {
    char input[] = "-456";
    int s21_value = 0, std_value = 0;

    s21_sscanf(input, "%d", &s21_value);
    sscanf(input, "%d", &std_value);

    ck_assert_int_eq(s21_value, std_value);
}
END_TEST

START_TEST(test_sscanf_d_zero) {
    char input[] = "0";
    int s21_value = 0, std_value = 0;

    s21_sscanf(input, "%d", &s21_value);
    sscanf(input, "%d", &std_value);

    ck_assert_int_eq(s21_value, std_value);
}
END_TEST

START_TEST(test_sscanf_d_with_leading_spaces) {
    char input[] = "   789";
    int s21_value = 0, std_value = 0;

    s21_sscanf(input, "%d", &s21_value);
    sscanf(input, "%d", &std_value);

    ck_assert_int_eq(s21_value, std_value);
}
END_TEST

START_TEST(test_sscanf_d_multiple_numbers) {
    char input[] = "10 20 30";
    int s21_value1 = 0, s21_value2 = 0, s21_value3 = 0;
    int std_value1 = 0, std_value2 = 0, std_value3 = 0;

    s21_sscanf(input, "%d %d %d", &s21_value1, &s21_value2, &s21_value3);
    sscanf(input, "%d %d %d", &std_value1, &std_value2, &std_value3);

    ck_assert_int_eq(s21_value1, std_value1);
    ck_assert_int_eq(s21_value2, std_value2);
    ck_assert_int_eq(s21_value3, std_value3);
}
END_TEST

START_TEST(test_sscanf_d_number_with_trailing_text) {
    char input[] = "999abc";
    int s21_value = 0, std_value = 0;

    s21_sscanf(input, "%d", &s21_value);
    sscanf(input, "%d", &std_value);

    ck_assert_int_eq(s21_value, std_value);
}
END_TEST

START_TEST(test_sscanf_d_with_format_string) {
    char input[] = "Value: 42";
    int s21_value = 0, std_value = 0;

    s21_sscanf(input, "Value: %d", &s21_value);
    sscanf(input, "Value: %d", &std_value);

    ck_assert_int_eq(s21_value, std_value);
}
END_TEST

START_TEST(test_sscanf_d_large_number) {
    char input[] = "2147483647";
    int s21_value = 0, std_value = 0;

    s21_sscanf(input, "%d", &s21_value);
    sscanf(input, "%d", &std_value);

    ck_assert_int_eq(s21_value, std_value);
}
END_TEST

START_TEST(test_sscanf_d_small_number) {
    char input[] = "-2147483648";
    int s21_value = 0, std_value = 0;

    s21_sscanf(input, "%d", &s21_value);
    sscanf(input, "%d", &std_value);

    ck_assert_int_eq(s21_value, std_value);
}
END_TEST

START_TEST(test_sscanf_d_invalid_input) {
    char input[] = "abc";
    int s21_value = 0, std_value = 0;
    int s21_ret = s21_sscanf(input, "%d", &s21_value);
    int std_ret = sscanf(input, "%d", &std_value);

    ck_assert_int_eq(s21_ret, std_ret);
    ck_assert_int_eq(s21_value, std_value);
}
END_TEST

START_TEST(test_sscanf_d_with_plus_sign) {
    char input[] = "+77";
    int s21_value = 0, std_value = 0;

    s21_sscanf(input, "%d", &s21_value);
    sscanf(input, "%d", &std_value);

    ck_assert_int_eq(s21_value, std_value);
}
END_TEST

START_TEST(test_sscanf_d_number_with_extra_spaces) {
    char input[] = "   123   ";
    int s21_value = 0, std_value = 0;

    s21_sscanf(input, " %d ", &s21_value);
    sscanf(input, " %d ", &std_value);

    ck_assert_int_eq(s21_value, std_value);
}
END_TEST

START_TEST(test_sscanf_d_spec) {
    char input[] = "ab 123 cd";
    int s21_value = 0, std_value = 0;

    s21_sscanf(input, "ab %d cd", &s21_value);
    sscanf(input, "ab %d cd", &std_value);

    ck_assert_int_eq(s21_value, std_value);
}
END_TEST



START_TEST(test_sscanf_i_spec) {
    char input[] = "ab 456 cd";
    int s21_value = 0, std_value = 0;

    s21_sscanf(input, "ab %i cd", &s21_value);
    sscanf(input, "ab %i cd", &std_value);

    ck_assert_int_eq(s21_value, std_value);
}
END_TEST

START_TEST(test_sscanf_i_basic) {
    char input[] = "42";
    int s21_value = 0, std_value = 0;

    s21_sscanf(input, "%i", &s21_value);
    sscanf(input, "%i", &std_value);

    ck_assert_int_eq(s21_value, std_value);
}
END_TEST

START_TEST(test_sscanf_i_negative) {
    char input[] = "-123";
    int s21_value = 0, std_value = 0;

    s21_sscanf(input, "%i", &s21_value);
    sscanf(input, "%i", &std_value);

    ck_assert_int_eq(s21_value, std_value);
}
END_TEST

START_TEST(test_sscanf_i_zero) {
    char input[] = "0";
    int s21_value = 0, std_value = 0;

    s21_sscanf(input, "%i", &s21_value);
    sscanf(input, "%i", &std_value);

    ck_assert_int_eq(s21_value, std_value);
}
END_TEST

START_TEST(test_sscanf_i_octal) {
    char input[] = "052";
    int s21_value = 0, std_value = 0;

    s21_sscanf(input, "%i", &s21_value);
    sscanf(input, "%i", &std_value);

    ck_assert_int_eq(s21_value, std_value);
}
END_TEST

START_TEST(test_sscanf_i_hex) {
    char input[] = "0x2A";
    int s21_value = 0, std_value = 0;

    s21_sscanf(input, "%i", &s21_value);
    sscanf(input, "%i", &std_value);

    ck_assert_int_eq(s21_value, std_value);
}
END_TEST

START_TEST(test_sscanf_i_mixed_spaces) {
    char input[] = "  -987   ";
    int s21_value = 0, std_value = 0;

    s21_sscanf(input, "%i", &s21_value);
    sscanf(input, "%i", &std_value);

    ck_assert_int_eq(s21_value, std_value);
}
END_TEST

START_TEST(test_sscanf_i_large_number) {
    char input[] = "2147483647";
    int s21_value = 0, std_value = 0;

    s21_sscanf(input, "%i", &s21_value);
    sscanf(input, "%i", &std_value);

    ck_assert_int_eq(s21_value, std_value);
}
END_TEST

START_TEST(test_sscanf_i_overflow) {
    char input[] = "999999999999999";
    int s21_value = 0, std_value = 0;

    int s21_result = s21_sscanf(input, "%i", &s21_value);
    int std_result = sscanf(input, "%i", &std_value);

    ck_assert_int_eq(s21_result, std_result);
}
END_TEST

START_TEST(test_sscanf_i_invalid) {
    char input[] = "abc123";
    int s21_value = 0, std_value = 0;

    int s21_result = s21_sscanf(input, "%i", &s21_value);
    int std_result = sscanf(input, "%i", &std_value);

    ck_assert_int_eq(s21_result, std_result);
}
END_TEST

START_TEST(test_sscanf_i_multiple_numbers) {
    char input[] = "42 -13 0xF";
    int s21_val1 = 0, s21_val2 = 0, s21_val3 = 0;
    int std_val1 = 0, std_val2 = 0, std_val3 = 0;

    s21_sscanf(input, "%i %i %i", &s21_val1, &s21_val2, &s21_val3);
    sscanf(input, "%i %i %i", &std_val1, &std_val2, &std_val3);

    ck_assert_int_eq(s21_val1, std_val1);
    ck_assert_int_eq(s21_val2, std_val2);
    ck_assert_int_eq(s21_val3, std_val3);
}
END_TEST


START_TEST(test_sscanf_e_basic) {
    char input[] = "3.14e2";
    float s21_value = 0, std_value = 0;

    s21_sscanf(input, "%e", &s21_value);
    sscanf(input, "%e", &std_value);

    ck_assert_float_eq(s21_value, std_value);
}
END_TEST

START_TEST(test_sscanf_e_negative_exponent) {
    char input[] = "3.14e-2";
    float s21_value = 0, std_value = 0;

    s21_sscanf(input, "%e", &s21_value);
    sscanf(input, "%e", &std_value);

    ck_assert_float_eq(s21_value, std_value);
}
END_TEST

START_TEST(test_sscanf_e_large_exponent) {
    char input[] = "1.23e100";
    float s21_value = 0, std_value = 0;

    s21_sscanf(input, "%e", &s21_value);
    sscanf(input, "%e", &std_value);

    ck_assert_float_eq(s21_value, std_value);
}
END_TEST

START_TEST(test_sscanf_e_small_exponent) {
    char input[] = "1.23e-100";
    float s21_value = 0, std_value = 0;

    s21_sscanf(input, "%e", &s21_value);
    sscanf(input, "%e", &std_value);

    ck_assert_float_eq(s21_value, std_value);
}
END_TEST

START_TEST(test_sscanf_e_no_exponent) {
    char input[] = "123.456";
    float s21_value = 0, std_value = 0;

    s21_sscanf(input, "%e", &s21_value);
    sscanf(input, "%e", &std_value);

    ck_assert_float_eq(s21_value, std_value);
}
END_TEST

START_TEST(test_sscanf_e_scientific_notation) {
    char input[] = "1.23E4";
    float s21_value = 0, std_value = 0;

    s21_sscanf(input, "%e", &s21_value);
    sscanf(input, "%e", &std_value);

    ck_assert_float_eq(s21_value, std_value);
}
END_TEST

START_TEST(test_sscanf_e_edge_case_zero) {
    char input[] = "0e0";
    float s21_value = 0, std_value = 0;

    s21_sscanf(input, "%e", &s21_value);
    sscanf(input, "%e", &std_value);

    ck_assert_float_eq(s21_value, std_value);
}
END_TEST

START_TEST(test_sscanf_e_edge_case_negative_zero) {
    char input[] = "-0e0";
    float s21_value = 0, std_value = 0;

    s21_sscanf(input, "%e", &s21_value);
    sscanf(input, "%e", &std_value);

    ck_assert_float_eq(s21_value, std_value);
}
END_TEST

START_TEST(test_sscanf_e_invalid_input) {
    char input[] = "abc123.45e2";
    float s21_value = 0, std_value = 0;

    int s21_result = s21_sscanf(input, "%e", &s21_value);
    int std_result = sscanf(input, "%e", &std_value);

    ck_assert_int_eq(s21_result, std_result);
}
END_TEST

START_TEST(test_sscanf_e_multiple_numbers) {
    char input[] = "3.14e2 -4.56e-3 1.23E4";
    float s21_val1 = 0, s21_val2 = 0, s21_val3 = 0;
    float std_val1 = 0, std_val2 = 0, std_val3 = 0;

    s21_sscanf(input, "%e %e %e", &s21_val1, &s21_val2, &s21_val3);
    sscanf(input, "%e %e %e", &std_val1, &std_val2, &std_val3);

    ck_assert_float_eq(s21_val1, std_val1);
    ck_assert_float_eq(s21_val2, std_val2);
    ck_assert_float_eq(s21_val3, std_val3);
}
END_TEST


START_TEST(test_sscanf_E_basic) {
    char input[] = "3.14E2";
    float s21_value = 0, std_value = 0;

    s21_sscanf(input, "%E", &s21_value);
    sscanf(input, "%E", &std_value);

    ck_assert_float_eq(s21_value, std_value);
}
END_TEST

START_TEST(test_sscanf_E_negative_exponent) {
    char input[] = "3.14E-2";
    float s21_value = 0, std_value = 0;

    s21_sscanf(input, "%E", &s21_value);
    sscanf(input, "%E", &std_value);

    ck_assert_float_eq(s21_value, std_value);
}
END_TEST

START_TEST(test_sscanf_E_large_exponent) {
    char input[] = "1.23E100";
    float s21_value = 0, std_value = 0;

    s21_sscanf(input, "%E", &s21_value);
    sscanf(input, "%E", &std_value);

    ck_assert_float_eq(s21_value, std_value);
}
END_TEST

START_TEST(test_sscanf_E_small_exponent) {
    char input[] = "1.23E-100";
    float s21_value = 0, std_value = 0;

    s21_sscanf(input, "%E", &s21_value);
    sscanf(input, "%E", &std_value);

    ck_assert_float_eq(s21_value, std_value);
}
END_TEST

START_TEST(test_sscanf_E_no_exponent) {
    char input[] = "123.456";
    float s21_value = 0, std_value = 0;

    s21_sscanf(input, "%E", &s21_value);
    sscanf(input, "%E", &std_value);

    ck_assert_float_eq(s21_value, std_value);
}
END_TEST

START_TEST(test_sscanf_E_scientific_notation) {
    char input[] = "1.23E4";
    float s21_value = 0, std_value = 0;

    s21_sscanf(input, "%E", &s21_value);
    sscanf(input, "%E", &std_value);

    ck_assert_float_eq(s21_value, std_value);
}
END_TEST

START_TEST(test_sscanf_E_edge_case_zero) {
    char input[] = "0E0";
    float s21_value = 0, std_value = 0;

    s21_sscanf(input, "%E", &s21_value);
    sscanf(input, "%E", &std_value);

    ck_assert_float_eq(s21_value, std_value);
}
END_TEST

START_TEST(test_sscanf_E_edge_case_negative_zero) {
    char input[] = "-0E0";
    float s21_value = 0, std_value = 0;

    s21_sscanf(input, "%E", &s21_value);
    sscanf(input, "%E", &std_value);

    ck_assert_float_eq(s21_value, std_value);
}
END_TEST

START_TEST(test_sscanf_E_invalid_input) {
    char input[] = "abc123.45E2";
    float s21_value = 0, std_value = 0;

    int s21_result = s21_sscanf(input, "%E", &s21_value);
    int std_result = sscanf(input, "%E", &std_value);

    ck_assert_int_eq(s21_result, std_result);
}
END_TEST

START_TEST(test_sscanf_E_multiple_numbers) {
    char input[] = "3.14E2 -4.56E-3 1.23E4";
    float s21_val1 = 0, s21_val2 = 0, s21_val3 = 0;
    float std_val1 = 0, std_val2 = 0, std_val3 = 0;

    s21_sscanf(input, "%E %E %E", &s21_val1, &s21_val2, &s21_val3);
    sscanf(input, "%E %E %E", &std_val1, &std_val2, &std_val3);

    ck_assert_float_eq(s21_val1, std_val1);
    ck_assert_float_eq(s21_val2, std_val2);
    ck_assert_float_eq(s21_val3, std_val3);
}
END_TEST


START_TEST(test_sscanf_f_basic) {
    char input[] = "3.14";
    float s21_value = 0, std_value = 0;

    s21_sscanf(input, "%f", &s21_value);
    sscanf(input, "%f", &std_value);

    ck_assert_float_eq(s21_value, std_value);
}
END_TEST

START_TEST(test_sscanf_f_negative) {
    char input[] = "-3.14";
    float s21_value = 0, std_value = 0;

    s21_sscanf(input, "%f", &s21_value);
    sscanf(input, "%f", &std_value);

    ck_assert_float_eq(s21_value, std_value);
}
END_TEST

START_TEST(test_sscanf_f_zero) {
    char input[] = "0.0";
    float s21_value = 0, std_value = 0;

    s21_sscanf(input, "%f", &s21_value);
    sscanf(input, "%f", &std_value);

    ck_assert_float_eq(s21_value, std_value);
}
END_TEST

START_TEST(test_sscanf_f_multiple_decimal_points) {
    char input[] = "3.14.15";
    float s21_value = 0, std_value = 0;

    int s21_result = s21_sscanf(input, "%f", &s21_value);
    int std_result = sscanf(input, "%f", &std_value);

    ck_assert_int_eq(s21_result, std_result);
}
END_TEST

START_TEST(test_sscanf_f_large_number) {
    char input[] = "1234567890.123456789";
    float s21_value = 0, std_value = 0;

    s21_sscanf(input, "%f", &s21_value);
    sscanf(input, "%f", &std_value);

    ck_assert_float_eq(s21_value, std_value);
}
END_TEST

START_TEST(test_sscanf_f_small_number) {
    char input[] = "0.000123";
    float s21_value = 0, std_value = 0;

    s21_sscanf(input, "%f", &s21_value);
    sscanf(input, "%f", &std_value);

    ck_assert_float_eq(s21_value, std_value);
}
END_TEST

START_TEST(test_sscanf_f_large_negative) {
    char input[] = "-9876543210.987654321";
    float s21_value = 0, std_value = 0;

    s21_sscanf(input, "%f", &s21_value);
    sscanf(input, "%f", &std_value);

    ck_assert_float_eq(s21_value, std_value);
}
END_TEST

START_TEST(test_sscanf_f_multiple_numbers) {
    char input[] = "1.23 4.56 7.89";
    float s21_val1 = 0, s21_val2 = 0, s21_val3 = 0;
    float std_val1 = 0, std_val2 = 0, std_val3 = 0;

    s21_sscanf(input, "%f %f %f", &s21_val1, &s21_val2, &s21_val3);
    sscanf(input, "%f %f %f", &std_val1, &std_val2, &std_val3);

    ck_assert_float_eq(s21_val1, std_val1);
    ck_assert_float_eq(s21_val2, std_val2);
    ck_assert_float_eq(s21_val3, std_val3);
}
END_TEST

START_TEST(test_sscanf_f_edge_case_zero) {
    char input[] = "0";
    float s21_value = 0, std_value = 0;

    s21_sscanf(input, "%f", &s21_value);
    sscanf(input, "%f", &std_value);

    ck_assert_float_eq(s21_value, std_value);
}
END_TEST

START_TEST(test_sscanf_f_edge_case_negative_zero) {
    char input[] = "-0";
    float s21_value = 0, std_value = 0;

    s21_sscanf(input, "%f", &s21_value);
    sscanf(input, "%f", &std_value);

    ck_assert_float_eq(s21_value, std_value);
}
END_TEST

START_TEST(test_sscanf_f_invalid_input) {
    char input[] = "abc 123.45";
    float s21_value = 0, std_value = 0;

    int s21_result = s21_sscanf(input, "%f", &s21_value);
    int std_result = sscanf(input, "%f", &std_value);

    ck_assert_int_eq(s21_result, std_result);
}
END_TEST

START_TEST(test_sscanf_f_precision) { 
    char input[] = "3.14159265358979";
    float s21_value = 0, std_value = 0;

    s21_sscanf(input, "%f", &s21_value);
    sscanf(input, "%f", &std_value);

    ck_assert_float_eq(s21_value, std_value);
}
END_TEST



START_TEST(test_sscanf_f_exponent) {
    char input[] = "3.14e2";
    float s21_value = 0, std_value = 0;

    s21_sscanf(input, "%f", &s21_value);
    sscanf(input, "%f", &std_value);

    ck_assert_float_eq(s21_value, std_value);
}
END_TEST

START_TEST(test_sscanf_f_invalid_float) {
    char input[] = "1.23abc";
    float s21_value = 0, std_value = 0;

    int s21_result = s21_sscanf(input, "%f", &s21_value);
    int std_result = sscanf(input, "%f", &std_value);

    ck_assert_int_eq(s21_result, std_result);
}
END_TEST

START_TEST(test_sscanf_g_basic) {
    char input[] = "3.14159";
    double s21_value = 0, std_value = 0;

    s21_sscanf(input, "%g", (float *)&s21_value);
    sscanf(input, "%g", (float *)&std_value);

    ck_assert_double_eq(s21_value, std_value);
}
END_TEST

START_TEST(test_sscanf_g_negative) {
    char input[] = "-3.14159";
    double s21_value = 0, std_value = 0;

    s21_sscanf(input, "%g", (float *)&s21_value);
    sscanf(input, "%g", (float *)&std_value);

    ck_assert_double_eq(s21_value, std_value);
}
END_TEST

START_TEST(test_sscanf_g_zero) {
    char input[] = "0";
    double s21_value = 0, std_value = 0;

    s21_sscanf(input, "%g", (float *)&s21_value);
    sscanf(input, "%g", (float *)&std_value);

    ck_assert_double_eq(s21_value, std_value);
}
END_TEST

START_TEST(test_sscanf_g_large_number) {
    char input[] = "1234567890.12345";
    double s21_value = 0, std_value = 0;

    s21_sscanf(input, "%g", &s21_value);
    sscanf(input, "%g", (float *)&std_value);

    ck_assert_double_eq(s21_value, std_value);
}
END_TEST

START_TEST(test_sscanf_g_scientific) {
    char input[] = "1.23e4";
    double s21_value = 0, std_value = 0;

    s21_sscanf(input, "%g", &s21_value);
    sscanf(input, "%g", (float *)&std_value);

    ck_assert_double_eq(s21_value, std_value);
}
END_TEST

START_TEST(test_sscanf_g_precision) {
    char input[] = "3.14159265358979";
    double s21_value = 0, std_value = 0;

    s21_sscanf(input, "%g", &s21_value);
    sscanf(input, "%g", (float *)&std_value);

    ck_assert_double_eq(s21_value, std_value);
}
END_TEST

START_TEST(test_sscanf_g_exponent_large) {
    char input[] = "1e100";
    double s21_value = 0, std_value = 0;

    s21_sscanf(input, "%g", &s21_value);
    sscanf(input, "%g", (float *)&std_value);

    ck_assert_double_eq(s21_value, std_value);
}
END_TEST

START_TEST(test_sscanf_g_exponent_small) {
    char input[] = "1e-100";
    double s21_value = 0, std_value = 0;

    s21_sscanf(input, "%g", &s21_value);
    sscanf(input, "%g", (float *)&std_value);

    ck_assert_double_eq(s21_value, std_value);
}
END_TEST

START_TEST(test_sscanf_g_exponent_mixed) {
    char input[] = "3.14e+2";
    double s21_value = 0, std_value = 0;

    s21_sscanf(input, "%g", &s21_value);
    sscanf(input, "%g", (float *)&std_value);

    ck_assert_double_eq(s21_value, std_value);
}
END_TEST

START_TEST(test_sscanf_g_invalid_input) {
    char input[] = "abc 3.14";
    double s21_value = 0, std_value = 0;

    int s21_result = s21_sscanf(input, "%g", &s21_value);
    int std_result = sscanf(input, "%g", (float *)&std_value);

    ck_assert_int_eq(s21_result, std_result);
}
END_TEST

START_TEST(test_sscanf_g_multiple_values) {
    char input[] = "3.14 1.23e3 5.67e-1";
    double s21_val1=0, s21_val2=0, s21_val3=0;
    double std_val1=0, std_val2=0, std_val3=0;

    s21_sscanf(input, "%g %g %g", &s21_val1, &s21_val2, &s21_val3);
    sscanf(input, "%g %g %g", (float *)&std_val1, (float *)&std_val2, (float *)&std_val3);

    ck_assert_double_eq(s21_val1, std_val1);
    ck_assert_double_eq(s21_val2, std_val2);
    ck_assert_double_eq(s21_val3, std_val3);
}
END_TEST

START_TEST(test_sscanf_g_edge_case_zero) {
    char input[] = "0.0";
    double s21_value = 0, std_value = 0;

    s21_sscanf(input, "%g", &s21_value);
    sscanf(input, "%g", (float *)&std_value);

    ck_assert_double_eq(s21_value, std_value);
}
END_TEST

START_TEST(test_sscanf_g_edge_case_negative_zero) {
    char input[] = "-0.0";
    double s21_value = 0, std_value = 0;

    s21_sscanf(input, "%g", &s21_value);
    sscanf(input, "%g", (float *)&std_value);

    ck_assert_double_eq(s21_value, std_value);
}
END_TEST

START_TEST(test_sscanf_g_invalid_exponent) {
    char input[] = "3.14eabc";
    double s21_value = 0, std_value = 0;

    int s21_result = s21_sscanf(input, "%g", &s21_value);
    int std_result = sscanf(input, "%g", (float *)&std_value);

    ck_assert_int_eq(s21_result, std_result);
}
END_TEST

START_TEST(test_sscanf_G_basic) {
    char input[] = "3.14159";
    double s21_value = 0, std_value = 0;

    s21_sscanf(input, "%G", &s21_value);
    sscanf(input, "%G", (float *)&std_value);

    ck_assert_double_eq(s21_value, std_value);
}
END_TEST

START_TEST(test_sscanf_G_negative) {
    char input[] = "-3.14159";
    double s21_value = 0, std_value = 0;

    s21_sscanf(input, "%G", &s21_value);
    sscanf(input, "%G", (float *)&std_value);

    ck_assert_double_eq(s21_value, std_value);
}
END_TEST

START_TEST(test_sscanf_G_zero) {
    char input[] = "0";
    double s21_value = 0, std_value = 0;

    s21_sscanf(input, "%G", &s21_value);
    sscanf(input, "%G", (float *)&std_value);

    ck_assert_double_eq(s21_value, std_value);
}
END_TEST

START_TEST(test_sscanf_G_large_number) {
    char input[] = "1234567890.12345";
    double s21_value = 0, std_value = 0;

    s21_sscanf(input, "%G", &s21_value);
    sscanf(input, "%G", (float *)&std_value);

    ck_assert_double_eq(s21_value, std_value);
}
END_TEST

START_TEST(test_sscanf_G_scientific) {
    char input[] = "1.23e4";
    double s21_value = 0, std_value = 0;

    s21_sscanf(input, "%G", &s21_value);
    sscanf(input, "%G", (float *)&std_value);

    ck_assert_double_eq(s21_value, std_value);
}
END_TEST

START_TEST(test_sscanf_G_precision) {
    char input[] = "3.14159265358979";
    double s21_value = 0, std_value = 0;

    s21_sscanf(input, "%G", &s21_value);
    sscanf(input, "%G", (float *)&std_value);

    ck_assert_double_eq(s21_value, std_value);
}
END_TEST

START_TEST(test_sscanf_G_exponent_large) {
    char input[] = "1e100";
    double s21_value = 0, std_value = 0;

    s21_sscanf(input, "%G", &s21_value);
    sscanf(input, "%G", (float *)&std_value);

    ck_assert_double_eq(s21_value, std_value);
}
END_TEST

START_TEST(test_sscanf_G_exponent_small) {
    char input[] = "1e-100";
    double s21_value = 0, std_value = 0;

    s21_sscanf(input, "%G", &s21_value);
    sscanf(input, "%G", (float *)&std_value);

    ck_assert_double_eq(s21_value, std_value);
}
END_TEST

START_TEST(test_sscanf_G_exponent_mixed) {
    char input[] = "3.14e+2";
    double s21_value = 0, std_value = 0;

    s21_sscanf(input, "%G", &s21_value);
    sscanf(input, "%G", (float *)&std_value);

    ck_assert_double_eq(s21_value, std_value);
}
END_TEST

START_TEST(test_sscanf_G_invalid_input) {
    char input[] = "abc 3.14";
    double s21_value = 0, std_value = 0;

    int s21_result = s21_sscanf(input, "%G", &s21_value);
    int std_result = sscanf(input, "%G", (float *)&std_value);

    ck_assert_int_eq(s21_result, std_result);
}
END_TEST

START_TEST(test_sscanf_G_multiple_values) {
    char input[] = "3.14 1.23e3 5.67e-1";
    double s21_val1 = 0, s21_val2 = 0, s21_val3 = 0;
    double std_val1 = 0, std_val2 = 0, std_val3 = 0;

    s21_sscanf(input, "%G %G %G", &s21_val1, &s21_val2, &s21_val3);
    sscanf(input, "%G %G %G", (float *)&std_val1, (float *)&std_val2, (float *)&std_val3);

    ck_assert_double_eq(s21_val1, std_val1);
    ck_assert_double_eq(s21_val2, std_val2);
    ck_assert_double_eq(s21_val3, std_val3);
}
END_TEST

START_TEST(test_sscanf_G_edge_case_zero) {
    char input[] = "0.0";
    double s21_value = 0, std_value = 0;

    s21_sscanf(input, "%G", &s21_value);
    sscanf(input, "%G", (float *)&std_value);

    ck_assert_double_eq(s21_value, std_value);
}
END_TEST

START_TEST(test_sscanf_G_edge_case_negative_zero) {
    char input[] = "-0.0";
    double s21_value = 0, std_value = 0;

    s21_sscanf(input, "%G", &s21_value);
    sscanf(input, "%G", (float *)&std_value);

    ck_assert_double_eq(s21_value, std_value);
}
END_TEST

START_TEST(test_sscanf_G_invalid_exponent) {
    char input[] = "3.14eabc";
    double s21_value = 0, std_value = 0;

    int s21_result = s21_sscanf(input, "%G", &s21_value);
    int std_result = sscanf(input, "%G", (float *)&std_value);

    ck_assert_int_eq(s21_result, std_result);
}
END_TEST

START_TEST(test_sscanf_o_basic) {
    char input[] = "1234";
    unsigned int s21_value = 0, std_value = 0;

    s21_sscanf(input, "%o", &s21_value);
    sscanf(input, "%o", &std_value);

    ck_assert_int_eq(s21_value, std_value);
}
END_TEST

START_TEST(test_sscanf_o_zero) {
    char input[] = "0";
    unsigned int s21_value = 0, std_value = 0;

    s21_sscanf(input, "%o", &s21_value);
    sscanf(input, "%o", &std_value);

    ck_assert_int_eq(s21_value, std_value);
}
END_TEST

START_TEST(test_sscanf_o_negative) {
    char input[] = "-1234";
    unsigned int s21_value = 0, std_value = 0;

    int s21_result = s21_sscanf(input, "%o", &s21_value);
    int std_result = sscanf(input, "%o", &std_value);

    ck_assert_int_eq(s21_result, std_result);
}
END_TEST

START_TEST(test_sscanf_o_large_number) {
    char input[] = "37777777777";
    unsigned int s21_value = 0, std_value = 0;

    s21_sscanf(input, "%o", &s21_value);
    sscanf(input, "%o", &std_value);

    ck_assert_int_eq(s21_value, std_value);
}
END_TEST

START_TEST(test_sscanf_o_scientific) {
    char input[] = "1.23";
    unsigned int s21_value = 0, std_value = 0;

    int s21_result = s21_sscanf(input, "%o", &s21_value);
    int std_result = sscanf(input, "%o", &std_value);

    ck_assert_int_eq(s21_result, std_result);
}
END_TEST

START_TEST(test_sscanf_o_multiple_values) {
    char input[] = "12 34 56";
    unsigned int s21_val1 = 0, s21_val2 = 0, s21_val3 = 0;
    unsigned int std_val1 = 0, std_val2 = 0, std_val3 = 0;

    s21_sscanf(input, "%o %o %o", &s21_val1, &s21_val2, &s21_val3);
    sscanf(input, "%o %o %o", &std_val1, &std_val2, &std_val3);

    ck_assert_int_eq(s21_val1, std_val1);
    ck_assert_int_eq(s21_val2, std_val2);
    ck_assert_int_eq(s21_val3, std_val3);
}
END_TEST

START_TEST(test_sscanf_o_invalid_input) {
    char input[] = "123a";
    unsigned int s21_value = 0, std_value = 0;

    int s21_result = s21_sscanf(input, "%o", &s21_value);
    int std_result = sscanf(input, "%o", &std_value);

    ck_assert_int_eq(s21_result, std_result);
}
END_TEST

START_TEST(test_sscanf_o_exceeding_size) {
    char input[] = "777777777777777777777";
    unsigned int s21_value = 0, std_value = 0;

    s21_sscanf(input, "%o", &s21_value);
    sscanf(input, "%o", &std_value);

    ck_assert_int_eq(s21_value, std_value);
}
END_TEST

START_TEST(test_sscanf_o_invalid_format) {
    char input[] = "abc 123";
    unsigned int s21_value = 0, std_value = 0;

    int s21_result = s21_sscanf(input, "%o", &s21_value);
    int std_result = sscanf(input, "%o", &std_value);

    ck_assert_int_eq(s21_result, std_result);
}
END_TEST

START_TEST(test_sscanf_o_prefixed) {
    char input[] = "01234";
    unsigned int s21_value = 0, std_value = 0;

    s21_sscanf(input, "%o", &s21_value);
    sscanf(input, "%o", &std_value);

    ck_assert_int_eq(s21_value, std_value);
}
END_TEST

START_TEST(test_sscanf_o_multiple_octal) {
    char input[] = "012 034 056";
    unsigned int s21_val1 = 0, s21_val2 = 0, s21_val3 = 0;
    unsigned int std_val1 = 0, std_val2 = 0, std_val3 = 0;

    s21_sscanf(input, "%o %o %o", &s21_val1, &s21_val2, &s21_val3);
    sscanf(input, "%o %o %o", &std_val1, &std_val2, &std_val3);

    ck_assert_int_eq(s21_val1, std_val1);
    ck_assert_int_eq(s21_val2, std_val2);
    ck_assert_int_eq(s21_val3, std_val3);
}
END_TEST

START_TEST(test_sscanf_s_basic) {
    char input[] = "Hello world";
    char s21_value[50], std_value[50];

    s21_sscanf(input, "%s", s21_value);
    sscanf(input, "%s", std_value);

    ck_assert_str_eq(s21_value, std_value);
}
END_TEST

START_TEST(test_sscanf_s_empty_string) {
    char input[] = "";
    char s21_value[50] = {0};
    char std_value[50] = {0};

    int s21_ret = s21_sscanf(input, "%s", s21_value);
    int std_ret = sscanf(input, "%s", std_value);

    ck_assert_int_eq(s21_ret, std_ret);
    ck_assert_str_eq(s21_value, std_value);
}
END_TEST

START_TEST(test_sscanf_s_whitespace) {
    char input[] = "Hello   world";
    char s21_value[50], std_value[50];

    s21_sscanf(input, "%s", s21_value);
    sscanf(input, "%s", std_value);

    ck_assert_str_eq(s21_value, std_value);
}
END_TEST

START_TEST(test_sscanf_s_multiple_words) {
    char input[] = "Hello world, this is C";
    char s21_value[50], std_value[50];

    s21_sscanf(input, "%s", s21_value);
    sscanf(input, "%s", std_value);

    ck_assert_str_eq(s21_value, std_value);
}
END_TEST

START_TEST(test_sscanf_s_non_alphanumeric) {
    char input[] = "Hello@world";
    char s21_value[50], std_value[50];

    s21_sscanf(input, "%s", s21_value);
    sscanf(input, "%s", std_value);

    ck_assert_str_eq(s21_value, std_value);
}
END_TEST

START_TEST(test_sscanf_s_large_string) {
    char input[] = "This is a very long string with spaces that should be truncated by sscanf";
    char s21_value[50], std_value[50];

    s21_sscanf(input, "%s", s21_value);
    sscanf(input, "%s", std_value);

    ck_assert_str_eq(s21_value, std_value);
}
END_TEST

START_TEST(test_sscanf_s_mixed_case) {
    char input[] = "Hello WORLD";
    char s21_value[50], std_value[50];

    s21_sscanf(input, "%s", s21_value);
    sscanf(input, "%s", std_value);

    ck_assert_str_eq(s21_value, std_value);
}
END_TEST

START_TEST(test_sscanf_s_no_spaces) {
    char input[] = "JustOneWord";
    char s21_value[50], std_value[50];

    s21_sscanf(input, "%s", s21_value);
    sscanf(input, "%s", std_value);

    ck_assert_str_eq(s21_value, std_value);
}
END_TEST

START_TEST(test_sscanf_s_with_numbers) {
    char input[] = "Hello123";
    char s21_value[50], std_value[50];

    s21_sscanf(input, "%s", s21_value);
    sscanf(input, "%s", std_value);

    ck_assert_str_eq(s21_value, std_value);
}
END_TEST

START_TEST(test_sscanf_s_mixed_whitespace) {
    char input[] = "   Hello world  ";
    char s21_value[50], std_value[50];

    s21_sscanf(input, "%s", s21_value);
    sscanf(input, "%s", std_value);

    ck_assert_str_eq(s21_value, std_value);
}
END_TEST

START_TEST(test_sscanf_s_trailing_spaces) {
    char input[] = "Hello world   ";
    char s21_value[50], std_value[50];

    s21_sscanf(input, "%s", s21_value);
    sscanf(input, "%s", std_value);

    ck_assert_str_eq(s21_value, std_value);
}
END_TEST

START_TEST(test_sscanf_s_special_characters) {
    char input[] = "Hello@world#2025";
    char s21_value[50], std_value[50];

    s21_sscanf(input, "%s", s21_value);
    sscanf(input, "%s", std_value);

    ck_assert_str_eq(s21_value, std_value);
}
END_TEST

START_TEST(test_sscanf_s_ignore_non_alphanumeric) {
    char input[] = "123abc456";
    char s21_value[50], std_value[50];

    s21_sscanf(input, "%s", s21_value);
    sscanf(input, "%s", std_value);

    ck_assert_str_eq(s21_value, std_value);
}
END_TEST

START_TEST(test_sscanf_u_basic) {
    char input[] = "12345";
    unsigned int s21_value = 0, std_value = 0;

    s21_sscanf(input, "%u", &s21_value);
    sscanf(input, "%u", &std_value);

    ck_assert_int_eq(s21_value, std_value);
}
END_TEST

START_TEST(test_sscanf_u_zero) {
    char input[] = "0";
    unsigned int s21_value = 0, std_value = 0;

    s21_sscanf(input, "%u", &s21_value);
    sscanf(input, "%u", &std_value);

    ck_assert_int_eq(s21_value, std_value);
}
END_TEST

START_TEST(test_sscanf_u_large_number) {
    char input[] = "4294967295";
    unsigned int s21_value = 0, std_value = 0;

    s21_sscanf(input, "%u", &s21_value);
    sscanf(input, "%u", &std_value);

    ck_assert_int_eq(s21_value, std_value);
}
END_TEST

START_TEST(test_sscanf_u_non_numeric) {
    char input[] = "abc";
    unsigned int s21_value = 0, std_value = 0;

    int s21_result = s21_sscanf(input, "%u", &s21_value);
    int std_result = sscanf(input, "%u", &std_value);

    ck_assert_int_eq(s21_result, std_result);
    ck_assert_int_eq(s21_value, std_value);
}
END_TEST

START_TEST(test_sscanf_u_with_spaces) {
    char input[] = " 12345 ";
    unsigned int s21_value = 0, std_value = 0;

    s21_sscanf(input, "%u", &s21_value);
    sscanf(input, "%u", &std_value);

    ck_assert_int_eq(s21_value, std_value);
}
END_TEST

START_TEST(test_sscanf_u_negative_input) {
    char input[] = "-12345";
    unsigned int s21_value = 0, std_value = 0;

    int s21_ret = s21_sscanf(input, "%u", &s21_value);
    int std_ret = sscanf(input, "%u", &std_value);

    ck_assert_int_eq(s21_ret, std_ret);
    ck_assert_int_eq(s21_value, std_value);
}
END_TEST

START_TEST(test_sscanf_u_multiple_values) {
    char input[] = "100 200 300";
    unsigned int s21_value1, s21_value2, s21_value3;
    unsigned int std_value1, std_value2, std_value3;

    s21_sscanf(input, "%u %u %u", &s21_value1, &s21_value2, &s21_value3);
    sscanf(input, "%u %u %u", &std_value1, &std_value2, &std_value3);

    ck_assert_int_eq(s21_value1, std_value1);
    ck_assert_int_eq(s21_value2, std_value2);
    ck_assert_int_eq(s21_value3, std_value3);
}
END_TEST

START_TEST(test_sscanf_u_with_leading_zero) {
    char input[] = "012345";
    unsigned int s21_value = 0, std_value = 0;

    s21_sscanf(input, "%u", &s21_value);
    sscanf(input, "%u", &std_value);

    ck_assert_int_eq(s21_value, std_value);
}
END_TEST

START_TEST(test_sscanf_u_with_non_decimal) {
    char input[] = "0x12345";
    unsigned int s21_value = 0, std_value = 0;

    int s21_result = s21_sscanf(input, "%u", &s21_value);
    int std_result = sscanf(input, "%u", &std_value);

    ck_assert_int_eq(s21_result, std_result);
    ck_assert_int_eq(s21_value, 0);
    ck_assert_int_eq(std_value, 0);
}
END_TEST

START_TEST(test_sscanf_u_with_spaces_between_numbers) {
    char input[] = " 12345  67890 ";
    unsigned int s21_value1, s21_value2;
    unsigned int std_value1, std_value2;

    s21_sscanf(input, "%u %u", &s21_value1, &s21_value2);
    sscanf(input, "%u %u", &std_value1, &std_value2);

    ck_assert_int_eq(s21_value1, std_value1);
    ck_assert_int_eq(s21_value2, std_value2);
}
END_TEST

START_TEST(test_sscanf_u_edge_case_zero_input) {
    char input[] = "0";
    unsigned int s21_value = 0, std_value = 0;

    s21_sscanf(input, "%u", &s21_value);
    sscanf(input, "%u", &std_value);

    ck_assert_int_eq(s21_value, std_value);
}
END_TEST

START_TEST(test_sscanf_x_hexadecimal_lowercase) {
    char input[] = "deadbeef";
    unsigned int s21_value = 0, std_value = 0;

    s21_sscanf(input, "%x", &s21_value);
    sscanf(input, "%x", &std_value);

    ck_assert_int_eq(s21_value, std_value);
}
END_TEST

START_TEST(test_sscanf_x_hexadecimal_uppercase) {
    char input[] = "DEADBEEF";
    unsigned int s21_value = 0, std_value = 0;

    s21_sscanf(input, "%x", &s21_value);
    sscanf(input, "%x", &std_value);

    ck_assert_int_eq(s21_value, std_value);
}
END_TEST

START_TEST(test_sscanf_x_with_leading_zero) {
    char input[] = "0x1a2b3c4d";
    unsigned int s21_value = 0, std_value = 0;

    s21_sscanf(input, "%x", &s21_value);
    sscanf(input, "%x", &std_value);

    ck_assert_int_eq(s21_value, std_value);
}
END_TEST

START_TEST(test_sscanf_x_with_mixed_case) {
    char input[] = "AbCdEf";
    unsigned int s21_value = 0, std_value = 0;

    s21_sscanf(input, "%x", &s21_value);
    sscanf(input, "%x", &std_value);

    ck_assert_int_eq(s21_value, std_value);
}
END_TEST

START_TEST(test_sscanf_x_with_non_hex_characters) {
    char input[] = "abcxyz";
    unsigned int s21_value = 0, std_value = 0;

    s21_sscanf(input, "%x", &s21_value);
    sscanf(input, "%x", &std_value);

    ck_assert_int_eq(s21_value, std_value);
}
END_TEST

START_TEST(test_sscanf_x_with_decimal_input) {
    char input[] = "12345";
    unsigned int s21_value = 0, std_value = 0;

    s21_sscanf(input, "%x", &s21_value);
    sscanf(input, "%x", &std_value);

    ck_assert_int_eq(s21_value, std_value);
}
END_TEST

START_TEST(test_sscanf_x_with_spaces) {
    char input[] = "  1f4a3b ";
    unsigned int s21_value = 0, std_value = 0;

    s21_sscanf(input, "%x", &s21_value);
    sscanf(input, "%x", &std_value);

    ck_assert_int_eq(s21_value, std_value);
}
END_TEST

START_TEST(test_sscanf_x_empty_input) {
    char input[] = "";
    unsigned int s21_value = 0, std_value = 0;

    s21_sscanf(input, "%x", &s21_value);
    sscanf(input, "%x", &std_value);

    ck_assert_int_eq(s21_value, std_value);
}
END_TEST

START_TEST(test_sscanf_x_edge_case_zero) {
    char input[] = "0";
    unsigned int s21_value = 0, std_value = 0;

    s21_sscanf(input, "%x", &s21_value);
    sscanf(input, "%x", &std_value);

    ck_assert_int_eq(s21_value, std_value);
}
END_TEST

START_TEST(test_sscanf_X_hexadecimal_uppercase) {
    char input[] = "DEADBEEF";
    unsigned int s21_value = 0, std_value = 0;

    s21_sscanf(input, "%X", &s21_value);
    sscanf(input, "%X", &std_value);

    ck_assert_int_eq(s21_value, std_value);
}
END_TEST

START_TEST(test_sscanf_X_hexadecimal_lowercase) {
    char input[] = "deadbeef";
    unsigned int s21_value = 0, std_value = 0;

    s21_sscanf(input, "%X", &s21_value);
    sscanf(input, "%X", &std_value);

    ck_assert_int_eq(s21_value, std_value);
}
END_TEST

START_TEST(test_sscanf_X_with_leading_zero) {
    char input[] = "0x1A2B3C4D";
    unsigned int s21_value = 0, std_value = 0;

    s21_sscanf(input, "%X", &s21_value);
    sscanf(input, "%X", &std_value);

    ck_assert_int_eq(s21_value, std_value);
}
END_TEST

START_TEST(test_sscanf_X_mixed_case) {
    char input[] = "AbCdEf";
    unsigned int s21_value = 0, std_value = 0;

    s21_sscanf(input, "%X", &s21_value);
    sscanf(input, "%X", &std_value);

    ck_assert_int_eq(s21_value, std_value);
}
END_TEST

START_TEST(test_sscanf_X_with_non_hex_characters) {
    char input[] = "abcxyz";
    unsigned int s21_value = 0, std_value = 0;

    s21_sscanf(input, "%X", &s21_value);
    sscanf(input, "%X", &std_value);

    ck_assert_int_eq(s21_value, std_value);
}
END_TEST

START_TEST(test_sscanf_X_with_decimal_input) {
    char input[] = "12345";
    unsigned int s21_value = 0, std_value = 0;

    s21_sscanf(input, "%X", &s21_value);
    sscanf(input, "%X", &std_value);

    ck_assert_int_eq(s21_value, std_value);
}
END_TEST

START_TEST(test_sscanf_X_with_spaces) {
    char input[] = "  1F4A3B ";
    unsigned int s21_value = 0, std_value = 0;

    s21_sscanf(input, "%X", &s21_value);
    sscanf(input, "%X", &std_value);

    ck_assert_int_eq(s21_value, std_value);
}
END_TEST

START_TEST(test_sscanf_X_empty_input) {
    char input[] = "";
    unsigned int s21_value = 0, std_value = 0;

    s21_sscanf(input, "%X", &s21_value);
    sscanf(input, "%X", &std_value);

    ck_assert_int_eq(s21_value, std_value);
}
END_TEST

START_TEST(test_sscanf_X_edge_case_zero) {
    char input[] = "0";
    unsigned int s21_value = 0, std_value = 0;

    s21_sscanf(input, "%X", &s21_value);
    sscanf(input, "%X", &std_value);

    ck_assert_int_eq(s21_value, std_value);
}
END_TEST

START_TEST(test_sscanf_p_valid_pointer) {
    char input[] = "0x7fffe80f9c98";
    void *s21_value, *std_value;

    s21_sscanf(input, "%p", &s21_value);
    sscanf(input, "%p", &std_value);

    ck_assert_ptr_eq(s21_value, std_value);
}
END_TEST

START_TEST(test_sscanf_p_null_pointer) {
    char input[] = "(nil)";
    void *s21_value = 0, *std_value = 0;

    s21_sscanf(input, "%p", &s21_value);
    sscanf(input, "%p", &std_value);

    ck_assert_ptr_eq(s21_value, std_value);
}
END_TEST

START_TEST(test_sscanf_p_invalid_pointer_format) {
    char input[] = "xyz123";
    void *s21_value = 0, *std_value = 0;

    s21_sscanf(input, "%p", &s21_value);
    sscanf(input, "%p", &std_value);

    ck_assert_ptr_eq(s21_value, std_value);
}
END_TEST

START_TEST(test_sscanf_p_with_leading_zero) {
    char input[] = "0x00112233445566778899aabbccddeeff";
    void *s21_value = 0, *std_value = 0;

    s21_sscanf(input, "%p", &s21_value);
    sscanf(input, "%p", &std_value);

    ck_assert_ptr_eq(s21_value, std_value);
}
END_TEST

START_TEST(test_sscanf_p_with_spaces) {
    char input[] = " 0x7fffe80f9c98 ";
    void *s21_value = 0, *std_value = 0;

    s21_sscanf(input, "%p", &s21_value);
    sscanf(input, "%p", &std_value);

    ck_assert_ptr_eq(s21_value, std_value);
}
END_TEST

START_TEST(test_sscanf_p_empty_input) {
    char input[] = "";
    void *s21_value = 0, *std_value = 0;

    s21_sscanf(input, "%p", &s21_value);
    sscanf(input, "%p", &std_value);

    ck_assert_ptr_eq(s21_value, std_value);
}
END_TEST

START_TEST(test_sscanf_p_with_hex_format) {
    char input[] = "0xdeadbeef";
    void *s21_value = 0, *std_value = 0;

    s21_sscanf(input, "%p", &s21_value);
    sscanf(input, "%p", &std_value);

    ck_assert_ptr_eq(s21_value, std_value);
}
END_TEST

START_TEST(test_sscanf_p_invalid_pointer_format_with_text) {
    char input[] = "pointer is 0x7fffe80f9c98";
    void *s21_value = 0, *std_value = 0;

    s21_sscanf(input, "%p", &s21_value);
    sscanf(input, "%p", &std_value);

    ck_assert_ptr_eq(s21_value, std_value);
}
END_TEST

START_TEST(test_sscanf_p_with_multiple_pointers) {
    char input[] = "0x7fffe80f9c98 0x123456789abc";
    void *s21_value1 = 0, *std_value1 = 0, *s21_value2 = 0, *std_value2 = 0;

    s21_sscanf(input, "%p %p", &s21_value1, &s21_value2);
    sscanf(input, "%p %p", &std_value1, &std_value2);

    ck_assert_ptr_eq(s21_value1, std_value1);
    ck_assert_ptr_eq(s21_value2, std_value2);
}
END_TEST

START_TEST(test_sscanf_p_mixed_valid_invalid) {
    char input[] = "0x7fffe80f9c98 not_a_pointer";
    void *s21_value1 = 0, *std_value1 = 0, *s21_value2 = 0, *std_value2 = 0;

    s21_sscanf(input, "%p %p", &s21_value1, &s21_value2);
    sscanf(input, "%p %p", &std_value1, &std_value2);

    ck_assert_ptr_eq(s21_value1, std_value1);
    ck_assert_ptr_eq(s21_value2, std_value2);
}
END_TEST

START_TEST(test_sscanf_n_basic) {
    char input[] = "Hello, world!";
    int s21_value = 0, std_value = 0;

    s21_sscanf(input, "%n", &s21_value);
    sscanf(input, "%n", &std_value);

    ck_assert_int_eq(s21_value, std_value);
}
END_TEST

START_TEST(test_sscanf_n_after_specifier) {
    char input[] = "Hello, 123 world!";
    int s21_value = 0, std_value = 0;

    s21_sscanf(input, "Hello, %d world!%n", &s21_value, &s21_value);
    sscanf(input, "Hello, %d world!%n", &std_value, &std_value);

    ck_assert_int_eq(s21_value, std_value);
}
END_TEST

START_TEST(test_sscanf_n_with_spaces) {
    char input[] = "   Hello, world!";
    int s21_value = 0, std_value = 0;

    s21_sscanf(input, "   Hello, world!%n", &s21_value);
    sscanf(input, "   Hello, world!%n", &std_value);

    ck_assert_int_eq(s21_value, std_value);
}
END_TEST

START_TEST(test_sscanf_n_invalid_input) {
    char input[] = "123abc";
    int s21_value = 0, std_value = 0;

    s21_sscanf(input, "%n", &s21_value);
    sscanf(input, "%n", &std_value);

    ck_assert_int_eq(s21_value, std_value);
}
END_TEST

START_TEST(test_sscanf_n_multiple_n_specifiers) {
    char input[] = "Hello there!";
    int s21_value1 = 0, s21_value2 = 0, std_value1 = 0, std_value2 = 0;

    s21_sscanf(input, "Hello%n there!%n", &s21_value1, &s21_value2);
    sscanf(input, "Hello%n there!%n", &std_value1, &std_value2);

    ck_assert_int_eq(s21_value1, std_value1);
    ck_assert_int_eq(s21_value2, std_value2);
}
END_TEST

START_TEST(test_sscanf_n_with_no_match) {
    char input[] = "No match";
    int s21_value = 0, std_value = 0;;

    s21_sscanf(input, "Yes match%n", &s21_value);
    sscanf(input, "Yes match%n", &std_value);

    ck_assert_int_eq(s21_value, std_value);
}
END_TEST

START_TEST(test_sscanf_n_with_text_before) {
    char input[] = "1234Hello";
    int s21_value = 0, std_value = 0;

    s21_sscanf(input, "%dHello%n", &s21_value, &s21_value);
    sscanf(input, "%dHello%n", &std_value, &std_value);

    ck_assert_int_eq(s21_value, std_value);
}
END_TEST

START_TEST(test_sscanf_n_with_no_format) {
    char input[] = "Just text";
    int s21_value = 0, std_value = 0;

    s21_sscanf(input, "%n", &s21_value);
    sscanf(input, "%n", &std_value);

    ck_assert_int_eq(s21_value, std_value);
}
END_TEST

START_TEST(test_sscanf_n_with_multiple_formats) {
    char input[] = "123 Hello 456 World!";
    int s21_value1 = 0, s21_value2 = 0, std_value1 = 0, std_value2 = 0;

    s21_sscanf(input, "%d Hello %d World!%n", &s21_value1, &s21_value2, &s21_value2);
    sscanf(input, "%d Hello %d World!%n", &std_value1, &std_value2, &std_value2);

    ck_assert_int_eq(s21_value2, std_value2);
}
END_TEST

START_TEST(test_sscanf_n_with_end_of_string) {
    char input[] = "Last test";
    int s21_value = 0, std_value = 0;

    s21_sscanf(input, "Last test%n", &s21_value);
    sscanf(input, "Last test%n", &std_value);

    ck_assert_int_eq(s21_value, std_value);
}
END_TEST

START_TEST(test_sscanf_n_after_string_literal) {
    char input[] = "Testing 1, 2, 3";
    int s21_value = 0, std_value = 0;

    s21_sscanf(input, "Testing %d, %d, %d%n", &s21_value, &s21_value, &s21_value, &s21_value);
    sscanf(input, "Testing %d, %d, %d%n", &std_value, &std_value, &std_value, &std_value);

    ck_assert_int_eq(s21_value, std_value); 
}
END_TEST

START_TEST(test_sscanf_percent_basic) {
    char input[] = "Hello % world!";
    
    int s21_result = s21_sscanf(input, "Hello %% world!");
    int std_result = sscanf(input, "Hello %% world!");

    ck_assert_int_eq(s21_result, std_result);
}
END_TEST


START_TEST(test_sscanf_percent_no_match) {
    char input[] = "Hello world!";
    int s21_value = 0, std_value = 0;

    s21_value = s21_sscanf(input, "Hello %% world!");
    std_value = sscanf(input, "Hello %% world!");

    ck_assert_int_eq(s21_value, std_value);
}
END_TEST

START_TEST(test_sscanf_percent_multiple_percent) {
    char input[] = "100% test % and % check";
    int s21_value = 0, std_value = 0;

    s21_sscanf(input, "%d%% test %% and %% check", &s21_value);
    sscanf(input, "%d%% test %% and %% check", &std_value);

    ck_assert_int_eq(s21_value, std_value);
}
END_TEST


START_TEST(test_sscanf_percent_with_integer) {
    char input[] = "Value 100% complete";
    int s21_value = 0, std_value = 0;

    s21_sscanf(input, "Value %d%% complete", &s21_value);
    sscanf(input, "Value %d%% complete", &std_value);

    ck_assert_int_eq(s21_value, std_value);
}
END_TEST

START_TEST(test_sscanf_percent_with_spaces) {
    char input[] = "Testing 10 % cases!";
    int s21_value = 0, std_value = 0;

    s21_sscanf(input, "Testing %d %% cases!", &s21_value);
    sscanf(input, "Testing %d %% cases!", &std_value);

    ck_assert_int_eq(s21_value, std_value);
}
END_TEST

START_TEST(test_sscanf_percent_multiple_percent_at_start) {
    char input[] = "%% start of string";
    int s21_value = 0, std_value = 0;

    s21_value = s21_sscanf(input, "%% start of string");
    std_value = sscanf(input, "%% start of string");

    ck_assert_int_eq(s21_value, std_value);
}
END_TEST

START_TEST(test_sscanf_percent_with_string) {
    char input[] = "percent %% in string";
    int s21_value = 0, std_value = 0;

    s21_value = s21_sscanf(input, "percent %% in string");
    std_value = sscanf(input, "percent %% in string");

    ck_assert_int_eq(s21_value, std_value);
}
END_TEST

START_TEST(test_sscanf_percent_after_number) {
    char input[] = "Number 50% complete";
    int s21_value = 0, std_value = 0;

    s21_sscanf(input, "Number %d%% complete", &s21_value);
    sscanf(input, "Number %d%% complete", &std_value);

    ck_assert_int_eq(s21_value, std_value);
}
END_TEST

START_TEST(test_sscanf_percent_with_extra_text) {
    char input[] = "Some text %% with percent";
    int s21_value = 0, std_value = 0;

    s21_value = s21_sscanf(input, "Some text %% with percent");
    std_value = sscanf(input, "Some text %% with percent");

    ck_assert_int_eq(s21_value, std_value);
}
END_TEST

START_TEST(test_sscanf_percent_at_end_of_string) {
    char input[] = "End of string %";
    int s21_value = 0, std_value = 0;

    s21_value = s21_sscanf(input, "End of string %%");
    std_value = sscanf(input, "End of string %%");

    ck_assert_int_eq(s21_value, std_value);
}
END_TEST

START_TEST(test_sscanf_max_width_int) {
    char input[] = "123456";
    int s21_value = 0, std_value = 0;

    s21_sscanf(input, "%3d", &s21_value);
    sscanf(input, "%3d", &std_value);

    ck_assert_int_eq(s21_value, std_value);
}
END_TEST

START_TEST(test_sscanf_max_width_string) {
    char input[] = "HelloWorld";
    char s21_value[6] = {0}, std_value[6] = {0};

    s21_sscanf(input, "%5s", s21_value);
    sscanf(input, "%5s", std_value);

    ck_assert_str_eq(s21_value, std_value);
}
END_TEST

START_TEST(test_sscanf_max_width_float) {
    char input[] = "3.14159";
    float s21_value = 0, std_value = 0;

    s21_sscanf(input, "%4f", &s21_value);
    sscanf(input, "%4f", &std_value);

    ck_assert_float_eq(s21_value, std_value);
}
END_TEST

START_TEST(test_sscanf_max_width_hex) {
    char input[] = "abcdef";
    unsigned int s21_value = 0, std_value = 0;

    s21_sscanf(input, "%3x", &s21_value);
    sscanf(input, "%3x", &std_value);

    ck_assert_int_eq(s21_value, std_value);
}
END_TEST

START_TEST(test_sscanf_max_width_char) {
    char input[] = "ABCD";
    char s21_value[3] = {0}, std_value[3] = {0};

    s21_sscanf(input, "%2c", s21_value);
    sscanf(input, "%2c", std_value);

    ck_assert_str_eq(s21_value, std_value);
}
END_TEST


START_TEST(test_sscanf_suppress_int) {
    char input[] = "123 456";
    int s21_value = 0, std_value = 0;

    s21_sscanf(input, "%*d %d", &s21_value);
    sscanf(input, "%*d %d", &std_value);

    ck_assert_int_eq(s21_value, std_value);
}
END_TEST

START_TEST(test_sscanf_suppress_float) {
    char input[] = "3.14 2.71";
    float s21_value = 0, std_value = 0;

    s21_sscanf(input, "%*f %f", &s21_value);
    sscanf(input, "%*f %f", &std_value);

    ck_assert_float_eq(s21_value, std_value);
}
END_TEST

START_TEST(test_sscanf_suppress_string) {
    char input[] = "Hello World";
    char s21_value[10] = {0}, std_value[10] = {0};

    s21_sscanf(input, "%*s %s", s21_value);
    sscanf(input, "%*s %s", std_value);

    ck_assert_str_eq(s21_value, std_value);
}
END_TEST

START_TEST(test_sscanf_suppress_hex) {
    char input[] = "0xFF 0xAB";
    unsigned int s21_value = 0, std_value = 0;

    s21_sscanf(input, "%*x %x", &s21_value);
    sscanf(input, "%*x %x", &std_value);

    ck_assert_int_eq(s21_value, std_value);
}
END_TEST

START_TEST(test_sscanf_suppress_char) {
    char input[] = "A B";
    char s21_value = 0, std_value = 0;

    s21_sscanf(input, "%*c %c", &s21_value);
    sscanf(input, "%*c %c", &std_value);

    ck_assert_int_eq(s21_value, std_value);
}
END_TEST

// short

START_TEST(test_sscanf_length_modifier_short_int) {
    char input[] = "32767";
    short int s21_value = 0, std_value = 0;

    s21_sscanf(input, "%3hd", &s21_value);
    sscanf(input, "%3hd", &std_value);

    ck_assert_int_eq(s21_value, std_value);
}

START_TEST(test_sscanf_length_modifier_short_int_with_more_length) {
    char input[] = "32767";
    short int s21_value = 0, std_value = 0;

    s21_sscanf(input, "%6hd", &s21_value);
    sscanf(input, "%6hd", &std_value);

    ck_assert_int_eq(s21_value, std_value);
}

START_TEST(test_sscanf_length_modifier_negative_short_int) {
    char input[] = "-32767";
    short int s21_value = 0, std_value = 0;

    s21_sscanf(input, "%4hd", &s21_value);
    sscanf(input, "%4hd", &std_value);

    ck_assert_int_eq(s21_value, std_value);
}

START_TEST(test_sscanf_length_modifier_unsigned_short_int) {
    char input[] = "65535";
    unsigned short int s21_value = 0, std_value = 0;

    s21_sscanf(input, "%6hu", &s21_value);
    sscanf(input, "%6hu", &std_value);

    ck_assert_int_eq(s21_value, std_value);
}

START_TEST(test_sscanf_length_modifier_short_int_leading_zeros) {
    char input[] = "00032767";
    short int s21_value = 0, std_value = 0;

    s21_sscanf(input, "%hd", &s21_value);
    sscanf(input, "%hd", &std_value);

    ck_assert_int_eq(s21_value, std_value);
}

START_TEST(test_sscanf_length_modifier_int_overflow) {
    char input[] = "70000";
    short int s21_value = 0, std_value = 0;

    s21_sscanf(input, "%hd", &s21_value);
    sscanf(input, "%hd", &std_value);

    ck_assert_int_eq(s21_value, std_value);
}

START_TEST(test_sscanf_length_modifier_zero_short_int) {
    char input[] = "0";
    short int s21_value = 0, std_value = 0;

    s21_sscanf(input, "%hd", &s21_value);
    sscanf(input, "%hd", &std_value);

    ck_assert_int_eq(s21_value, std_value);
}

START_TEST(test_sscanf_length_modifier_invalid_input) {
    char input[] = "abcxyz";
    short int s21_value = 0, std_value = 0;

    int result_s21 = s21_sscanf(input, "%hd", &s21_value);
    int result_std = sscanf(input, "%hd", &std_value);

    ck_assert_int_eq(result_s21, result_std);
}

START_TEST(test_sscanf_length_modifier_short_int_integer) {
    char input[] = "042";
    short int s21_value = 0, std_value = 0;

    s21_sscanf(input, "%hi", &s21_value);
    sscanf(input, "%hi", &std_value);

    ck_assert_int_eq(s21_value, std_value);
}

START_TEST(test_sscanf_length_modifier_unsigned_short_int_decimal) {
    char input[] = "65535";
    unsigned short int s21_value = 0, std_value = 0;

    s21_sscanf(input, "%hu", &s21_value);
    sscanf(input, "%hu", &std_value);

    ck_assert_int_eq(s21_value, std_value);
}

START_TEST(test_sscanf_length_modifier_unsigned_short_int_negative) {
    char input[] = "-65535";
    unsigned short int s21_value = 0, std_value = 0;

    s21_sscanf(input, "%hu", &s21_value);
    sscanf(input, "%hu", &std_value);

    ck_assert_int_eq(s21_value, std_value);
}

START_TEST(test_sscanf_length_modifier_short_int_octal) {
    char input[] = "0777";
    short int s21_value = 0, std_value = 0;

    s21_sscanf(input, "%ho", &s21_value);
    sscanf(input, "%ho", &std_value);

    ck_assert_int_eq(s21_value, std_value);
}


START_TEST(test_sscanf_length_modifier_short_int_hex_lower) {
    char input[] = "1f4";  // 500
    short int s21_value = 0, std_value = 0;

    s21_sscanf(input, "%hx", &s21_value);
    sscanf(input, "%hx", &std_value);

    ck_assert_int_eq(s21_value, std_value);
}

START_TEST(test_sscanf_length_modifier_short_int_hex_upper) {
    char input[] = "1F4";  // 500
    short int s21_value = 0, std_value = 0;

    s21_sscanf(input, "%hX", &s21_value);
    sscanf(input, "%hX", &std_value);

    ck_assert_int_eq(s21_value, std_value);
}

START_TEST(test_sscanf_length_modifier_negative_short_int_hex) {
    char input[] = "-1f4";  // -500
    short int s21_value = 0, std_value = 0;

    s21_sscanf(input, "%hx", &s21_value);
    sscanf(input, "%hx", &std_value);

    ck_assert_int_eq(s21_value, std_value);
}


START_TEST(test_sscanf_length_modifier_mixed_base) {
    char input[] = "32767 0x1f4";
    short int s21_value_1 = 0, std_value_1 = 0;
    short int s21_value_2 = 0, std_value_2 = 0;

    s21_sscanf(input, "%hd %hx", &s21_value_1, &s21_value_2);
    sscanf(input, "%hd %hx", &std_value_1, &std_value_2);

    ck_assert_int_eq(s21_value_1, std_value_1);
    ck_assert_int_eq(s21_value_2, std_value_2);
}

// long

START_TEST(test_sscanf_length_modifier_long_int_decimal) {
    char input[] = "2147483647";
    long int s21_value = 0, std_value = 0;

    s21_sscanf(input, "%ld", &s21_value);
    sscanf(input, "%ld", &std_value);

    ck_assert_int_eq(s21_value, std_value);
}

START_TEST(test_sscanf_length_modifier_negative_long_int_decimal) {
    char input[] = "-2147";
    long int s21_value = 0, std_value = 0;

    s21_sscanf(input, "%ld", &s21_value);
    sscanf(input, "%ld", &std_value);

    ck_assert_int_eq(s21_value, std_value); 
}

START_TEST(test_sscanf_length_modifier_long_int_decimal_with_length) {
    char input[] = "2147483647";
    long int s21_value = 0, std_value = 0;

    s21_sscanf(input, "%5ld", &s21_value);
    sscanf(input, "%5ld", &std_value);

    ck_assert_int_eq(s21_value, std_value);
}

START_TEST(test_sscanf_length_modifier_negative_long_int_decimal_with_length) {
    char input[] = "-2147483647";
    long int s21_value = 0, std_value = 0;

    s21_sscanf(input, "%5ld", &s21_value);
    sscanf(input, "%5ld", &std_value);

    ck_assert_int_eq(s21_value, std_value); 
}

START_TEST(test_sscanf_length_modifier_long_int_integer) {
    char input[] = "042";
    long int s21_value = 0, std_value = 0;

    s21_sscanf(input, "%li", &s21_value);
    sscanf(input, "%li", &std_value);

    ck_assert_int_eq(s21_value, std_value);
}

START_TEST(test_sscanf_length_modifier_unsigned_long_int_decimal) {
    char input[] = "4294967295";
    unsigned long int s21_value = 0, std_value = 0;

    s21_sscanf(input, "%lu", &s21_value);
    sscanf(input, "%lu", &std_value);

    ck_assert_int_eq(s21_value, std_value);
}

START_TEST(test_sscanf_length_modifier_long_int_octal) {
    char input[] = "0777";
    long int s21_value = 0, std_value = 0;

    s21_sscanf(input, "%lo", &s21_value);
    sscanf(input, "%lo", &std_value);

    ck_assert_int_eq(s21_value, std_value);
}

START_TEST(test_sscanf_length_modifier_invalid_octal) {
    char input[] = "089";
    long int s21_value = 0, std_value = 0;

    int result_s21 = s21_sscanf(input, "%lo", &s21_value);
    int result_std = sscanf(input, "%lo", &std_value);

    ck_assert_int_eq(result_s21, result_std);
}

START_TEST(test_sscanf_length_modifier_long_int_hex_lower) {
    char input[] = "1f4"; // 500
    long int s21_value = 0, std_value = 0;

    s21_sscanf(input, "%lx", &s21_value);
    sscanf(input, "%lx", &std_value);

    ck_assert_int_eq(s21_value, std_value);
}

START_TEST(test_sscanf_length_modifier_long_int_hex_upper) {
    char input[] = "1F4"; // 500
    long int s21_value = 0, std_value = 0;

    s21_sscanf(input, "%lX", &s21_value);
    sscanf(input, "%lX", &std_value);

    ck_assert_int_eq(s21_value, std_value);
}

// START_TEST(test_sscanf_length_modifier_negative_long_int_hex) {
//     char input[] = "-1f4";  // -500
//     long int s21_value = 0, std_value = 0;

//     s21_sscanf(input, "%lx", &s21_value);
//     sscanf(input, "%lx", &std_value);

//     ck_assert_int_eq(s21_value, std_value);
// }

START_TEST(test_sscanf_length_modifier_long_int_overflow) {
    char input[] = "9223372036854775807";
    long int s21_value = 0, std_value = 0;

    s21_sscanf(input, "%5ld", &s21_value);
    sscanf(input, "%5ld", &std_value);

    ck_assert_int_eq(s21_value, std_value);  // TODO: Make SURE --------------HERE----------------------
}

START_TEST(test_sscanf_length_modifier_long_int_leading_zeros) {
    char input[] = "0002147483647";
    long int s21_value = 0, std_value = 0;

    s21_sscanf(input, "%ld", &s21_value);
    sscanf(input, "%ld", &std_value);

    ck_assert_int_eq(s21_value, std_value);  // 2147483647
}

START_TEST(test_sscanf_length_modifier_mixed_long_int_and_unsigned_long_int) {
    char input[] = "2147483647 4294967295";  //
    long int s21_value_1 = 0, std_value_1 = 0;
    unsigned long int s21_value_2 = 0, std_value_2 = 0;

    s21_sscanf(input, "%ld %lu", &s21_value_1, &s21_value_2);
    sscanf(input, "%ld %lu", &std_value_1, &std_value_2);

    ck_assert_int_eq(s21_value_1, std_value_1);
    ck_assert_int_eq(s21_value_2, std_value_2);
}

START_TEST(test_sscanf_length_modifier_unsigned_long_int_octal) {
    char input[] = "0777";  // 511
    unsigned long int s21_value = 0, std_value = 0;

    s21_sscanf(input, "%lo", &s21_value);
    sscanf(input, "%lo", &std_value);

    ck_assert_int_eq(s21_value, std_value);
}

START_TEST(test_sscanf_length_modifier_unsigned_long_int_invalid_input) {
    char input[] = "abcxyz";
    unsigned long int s21_value = 0, std_value = 0;

    int result_s21 = s21_sscanf(input, "%lu", &s21_value);
    int result_std = sscanf(input, "%lu", &std_value);

    ck_assert_int_eq(result_s21, result_std);
}

START_TEST(test_sscanf_length_modifier_long_double_scientific) {
    char input[] = "1.234567e2";  // 123.4567
    long double s21_value = 0.0, std_value = 0.0;

    s21_sscanf(input, "%Le", &s21_value);
    sscanf(input, "%Le", &std_value);

    ck_assert_ldouble_eq(s21_value, std_value);
}

START_TEST(test_sscanf_length_modifier_negative_long_double_scientific) {
    char input[] = "-1.234567e2";  // -123.4567
    long double s21_value = 0.0, std_value = 0.0;

    s21_sscanf(input, "%Le", &s21_value);
    sscanf(input, "%Le", &std_value);

    ck_assert_ldouble_eq(s21_value, std_value);
}

START_TEST(test_sscanf_length_modifier_long_double_standard) {
    char input[] = "123.456";
    long double s21_value = 0.0, std_value = 0.0;

    s21_sscanf(input, "%Lf", &s21_value);
    sscanf(input, "%Lf", &std_value);

    ck_assert_ldouble_eq(s21_value, std_value);
}


START_TEST(test_sscanf_length_modifier_negative_long_double_standard) {
    char input[] = "-123.456";
    long double s21_value = 0.0, std_value = 0.0;

    s21_sscanf(input, "%Lf", &s21_value);
    sscanf(input, "%Lf", &std_value);

    ck_assert_ldouble_eq(s21_value, std_value);
}

START_TEST(test_sscanf_length_modifier_long_double_exponential) {
    char input[] = "1.23456e2";  // 123.456
    long double s21_value = 0.0, std_value = 0.0;

    s21_sscanf(input, "%Lg", &s21_value);
    sscanf(input, "%Lg", &std_value);

    ck_assert_ldouble_eq(s21_value, std_value);
}

START_TEST(test_sscanf_length_modifier_negative_long_double_exponential) {
    char input[] = "-1.23456e2";  // -123.456
    long double s21_value = 0.0, std_value = 0.0;

    s21_sscanf(input, "%Lg", &s21_value);
    sscanf(input, "%Lg", &std_value);

    ck_assert_ldouble_eq(s21_value, std_value);
}

START_TEST(test_sscanf_length_modifier_long_double_precision) {
    char input[] = "123.456789";
    long double s21_value = 0.0, std_value = 0.0;

    s21_sscanf(input, "%Lf", &s21_value);
    sscanf(input, "%Lf", &std_value);

    ck_assert_ldouble_eq(s21_value, std_value);
}

START_TEST(test_sscanf_length_modifier_long_double_precision_exponential) {
    char input[] = "1.234567e2";  // 123.4567
    long double s21_value = 0.0, std_value = 0.0;

    s21_sscanf(input, "%Lg", &s21_value);
    sscanf(input, "%Lg", &std_value);

    ck_assert_ldouble_eq(s21_value, std_value);
}

START_TEST(test_sscanf_length_modifier_long_double_overflow) {
    char input[] = "1.7e308";
    long double s21_value = 0.0, std_value = 0.0;

    s21_sscanf(input, "%Lf", &s21_value);
    sscanf(input, "%Lf", &std_value);

    ck_assert_ldouble_eq(s21_value, std_value);
}

START_TEST(test_sscanf_length_modifier_long_double_infinity) {
    char input[] = "inf";
    long double s21_value = 0.0, std_value = 0.0;

    s21_sscanf(input, "%Lf", &s21_value);
    sscanf(input, "%Lf", &std_value);

    ck_assert_ldouble_eq(s21_value, std_value);  // Should be inf
}

START_TEST(test_sscanf_length_modifier_long_double_leading_zeros) {
    char input[] = "000123.456";
    long double s21_value = 0.0, std_value = 0.0;

    s21_sscanf(input, "%Lf", &s21_value);
    sscanf(input, "%Lf", &std_value);

    ck_assert_ldouble_eq(s21_value, std_value);  // Should be 123.456
}

START_TEST(test_sscanf_length_modifier_long_double_mixed_format) {
    char input[] = "123.456 1.23e2";
    long double s21_value_1 = 0.0, std_value_1 = 0.0;
    long double s21_value_2 = 0.0, std_value_2 = 0.0;

    s21_sscanf(input, "%Lf %Le", &s21_value_1, &s21_value_2);
    sscanf(input, "%Lf %Le", &std_value_1, &std_value_2);

    ck_assert_ldouble_eq(s21_value_1, std_value_1);
    ck_assert_ldouble_eq(s21_value_2, std_value_2);
}


Suite *sprintf_suite(void) {
    Suite *s = suite_create("s21_sscanf");
    TCase *tc = tcase_create("Core");
    // %c specifier
    tcase_add_test(tc, test_sscanf_c_spec);
    tcase_add_test(tc, test_sscanf_c_single_char);
    tcase_add_test(tc, test_sscanf_c_with_leading_spaces);
    tcase_add_test(tc, test_sscanf_c_with_trailing_spaces);
    tcase_add_test(tc, test_sscanf_c_multiple_chars);
    tcase_add_test(tc, test_sscanf_c_newline_character);
    tcase_add_test(tc, test_sscanf_c_tab_character);
    tcase_add_test(tc, test_sscanf_c_special_character);
    tcase_add_test(tc, test_sscanf_c_numeric_character);
    tcase_add_test(tc, test_sscanf_c_with_format_string);

    // %d specifier
    tcase_add_test(tc, test_sscanf_d_positive_number);
    tcase_add_test(tc, test_sscanf_d_negative_number);
    tcase_add_test(tc, test_sscanf_d_zero);
    tcase_add_test(tc, test_sscanf_d_with_leading_spaces);
    tcase_add_test(tc, test_sscanf_d_multiple_numbers);
    tcase_add_test(tc, test_sscanf_d_number_with_trailing_text);
    tcase_add_test(tc, test_sscanf_d_with_format_string);
    tcase_add_test(tc, test_sscanf_d_large_number);
    tcase_add_test(tc, test_sscanf_d_small_number);
    tcase_add_test(tc, test_sscanf_d_invalid_input);
    tcase_add_test(tc, test_sscanf_d_with_plus_sign);
    tcase_add_test(tc, test_sscanf_d_number_with_extra_spaces);
    tcase_add_test(tc, test_sscanf_d_spec);

    // %i specifier
    tcase_add_test(tc, test_sscanf_i_spec);
    tcase_add_test(tc, test_sscanf_i_basic);
    tcase_add_test(tc, test_sscanf_i_negative);
    tcase_add_test(tc, test_sscanf_i_zero);
    tcase_add_test(tc, test_sscanf_i_octal);
    tcase_add_test(tc, test_sscanf_i_hex);
    tcase_add_test(tc, test_sscanf_i_mixed_spaces);
    tcase_add_test(tc, test_sscanf_i_large_number);
    tcase_add_test(tc, test_sscanf_i_overflow);
    tcase_add_test(tc, test_sscanf_i_invalid);
    tcase_add_test(tc, test_sscanf_i_multiple_numbers);

    // %e specifier
    tcase_add_test(tc, test_sscanf_e_basic);
    tcase_add_test(tc, test_sscanf_e_negative_exponent);
    tcase_add_test(tc, test_sscanf_e_large_exponent);
    tcase_add_test(tc, test_sscanf_e_small_exponent);
    tcase_add_test(tc, test_sscanf_e_no_exponent);
    tcase_add_test(tc, test_sscanf_e_scientific_notation);
    tcase_add_test(tc, test_sscanf_e_edge_case_zero);
    tcase_add_test(tc, test_sscanf_e_edge_case_negative_zero);
    tcase_add_test(tc, test_sscanf_e_invalid_input);
    tcase_add_test(tc, test_sscanf_e_multiple_numbers);

    // %E specifier
    tcase_add_test(tc, test_sscanf_E_basic);
    tcase_add_test(tc, test_sscanf_E_negative_exponent);
    tcase_add_test(tc, test_sscanf_E_large_exponent);
    tcase_add_test(tc, test_sscanf_E_small_exponent);
    tcase_add_test(tc, test_sscanf_E_no_exponent);
    tcase_add_test(tc, test_sscanf_E_scientific_notation);
    tcase_add_test(tc, test_sscanf_E_edge_case_zero);
    tcase_add_test(tc, test_sscanf_E_edge_case_negative_zero);
    tcase_add_test(tc, test_sscanf_E_invalid_input);
    tcase_add_test(tc, test_sscanf_E_multiple_numbers);

    // %f specifier
    tcase_add_test(tc, test_sscanf_f_basic);
    tcase_add_test(tc, test_sscanf_f_negative);
    tcase_add_test(tc, test_sscanf_f_zero);
    tcase_add_test(tc, test_sscanf_f_multiple_decimal_points);
    tcase_add_test(tc, test_sscanf_f_large_number);
    tcase_add_test(tc, test_sscanf_f_small_number);
    tcase_add_test(tc, test_sscanf_f_large_negative);
    tcase_add_test(tc, test_sscanf_f_multiple_numbers);
    tcase_add_test(tc, test_sscanf_f_edge_case_zero);
    tcase_add_test(tc, test_sscanf_f_edge_case_negative_zero);
    tcase_add_test(tc, test_sscanf_f_invalid_input);
    tcase_add_test(tc, test_sscanf_f_precision);
    tcase_add_test(tc, test_sscanf_f_exponent);
    tcase_add_test(tc, test_sscanf_f_invalid_float);

    // %g specifier
    tcase_add_test(tc, test_sscanf_g_basic);
    tcase_add_test(tc, test_sscanf_g_negative);
    tcase_add_test(tc, test_sscanf_g_zero);
    tcase_add_test(tc, test_sscanf_g_large_number);
    tcase_add_test(tc, test_sscanf_g_scientific);
    tcase_add_test(tc, test_sscanf_g_precision);
    tcase_add_test(tc, test_sscanf_g_exponent_large);
    tcase_add_test(tc, test_sscanf_g_exponent_small);
    tcase_add_test(tc, test_sscanf_g_exponent_mixed);
    tcase_add_test(tc, test_sscanf_g_invalid_input);
    tcase_add_test(tc, test_sscanf_g_multiple_values);
    tcase_add_test(tc, test_sscanf_g_edge_case_zero);
    tcase_add_test(tc, test_sscanf_g_edge_case_negative_zero);
    tcase_add_test(tc, test_sscanf_g_invalid_exponent);

    // %G specifier
    tcase_add_test(tc, test_sscanf_G_basic);
    tcase_add_test(tc, test_sscanf_G_negative);
    tcase_add_test(tc, test_sscanf_G_zero);
    tcase_add_test(tc, test_sscanf_G_large_number);
    tcase_add_test(tc, test_sscanf_G_scientific);
    tcase_add_test(tc, test_sscanf_G_precision);
    tcase_add_test(tc, test_sscanf_G_exponent_large);
    tcase_add_test(tc, test_sscanf_G_exponent_small);
    tcase_add_test(tc, test_sscanf_G_exponent_mixed);
    tcase_add_test(tc, test_sscanf_G_invalid_input);
    tcase_add_test(tc, test_sscanf_G_multiple_values);
    tcase_add_test(tc, test_sscanf_G_edge_case_zero);
    tcase_add_test(tc, test_sscanf_G_edge_case_negative_zero);
    tcase_add_test(tc, test_sscanf_G_invalid_exponent);

    // %o specifier
    tcase_add_test(tc, test_sscanf_o_basic);
    tcase_add_test(tc, test_sscanf_o_zero);
    tcase_add_test(tc, test_sscanf_o_negative);
    tcase_add_test(tc, test_sscanf_o_large_number);
    tcase_add_test(tc, test_sscanf_o_scientific);
    tcase_add_test(tc, test_sscanf_o_multiple_values);
    tcase_add_test(tc, test_sscanf_o_invalid_input);
    tcase_add_test(tc, test_sscanf_o_exceeding_size);
    tcase_add_test(tc, test_sscanf_o_invalid_format);
    tcase_add_test(tc, test_sscanf_o_prefixed);
    tcase_add_test(tc, test_sscanf_o_multiple_octal);

    // %s specifier
    tcase_add_test(tc, test_sscanf_s_basic);
    tcase_add_test(tc, test_sscanf_s_empty_string);
    tcase_add_test(tc, test_sscanf_s_whitespace);
    tcase_add_test(tc, test_sscanf_s_multiple_words);
    tcase_add_test(tc, test_sscanf_s_non_alphanumeric);
    tcase_add_test(tc, test_sscanf_s_large_string);
    tcase_add_test(tc, test_sscanf_s_mixed_case);
    tcase_add_test(tc, test_sscanf_s_no_spaces);
    tcase_add_test(tc, test_sscanf_s_mixed_whitespace);
    tcase_add_test(tc, test_sscanf_s_trailing_spaces);
    tcase_add_test(tc, test_sscanf_s_special_characters);
    tcase_add_test(tc, test_sscanf_s_ignore_non_alphanumeric);
    tcase_add_test(tc, test_sscanf_s_with_numbers);

    // %u specifier
    tcase_add_test(tc, test_sscanf_u_basic);
    tcase_add_test(tc, test_sscanf_u_zero);
    tcase_add_test(tc, test_sscanf_u_large_number);
    tcase_add_test(tc, test_sscanf_u_non_numeric);
    tcase_add_test(tc, test_sscanf_u_with_spaces);
    tcase_add_test(tc, test_sscanf_u_negative_input);
    tcase_add_test(tc, test_sscanf_u_multiple_values);
    tcase_add_test(tc, test_sscanf_u_with_non_decimal);
    tcase_add_test(tc, test_sscanf_u_with_spaces_between_numbers);
    tcase_add_test(tc, test_sscanf_u_edge_case_zero_input);
    tcase_add_test(tc, test_sscanf_u_with_leading_zero);
    
    // %x specifier
    tcase_add_test(tc, test_sscanf_x_hexadecimal_lowercase);
    tcase_add_test(tc, test_sscanf_x_hexadecimal_uppercase);
    tcase_add_test(tc, test_sscanf_x_with_leading_zero);    
    tcase_add_test(tc, test_sscanf_x_with_mixed_case);
    tcase_add_test(tc, test_sscanf_x_with_non_hex_characters);
    tcase_add_test(tc, test_sscanf_x_with_decimal_input);
    tcase_add_test(tc, test_sscanf_x_with_spaces);
    tcase_add_test(tc, test_sscanf_x_empty_input);
    tcase_add_test(tc, test_sscanf_x_edge_case_zero);    

    // %X specifier
    tcase_add_test(tc, test_sscanf_X_hexadecimal_lowercase);
    tcase_add_test(tc, test_sscanf_X_hexadecimal_uppercase);
    tcase_add_test(tc, test_sscanf_X_with_leading_zero);    
    tcase_add_test(tc, test_sscanf_X_mixed_case);
    tcase_add_test(tc, test_sscanf_X_with_non_hex_characters);
    tcase_add_test(tc, test_sscanf_X_with_decimal_input);
    tcase_add_test(tc, test_sscanf_X_with_spaces);
    tcase_add_test(tc, test_sscanf_X_empty_input);
    tcase_add_test(tc, test_sscanf_X_edge_case_zero);


    // %p specifier
    tcase_add_test(tc, test_sscanf_p_valid_pointer);
    tcase_add_test(tc, test_sscanf_p_null_pointer);
    tcase_add_test(tc, test_sscanf_p_invalid_pointer_format);    
    tcase_add_test(tc, test_sscanf_p_with_leading_zero);
    tcase_add_test(tc, test_sscanf_p_with_spaces);
    tcase_add_test(tc, test_sscanf_p_empty_input);
    tcase_add_test(tc, test_sscanf_p_with_hex_format);
    tcase_add_test(tc, test_sscanf_p_invalid_pointer_format_with_text);
    tcase_add_test(tc, test_sscanf_p_with_multiple_pointers);
    tcase_add_test(tc, test_sscanf_p_mixed_valid_invalid);

    // %n specifier
    tcase_add_test(tc, test_sscanf_n_basic);
    tcase_add_test(tc, test_sscanf_n_after_specifier);
    tcase_add_test(tc, test_sscanf_n_with_spaces);    
    tcase_add_test(tc, test_sscanf_n_invalid_input);
    tcase_add_test(tc, test_sscanf_n_multiple_n_specifiers);
    tcase_add_test(tc, test_sscanf_n_with_no_match);
    tcase_add_test(tc, test_sscanf_n_with_text_before);
    tcase_add_test(tc, test_sscanf_n_with_no_format);
    tcase_add_test(tc, test_sscanf_n_with_multiple_formats);
    tcase_add_test(tc, test_sscanf_n_with_end_of_string);
    tcase_add_test(tc, test_sscanf_n_after_string_literal);

    // % specifier
    tcase_add_test(tc, test_sscanf_percent_basic);
    tcase_add_test(tc, test_sscanf_percent_no_match);
    tcase_add_test(tc, test_sscanf_percent_multiple_percent);    
    tcase_add_test(tc, test_sscanf_percent_with_integer);
    tcase_add_test(tc, test_sscanf_percent_with_spaces);
    tcase_add_test(tc, test_sscanf_percent_multiple_percent_at_start);
    tcase_add_test(tc, test_sscanf_percent_with_string);
    tcase_add_test(tc, test_sscanf_percent_after_number);
    tcase_add_test(tc, test_sscanf_percent_with_extra_text);
    tcase_add_test(tc, test_sscanf_percent_at_end_of_string);
    tcase_add_test(tc, test_sscanf_max_width_string);
    tcase_add_test(tc, test_sscanf_max_width_int);
    tcase_add_test(tc, test_sscanf_max_width_float);
    tcase_add_test(tc, test_sscanf_max_width_hex);
    tcase_add_test(tc, test_sscanf_max_width_char);

    tcase_add_test(tc, test_sscanf_suppress_int);
    tcase_add_test(tc, test_sscanf_suppress_float);
    tcase_add_test(tc, test_sscanf_suppress_string);
    tcase_add_test(tc, test_sscanf_suppress_hex);
    tcase_add_test(tc, test_sscanf_suppress_char);


    // length description
    tcase_add_test(tc, test_sscanf_length_modifier_short_int);
    tcase_add_test(tc, test_sscanf_length_modifier_short_int_with_more_length);
    tcase_add_test(tc, test_sscanf_length_modifier_negative_short_int);
    tcase_add_test(tc, test_sscanf_length_modifier_unsigned_short_int);
    tcase_add_test(tc, test_sscanf_length_modifier_short_int_leading_zeros);
    tcase_add_test(tc, test_sscanf_length_modifier_int_overflow);
    tcase_add_test(tc, test_sscanf_length_modifier_zero_short_int);
    tcase_add_test(tc, test_sscanf_length_modifier_invalid_input);
    tcase_add_test(tc, test_sscanf_length_modifier_short_int_integer);
    tcase_add_test(tc, test_sscanf_length_modifier_unsigned_short_int_decimal);
    tcase_add_test(tc, test_sscanf_length_modifier_unsigned_short_int_negative);
    tcase_add_test(tc, test_sscanf_length_modifier_short_int_octal);
    tcase_add_test(tc, test_sscanf_length_modifier_invalid_octal);
    tcase_add_test(tc, test_sscanf_length_modifier_short_int_hex_lower);
    tcase_add_test(tc, test_sscanf_length_modifier_short_int_hex_upper);
    tcase_add_test(tc, test_sscanf_length_modifier_negative_short_int_hex);
    tcase_add_test(tc, test_sscanf_length_modifier_mixed_base);
    tcase_add_test(tc, test_sscanf_length_modifier_long_int_decimal);
    tcase_add_test(tc, test_sscanf_length_modifier_negative_long_int_decimal);
    tcase_add_test(tc, test_sscanf_length_modifier_long_int_decimal_with_length);
    tcase_add_test(tc, test_sscanf_length_modifier_negative_long_int_decimal_with_length);
    tcase_add_test(tc, test_sscanf_length_modifier_long_int_integer);
    tcase_add_test(tc, test_sscanf_length_modifier_unsigned_long_int_decimal);
    tcase_add_test(tc, test_sscanf_length_modifier_long_int_octal);
    tcase_add_test(tc, test_sscanf_length_modifier_long_int_hex_lower);
    tcase_add_test(tc, test_sscanf_length_modifier_long_int_hex_upper);
    // tcase_add_test(tc, test_sscanf_length_modifier_negative_long_int_hex);
    tcase_add_test(tc, test_sscanf_length_modifier_long_int_overflow);
    tcase_add_test(tc, test_sscanf_length_modifier_long_int_leading_zeros);
    tcase_add_test(tc, test_sscanf_length_modifier_mixed_long_int_and_unsigned_long_int);
    tcase_add_test(tc, test_sscanf_length_modifier_unsigned_long_int_octal);
    tcase_add_test(tc, test_sscanf_length_modifier_unsigned_long_int_invalid_input);
    tcase_add_test(tc, test_sscanf_length_modifier_long_double_scientific);
    tcase_add_test(tc, test_sscanf_length_modifier_negative_long_double_scientific);
    tcase_add_test(tc, test_sscanf_length_modifier_long_double_standard);
    tcase_add_test(tc, test_sscanf_length_modifier_negative_long_double_standard);
    tcase_add_test(tc, test_sscanf_length_modifier_long_double_exponential);
    tcase_add_test(tc, test_sscanf_length_modifier_negative_long_double_exponential);
    tcase_add_test(tc, test_sscanf_length_modifier_long_double_precision);
    tcase_add_test(tc, test_sscanf_length_modifier_long_double_precision_exponential);
    tcase_add_test(tc, test_sscanf_length_modifier_long_double_overflow);
    tcase_add_test(tc, test_sscanf_length_modifier_long_double_infinity);
    tcase_add_test(tc, test_sscanf_length_modifier_long_double_leading_zeros);
    tcase_add_test(tc, test_sscanf_length_modifier_long_double_mixed_format);


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
