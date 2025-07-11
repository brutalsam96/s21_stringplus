#include "s21_sscanf.h"

int s21_sscanf(const char *str, const char *format, ...) {
  int done;
  va_list args;
  va_start(args, format);
  done = proccess_scanf(str, format, &args);

  va_end(args);
  return done;
}

int proccess_scanf(const char *str, const char *format, va_list *args) {
  const char *current = format, *start_str = str;

  int str_i = 0;
  if (!*str) return -1;  // Return -1 if input string is empty
  while (*current) {
    if (*current == '%' && *(current + 1) != '\0') {
      char len_mod = 0;
      int width = 0;
      current++;
      if (isdigit(*current)) {
        parse_number(&current, 10, &width, 0);
      } else if (*current == '*') {
        width = -5;
        (void)*current++;
      }
      if (*current == 'h' || *current == 'l' || *current == 'L') {
        len_mod = *current;
        (void)*current++;
      }
      if (*current == 'c') {
        c_specifier(args, &str, len_mod, width);
        str_i++;
        (void)*current++;
      } else if (*current == 'd') {
        d_specifier(args, &str, len_mod, width) ? 0 : str_i++;
        (void)*current++;
      } else if (*current == 'u') {
        u_specifier(args, &str, len_mod, width) ? 0 : str_i++;
        (void)*current++;
      } else if (*current == 'i') {
        i_specifier(args, &str, len_mod, width) ? 0 : str_i++;
        (void)*current++;
      } else if (*current == 'e' || *current == 'E') {
        e_specifier(args, &str, len_mod, width) ? 0 : str_i++;
        (void)*current++;
      } else if (*current == 'f') {
        f_specifier(args, &str, len_mod, width) ? 0 : str_i++;
        (void)*current++;
      } else if (*current == 'g' || *current == 'G') {
        g_specifier(args, &str, len_mod, width) ? 0 : str_i++;
        (void)*current++;
      } else if (*current == 's') {
        s_specifier(args, &str, len_mod, width) ? 0 : str_i++;
        (void)*current++;
      } else if (*current == 'o') {
        o_specifier(args, &str, len_mod, width) ? 0 : str_i++;
        (void)*current++;
      } else if (*current == 'x' || *current == 'X') {
        x_specifier(args, &str, len_mod, width) ? 0 : str_i++;
        (void)*current++;
      } else if (*current == 'n') {
        n_specifier(args, &str, start_str);
        (void)*current++;
      } else if (*current == 'p') {
        p_specifier(args, &str) ? 0 : str_i++;
        (void)*current++;
      } else if (*current == '%') {
        current++;
        continue;
      } else {
        current++;
        continue;
      }
      width = 0;
    }
    if (*current == '\0')
      break;
    else if (isspace(*current)) {
      while (isspace(*current)) {
        current++;
      }
      while (isspace(*str)) {
        str++;
      }
    } else if (*current == *str) {  // literal matches: advance both pointers
      current++;
      str++;
    } else if (*current == '%')
      continue;
    else
      break;
  }
  return str_i;
}

void parse_number(const char **str, int base, int *num, int width) {
  int count = 1;
  while (isspace(**str)) (*str)++;
  while ((base == 10 && isdigit(**str)) ||
         (base == 8 && **str >= '0' && **str <= '7') ||
         (base == 16 && (isdigit(**str) || ((**str >= 'a' && **str <= 'f') ||
                                            (**str >= 'A' && **str <= 'F'))))) {
    *num = (*num * base) + (isdigit(**str) ? (**str - '0')
                                           : ((**str >= 'a' && **str <= 'f')
                                                  ? (**str - 'a' + 10)
                                                  : (**str - 'A' + 10)));
    (*str)++;
    if (count == width) break;
    count++;
  }
}

void parse_number_u(const char **str, int base, unsigned int *num, int width) {
  int count = 1;
  while (isspace(**str)) (*str)++;
  while ((base == 10 && isdigit(**str)) ||
         (base == 8 && **str >= '0' && **str <= '7') ||
         (base == 16 && (isdigit(**str) || ((**str >= 'a' && **str <= 'f') ||
                                            (**str >= 'A' && **str <= 'F'))))) {
    *num = (*num * base) + (isdigit(**str) ? (**str - '0')
                                           : ((**str >= 'a' && **str <= 'f')
                                                  ? (**str - 'a' + 10)
                                                  : (**str - 'A' + 10)));
    (*str)++;
    if (count == width) break;
    count++;
  }
}

void parse_number_l(const char **str, int base, long int *num, int width) {
  int count = 1;
  while (isspace(**str)) (*str)++;
  while ((base == 10 && isdigit(**str)) ||
         (base == 8 && **str >= '0' && **str <= '7') ||
         (base == 16 && (isdigit(**str) || ((**str >= 'a' && **str <= 'f') ||
                                            (**str >= 'A' && **str <= 'F'))))) {
    *num = (*num * base) + (isdigit(**str) ? (**str - '0')
                                           : ((**str >= 'a' && **str <= 'f')
                                                  ? (**str - 'a' + 10)
                                                  : (**str - 'A' + 10)));
    (*str)++;
    if (count == width) break;
    count++;
  }
}

int check_e(const char *str) {
  int has_dot = 0;
  int has_exp = 0;
  while (!isspace(*str) && *str != '\0') {
    if (*str == '.') has_dot = 1;
    if (*str == 'e' || *str == 'E') has_exp = 1;
    str++;
  }
  if (!(has_dot && has_exp)) return -1;
  return has_exp ? 1 : 0;
}

int c_specifier(va_list *args, const char **str, char len_mod, int width) {
  if (width == -5) {
    while (**str != '\0' && !isspace(**str)) {
      (*str)++;
    }
    return 1;
  }
  if (len_mod == 'l') {
    wchar_t *wch_ptr = va_arg(*args, wchar_t *);
    if (wch_ptr) {
      if (width > (int)wcslen(wch_ptr)) {
        for (int i = 0; i < width; i++) {
          *wch_ptr = **str;
          (*str)++;
          (*wch_ptr)++;
        }
      } else {
        *wch_ptr = **str;
        (*str)++;
      }
    }
  } else {
    char *char_ptr = va_arg(*args, char *);
    if (char_ptr) {
      if (width > (int)strlen(char_ptr)) {
        for (int i = 0; i < width; i++) {
          char_ptr[i] = **str;
          (*str)++;
        }
      } else {
        *char_ptr = **str;
        (*str)++;
      }
    }
  }

  return 0;
}

int d_specifier(va_list *args, const char **str, char len_mod, int width) {
  int sign = 1;
  short int *short_ptr;
  long int *long_ptr;
  int *int_ptr;

  if (width == -5) {
    while (**str != '\0' && !isspace(**str)) {
      (*str)++;
    }
    return 1;
  }
  if (len_mod == 'h') {
    short_ptr = va_arg(*args, short int *);
    int_ptr = (int *)short_ptr;
  } else if (len_mod == 'l') {
    long_ptr = va_arg(*args, long int *);
    int_ptr = (int *)long_ptr;
  } else {
    int_ptr = va_arg(*args, int *);
  }

  while (isspace(**str)) (*str)++;

  if (**str == '-') {
    (*str)++;
    sign = -1;
    width--;
  } else if (**str == '+') {
    (*str)++;
  }

  if (!(isdigit(**str))) {
    return 1;
  }

  int temp_int = 0;
  if (len_mod == 'h') {
    parse_number(str, 10, &temp_int, width);
    *short_ptr = sign * (short)temp_int;
  } else if (len_mod == 'l') {
    parse_number(str, 10, &temp_int, width);
    *long_ptr = sign * (long)temp_int;
  } else {
    parse_number(str, 10, &temp_int, width);
    *int_ptr = sign * temp_int;
  }
  return 0;
}

int u_specifier(va_list *args, const char **str, char len_mod, int width) {
  unsigned short int *short_ptr;
  unsigned long int *long_ptr;
  unsigned int *val = S21_NULL;
  int is_negative = 0;

  if (width == -5) {
    while (**str != '\0' && !isspace(**str)) {
      (*str)++;
    }
    return 1;
  }

  if (len_mod == 'h') {
    short_ptr = va_arg(*args, unsigned short int *);
    val = (unsigned int *)short_ptr;
  } else if (len_mod == 'l') {
    long_ptr = va_arg(*args, unsigned long int *);
    val = (unsigned int *)long_ptr;
  } else {
    val = va_arg(*args, unsigned int *);
  }

  while (isspace(**str)) (*str)++;

  if (**str == '-') {
    (*str)++;
    is_negative = 1;
  } else if (**str == '+') {
    (*str)++;
  }

  if (!(isdigit(**str))) {
    return 1;
  }

  *val = 0;
  parse_number_u(str, 10, val, width);
  if (is_negative) {
    *val = (unsigned int)(pow(2, 32) - *val);
  } else {
    *val = (unsigned int)*val;
  }

  return 0;
}

int o_specifier(va_list *args, const char **str, char len_mod, int width) {
  int is_negative = 0;
  unsigned short int *short_ptr;
  unsigned long int *long_ptr;
  unsigned int *val = S21_NULL;

  if (width == -5) {
    while (**str != '\0' && !isspace(**str)) {
      (*str)++;
    }
    return 1;
  }

  if (len_mod == 'h') {
    short_ptr = va_arg(*args, unsigned short int *);
    val = (unsigned int *)short_ptr;
  } else if (len_mod == 'l') {
    long_ptr = va_arg(*args, unsigned long int *);
    val = (unsigned int *)long_ptr;
  } else {
    val = va_arg(*args, unsigned int *);
  }
  *val = 0;

  while (isspace(**str)) (*str)++;
  if (**str == '-') {
    is_negative = 1;
    (*str)++;
  } else if (**str == '+') {
    (*str)++;
  }

  if (!(isdigit(**str))) {
    return 1;
  }

  parse_number_u(str, 8, val, width);
  if (is_negative) {
    *val = (unsigned int)(pow(2, 32) - *val);
  }
  return 0;
}

int s_specifier(va_list *args, const char **str, char len_mod, int width) {
  while (isspace(**str)) (*str)++;
  if (width == -5) {
    while (**str != '\0' && !isspace(**str)) {
      (*str)++;
    }
    return 1;
  }
  if (len_mod == 'l') {
    wchar_t *buffer = va_arg(*args, wchar_t *);
    int i = 0;
    while (**str != '\0' && !isspace(**str)) {
      buffer[i++] = **str;
      (*str)++;
      if (i == width) break;
    }
    buffer[i] = '\0';
  } else {
    char *buffer = va_arg(*args, char *);
    int i = 0;
    while (**str != '\0' && !isspace(**str)) {
      buffer[i++] = **str;
      (*str)++;
      if (i == width) break;
    }
    buffer[i] = '\0';
  }
  return 0;
}

int i_specifier(va_list *args, const char **str, char len_mod, int width) {
  int sign = 1;

  short int *short_ptr;
  long int *long_ptr;
  int *num = S21_NULL;

  if (width == -5) {
    while (**str != '\0' && !isspace(**str)) {
      (*str)++;
    }
    return 1;
  }

  if (len_mod == 'h') {
    short_ptr = va_arg(*args, short int *);
    num = (int *)short_ptr;
  } else if (len_mod == 'l') {
    long_ptr = va_arg(*args, long int *);
    num = (int *)long_ptr;
  } else {
    num = va_arg(*args, int *);
  }

  while (isspace(**str)) (*str)++;

  if (**str == '-') {
    sign = -1;
    (*str)++;
  } else if (**str == '+') {
    (*str)++;
  }

  if (!(isdigit(**str))) {
    return 1;
  }

  *num = 0;
  int base = 10;

  if (**str == '0') {
    (*str)++;  // Move past '0'
    if (**str == 'x' || **str == 'X') {
      base = 16;  // Hexadecimal
      (*str)++;

    } else {
      base = 8;  // Octal
    }
  }

  parse_number(str, base, num, width);

  *num *= sign;
  return 0;
}

int e_specifier(va_list *args, const char **str, char len_mod, int width) {
  int has_width = 0;
  long double *num;
  float *float_ptr;
  int sign = 1;
  long double temp = 0.0;
  if (width == -5) {
    while (**str != '\0' && !isspace(**str)) {
      (*str)++;
    }
    return 1;
  }
  if (width > 0) has_width = 1;

  if (len_mod == 'L') {
    num = va_arg(*args, long double *);
  } else {
    float_ptr = va_arg(*args, float *);
    num = &temp;
  }

  while (isspace(**str)) (*str)++;

  if (**str == '-') {
    sign = -1;
    (*str)++;
    if (has_width) width--;
  } else if (**str == '+') {
    (*str)++;
  }

  if (!(isdigit(**str))) {
    return 1;
  }
  *num = 0.0;
  long int int_part = 0;
  parse_number_l(str, 10, &int_part, width);
  int dig_counter = 0;
  if (int_part > 0 && has_width) {
    int int_part_cpy = int_part;
    while (int_part_cpy > 0) {
      dig_counter++;
      int_part_cpy = int_part_cpy / 10;
    }
    if (dig_counter == width || dig_counter + 1 == width) {
      width = 0;
      *num = int_part;
      return 0;
    } else {
      width -= dig_counter;
    }
  }

  double fraction = 0.0;
  if (**str == '.') {
    (*str)++;  // Move past the decimal point
    if (has_width) width--;
    double divisor = 10.0;
    while (isdigit(**str)) {
      fraction += ((**str - '0') / divisor);
      divisor *= 10.0;
      (*str)++;
    }
  }
  int exp_sign = 1;
  if (**str == 'e' || **str == 'E') {
    (*str)++;
    if (**str == '-') {
      exp_sign = -1;
      (*str)++;
    } else if (**str == '+') {
      (*str)++;
    }
  }

  int exponent = 0;
  while (isdigit(**str)) {
    exponent = exponent * 10 + (**str - '0');
    (*str)++;
    if (has_width) width--;
    if (has_width && width == 0) break;
  }

  fraction = roundl(fraction * 1000000000000.0) / 1000000000000.0;

  *num = ((long double)((int_part + fraction) * 1000000000000.0) /
          1000000000000.0);
  *num *= pow(10, exp_sign * exponent);
  *num *= sign;

  if (len_mod != 'L') *float_ptr = (float)temp;

  // *double_ptr = (float)num;
  return 0;
}

int f_specifier(va_list *args, const char **str, char len_mod, int width) {
  int has_width = 0;
  long double *num;
  float *float_ptr;
  int sign = 1;
  long double temp = 0.0;
  if (width == -5) {
    while (**str != '\0' && !isspace(**str)) {
      (*str)++;
    }
    return 1;
  }

  if (width > 0) has_width = 1;

  if (len_mod == 'L') {
    num = va_arg(*args, long double *);
  } else {
    float_ptr = va_arg(*args, float *);
    num = &temp;
  }

  while (isspace(**str)) (*str)++;

  if (**str == '-') {
    sign = -1;
    (*str)++;
    if (has_width) width--;
  } else if (**str == '+') {
    (*str)++;
  }

  // Handle "inf" and "infinity"
  if (strncmp(*str, "inf", 3) == 0) {
    *num = sign * INFINITY;
    *str += 3;
    return 0;
  }
  if (strncmp(*str, "infinity", 8) == 0) {
    *num = sign * INFINITY;
    *str += 8;
    return 0;
  }

  if (!(isdigit(**str))) {
    return 1;
  }
  *num = 0.0;
  long int int_part = 0;
  parse_number_l(str, 10, &int_part, width);
  int dig_counter = 0;
  if (int_part > 0 && has_width) {
    int int_part_cpy = int_part;
    while (int_part_cpy > 0) {
      dig_counter++;
      int_part_cpy = int_part_cpy / 10;
    }
    if (dig_counter == width || dig_counter + 1 == width) {
      width = 0;
      *num = int_part;
      return 0;
    } else {
      width -= dig_counter;
    }
  }

  if (**str == '.') {
    (*str)++;  // Move past the decimal point
    if (has_width) width--;
    double fractional = 0.0;
    double decimal_place = 1.0;

    while (isdigit(**str)) {
      fractional = fractional * 10.0 + (**str - '0');
      decimal_place *= 10.0;
      (*str)++;
      if (has_width) width--;
      if (has_width && width == 0) break;
    }
    fractional /= decimal_place;
    fractional = roundl(fractional * 10000000000) / 10000000000.0;
    *num = ((long double)((int_part + fractional) * 10000000000.0) /
            10000000000.0);
  } else {
    return 1;
  }
  if (**str == 'e' || **str == 'E') {
    (*str)++;
    int exp_sign = 1;
    int exponent = 0;

    if (**str == '-') {
      exp_sign = -1;
      (*str)++;
    } else if (**str == '+') {
      (*str)++;
    }

    while (isdigit(**str)) {
      exponent = exponent * 10 + (**str - '0');
      (*str)++;
    }

    *num *= powl(10, exp_sign * exponent);  // Use powl() for long double
  }

  *num *= sign;

  if (len_mod != 'L') *float_ptr = (float)temp;

  return 0;
}

int g_specifier(va_list *args, const char **str, char len_mod, int width) {
  // if (!(isdigit(**str)) && **str != '-' && **str != '+') {
  //     return 1;
  // }
  int ret = 1;
  if (check_e(*str)) {
    ret = e_specifier(args, str, len_mod, width);
  } else {
    ret = f_specifier(args, str, len_mod, width);
  }
  return ret;
}

int n_specifier(va_list *args, const char **str, const char *start) {
  int *count_ptr = va_arg(*args, int *);
  if (count_ptr == S21_NULL) return 1;
  *count_ptr = *str - start;
  return 0;
}

int p_specifier(va_list *args, const char **str) {
  s21_uintptr_t *addr_ptr = va_arg(*args, s21_uintptr_t *);
  if (addr_ptr == S21_NULL) {
    return 1;
  }
  *addr_ptr = 0;
  while (isspace(**str)) (*str)++;
  while (isxdigit(**str)) {
    if (**str == '0' && ((*str)[1] == 'x' || (*str)[1] == 'X')) {
      *str += 2;
      *addr_ptr = hex2dec_ptr(str);
      break;
    } else {
      (*str)++;
    }
  }
  return 0;
}

int x_specifier(va_list *args, const char **str, char len_mod, int width) {
  unsigned short int *short_ptr;
  unsigned long int *long_ptr;
  unsigned int *val = S21_NULL;
  int sign = 1;

  if (width == -5) {
    while (**str != '\0' && !isspace(**str)) {
      (*str)++;
    }
    return 1;
  }

  if (len_mod == 'h') {
    short_ptr = va_arg(*args, unsigned short int *);
    val = (unsigned int *)short_ptr;
  } else if (len_mod == 'l') {
    long_ptr = va_arg(*args, unsigned long int *);
    val = (unsigned int *)long_ptr;
  } else {
    val = va_arg(*args, unsigned int *);
  }

  while (isspace(**str)) (*str)++;

  if (**str == '-') {
    sign = -1;
    (*str)++;
    // if (len_mod == 'l') {
    //     val = (int *)val;
    // }
  } else if (**str == '+') {
    sign = 1;
    (*str)++;
  }

  if (**str == '0' && (*(*str + 1) == 'x' || *(*str + 1) == 'X')) (*str) += 2;

  if (!(isxdigit(**str))) {
    return 1;
  }
  *val = 0;
  parse_number_u(str, 16, val, width);
  *val *= sign;
  return 0;
}

s21_uintptr_t hex2dec_ptr(const char **str) {
  s21_uintptr_t dec = 0;
  while (isxdigit(**str)) {
    char ch = toupper(**str);
    int val;
    if (ch >= '0' && ch <= '9') {
      val = ch - '0';
    } else if (ch >= 'A' && ch <= 'F') {
      val = ch - 'A' + 10;
    } else {
      continue;
    }

    if (dec > (((s21_uintptr_t)-1) - val) / 16) {
      dec = ((s21_uintptr_t)-1);
      break;
    }

    dec = dec * 16 + val;
    (*str)++;
  }
  return dec;
}