#ifndef S21_STRING
#define S21_STRING

#include "s21_string.h"
#include "s21_sprintf.h"
#include <stdio.h>
#include <stdlib.h>

// String types
typedef long unsigned int s21_size_t;

// MACRO
#define S21_NULL 0





void *s21_memchr(const void *str, int c, s21_size_t n);
int s21_memcmp(const void *str1, const void *str2, s21_size_t n);
void *s21_memcpy(void *dest, const void *src, s21_size_t n);
void *s21_memset(void *str, int c, s21_size_t n);
char *s21_strncat(char *dest, const char *src, s21_size_t n);
char *s21_strchr(const char *str, int c);
int s21_strncmp(const char *str1, const char *str2, s21_size_t n);
char *s21_strncpy(char *dest, const char *src, s21_size_t n);
s21_size_t s21_strcspn(const char *str1, const char *str2);
char *s21_strerror(int errnum);
s21_size_t s21_strlen(const char *str);
char *s21_strpbrk(const char *str1, const char *str2);
char *s21_strrchr(const char *str, int c);
char *s21_strstr(const char *haystack, const char *needle);
char *s21_strtok(char *str, const char *delim);

char *s21_strcpy(char *dest, const char *src);
char *s21_strcat(char *dest, const char *src);

void *s21_to_upper(const char *str);
void *s21_to_lower(const char *str);
void *s21_insert(const char *src, const char *str, s21_size_t start_index);
int is_trim_char(char c, const char *trim_chars);
char *s21_trim(const char *src, const char *trim_chars);



typedef struct {
  int error_code;  // Error code (e.g., ENOENT)
  const char *
      message;  // Error message/description (e.g., "No such file or directory")
} ErrorCode;

#endif
