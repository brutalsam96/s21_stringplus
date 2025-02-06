#ifndef S21_SSCANF
#define S21_SSCANF


#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdarg.h>

int s21_sscanf(const char *str, const char *format, ...);
int proccess_scanf(const char *str, const char *format, va_list *args);

void c_specifier(va_list *args, const char **str);
void d_specifier(va_list *args, const char **str);
// void i_specifier(va_list *args, const char **str);
// void e_specifier(va_list *args, const char **str);
// void E_specifier(va_list *args, const char **str);
// void f_specifier(va_list *args, const char **str);
// void g_specifier(va_list *args, const char **str);
// void G_specifier(va_list *args, const char **str);
// void o_specifier(va_list *args, const char **str);
void s_specifier(va_list *args, const char **str);
// void u_specifier(va_list *args, const char **str);
// void x_specifier(va_list *args, const char **str);
// void X_specifier(va_list *args, const char **str);
// void p_specifier(va_list *args, const char **str);
// void n_specifier(va_list *args, const char **str);

typedef void (*Specifier)(va_list *args, const char **);

typedef struct {
    const char flag;
    Specifier function;
} SpecifierMap;

SpecifierMap specifier_map[] = {
    {'c', c_specifier},
    {'d', d_specifier},
    // {'i', i_specifier},
    // {'e', e_specifier},
    // {'E', E_specifier},
    // {'f', f_specifier},
    // {'g', g_specifier},
    // {'G', G_specifier},
    // {'o', o_specifier},
    {'s', s_specifier},
    // {'u', u_specifier},
    // {'x', x_specifier},
    // {'X', X_specifier},
    // {'p', p_specifier},
    // {'n', n_specifier},
    {'\0', NULL}
};


#endif