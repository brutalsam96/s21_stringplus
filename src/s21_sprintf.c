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
  return done;   // proccesed values
}

int process_string(char *str, const char *format, va_list *args) {
  /* flags, width and precision modifiers*/

  char symbol = '%';
  const char *current = format;
  int str_index = 0;

  while (*current != '\0') {
    const char *next_symbol = s21_strchr(current, symbol);
    if (next_symbol) {
      markers mrk;
      mrk.flags = 0, mrk.width = 0, mrk.precision = -1;
      mrk.length_modifier = '\0';
      while (current < next_symbol) {
        str[str_index++] = *current++;
      }
      current++;
      parse_flags(&current, &mrk);
      parse_width(&current, args, &mrk);
      parse_precision(&current, args, &mrk);
      parse_length_modifiers(&current, &mrk);
      parse_type_spec(&current, str, args, &str_index, &mrk);

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

int parse_flags(const char **current, markers *mrk) {
  // printf("%c", *current);
  while (**current == '-' || **current == '+' || **current == ' ' ||
         **current == '#' || **current == '0') {
    switch (**current) {
      case '-':
        mrk->flags |= FLAG_LEFT;
        break;  // bitwise OR
      case '+':
        mrk->flags |= FLAG_SIGN;
        break;
      case ' ':
        mrk->flags |= FLAG_SPACE;
        break;
      case '#':
        mrk->flags |= FLAG_ALT;
        break;
      case '0':
        mrk->flags |= FLAG_ZERO;
        break;
    }
    (*current)++;
  }

  if (mrk->flags) {
    return 1;  // flag found
  } else {
    return 0;  // no flag found
  }
}

int parse_width(const char **current, va_list *args, markers *mrk) {
  mrk->width = 0;

  if (isdigit(**current)) {
    while (isdigit(**current)) {
      mrk->width = mrk->width * 10 + (**current - '0');
      (*current)++;
    }
    return 1;
  }

  if (**current == '*') {
    (*current)++;
    mrk->width = va_arg(*args, int);

    if (mrk->width < 0) {  // need a test case for this
      mrk->flags |= FLAG_LEFT;
      mrk->width = -(mrk->width);
    }
    return 1;
  }
  return 0;  // not found
}

int parse_precision(const char **current, va_list *args, markers *mrk) {
  if (**current == '.') {
    (*current)++;
    mrk->precision = 0;
    if (isdigit(**current)) {
      while (isdigit(**current)) {
        mrk->precision = mrk->precision * 10 + (**current - '0');
        (*current)++;
      }
    } else if (**current == '*') {
      (*current)++;
      mrk->precision = va_arg(*args, int);
      if (mrk->precision < 0) {
        mrk->precision = -1;
      }
    }
  }
  if ((mrk->precision) == -1) {
    return 1;  // no precision
  } else {
    return 0;  // found precision modifier
  }
}

int parse_length_modifiers(const char **current, markers *mrk) {
  switch (**current) {
    case 'h':
      mrk->length_modifier = 'h';
      (*current)++;
      break;
    case 'l':
      mrk->length_modifier = 'l';
      (*current)++;
      break;
    case 'L':
      mrk->length_modifier = 'L';
      (*current)++;
      break;
    default:
      mrk->length_modifier = '\0';
      return 0;  // no length modifier
  }
  if (mrk->length_modifier) {
    return 1;  // found length_modifier
  } else {
    return 0;  // no length modifier
  }
}

void parse_type_spec(const char **current, char *str, va_list *args, int *index,
           markers *mrk) {
  char spec = **current;
  if (spec == 'd' || spec == 'i') {
  union signed_value value = {0};
  if (mrk->length_modifier == 'h')
    value.s = (short)va_arg(*args, int);
  else if (mrk->length_modifier == 'l')
    value.l = va_arg(*args, long);
  else
    value.i = va_arg(*args, int);
  process_signed_int(str, &value, index, mrk);
  } else if (spec == 'u' || spec == 'o' || spec == 'x' || spec == 'X') {
  union unsigned_value u_value = {0};
  int base = (spec == 'o') ? 8 : ((spec == 'x' || spec == 'X') ? 16 : 10);
  if (mrk->length_modifier == 'h')
    u_value.s = (unsigned short)va_arg(*args, unsigned int);
  else if (mrk->length_modifier == 'l')
    u_value.l = va_arg(*args, unsigned long);
  else
    u_value.i = va_arg(*args, unsigned int);
  process_unsigned_int(str, &u_value, index, mrk, base, spec == 'X',
             (spec == 'x' || spec == 'X'));
  } else if (spec == 'F' || spec == 'f') {
  union signed_value value = {0};
  if (mrk->length_modifier == 'L')
    value.dll = va_arg(*args, long double);
  else
    value.db = va_arg(*args, double);
  process_float(str, &value, index, mrk, spec == 'F');
  } else if (spec == 'E' || spec == 'e') {
  union signed_value value = {0};
  if (mrk->length_modifier == 'L')
    value.dll = va_arg(*args, long double);
  else
    value.db = va_arg(*args, double);
  process_scientific(str, &value, index, mrk, spec == 'E');
  } else if (spec == 'g' || spec == 'G') {
  union signed_value value = {0};
  if (mrk->length_modifier == 'L')
    value.dll = va_arg(*args, long double);
  else
    value.db = va_arg(*args, double);
  process_compact(str, &value, index, mrk, spec == 'G');
  } else if (spec == 's')
  process_string_arg(str, args, index, mrk);
  else if (spec == 'c')
  process_char(str, args, index, mrk);
  else if (spec == 'p')
  process_pointer(str, args, index, mrk);
  else if (spec == 'n')
  process_char_counter(args, index);
  else if (spec == '%' )
  str[(*index)++] = '%';
  else
  str[(*index)++] = '%';
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
  int val_width = 0, temp_val = fabs((double)value);
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

int process_signed_int(char *str, void *value, int *index, markers *mrk) {
  if (mrk->precision == 0) return 0;
  int val = 0;
  long long long_val = 0;
  char itc[BUFSIZ] = {0};
  int len;

  if (mrk->length_modifier == 'h') {
    val = *(short *)value;
    s21_itoa(val, itc, 10);
  } else if (mrk->length_modifier == 'l') {
    long_val = *(long *)value;
    s21_lltoa(long_val, itc, 10);
  } else {
    val = *(int *)value;
    s21_itoa(val, itc, 10);
  }
  len = s21_strlen(itc);

  if (!(mrk->flags & FLAG_LEFT) && !(mrk->flags & FLAG_ZERO) &&
      mrk->width > len) {
    handle_width_padding(str, index, mrk->width - len, mrk->flags);
  }

  if (mrk->flags & FLAG_SIGN || mrk->flags & FLAG_SPACE || val < 0) {
    handle_sign_space(str, index, val, mrk->flags);
    (mrk->width)--;
  }

  if (!(mrk->flags & FLAG_LEFT) && (mrk->flags & FLAG_ZERO) &&
      mrk->width > len) {
    handle_width_padding(str, index, mrk->width - len, mrk->flags);
  }

  if (mrk->precision > len) {
    handle_precision_padding(str, index, mrk->precision, val);
  }

  s21_strcpy(&str[*index], itc);
  *index += len;

  if ((mrk->flags & FLAG_LEFT) && mrk->width > len) {
    if (mrk->flags & FLAG_ZERO) mrk->flags &= ~FLAG_ZERO;
    handle_width_padding(str, index, mrk->width - len, mrk->flags);
  }

  return 0;
}

int process_unsigned_int(char *str, void *u_value, int *index, markers *mrk,
                         int base, int IsUpper, int isX) {
  if (mrk->precision == 0) return 0;
  unsigned int val = 0;
  unsigned long long long_val = 0;
  char itc[BUFSIZ] = {0};
  int len;
  if (mrk->length_modifier == 'h') {
    // shorts and ints can use regular s21_itoa
    val = *(unsigned short *)u_value;
    s21_utoa(val, itc, base, IsUpper);
  } else if (mrk->length_modifier == 'l') {
    // long and long long use s21_ltoa
    long_val = *(unsigned long *)u_value;
    s21_llutoa(long_val, itc, base, IsUpper);
  } else {
    val = *(unsigned int *)u_value;
    s21_utoa(val, itc, base, IsUpper);
  }
  len = s21_strlen(itc);
  if (mrk->flags & FLAG_SIGN) mrk->flags &= ~FLAG_SIGN;
  if (!(mrk->flags & FLAG_LEFT) && !(mrk->flags & FLAG_ZERO) &&
      mrk->width > (mrk->flags & FLAG_ALT ? (isX ? len + 2 : len + 1) : len)) {
    handle_width_padding(
        str, index,
        mrk->width - (mrk->flags & FLAG_ALT ? (isX ? len + 2 : len + 1) : len),
        mrk->flags);
  }
  if (mrk->flags & FLAG_ALT && val != 0) {
    str[(*index)++] = '0';
    if (isX) str[(*index)++] = IsUpper ? 'X' : 'x';
  }
  if (!(mrk->flags & FLAG_LEFT) && (mrk->flags & FLAG_ZERO) &&
      mrk->width > (mrk->flags & FLAG_ALT ? (isX ? len + 2 : len + 1) : len)) {
    handle_width_padding(
        str, index,
        mrk->width - (mrk->flags & FLAG_ALT ? (isX ? len + 2 : len + 1) : len),
        mrk->flags);
  }

  if (mrk->precision >
      (mrk->flags & FLAG_ALT ? (isX ? len + 0 : len + 1) : len)) {
    handle_precision_pad_str(
        str, index, mrk->precision,
        (mrk->flags & FLAG_ALT ? (isX ? len + 0 : len + 1) : len));
  }

  s21_strcpy(&str[*index], itc);
  *index += len;

  if ((mrk->flags & FLAG_LEFT) && mrk->width > len) {
    if (mrk->flags & FLAG_ZERO) mrk->flags &= ~FLAG_ZERO;
    handle_width_padding(str, index, mrk->width - len, mrk->flags);
  }
  return 0;
}

int process_float(char *str, void *value, int *index, markers *mrk,
                  int IsUpper) {
  char itc[BUFSIZ] = {0};
  int len;
  long double val;

  if (mrk->precision == -1) mrk->precision = 6;

  if (mrk->length_modifier == 'L') {
    val = *(long double *)value;
    s21_lftoa(val, itc, mrk->precision);
  } else {
    val = *(double *)value;
    s21_ftoa(val, itc, mrk->precision);
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

  if (!(mrk->flags & FLAG_LEFT) && !(mrk->flags & FLAG_ZERO) &&
      mrk->width > len) {
    handle_width_padding(str, index, mrk->width - len, mrk->flags);
  }

  if (mrk->flags & FLAG_SIGN || mrk->flags & FLAG_SPACE || val < 0 ||
      (val == 0.0L && signbit(val))) {
    handle_sign_space(str, index, (signbit(val) ? -1 : 1), mrk->flags);
    (mrk->width)--;
  }

  if (!(mrk->flags & FLAG_LEFT) && (mrk->flags & FLAG_ZERO) &&
      mrk->width > len) {
    handle_width_padding(str, index, mrk->width - len, mrk->flags);
  }

  if (mrk->precision > len) {
    handle_precision_padding(str, index, mrk->precision, val);
  }
  s21_strcpy(&str[*index], itc);
  *index += len;

  if (mrk->flags & FLAG_ALT && mrk->precision == 0) {
    str[(*index)++] = '.';
  }
  if ((mrk->flags & FLAG_LEFT) && mrk->width > len) {
    if (mrk->flags & FLAG_ZERO) mrk->flags &= ~FLAG_ZERO;
    handle_width_padding(str, index, mrk->width - len, mrk->flags);
  }
  return 0;
}

int process_scientific(char *str, void *value, int *index, markers *mrk,
                       int IsUpper) {
  char itc[BUFSIZ] = {0};
  int exponent = 0;
  int len;
  double val;

  if (mrk->precision == -1) mrk->precision = 6;

  if (mrk->length_modifier == 'L') {
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

  exponent = round_to_sig_digits(&val, mrk->precision, 0);
  s21_ftoa(fabs(val), itc, mrk->precision);

  len = s21_strlen(itc);
  if (mrk->flags & FLAG_ALT && mrk->precision == 0) {
    itc[len++] = '.';
  }
  itc[len++] = IsUpper ? 'E' : 'e';
  itc[len++] = (exponent < 0) ? '-' : '+';
  if (fabs((double)exponent) < 10.0L)
    itc[len++] =
        '0';  // added cast to double might break the programm need to test
  s21_itoa(fabs((double)exponent), &itc[len], 10);

  len = s21_strlen(itc);

  if (!(mrk->flags & FLAG_LEFT) && !(mrk->flags & FLAG_ZERO) &&
      mrk->width > len) {
    handle_width_padding(str, index, mrk->width - len, mrk->flags);
  }

  if (mrk->flags & FLAG_SIGN || mrk->flags & FLAG_SPACE || val < 0 ||
      (val == 0.0L && signbit(val))) {
    handle_sign_space(str, index, (signbit(val) ? -1 : 1), mrk->flags);
    (mrk->width)--;
  }

  if (!(mrk->flags & FLAG_LEFT) && (mrk->flags & FLAG_ZERO) &&
      mrk->width > len) {
    handle_width_padding(str, index, mrk->width - len, mrk->flags);
  }

  if (mrk->precision > len) {
    handle_precision_padding(str, index, mrk->precision, val);
  }

  s21_strcpy(&str[*index], itc);
  *index += len;

  if ((mrk->flags & FLAG_LEFT) && mrk->width > len) {
    if (mrk->flags & FLAG_ZERO)
      mrk->flags &= ~FLAG_ZERO;  // COULD BE EXTRA LINE OF CODE NEED TO CHECK
    handle_width_padding(str, index, mrk->width - len, mrk->flags);
  }

  return 0;
}

int process_compact(char *str, void *value, int *index, markers *mrk,
                    int IsUpper) {
  char itc[BUFSIZ] = {0};
  int exponent = 0;
  int len;
  long double val;

  if (mrk->precision == -1)
    mrk->precision = 6;  // Default precision
  else if (mrk->precision == 0)
    mrk->precision = 1;  // %g with precision 0 → 1 sig digit

  if (mrk->length_modifier == 'L') {
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
  exponent = round_to_sig_digits_l(&val, &mrk->precision, 1);

  // Determine if scientific notation is needed
  if ((exponent < -4 || exponent >= mrk->precision)) {
    // Format for scientific notation
    s21_ftoa(fabsl(val), itc,
             mrk->precision - 1);  // Sig digs after decimal: precision-1
    if (!(mrk->flags & FLAG_ALT)) {
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
    mrk->precision = mrk->precision - 1 - exponent;
    if (mrk->precision < 0)
      mrk->precision = 0;
    else if (val == 0.0L && !(mrk->flags & FLAG_ALT))
      mrk->precision = 1;
    long double original_val = val * powl(10, exponent);
    s21_ftoa(original_val, itc, mrk->precision);
    if (!(mrk->flags & FLAG_ALT)) {
      int removed_zeroes = remove_trailing_zeroes(
          itc);  // Remove trailing zeros unless # flag is set
      mrk->precision -= removed_zeroes;
      if (mrk->precision < 0) mrk->precision = 0;
    }
  }

  len = s21_strlen(itc);

  if (!(mrk->flags & FLAG_LEFT) && !(mrk->flags & FLAG_ZERO) &&
      mrk->width > len) {
    handle_width_padding(str, index, mrk->width - len, mrk->flags);
  }

  if (mrk->flags & FLAG_SIGN || mrk->flags & FLAG_SPACE || val < 0 ||
      (val == 0.0L && signbit(val))) {
    handle_sign_space(str, index, (signbit(val) ? -1 : 1), mrk->flags);
    (mrk->width)--;
  }

  if (!(mrk->flags & FLAG_LEFT) && (mrk->flags & FLAG_ZERO) &&
      mrk->width > len) {
    handle_width_padding(str, index, mrk->width - len, mrk->flags);
  }

  if (mrk->precision > len) {
    handle_precision_padding(str, index, mrk->precision, val);
  }

  s21_strcpy(&str[*index], itc);
  *index += len;

  if (mrk->flags & FLAG_ALT && mrk->precision == 0) {
    str[(*index)++] = '.';
  }

  if ((mrk->flags & FLAG_LEFT) && mrk->width > len) {
    if (mrk->flags & FLAG_ZERO) mrk->flags &= ~FLAG_ZERO;
    handle_width_padding(str, index, mrk->width - len, mrk->flags);
  }

  return 0;
}

/* Removed flags, width, precision and length for string, char, char counter and
pointer i don't think they are required by task*/

int process_string_arg(char *str, va_list *args, int *index, markers *mrk) {
  char *value = va_arg(*args, char *);
  int val_len = s21_strlen(value);
  if (mrk->flags & FLAG_ZERO) mrk->flags &= ~FLAG_ZERO;

  if (!(mrk->flags & FLAG_LEFT) && mrk->width > val_len) {
    handle_width_padding(str, index, mrk->width - val_len, mrk->flags);
  }

  if (mrk->precision != -1) {
    if (mrk->precision > val_len) {
      mrk->precision = val_len;
    } else {
      val_len = mrk->precision;
    }
  }
  s21_strncpy(&str[*index], value, val_len);

  *index += val_len;
  if ((mrk->flags & FLAG_LEFT) && mrk->width > val_len) {
    handle_width_padding(str, index, mrk->width - val_len, mrk->flags);
  }
  return 0;
}

int process_char(char *str, va_list *args, int *index, markers *mrk) {
  char value = va_arg(*args, int);
  if (mrk->flags & FLAG_ZERO) mrk->flags &= ~FLAG_ZERO;
  if (mrk->flags & FLAG_SIGN) mrk->flags &= ~FLAG_SIGN;
  if (!(mrk->flags & FLAG_LEFT) && mrk->width > 1) {
    handle_width_padding(str, index, mrk->width - 1, mrk->flags);
  }
  str[*index] = (unsigned char)value;
  *index += 1;
  if ((mrk->flags & FLAG_LEFT) && mrk->width > 1) {
    handle_width_padding(str, index, mrk->width - 1, mrk->flags);
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

int process_pointer(char *str, va_list *args, int *index, markers *mrk) {
  char itc[BUFSIZ] = {0};
  void *value = va_arg(*args, void *);
  if (value == S21_NULL) {
    s21_strcpy(&str[*index], "(nil)");
    *index += 5;
    return 0;
  }
  s21_uintptr_t addr = (s21_uintptr_t)value;
  s21_llutoa(addr, itc, 16, 0);
  s21_strcpy(&str[*index], (mrk->flags & FLAG_SIGN) ? "+0x" : "0x");
  if (mrk->flags & FLAG_SIGN) {
    *index += 3;
  } else {
    *index += 2;
  }
  s21_strcpy(&str[*index], itc);
  *index += s21_strlen(itc);
  return 0;
}