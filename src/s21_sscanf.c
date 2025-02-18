#include "s21_sscanf.h"

#include <stdio.h>
#include <assert.h>

int s21_sscanf(const char *str, const char *format, ...) {
    int done;
    va_list args;
    va_start(args, format);
    done = proccess_scanf(str, format, &args);

    va_end(args);
    return done;
}

int proccess_scanf(const char *str, const char *format, va_list *args) {
    const char *current = format, *start = str;
    int str_i = 0;
    while (*current) {
        if (*current == '%' && *(current + 1) != '\0') {
            current++;
            if (*current == 'c') { c_specifier(args, &str); str_i++; }
            else if (*current == 'd') { d_specifier(args, &str) ? 0 : str_i++; }
            else if (*current == 'u') { u_specifier(args, &str) ? 0 : str_i++; }
            else if (*current == 'i') { i_specifier(args, &str) ? 0 : str_i++; }
            else if (*current == 'e' || *current == 'E') { e_specifier(args, &str) ? 0 : str_i++; }
            else if (*current == 'f') { f_specifier(args, &str) ? 0 : str_i++; }
            else if (*current == 'g' || *current == 'G') { g_specifier(args, &str) ? 0 : str_i++; }
            else if (*current == 's') { s_specifier(args, &str) ? 0 : str_i++; }
            else if (*current == 'o') { o_specifier(args, &str) ? 0 : str_i++;}
            else if (*current == 'x' || *current == 'X') { x_specifier(args, &str) ? 0 : str_i++;}
            else if (*current == 'n') { n_specifier(args, &str, start); }
            else if (*current == 'p') { p_specifier(args, &str) ? 0 : str_i++;}
            else if (*current == '%') { current++; continue; }
            else { current++; continue; }
            continue;
        }
        if (isspace(*current)) {
            while (isspace(*current)) current++;
            while (isspace(*str)) str++;
        } else if (*current == *str) { // literal matches: advance both pointers
            current++;
            str++;
        } else current++;
    }
    return str_i;
}

void parse_number(const char **str, int base, int *num) {
    while ((base == 10 && isdigit(**str)) ||
           (base == 8 && **str >= '0' && **str <= '7') ||
           (base == 16 && (isdigit(**str) ||
                           ((**str >= 'a' && **str <= 'f') ||
                            (**str >= 'A' && **str <= 'F'))))) {
        *num = (*num * base) +
               (isdigit(**str) ? (**str - '0') :
               ((**str >= 'a' && **str <= 'f') ? (**str - 'a' + 10) :
                (**str - 'A' + 10)));
        (*str)++;
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
    return has_dot && has_exp ? 1 : 0;
}


int c_specifier(va_list *args, const char **str) {
    char *char_ptr = va_arg(*args, char *);
    *char_ptr = **str;
    (*str)++;
    return 0;
}


int d_specifier(va_list *args, const char **str) {
    int *int_ptr = va_arg(*args, int *);
    int num = 0;
    int sign = 1;

    if (**str == '-') {
        sign = -1;
        (*str)++;
    } else if (**str == '+') {
        (*str)++; // Ignore the '+' sign
    }

    parse_number(str, 10, &num);

    *int_ptr = sign * num;
    return 0;
}

int u_specifier(va_list *args, const char **str) {
    unsigned int *int_ptr = va_arg(*args, int *);
    int num = 0;
    parse_number(str, 10, &num);
    *int_ptr = num;
    return 0;
}

int o_specifier(va_list *args, const char **str) {
    unsigned int *val  = va_arg(*args, unsigned int *);
    int num = 0;
    parse_number(str, 8, &num);
    *val = num;
    return 0;
}

int s_specifier(va_list *args, const char **str) {
    char *buffer = va_arg(*args, char *);
    int i = 0;

    while (**str != '\0' && !isspace(**str)) {
        buffer[i++] = **str;
        (*str)++;
    }

    buffer[i] = '\0';
    return 0;
}


int i_specifier(va_list *args, const char **str) {
    int *num = va_arg(*args, int *);
    *num = 0;
    int sign = 1;

    if (**str == '-') {
        sign = -1;
        (*str)++;
    } else if (**str == '+') {
        (*str)++;
    }

    int base = 10;
    if (**str == '0') {
        (*str)++;  // Move past '0'

        if (**str == 'x' || **str == 'X') {
            base = 16;  // Hexadecimal
            (*str)++;
        } else {
            base = 8;   // Octal
        }
    }

    parse_number(str, base, num);

    *num *= sign;
    return 0;
}
 
int e_specifier(va_list *args, const char **str) {
    float *double_ptr = va_arg(*args, float *);
    double num = 0.0;
    int sign = 1;

    if (**str == '-') {
        sign = -1;
        (*str)++;
    } else if (**str == '+') {
        (*str)++;
    }

    int int_part = 0;
    parse_number(str, 10, &int_part);
    double fraction = 0.0;
    if (**str == '.') {
        (*str)++;  // Move past the decimal point
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
    }

    num = (int_part + fraction) * pow(10, exp_sign * exponent);
    num *= sign;
    *double_ptr = (float)num;
    return 0;
}


int f_specifier(va_list *args, const char **str) {
    float *float_ptr = va_arg(*args, float *);  // Retrieve argument
    double num = 0;  // Initialize result
    int sign = 1;

    // Handle sign
    if (**str == '-') {
        sign = -1;
        (*str)++;
    } else if (**str == '+') {
        (*str)++;
    }

    // Parse integer part

    // char *start = (char*)*str;
    int int_part = 0;
    parse_number(str, 10, &int_part);
    // int exp = *str - start;

    // Parse fractional part
    if (**str == '.') {
        (*str)++;  // Move past the decimal point
        int fractional = 0.0;
        int decimal_place = 1;

        while (isdigit(**str)) {
            fractional = round(fractional * 10.0 + (**str - '0'));
            decimal_place *= 10;
            (*str)++;
        }

        num += int_part + fractional / decimal_place;
    }

    // Apply sign
    num *= sign;

    *float_ptr = num;
    return 0;
}

int g_specifier(va_list *args, const char **str) {
    check_e(*str) ? e_specifier(args, str) : f_specifier(args, str);
    return 0;
}

int n_specifier(va_list *args, const char **str, const char *start) {
    int *count_ptr = va_arg(*args, int *);
    *count_ptr = *str - start;
}

int p_specifier(va_list *args, const char **str) {
    s21_uintptr_t *addr_ptr = va_arg(*args, s21_uintptr_t *);
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


int x_specifier(va_list *args, const char **str) {
    unsigned int *val  = va_arg(*args, unsigned int *);
    unsigned int res = 0;
    parse_number(str, 16, &res);
    *val = res;
    return 0;
}

s21_uintptr_t hex2dec_ptr(const char **str) {
    s21_uintptr_t dec = 0;
    while (isxdigit(**str))  {
        char ch = toupper(**str);
        int val;
        if (ch >= '0' && ch <= '9') {
            val = ch - '0';
        } else if (ch >= 'A' && ch <= 'F') {
            val = ch - 'A' + 10;
        } else {
            continue;
        }
        dec = dec * 16 + val;
        (*str)++;
    }
    return dec;
}