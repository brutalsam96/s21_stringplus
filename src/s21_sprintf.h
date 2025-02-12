#ifndef SPRINTF_H
#define SPRINTF_H

#include <ctype.h>
#include <limits.h>
#include <math.h>
#include <stdarg.h>
#include <stdio.h>

/* SPRINTF FLAGS */
#define FLAG_LEFT 1
#define FLAG_SIGN 2
#define FLAG_SPACE 4
#define FLAG_ALT 8
#define FLAG_ZERO 16

typedef struct {
  int flags;
  int width;
  int precision;
  char length_modifier;
} markers;

// main functions
int s21_sprintf(char *str, const char *format, ...);
int process_string(char *str, const char *format, va_list *args);

// parsers
int parse_flags(const char **current, markers *mrk);
int parse_width(const char **current, va_list *args, markers *mrk);
int parse_precision(const char **current, va_list *args, markers *mrk);
int parse_length_modifiers(const char **current, markers *mrk);
void parse_type_spec(const char **current, char *str, va_list *args, int *index, markers *mrk);

// process TODO GOTTA FIX VALUE types
int process_signed_int(char *str, void *value, int *index, markers *mrk);

int process_unsigned_int(char *str, void *u_value, int *index, markers *mrk, int base, int IsUpper, int isX);

int process_float(char *str, void *value, int *index, markers *mrk, int IsUpper);

int process_scientific(char *str, void *value, int *index, markers *mrk, int IsUpper);

int process_compact(char *str, void *value, int *index, markers *mrk, int IsUpper);

int process_string_arg(char *str, va_list *args, int *index, markers *mrk);
int process_char(char *str, va_list *args, int *index, markers *mrk);

int process_char_counter(va_list *args, int *index);

int process_pointer(char *str, va_list *args, int *index, markers *mrk);

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
