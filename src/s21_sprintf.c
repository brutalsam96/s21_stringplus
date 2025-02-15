#include "s21_sprintf.h"
#include "s21_string.h"

/*%
    [flags][width][.precision][length]specifier
*/
int s21_sprintf(char *str, const char *format, ...) {  // variadic
  int done;
  va_list args;
  va_start(args, format);
  done = process_string(str, format, &args);
  va_end(args); 
  return done; 
}

