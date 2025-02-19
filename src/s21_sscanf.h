#ifndef S21_SSCANF
#define S21_SSCANF


#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdarg.h>
#include <math.h>

typedef long long unsigned int s21_uintptr_t; // TODO could confilct with sprintf one

void parse_number(const char **str, int base, long long *num);
int check_e(const char *str);

int s21_sscanf(const char *str, const char *format, ...);

int proccess_scanf(const char *str, const char *format, va_list *args);
int c_specifier(va_list *args, const char **str);
int d_specifier(va_list *args, const char **str);
int u_specifier(va_list *args, const char **str);
int i_specifier(va_list *args, const char **str);
int e_specifier(va_list *args, const char **str);
int f_specifier(va_list *args, const char **str);
int g_specifier(va_list *args, const char **str);
int o_specifier(va_list *args, const char **str);
int s_specifier(va_list *args, const char **str);
int u_specifier(va_list *args, const char **str);
int x_specifier(va_list *args, const char **str);
int n_specifier(va_list *args, const char **str, const char *start);
int p_specifier(va_list *args, const char **str);

s21_uintptr_t hex2dec_ptr(const char **str);


#endif

