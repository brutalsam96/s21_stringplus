#include "s21_sprintf.h"

#include "s21_utils.h"
#include "string_functions.h"

/*%
    ### [flags][width][.precision][length]specifier
    %
*/
int s21_sprintf(char *str, const char *format, ...) {  // variadic
  int done;
  va_list args;
  va_start(args, format);
  done = process_string(str, format, &args);
  // printf("%d", done); // debug
  va_end(args);  // for cleanup
  return done;   // TODO need to test if it is returning correct amount of
                 // proccesed values
}

int process_string(char *str, const char *format, va_list *args) {
  /* flags, width and precision modifiers*/

  char symbol = '%';
  const char *current = format;
  int str_index = 0;

  while (*current != '\0') {
    const char *next_symbol = s21_strchr(current, symbol);
    if (next_symbol) {
      int flags = 0, width = 0, precision = -1;
      char length_modifier = '\0';
      while (current < next_symbol) {
        str[str_index++] = *current++;
      }
      current++;
      parse_flags(&current, &flags);
      parse_width(&current, &width, args, &flags);
      parse_precision(&current, &precision, args);
      parse_length_modifiers(&current, &length_modifier);
      parse_type_spec(&current, str, args, &str_index, flags, precision, width,
                      length_modifier);

    } else {
      while (*current != '\0') {
        // printf("%c\n", *current++);
        // printf("ran");
        str[str_index++] = *current++;
      }
    }
  }
  str[str_index] = '\0';
  return str_index;  // returns amount of chars appended
}

int parse_flags(const char **current, int *flags) {
  // printf("%c", *current);
  while (**current == '-' || **current == '+' || **current == ' ' ||
         **current == '#' || **current == '0') {
    switch (**current) {
      case '-':
        *flags |= FLAG_LEFT;
        break;  // bitwise OR
      case '+':
        *flags |= FLAG_SIGN;
        break;
      case ' ':
        *flags |= FLAG_SPACE;
        break;
      case '#':
        *flags |= FLAG_ALT;
        break;
      case '0':
        *flags |= FLAG_ZERO;
        break;
    }
    (*current)++;
  }

  if (*flags) {
    return 1;  // flag found
  } else {
    return 0;  // no flag found
  }
}

int parse_width(const char **current, int *width, va_list *args, int *flags) {
  *width = 0;

  if (isdigit(**current)) {
    while (isdigit(**current)) {
      *width = *width * 10 + (**current - '0');
      (*current)++;
    }
    return 1;
  }

  if (**current == '*') {
    (*current)++;
    *width = va_arg(*args, int);

    if (*width < 0) {  // need a test case for this
      *flags |= FLAG_LEFT;
      *width = -(*width);
    }
    return 1;
  }
  return 0;  // not found
}

int parse_precision(const char **current, int *precision, va_list *args) {
  if (**current == '.') {
    (*current)++;
    *precision = 0;
    if (isdigit(**current)) {
      while (isdigit(**current)) {
        *precision = *precision * 10 + (**current - '0');
        (*current)++;
      }
    } else if (**current == '*') {
      (*current)++;
      *precision = va_arg(*args, int);
      if (*precision < 0) {
        *precision = -1;
      }
    }
  }
  if ((*precision) == -1) {
    return 1;  // no precision
  } else {
    return 0;  // found precision modifier
  }
}

int parse_length_modifiers(const char **current, char *length_modifier) {
  switch (**current) {
    case 'h':
      *length_modifier = 'h';
      (*current)++;
      break;
    case 'l':
      *length_modifier = 'l';
      (*current)++;
      break;
    case 'L':
      *length_modifier = 'L';
      (*current)++;
      break;
    default:
      *length_modifier = '\0';
      return 0;  // no length modifier
  }
  if (*length_modifier) {
    return 1;  // found length_modifier
  } else {
    return 0;  // no length modifier
  }
}

// can use ternary on uppercases to reduce function size if needed
void parse_type_spec(const char **current, char *str, va_list *args, int *index,
                     int flags, int precision, int width,
                     char length_modifiers) {
  union signed_value value = {0};
  union unsigned_value u_value = {0};
  int base = 10;
  switch (**current) {
    case 'd':
    case 'i':
      // logic to write decimal signed ints
      switch (length_modifiers) {
        case 'h':
          value.s = (short)va_arg(*args, int);
          break;
        case 'l':
          value.l = va_arg(*args, long);
          break;
        default:
          value.i = va_arg(*args, int);
      }

      process_signed_int(str, &value, index, &flags, &width, &precision,
                         length_modifiers);
      break;

    case 'u':
      // logic to process unsigned integers
      base = 10;
      switch (length_modifiers) {
        case 'h':
          u_value.s = (unsigned short)va_arg(*args, unsigned int);
          break;
        case 'l':
          u_value.l = va_arg(*args, unsigned long);
          break;
        default:
          u_value.i = va_arg(*args, unsigned int);
      }
      process_unsigned_int(str, &u_value, index, &flags, &width, &precision,
                           length_modifiers, base, 0, 0);
      break;
    case 'o':
      // logic to process unsigned integers in base 8
      base = 8;
      switch (length_modifiers) {
        case 'h':
          u_value.s = (unsigned short)va_arg(*args, unsigned int);
          break;
        case 'l':
          u_value.l = va_arg(*args, unsigned long);
          break;
        default:
          u_value.i = va_arg(*args, unsigned int);
      }
      process_unsigned_int(str, &u_value, index, &flags, &width, &precision,
                           length_modifiers, base, 0, 0);
      break;
    case 'X':
    case 'x':
      // logic to process unsigned integers in base 16, lowercase
      base = 16;
      switch (length_modifiers) {
        case 'h':
          u_value.s = (unsigned short)va_arg(*args, unsigned int);
          break;
        case 'l':
          u_value.l = va_arg(*args, unsigned long);
          break;
        default:
          u_value.i = va_arg(*args, unsigned int);
      }
      process_unsigned_int(str, &u_value, index, &flags, &width, &precision,
                           length_modifiers, base, **current == 'X', 1);
      break;
    case 'F':
    case 'f':
      // logic to process scientific
      switch (length_modifiers) {
        case 'L':
          value.dll = va_arg(*args, long double);
          break;
        default:
          value.db = va_arg(*args, double);
      }
      process_float(str, &value, index, &flags, &width, &precision,
                    length_modifiers, **current == 'F');
      break;
    case 'E':
    case 'e':
      // logic to process scientific uppercase
      switch (length_modifiers) {
        case 'L':
          value.dll = va_arg(*args, long double);
          break;
        default:
          value.db = va_arg(*args, double);
      }
      process_scientific(str, &value, index, &flags, &width, &precision,
                         length_modifiers,
                         **current == 'E');  // tricky operator comparision
      break;
    case 'g':
    case 'G':
      // logic to process scientific
      switch (length_modifiers) {
        case 'L':
          value.dll = va_arg(*args, long double);
          break;
        default:
          value.db = va_arg(*args, double);
      }
      process_compact(str, &value, index, &flags, &width, &precision,
                      length_modifiers, **current == 'G');
      break;
    case 's':
      // logic to process strings
      process_string_arg(str, args, index, &flags, &width);
      break;
    case 'c':
      // logic to process chars
      process_char(str, args, index, &flags, &width);
      break;
    case 'p':
      // logic to process pointers
      process_pointer(str, args, index, &flags);
      break;
    case 'n':
      // write number of characters written so far
      process_char_counter(args, index);
      break;
    case '%':
      // put '%'
      str[*index] = '%';
      *index += 1;
      break;
    default:
      // handle invalid input
      break;
  }
  (*current)++;
}

void handle_width_padding(char *str, int *index, int width, int flags) {
  if (flags & FLAG_ZERO) {
    for (int i = 0; i < width; i++) {
      str[(*index)++] = '0';
    }
  } else if (flags & FLAG_LEFT) {
    for (int i = 0; i < width; i++) {
      str[(*index)++] = ' ';
    }
  } else {
    if ((flags & FLAG_SIGN) || (flags & FLAG_SPACE))
      width--;  // TODO fix this so it modifies width pointer and can remove
                // extra step to modify on sign if block
    for (int i = 0; i < width; i++) {
      str[(*index)++] = ' ';
    }
  }
}

void handle_precision_padding(char *str, int *index, int precision, int value) {
  int val_width = 1, temp_val = fabs((double)value);
  for (; temp_val > 0; val_width++) {
    temp_val /= 10;
  }
  int new_precision = (precision > val_width) ? (precision - val_width) : 0;
  if (new_precision > 0) {
    for (int i = 0; i < new_precision; i++) {
      str[(*index)++] = '0';
    }
  }
}

void handle_precision_pad_str(char *str, int *index, int precision, int len) {
  if (precision > 0) {
    for (; len < precision; len++) {
      str[(*index)++] = '0';
    }
  }
}

// void handle_precision_padding(char *str, int *index, int precision, int
// value) {
//   int val_width = 1, temp_val = value;
//   for (val_width++; temp_val > 0;) {
//     temp_val /= 10;
//   }
//   int new_precision = precision - val_width;
//   for (int i = 0; i < new_precision; i++) {
//     str[(*index)++] = '0';
//   }
// }

void handle_sign_space(char *str, int *index, int value, int flags) {
  if (value >= 0) {
    if (flags & FLAG_SIGN) {
      str[(*index)++] = '+';
    } else if (flags & FLAG_SPACE) {
      str[(*index)++] = ' ';
    }
  } else if (value < 0.0L) {
    str[(*index)++] = '-';
  }
}

int process_signed_int(char *str, void *value, int *index, int *flags,
                       int *width, int *precision, char length_modifier) {
  int val = 0;
  long long long_val = 0;
  char itc[BUFSIZ] = {0};
  int len;

  if (length_modifier == 'h') {
    val = *(short *)value;
    s21_itoa(val, itc, 10);
  } else if (length_modifier == 'l') {
    long_val = *(long *)value;
    s21_lltoa(long_val, itc, 10);
  } else {
    val = *(int *)value;
    s21_itoa(val, itc, 10);
  }

  len = s21_strlen(itc);

  if (!(*flags & FLAG_LEFT) && !(*flags & FLAG_ZERO) && *width > len) {
    handle_width_padding(str, index, *width - len, *flags);
  }

  if (*flags & FLAG_SIGN || *flags & FLAG_SPACE || val < 0) {
    handle_sign_space(str, index, val, *flags);
    (*width)--;
  }

  if (!(*flags & FLAG_LEFT) && (*flags & FLAG_ZERO) && *width > len) {
    handle_width_padding(str, index, *width - len, *flags);
  }

  if (*precision > len) {
    handle_precision_padding(str, index, *precision, val);
  }

  s21_strcpy(&str[*index], itc);
  *index += len;

  if ((*flags & FLAG_LEFT) && *width > len) {
    if (*flags & FLAG_ZERO) *flags &= ~FLAG_ZERO;
    handle_width_padding(str, index, *width - len, *flags);
  }

  return 0;
}

int process_unsigned_int(char *str, void *u_value, int *index, int *flags,
                         int *width, int *precision, char length_modifier,
                         int base, int IsUpper, int isX) {
  unsigned int val = 0;
  unsigned long long long_val = 0;
  char itc[BUFSIZ] = {0};
  int len;

  if (length_modifier == 'h') {  // TODO GOTTA CHECK ALL LENGTH MODIFIERS
    // shorts and ints can use regular s21_itoa
    val = *(unsigned short *)u_value;
    s21_utoa(val, itc, base, IsUpper);
  } else if (length_modifier == 'l') {
    // long and long long use s21_ltoa
    long_val = *(unsigned long *)u_value;
    s21_llutoa(long_val, itc, base, IsUpper);
  } else {
    val = *(unsigned int *)u_value;
    s21_utoa(val, itc, base, IsUpper);
  }

  len = s21_strlen(itc);

  if (*flags & FLAG_SIGN) *flags &= ~FLAG_SIGN;

  if (!(*flags & FLAG_LEFT) && !(*flags & FLAG_ZERO) &&
      *width > (*flags & FLAG_ALT ? (isX ? len + 2 : len + 1) : len)) {
    handle_width_padding(
        str, index,
        *width - (*flags & FLAG_ALT ? (isX ? len + 2 : len + 1) : len), *flags);
  }

  if (*flags & FLAG_ALT && val != 0) {
    str[(*index)++] = '0';
    if (isX) str[(*index)++] = IsUpper ? 'X' : 'x';
  }

  if (!(*flags & FLAG_LEFT) && (*flags & FLAG_ZERO) &&
      *width > (*flags & FLAG_ALT ? (isX ? len + 2 : len + 1) : len)) {
    handle_width_padding(
        str, index,
        *width - (*flags & FLAG_ALT ? (isX ? len + 2 : len + 1) : len), *flags);
  }

  if (*precision > (*flags & FLAG_ALT ? (isX ? len + 0 : len + 1) : len)) {
    handle_precision_pad_str(
        str, index, *precision,
        (*flags & FLAG_ALT ? (isX ? len + 0 : len + 1) : len));
  }

  s21_strcpy(&str[*index], itc);
  *index += len;

  if ((*flags & FLAG_LEFT) && *width > len) {
    if (*flags & FLAG_ZERO) *flags &= ~FLAG_ZERO;
    handle_width_padding(str, index, *width - len, *flags);
  }
  return 0;
}

int process_float(char *str, void *value, int *index, int *flags, int *width,
                  int *precision, char length_modifier, int IsUpper) {
  char itc[BUFSIZ] = {0};
  int len;
  long double val;

  if (*precision == -1) *precision = 6;

  if (length_modifier == 'L') {
    val = *(long double *)value;
    s21_lftoa(val, itc, *precision);
  } else {
    val = *(double *)value;
    s21_ftoa(val, itc, *precision);
  }

  if (isinf(val)) {
    s21_strcpy(&str[*index], (val < 0) ? IsUpper ? "-INF" : "-inf"
                             : IsUpper ? "INF"
                                       : "inf");
    *index += (val < 0) ? 4 : 3;
    return -1;
  }
  if (isnan(val)) {
    s21_strcpy(&str[*index], IsUpper ? "NAN" : "nan");
    *index += 3;
    return -1;
  }

  len = s21_strlen(itc);

  if (!(*flags & FLAG_LEFT) && !(*flags & FLAG_ZERO) && *width > len) {
    handle_width_padding(str, index, *width - len, *flags);
  }

  if (*flags & FLAG_SIGN || *flags & FLAG_SPACE || val < 0 ||
      (val == 0.0L && signbit(val))) {
    handle_sign_space(str, index, (signbit(val) ? -1 : 1), *flags);
    (*width)--;
  }

  if (!(*flags & FLAG_LEFT) && (*flags & FLAG_ZERO) && *width > len) {
    handle_width_padding(str, index, *width - len, *flags);
  }

  if (*precision > len) {
    handle_precision_padding(str, index, *precision, val);
  }
  s21_strcpy(&str[*index], itc);
  *index += len;

  if (*flags & FLAG_ALT && *precision == 0) {
    str[(*index)++] = '.';
  }
  if ((*flags & FLAG_LEFT) && *width > len) {
    if (*flags & FLAG_ZERO) *flags &= ~FLAG_ZERO;
    handle_width_padding(str, index, *width - len, *flags);
  }
  return 0;
}

int process_scientific(char *str, void *value, int *index, int *flags,
                       int *width, int *precision, char length_modifier,
                       int IsUpper) {
  char itc[BUFSIZ] = {0};
  int exponent = 0;
  int len;
  double val;

  if (*precision == -1) *precision = 6;

  if (length_modifier == 'L') {
    val = *(long double *)value;
    // if (*precision == 0) val = roundl(val);

  } else {
    val = *(double *)value;
    // if (*precision == 0) val = roundl(val);
  }

  if (isinf(val)) {
    s21_strcpy(&str[*index], (val < 0) ? IsUpper ? "-INF" : "-inf"
                             : IsUpper ? "INF"
                                       : "inf");
    *index += (val < 0) ? 4 : 3;
    return 0;
  }
  if (isnan(val)) {
    s21_strcpy(&str[*index], IsUpper ? "NAN" : "nan");
    *index += 3;
    return 0;
  }

  // TODO handle case 0.0L here
  exponent = round_to_sig_digits(&val, precision, 0);
  // TODO need else block to handle value == 0

  s21_ftoa(fabs(val), itc, *precision);

  len = s21_strlen(itc);
  if (*flags & FLAG_ALT && *precision == 0) {
    itc[len++] = '.';
  }
  itc[len++] = IsUpper ? 'E' : 'e';
  itc[len++] = (exponent < 0) ? '-' : '+';
  if (fabs((double)exponent) < 10.0L)
    itc[len++] =
        '0';  // added cast to double might break the programm need to test
  s21_itoa(fabs((double)exponent), &itc[len], 10);

  len = s21_strlen(itc);

  if (!(*flags & FLAG_LEFT) && !(*flags & FLAG_ZERO) && *width > len) {
    handle_width_padding(str, index, *width - len, *flags);
  }

  if (*flags & FLAG_SIGN || *flags & FLAG_SPACE || val < 0 ||
      (val == 0.0L && signbit(val))) {
    handle_sign_space(str, index, (signbit(val) ? -1 : 1), *flags);
    (*width)--;
  }

  if (!(*flags & FLAG_LEFT) && (*flags & FLAG_ZERO) && *width > len) {
    handle_width_padding(str, index, *width - len, *flags);
  }

  if (*precision > len) {
    handle_precision_padding(str, index, *precision, val);
  }

  s21_strcpy(&str[*index], itc);
  *index += len;

  if ((*flags & FLAG_LEFT) && *width > len) {
    if (*flags & FLAG_ZERO)
      *flags &= ~FLAG_ZERO;  // TODO COULD BE EXTRA NEED TO CHECK
    handle_width_padding(str, index, *width - len, *flags);
  }

  return 0;
}

int process_compact(char *str, void *value, int *index, int *flags, int *width,
                    int *precision, char length_modifier, int IsUpper) {
  char itc[BUFSIZ] = {0};
  int exponent = 0;
  int len;
  long double val;

  if (*precision == -1)
    *precision = 6;  // Default precision
  else if (*precision == 0)
    *precision = 1;  // %g with precision 0 → 1 sig digit

  if (length_modifier == 'L') {
    val = *(long double *)value;
  } else {
    val = *(double *)value;
  }

  if (isinf(val)) {
    s21_strcpy(&str[*index], (val < 0) ? IsUpper ? "-INF" : "-inf"
                             : IsUpper ? "INF"
                                       : "inf");
    *index += (val < 0) ? 4 : 3;
    return 0;
  }
  if (isnan(val)) {
    s21_strcpy(&str[*index], IsUpper ? "NAN" : "nan");
    *index += 3;
    return 0;
  }
  exponent = round_to_sig_digits_l(&val, precision, 1);

  // Determine if scientific notation is needed
  if ((exponent < -4 || exponent >= *precision)) {
    // Format for scientific notation
    s21_ftoa(fabsl(val), itc,
             *precision - 1);  // Sig digs after decimal: precision-1
    if (!(*flags & FLAG_ALT)) {
      remove_trailing_zeroes(itc);  // Remove insignificant zeros
    }
    len = s21_strlen(itc);
    itc[len++] = IsUpper ? 'E' : 'e';
    itc[len++] = (exponent < 0) ? '-' : '+';
    if (fabs((double)exponent) < 10)
      itc[len++] = '0';  // Leading zero for single-digit exponents cast to
                         // double b4 fabl might break it so check it
    s21_itoa(fabs((double)exponent), &itc[len], 10);
  } else {
    // Fixed notation
    *precision = *precision - 1 - exponent;
    if (*precision < 0)
      *precision = 0;
    else if (val == 0.0L && !(*flags & FLAG_ALT))
      *precision = 1;
    long double original_val = val * powl(10, exponent);
    s21_ftoa(original_val, itc, *precision);
    if (!(*flags & FLAG_ALT)) {
      int removed_zeroes = remove_trailing_zeroes(
          itc);  // Remove trailing zeros unless # flag is set
      *precision -= removed_zeroes;
      if (*precision < 0) *precision = 0;
    }
  }

  len = s21_strlen(itc);

  if (!(*flags & FLAG_LEFT) && !(*flags & FLAG_ZERO) && *width > len) {
    handle_width_padding(str, index, *width - len, *flags);
  }

  if (*flags & FLAG_SIGN || *flags & FLAG_SPACE || val < 0 ||
      (val == 0.0L && signbit(val))) {
    handle_sign_space(str, index, (signbit(val) ? -1 : 1), *flags);
    (*width)--;
  }

  if (!(*flags & FLAG_LEFT) && (*flags & FLAG_ZERO) && *width > len) {
    handle_width_padding(str, index, *width - len, *flags);
  }

  if (*precision > len) {
    handle_precision_padding(str, index, *precision, val);
  }

  s21_strcpy(&str[*index], itc);
  *index += len;

  if (*flags & FLAG_ALT && *precision == 0) {
    str[(*index)++] = '.';
  }

  if ((*flags & FLAG_LEFT) && *width > len) {
    if (*flags & FLAG_ZERO) *flags &= ~FLAG_ZERO;
    handle_width_padding(str, index, *width - len, *flags);
  }

  return 0;
}

/* Removed flags, width, precision and length for string, char, char counter and
pointer i don't think they are required by task*/

int process_string_arg(char *str, va_list *args, int *index, int *flags,
                       int *width) {
  char *value = va_arg(*args, char *);
  int val_len = s21_strlen(value);
  if (*flags & FLAG_ZERO) *flags &= ~FLAG_ZERO;

  if (!(*flags & FLAG_LEFT) && *width > val_len) {
    handle_width_padding(str, index, *width - val_len, *flags);
  }
  s21_strcpy(&str[*index], value);
  *index += val_len;
  if ((*flags & FLAG_LEFT) && *width > val_len) {
    handle_width_padding(str, index, *width - val_len, *flags);
  }
  return 0;
}

int process_char(char *str, va_list *args, int *index, int *flags, int *width) {
  char value = va_arg(*args, int);
  if (*flags & FLAG_ZERO) *flags &= ~FLAG_ZERO;
  if (*flags & FLAG_SIGN) *flags &= ~FLAG_SIGN;
  if (!(*flags & FLAG_LEFT) && *width > 1) {
    handle_width_padding(str, index, *width - 1, *flags);
  }
  str[*index] = (unsigned char)value;
  *index += 1;
  if ((*flags & FLAG_LEFT) && *width > 1) {
    handle_width_padding(str, index, *width - 1, *flags);
  }
  return 0;
}

int process_char_counter(va_list *args, int *index) {
  int *value = va_arg(*args, int *);
  *value = *index;
  char itc[BUFSIZ] = {0};
  *index += s21_strlen(itc);
  return 0;
}

int process_pointer(char *str, va_list *args, int *index, int *flags) {
  // Padding should work with pointer ? should it ??? removed implementation
  // might need to add it though
  char itc[BUFSIZ] = {0};
  void *value = va_arg(*args, void *);
  s21_uintptr_t addr = (s21_uintptr_t)value;
  s21_llutoa(addr, itc, 16, 0);
  s21_strcpy(&str[*index], (*flags & FLAG_SIGN) ? "+0x" : "0x");
  if (*flags & FLAG_SIGN) {
    *index += 3;
  } else {
    *index += 2;
  }
  s21_strcpy(&str[*index], itc);
  *index += s21_strlen(itc);
  return 0;
}

// int main() {
// char buff[256];
// char buff2[256];
// s21_sprintf(buff, "ab %-010g cd", 5.0);
// sprintf(buff2, "ab %-010g cd", 5.0);
// printf("s21: %s\n std: %s\n", buff, buff2);
//   char buff3[256];
//   char buff4[256];
//   char buff5[256];
//   char buff6[256];
// s21_sprintf(buff, "ab %g cd", 123.0);
// sprintf(buff2, "ab %g cd", 12454645.0348);
// s21_sprintf(buff, "ab %.3g cd", 12345.67);
// sprintf(buff2, "ab %.3g cd", 12345.67);

// s21_sprintf(buff, "ab %p cd", p);
// sprintf(buff2, "ab %p cd", p);

//   s21_sprintf(buff, "ab %#x cd", 351351351);
//   sprintf(buff2, "ab %#x cd", 351351351);

// sprintf(buff2, "ab %.0g cd", 0.0042069);
// s21_sprintf(buff, "ab %g cd", 1.435800);
// sprintf(buff2, "ab %g cd", 1.435800);
// s21_sprintf(buff, "ab %.e cd", -123.45);
// sprintf(buff2, "ab %.e cd", -123.45);

// /* %O ALT TESTS CHECK */
//   printf("************************\n");
//   s21_sprintf(buff, "%#o", 8);
//   s21_sprintf(buff2, "%#o", 0);
//   s21_sprintf(buff3, "%- #6o", 8);
//   s21_sprintf(buff4, "%0#6o", 8);
//   s21_sprintf(buff5, "%#.4o", 8);
//   s21_sprintf(buff6, "%#6o", 8);

//   printf("%s\n", buff);
//   printf("%s\n", buff2);
//   printf("%s\n", buff3);
//   printf("%s\n", buff4);
//   printf("%s\n", buff5);
//   printf("%s\n", buff6);
//   printf("----------------\n");
//   sprintf(buff, "%#o", 8);
//   sprintf(buff2, "%#o", 0);
//   sprintf(buff3, "%- #6o", 8);
//   sprintf(buff4, "%0#6o", 8);
//   sprintf(buff5, "%#.4o", 8);
//   sprintf(buff6, "%#6o", 8);

//   printf("%s\n", buff);
//   printf("%s\n", buff2);
//   printf("%s\n", buff3);
//   printf("%s\n", buff4);
//   printf("%s\n", buff5);
//   printf("%s\n", buff6);
//   printf("************************\n");
// /* %X ALT TESTS CHECK */
//   printf("************************\n");
//   s21_sprintf(buff,  "%#x", 	    255);
//   s21_sprintf(buff2, "%#X", 	    255);
//   s21_sprintf(buff3, "%#6x",    	15);
//   s21_sprintf(buff4, "%- #8X",  	15);
//   s21_sprintf(buff5, "%#08x",   	15);
//   s21_sprintf(buff6, "%#.4x",   	15);

//   printf("%s\n", buff);
//   printf("%s\n", buff2);
//   printf("%s\n", buff3);
//   printf("%s\n", buff4);
//   printf("%s\n", buff5);
//   printf("%s\n", buff6);
//   printf("----------------\n");

//   sprintf(buff,  "%#x", 	    255);
//   sprintf(buff2, "%#X", 	    255);
//   sprintf(buff3, "%#6x",    	15);
//   sprintf(buff4, "%- #8X",  	15);
//   sprintf(buff5, "%#08x",   	15);
//   sprintf(buff6, "%#.4x",   	15);

//   printf("%s\n", buff);
//   printf("%s\n", buff2);
//   printf("%s\n", buff3);
//   printf("%s\n", buff4);
//   printf("%s\n", buff5);
//   printf("%s\n", buff6);
//   printf("************************\n");
// /* %F ALT TESTS CHECK */
//   printf("************************\n");
//   s21_sprintf(buff,  "%#.0f"	, 3.0	);
//   s21_sprintf(buff2, "%#.2f"	, 3	    );
//   s21_sprintf(buff3, "%+#.0f"	, 3.0	);
//   s21_sprintf(buff4, "% -#10.2f", 3.5	);
//   s21_sprintf(buff5, "%0#10.2f"	, 3.5	);
//   s21_sprintf(buff6, "%#.0f"	, 0.0	);

//   printf("%s\n", buff);
//   printf("%s\n", buff2);
//   printf("%s\n", buff3);
//   printf("%s\n", buff4);
//   printf("%s\n", buff5);
//   printf("%s\n", buff6);
//   printf("----------------\n");

//   sprintf(buff,  "%#.0f"	, 3.0	);
//   sprintf(buff2, "%#.2f"	, 3	    );
//   sprintf(buff3, "%+#.0f"	, 3.0	);
//   sprintf(buff4, "% -#10.2f", 3.5	);
//   sprintf(buff5, "%0#10.2f"	, 3.5	);
//   sprintf(buff6, "%#.0f"	, 0.0	);

//   printf("%s\n", buff);
//   printf("%s\n", buff2);
//   printf("%s\n", buff3);
//   printf("%s\n", buff4);
//   printf("%s\n", buff5);
//   printf("%s\n", buff6);
//   printf("************************\n");
// /* %E ALT TEST CHECK */
//   printf("************************\n");
//   s21_sprintf(buff,  "%#.0e"	, 3000.0	);
//   s21_sprintf(buff2, "%#.3e"	, 100.0    );
//   s21_sprintf(buff3, "%+#10.2e"	, 123.456	);
//   s21_sprintf(buff4, "%- #.4e"	, 123.456	);
//   s21_sprintf(buff5, "%0#12.3e"	, 7.89	);

//   printf("%s\n", buff);
//   printf("%s\n", buff2);
//   printf("%s\n", buff3);
//   printf("%s\n", buff4);
//   printf("%s\n", buff5);

//   printf("----------------\n");

//   sprintf(buff,  "%#.0e"	, 3000.0	);
//   sprintf(buff2, "%#.3e"	, 100.0    );
//   sprintf(buff3, "%+#10.2e"	, 123.456	);
//   sprintf(buff4, "%- #.4e"	, 123.456	);
//   sprintf(buff5, "%0#12.3e"	, 7.89	);

//   printf("%s\n", buff);
//   printf("%s\n", buff2);
//   printf("%s\n", buff3);
//   printf("%s\n", buff4);
//   printf("%s\n", buff5);
//   printf("************************\n");
//   /* %G ALT TEST CHECK */
//   printf("************************\n");
//   s21_sprintf(buff,  "%#g"	    ,3.0	);
//   s21_sprintf(buff2, "%#g"	    ,123.0);
//   s21_sprintf(buff3, "%#.3g"	,12345);
//   s21_sprintf(buff4, "%#.5g"	,123.456);
//   s21_sprintf(buff5, "%+#.0g"	,5.0);
//   s21_sprintf(buff6, "%#.4g"	,0.00123);

//   printf("%s\n", buff);
//   printf("%s\n", buff2);
//   printf("%s\n", buff3);
//   printf("%s\n", buff4);
//   printf("%s\n", buff5);
//   printf("%s\n", buff6);
//   printf("----------------\n");

//   sprintf(buff,  "%#g"	    ,3.0	);
//   sprintf(buff2, "%#g"	    ,123.0);
//   sprintf(buff3, "%#.3g"	,12345);
//   sprintf(buff4, "%#.5g"	,123.456);
//   sprintf(buff5, "%+#.0g"	,5.0);
//   sprintf(buff6, "%#.4g"	,0.00123);

// printf("%s\n", buff);
// printf("%s\n", buff2);
//   printf("%s\n", buff3);
//   printf("%s\n", buff4);
//   printf("%s\n", buff5);
//   printf("%s\n", buff6);
//   printf("************************\n");

//   return 0;
// }

// need to test negative numbers with hex and octal

// need to test this too
// s21_sprintf(buff1, "ab %#g cd", 0.0);
// sprintf(buff2, "ab %#g cd", 0.0);
// test cases for negative zeroes
// s21_sprintf(buff1, "ab %f cd", -0.0);
// sprintf(buff2, "ab %f cd", -0.0);