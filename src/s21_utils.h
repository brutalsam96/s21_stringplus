#ifndef S21_UTILS
#define S21_UTILS

#include <limits.h>
#include <math.h>
#include <stdio.h>

void reverse(char *str, int length);
char *s21_itoa(int value, char *buffer, int base);
char *s21_utoa(unsigned int value, char *buffer, int base, int isUpper);
char *s21_ftoa(double value, char *buffer, int precision);
char *s21_lftoa(long double value, char *buffer, int precision);
char *s21_lltoa(long value, char *buffer, int base);
char *s21_llutoa(unsigned long value, char *buffer, int base, int IsUpper);
char *s21_etoa(double value, char *buffer, int precision);
// int round_to_sig_digits(double *value, int *precision, int IsComp);
int round_to_sig_digits(double *value, int *precision, int IsComp);
int round_to_sig_digits_l(long double *value, int *precision, int IsComp);
int remove_trailing_zeroes(char *itc);

typedef long long unsigned int s21_uintptr_t;

#endif
