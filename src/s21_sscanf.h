#ifndef S21_SSCANF
#define S21_SSCANF


#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdarg.h>
#include <math.h>

int s21_sscanf(const char *str, const char *format, ...);
int proccess_scanf(const char *str, const char *format, va_list *args);

void c_specifier(va_list *args, const char **str);
void d_specifier(va_list *args, const char **str);
void i_specifier(va_list *args, const char **str);
void e_specifier(va_list *args, const char **str);
void f_specifier(va_list *args, const char **str);
// void g_specifier(va_list *args, const char **str);
// void o_specifier(va_list *args, const char **str);
void s_specifier(va_list *args, const char **str);
// void u_specifier(va_list *args, const char **str);
// void x_specifier(va_list *args, const char **str);
// void p_specifier(va_list *args, const char **str);
void n_specifier(va_list *args, const char **str, const char *start);



#endif