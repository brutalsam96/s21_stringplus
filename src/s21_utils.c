#include "s21_sprintf.h"
#include "s21_string.h"

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
  } else if (spec == 's') {
    union signed_value value = {0};
    if (mrk->length_modifier == 'l')
      value.wcstr = va_arg(*args, wchar_t *);
    else
      value.str = va_arg(*args, char *);
    process_string_arg(str, &value, index, mrk);
  } else if (spec == 'c') {
    union signed_value value = {0};
    if (mrk->length_modifier == 'l')
      value.wc = va_arg(*args, wchar_t);
    else
      value.c = va_arg(*args, int);
    process_char(str, &value, index, mrk);
  } else if (spec == 'p')
    process_pointer(str, args, index, mrk);
  else if (spec == 'n')
    process_char_counter(args, index);
  else if (spec == '%')
    str[(*index)++] = '%';
  else
    str[(*index)++] = '%';
  (*current)++;
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

  exponent = round_to_sig_digits(&val, &mrk->precision, 0);
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

int process_string_arg(char *str, void *value, int *index, markers *mrk) {
  char *val;
  char *temp;

  if (mrk->length_modifier == 'l') {
    wchar_t *wstr = ((union signed_value *)value)->wcstr;
    size_t wlen = wcslen(wstr);
    temp = (char *)malloc((wlen * MB_CUR_MAX + 1) * sizeof(char));
    wcstombs(temp, wstr, wlen * MB_CUR_MAX + 1);
    val = temp;
  } else {
    val = (((union signed_value *)value)->str);
  }

  int val_len = s21_strlen(val);
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
  s21_strncpy(&str[*index], val, val_len);

  *index += val_len;
  if ((mrk->flags & FLAG_LEFT) && mrk->width > val_len) {
    handle_width_padding(str, index, mrk->width - val_len, mrk->flags);
  }
  if (mrk->length_modifier == 'l') free(temp);
  return 0;
}

int process_char(char *str, void *value, int *index, markers *mrk) {
  wchar_t val;

  if (mrk->length_modifier == 'l') {
    val = *(wchar_t *)value;
  } else {
    val = *(char *)value;
  }

  if (mrk->flags & FLAG_ZERO) mrk->flags &= ~FLAG_ZERO;
  if (mrk->flags & FLAG_SIGN) mrk->flags &= ~FLAG_SIGN;
  if (!(mrk->flags & FLAG_LEFT) && mrk->width > 1) {
    handle_width_padding(str, index, mrk->width - 1, mrk->flags);
  }
  str[*index] = val;
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

void reverse(char *str, int length) {
  int start = 0;
  int end = length - 1;
  while (start < end) {
    char temp = str[start];
    str[start] = str[end];
    str[end] = temp;
    start++;
    end--;
  }
}

int round_to_sig_digits(double *value, int *precision, int IsComp) {
  if (*value == 0.0) return 0;

  int exponent = (int)floor(log10(fabs(*value)));

  if (IsComp) {
    // %g: Round to 'precision' significant digits
    double scale = pow(10, *precision - 1 - exponent);
    *value = round(*value * scale) / scale;

    // Recalculate exponent post-rounding
    if (*value != 0.0) {
      exponent = (int)floor(log10(fabs(*value)));
      double norm_scale = pow(10, exponent);
      *value /= norm_scale;

      // Handle cases where rounding pushed value to 10.0 or 0.0999
      if (*value >= 10.0) {
        *value /= 10.0;
        exponent++;
      } else if (*value < 1.0) {
        *value *= 10.0;
        exponent--;
      }
    }
  } else {
    // %e: Normalize to [1.0, 10.0)
    double scale = pow(10, -exponent);
    *value *= scale;
    if (*value >= 10.0) {
      *value /= 10.0;
      exponent++;
    }
  }

  // Adjust precision for numbers with leading zeros
  if (exponent < 0 && (int)fabs((double)exponent) >
                          *precision) {  // again might be trouble with casting
                                         // int to double for fabs
    *precision = (int)fabs((double)exponent);
  }
  return exponent;
}

int round_to_sig_digits_l(long double *value, int *precision, int IsComp) {
  if (*value == 0.0) return 0;

  int exponent = (int)floor(log10(fabsl(*value)));

  if (IsComp) {
    // %g: Round to 'precision' significant digits
    long double scale = pow(10, *precision - 1 - exponent);
    *value = round(*value * scale) / scale;

    // Recalculate exponent post-rounding
    if (*value != 0.0) {
      exponent = (int)floor(log10(fabsl(*value)));
      long double norm_scale = pow(10, exponent);
      *value /= norm_scale;

      // Handle cases where rounding pushed value to 10.0 or 0.0999
      if (*value >= 10.0) {
        *value /= 10.0;
        exponent++;
      } else if (*value < 1.0) {
        *value *= 10.0;
        exponent--;
      }
    }
  } else {
    // %e: Normalize to [1.0, 10.0)
    long double scale = pow(10, -exponent);
    *value *= scale;
    if (*value >= 10.0) {
      *value /= 10.0;
      exponent++;
    }
  }

  // Adjust precision for numbers with leading zeros
  if (exponent < 0 && (int)fabsl((long double)exponent) >
                          *precision) {  // again might be trouble with casting
                                         // int to double for fabs
    *precision = (int)fabsl((long double)exponent);
  }
  return exponent;
}

int remove_trailing_zeroes(char *itc) {
  int removed_count = 0;
  int i_len = s21_strlen(itc) - 1;
  while (i_len >= 0 && itc[i_len] == '0') {
    itc[i_len] = '\0';
    i_len--;
    removed_count++;
  }
  if (i_len >= 0 && itc[i_len] == '.') itc[i_len] = '\0';
  return removed_count;
}

char *s21_itoa(int value, char *buffer, int base) {
  if (base < 2 ||
      base > 36) {  // returns empty string if base argument is invalid
    *buffer = '\0';
    return buffer;
  }

  int i = s21_strlen(buffer);
  // int is_negative = 0; unused

  // Handle 0 value
  if (value == 0) {
    buffer[i++] = '0';
    buffer[i] = '\0';
    return buffer;
  }

  // Handle INT MIN specially
  // if (value == INT_MIN && base == 10) {
  //   s21_strcpy(buffer, "-2147483648");
  //   return buffer;
  // }

  // // negative numbers
  if (value < 0 &&
      base == 10) {  // turn negative numbers to positive since they are handled
    value = -value;
  }

  // Convert number to the given base
  while (value != 0) {
    int remainder = value % base;
    buffer[i++] = (remainder > 9) ? (remainder - 10) + 'a' : remainder + '0';
    value /= base;
  }

  // // base 10 negative sign
  // if (is_negative) {
  //     buffer[i++] = '-';
  // }

  buffer[i] = '\0';  // null at the end

  // reverse string to restore original order
  reverse(buffer, i);

  return buffer;
}

char *s21_lltoa(long value, char *buffer, int base) {
  if (base < 2 ||
      base > 36) {  // returns empty string if base argument is invalid
    *buffer = '\0';
    return buffer;
  }

  int i = s21_strlen(buffer);
  // int is_negative = 0;

  // Handle LONG_MIN specially
  // if (value == LONG_MIN && base == 10) {
  //   s21_strcpy(buffer, "-9223372036854775808");
  //   return buffer;
  // }
  // if (value >= LONG_MAX && base == 10) {
  //   s21_strcpy(buffer, "-1");
  //   buffer[2] = '\0';
  //   return buffer;
  // }

  // Handle 0 value
  if (value == 0) {
    buffer[i++] = '0';
    buffer[i] = '\0';
    return buffer;
  }
  // negative numbers
  if (value < 0 &&
      base == 10) {  // turn negative numbers to positive since they are handled
    value = -value;
  }

  // Convert number to the given base
  while (value != 0) {
    int remainder = value % base;
    buffer[i++] = (remainder > 9) ? (remainder - 10) + 'a' : remainder + '0';
    value /= base;
  }

  // // base 10 negative sign
  // if (is_negative) {
  //     buffer[i++] = '-';
  // }

  buffer[i] = '\0';  // null at the end

  // reverse string to restore original order
  reverse(buffer, i);

  return buffer;
}

char *s21_utoa(unsigned int value, char *buffer, int base, int IsUpper) {
  if (base < 2 ||
      base > 36) {  // returns empty string if base argument is invalid
    *buffer = '\0';
    return buffer;
  }

  int i = 0;

  // Handle 0 value
  if (value == 0) {
    buffer[i++] = '0';
    buffer[i] = '\0';
    return buffer;
  }

  // Convert number to the given base
  while (value != 0) {
    unsigned int remainder = value % base;
    buffer[i++] = (remainder > 9) ? (remainder - 10) + (IsUpper ? 'A' : 'a')
                                  : remainder + '0';
    value /= base;
  }

  buffer[i] = '\0';  // null at the end

  // reverse string to restore original order
  reverse(buffer, i);

  return buffer;
}

char *s21_llutoa(unsigned long value, char *buffer, int base, int IsUpper) {
  if (base < 2 ||
      base > 36) {  // returns empty string if base argument is invalid
    *buffer = '\0';
    return buffer;
  }

  int i = 0;

  // Handle 0 value
  if (value == 0) {
    buffer[i++] = '0';
    buffer[i] = '\0';
    return buffer;
  }

  // Convert number to the given base
  while (value != 0) {
    unsigned int remainder = value % base;
    buffer[i++] = (remainder > 9) ? (remainder - 10) + (IsUpper ? 'A' : 'a')
                                  : remainder + '0';
    value /= base;
  }

  buffer[i] = '\0';  // null at the end

  // reverse string to restore original order
  reverse(buffer, i);

  return buffer;
}

char *s21_ftoa(double value, char *buffer, int precision) {
  char temp[50] = {0};
  double integral;
  double fractional = modf(value, &integral);
  // printf("%.12f\n", fractional);

  if (value < 0) {
    integral = -integral;
    fractional = -fractional;
  } else {
    buffer[0] = '\0';
  }

  s21_itoa((int)integral, temp, 10);
  s21_strcat(buffer, temp);
  int i = s21_strlen(buffer);
  if (precision > 0) {
    // TODO precision = 2; it should set precision to 2 temproraly if there are
    // zeroes after .
    buffer[i++] = '.';
    double multiplier = pow(10, precision);
    long frac_part = roundl(fractional * multiplier);
    frac_part = frac_part < 0 ? -frac_part : frac_part;

    // Convert fraction to string
    temp[0] = '\0';
    s21_lltoa(frac_part, temp, 10);

    int frac_len = s21_strlen(temp);

    // Add leading zeros
    for (int j = 0; j < precision - frac_len; j++) {
      buffer[i++] = '0';
    }

    // Copy the fraction digits
    s21_strcpy(&buffer[i], temp);
  }

  return buffer;
}

char *s21_lftoa(long double value, char *buffer, int precision) {
  char temp[60] = {0};
  long double integral;
  long double fractional = modfl(value, &integral);

  if (value < 0) {
    integral = -integral;
    fractional = -fractional;
  } else {
    buffer[0] = '\0';
  }

  s21_itoa((int)integral, temp, 10);
  s21_strcat(buffer, temp);

  int i = s21_strlen(buffer);  // TODO NEED TO CHECK THIS MIGHT BUG OUT

  if (precision > 0) {
    buffer[i++] = '.';
    long double multiplier = pow(10, precision);
    long frac_part = round(fractional * multiplier);
    frac_part = frac_part < 0 ? -frac_part : frac_part;

    // Convert fraction to string
    temp[0] = '\0';
    s21_lltoa(frac_part, temp, 10);
    int frac_len = s21_strlen(temp);

    // Add leading zeros
    for (int j = 0; j < precision - frac_len; j++) {
      buffer[i++] = '0';
    }

    // Copy the fraction digits
    s21_strcpy(&buffer[i], temp);
  }

  return buffer;
}

/*
test cases:
0.0000
*/
char *s21_etoa(double value, char *buffer, int precision) {
  char temp[100];  // temporary buffer to hold the integer part
  int e_width = 0;
  if (value < 0) {
    value = -value;
  } else {
    buffer[0] = '\0';
  }

  if (value < 1.0) {
    while (value < 1.0) {
      value *= 10;
      e_width++;
    }
  } else {
    while (fmod(value, 10) >= 10) {
      value /= 10;
      e_width++;
    }
  }
  s21_ftoa(value, buffer, precision);
  buffer[s21_strlen(buffer)] = 'e';
  buffer[s21_strlen(buffer)] = '\0';

  int int_part = (int)value;  // separate part of float before fraction
  double frac_part =
      value - (double)int_part;  // separate fraction from integer
  s21_itoa(int_part, temp, 10);  // convert integer part to string

  int i = 0;
  while (temp[i] != '\0') {  // copy integer part to buffer
    buffer[i] = temp[i];
    i++;
  }

  if (precision == -1) precision = 6;

  if (precision > 0) {
    buffer[i++] = '.';  // place dot before fraction
    while (precision-- > 0) {
      // printf("%f\n",frac_part);
      frac_part *= 10;
      int frac_int = (int)(frac_part + 0.5);
      // printf("%d\n",frac_int);
      buffer[i++] = frac_int + '0';
      frac_part -= frac_int;
    }
  }

  buffer[i] = '\0';
  return buffer;
}

// int main()
// {
// char a[] = "abc";
//   wchar_t a[] = L"abc";
//   char buf[256];
//   s21_sprintf(buf, "a b %s", a);
//   return 0;
// }
