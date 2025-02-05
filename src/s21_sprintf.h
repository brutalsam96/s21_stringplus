#ifndef SPRINTF_H
#define SPRINTF_H


#include <stdarg.h>
#include <ctype.h>
#include <math.h>
#include <limits.h>


#include <stdio.h>


/* SPRINTF FLAGS */
#define FLAG_LEFT 1
#define FLAG_SIGN 2
#define FLAG_SPACE 4
#define FLAG_ALT 8
#define FLAG_ZERO 16

// main functions
int s21_sprintf(char *str, const char *format, ...);
int proccess_string(char *str, const char *format, va_list *args);

// parsers
int parse_flags(const char **current, int *flags);
int parse_width(const char **current, int *width, va_list *args, int *flags);
int parse_precision(const char **current, int *precision, va_list *args);
int parse_length_modifiers(const char **current, char *length_modifier);
void parse_type_spec(const char **current, char *str, va_list *args, int *index,
                    int flags, int precision, int width, char length_modifiers);

// Proccess TODO GOTTA FIX VALUE types
int proccess_signed_int(char *str, void *value, int *index, int *flags,
                        int *width, int *precision, char length_modifier);

int proccess_unsigned_int(char *str, void *u_value, int *index, int *flags,
                          int *width, int *precision, char length_modifier,
                          int base, int IsUpper, int isX);

int proccess_float(char *str, void *value, int *index, int *flags, int *width,
                   int *precision, char length_modifier, int IsUpper);

int proccess_scientific(char *str, void *value, int *index, int *flags,
                        int *width, int *precision, char length_modifier,
                        int IsUpper);

int proccess_compact(char *str, void *value, int *index, int *flags, int *width,
                     int *precision, char length_modifier, int IsUpper);
int proccess_string_arg(char *str, va_list *args, int *index);
int proccess_char(char *str, va_list *args, int *index);

int proccess_char_counter(char *str, va_list *args, int *index);

int proccess_pointer(char *str, va_list *args, int *index);

// HELPER
void handle_width_padding(char *str, int *index, int width, int flags);

void handle_precision_padding(char *str, int *index, int precision, int value);

void handle_precision_pad_str(char *str, int *index, int precision, int len);

void handle_sign_space(char *str, int *index, int value, int flags);

union signed_value {
  char c;
  short s;
  int i;
  long l;
  long long ll;
  long double dll;
  double db;
};

union unsigned_value {
  unsigned char c;
  unsigned short s;
  unsigned int i;
  unsigned long l;
  unsigned long long ll;
};

typedef long long unsigned int s21_uintptr_t;

#endif
