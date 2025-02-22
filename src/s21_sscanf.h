#ifndef S21_SSCANF
#define S21_SSCANF


#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdarg.h>
#include <math.h>
#include <wchar.h>

typedef long long unsigned int s21_uintptr_t; // TODO could confilct with sprintf one

void parse_number(const char **str, int base, int *num, int width);
void parse_number_u(const char **str, int base, unsigned int *num, int width);
int check_e(const char *str);

int s21_sscanf(const char *str, const char *format, ...);

int proccess_scanf(const char *str, const char *format, va_list *args);
int c_specifier(va_list *args, const char **str, char len_mod, int width);
int d_specifier(va_list *args, const char **str, char len_mod, int width);
int u_specifier(va_list *args, const char **str, char len_mod, int width);
int i_specifier(va_list *args, const char **str, char len_mod, int width);
int e_specifier(va_list *args, const char **str, char len_mod, int width);
int f_specifier(va_list *args, const char **str, char len_mod, int width);
int g_specifier(va_list *args, const char **str, char len_mod, int width);
int o_specifier(va_list *args, const char **str, char len_mod, int width);
int s_specifier(va_list *args, const char **str, char len_mod, int width);
int u_specifier(va_list *args, const char **str, char len_mod, int width);
int x_specifier(va_list *args, const char **str, char len_mod, int width);
int n_specifier(va_list *args, char *buffer, int len);
int p_specifier(va_list *args, const char **str);

s21_uintptr_t hex2dec_ptr(const char **str);


#endif

