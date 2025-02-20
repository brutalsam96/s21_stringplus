#include "s21_sscanf.h"

#include <stdio.h>
#include <assert.h>

/* TASK LIST

void va_start(va_list ap, paramN) - This macro enables access to variadic function arguments
void va_arg(va_list ap, type) - This macro retrieves the next argument in the parameter list of the function
with the type type
void va_end(va_list p) This macro allows to end traversal of the variadic function arguments.

c - DONE
d - DONE
i - DONE
e - DONE
E - DONE
f - DONE
g - DONE
G - DONE
o - DONE
s - DONE
u - DONE
x - DONE
X - DONE
p - DONE
n - DONE
% - DONE
git 
*/


int main() {
    // s specifier usage
    // char input[] = "this is new string";
    // char str1[20], str2[20];

    // int matched = s21_sscanf(input, "%s %s", str1, str2);
    // printf("Matched: %d\n", matched);
    // printf("a = %s, b = %s\n", str1, str2);


    // i specifier usage
    // char input[] = "  -123 0123 0x1A";

    // int num1, num2, num3;

    // int matched = s21_sscanf(input, "%i %i %i", &num1, &num2, &num3);
    // printf("Matched: %d\n", matched);
    // printf("num1 = %d num2 = %d num3 = %d", num1, num2, num3);

    // char input[] = "1.23e4 -5.67E-3 9E2";
    // float num1, num2, num3;

    // int matched = s21_sscanf(input, "%e %e %e", &num1, &num2, &num3);
    // printf("Matched: %d\n", matched);
    // printf("num1 = %f num2 = %f num3 = %f\n", num1, num2, num3);

    // const char *input = "3.14 -0.001 42.0";
    // float num1, num2, num3;
    
    
    
    


    // const char *input = "0x7f9f5187daf0";
    // void *ptr;
    // void *ptr2;
    // printf("%d\n", s21_sscanf(input, "Discount: %p", &ptr));
    // printf("%d\n", sscanf(input, "Discount: %p", &ptr2));
    // printf("Matched: %p\n", ptr);
    // printf("Matched: %p\n", ptr2);
    
    // printf("%lu\n", *(unsigned long*)ptr);


    // int dummy;
    // int dummy2;
    // char test_buffer[50];
    // void *ptr_original, *ptr_custom;
    // void *ptr_original2, *ptr_custom2;

    // sprintf(test_buffer, "%p %p", &dummy, &dummy2);

    // int res_original = sscanf(test_buffer, "%p %p", &ptr_original, &ptr_original2);
    // int res_custom = s21_sscanf(test_buffer, "%p %p", &ptr_custom, &ptr_custom2);

    // printf("%p %p %p %p\n", ptr_original, ptr_custom, ptr_original2, ptr_custom2);
    // printf("%d %d", res_original, res_custom);

    //     sprintf(test_buffer, "%p", (void*)NULL);
    // res_original = sscanf(test_buffer, "%p", &ptr_original);
    // res_custom = my_sscanf(test_buffer, "%p", &ptr_custom);
    // assert(res_original == res_custom && ptr_original == ptr_custom);

    // // Test invalid input
    // const char *invalid_input = "not_a_pointer";
    // res_original = sscanf(invalid_input, "%p", &ptr_original);
    // res_custom = my_sscanf(invalid_input, "%p", &ptr_custom);
    // assert(res_original == res_custom);


    // const char *input = "Discount: 0x74fa";
    // int discount;
    
    // printf("%d\n", s21_sscanf(input, "Discount: %X", &discount));
    // printf("%d\n", sscanf(input, "Discount: %x", &discount));
    // printf("Matched: %d\n", discount);


    // const char *input = "Discount: 0x74f";
    
    // const char *input = "Discount: -1.250000";
    // float discount;
    // float discount2;
    // printf("%d\n", s21_sscanf(input, "Discount: %f", &discount));
    // printf("Matched: %f\n", discount);
    // printf("%d\n", sscanf(input, "Discount: %f", &discount2));
    // printf("Matched: %f\n", discount2);
    
    // const char *input = "1005";
    // short int a;

    // int result = s21_sscanf(input, "%hd", &a);
    // printf("Read values: a = %hd\n", a);

    // const char *input = "123.456 -42.0";
    // float a, b;

    // int result = s21_sscanf(input, "%f %f", &a, &b);
    // printf("Read values: a = %f, b = %f", a, b);


    // char input[] = "Hello"; // ASCII narrow string
    // wchar_t ws[50];         // Wide string buffer

    // s21_sscanf(input, "%*ls", 5 ,ws); // Works for ASCII but no encoding conversion
    // wprintf(L"Scanned wide string: %ls\n", ws);  // Output: Hello

    // char input2[] = "H";  // Single ASCII character
    // wchar_t wc2;

    // s21_sscanf(input2, "%11lc", &wc2); // Works fine for ASCII
    // wprintf(L"Scanned wide character: %lc\n", wc2);  // Output: H

    char input[] = "12345";
    int ws = 0;
    s21_sscanf(input, "%3d", &ws);
    return 0;
}

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
            char len_mod = 0;
            int width = 0;
            current++;
            if (isdigit(*current)) {parse_number(&current, 10, &width, 0);}
            else if (*current == '*') {width = va_arg(*args, int); *current++;}
            if (*current == 'h' || *current == 'l' || *current == 'L') { len_mod = *current; *current++;}
            if (*current == 'c') { c_specifier(args, &str, len_mod, width); str_i++; }
            else if (*current == 'd') { d_specifier(args, &str, len_mod, width) ? 0 : str_i++; }
            else if (*current == 'u') { u_specifier(args, &str, len_mod, width) ? 0 : str_i++; }
            else if (*current == 'i') { i_specifier(args, &str, len_mod, width) ? 0 : str_i++; }
            else if (*current == 'e' || *current == 'E') { e_specifier(args, &str, len_mod, width) ? 0 : str_i++; }
            else if (*current == 'f') { f_specifier(args, &str, len_mod, width) ? 0 : str_i++; }
            else if (*current == 'g' || *current == 'G') { g_specifier(args, &str, len_mod, width) ? 0 : str_i++; }
            else if (*current == 's') { s_specifier(args, &str, len_mod, width) ? 0 : str_i++; }
            else if (*current == 'o') { o_specifier(args, &str, len_mod, width) ? 0 : str_i++;}
            else if (*current == 'x' || *current == 'X') { x_specifier(args, &str, len_mod, width) ? 0 : str_i++;}
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

void parse_number(const char **str, int base, int *num, int width) {
    int count = 1;
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
    return has_dot && has_exp ? 1 : 0;
}


int c_specifier(va_list *args, const char **str, char len_mod, int width) {
    if (len_mod == 'l') {
        wchar_t *wch_ptr = va_arg(*args, wchar_t *);
        if (wch_ptr) {
            *wch_ptr = **str;
        }
    } else {
        char *char_ptr = va_arg(*args, char *);
        if (char_ptr) {
            *char_ptr = **str;
        }
    }
    (*str)++;
    return 0;
}


int d_specifier(va_list *args, const char **str, char len_mod, int width) {
    int num = 0;
    int sign = 1;
    short int *short_ptr;
    long int *long_ptr;
    int *int_ptr = NULL;

    if (len_mod == 'h') {
        short_ptr = va_arg(*args, short int *);
        int_ptr = (int *)short_ptr;
    } else if (len_mod == 'l') {
        long_ptr = va_arg(*args, long int *);
        int_ptr = (int *)long_ptr;
    } else {
        int_ptr = va_arg(*args, int *);
    }

    if (**str == '-') {
    parse_number(str, 10, &num, width);

    if (int_ptr) *int_ptr = sign * num;
    return 0;
}

    parse_number(str, 10, &num, width);

    *int_ptr = sign * num;
    return 0;
}

int u_specifier(va_list *args, const char **str, char len_mod, int width) {
    int num = 0;

    unsigned short int *short_ptr;
    unsigned long int *long_ptr;
    unsigned int *int_ptr = NULL;

    if (len_mod == 'h') {
        short_ptr = va_arg(*args, unsigned short int *);
        int_ptr = (unsigned int *)short_ptr;
    } else if (len_mod == 'l') {
        long_ptr = va_arg(*args,unsigned  long int *);
        int_ptr = (unsigned int *)long_ptr;
    } else {
        unsigned int *int_ptr = va_arg(*args, unsigned int *);
    }
    
    
    parse_number(str, 10, &num, width);
    *int_ptr = num;
    return 0;
}

int o_specifier(va_list *args, const char **str, char len_mod, int width) {
    int num = 0;
    unsigned short int *short_ptr;
    unsigned long int *long_ptr;
    unsigned int *val = NULL;

    if (len_mod == 'h') {
        short_ptr = va_arg(*args, unsigned short int *);
        val = (unsigned int *)short_ptr;
    } else if (len_mod == 'l') {
        long_ptr = va_arg(*args,unsigned  long int *);
        val = (unsigned int *)long_ptr;
    } else {
        unsigned int *val = va_arg(*args, unsigned int *);
    }
    parse_number(str, 8, &num, width);
    *val = num;
    return 0;
}

int s_specifier(va_list *args, const char **str, char len_mod, int width) {
    if (len_mod == 'l'){
        wchar_t *buffer = va_arg(*args, wchar_t *);
        int i = 0;
        while (**str != '\0' && !isspace(**str)) {
            buffer[i++] = **str;
            (*str)++;
        }
        buffer[i] = '\0';
    } else {
        char *buffer = va_arg(*args, char *);
        int i = 0;
        while (**str != '\0' && !isspace(**str)) {
            buffer[i++] = **str;
            (*str)++;
        }
        buffer[i] = '\0';
    }
    return 0;
}


int i_specifier(va_list *args, const char **str, char len_mod, int width) {
    int sign = 1;

    unsigned short int *short_ptr;
    unsigned long int *long_ptr;
    unsigned int *num = NULL;

    if (len_mod == 'h') {
        short_ptr = va_arg(*args, unsigned short int *);
        num = (unsigned int *)short_ptr;
    } else if (len_mod == 'l') {
        long_ptr = va_arg(*args,unsigned  long int *);
        num = (unsigned int *)long_ptr;
    } else {
        unsigned int *num = va_arg(*args, unsigned int *);
    }

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

    parse_number(str, base, num, width);

    *num *= sign;
    return 0;
}
 
int e_specifier(va_list *args, const char **str, char len_mod, int width) {
    // float *double_ptr = va_arg(*args, float *);
    float *num = NULL;
    double long *long_ptr;
    int sign = 1;

    if (len_mod == 'L') {
        long_ptr = va_arg(*args, double long *);
        num = (float *)long_ptr;
    } else {
        float *num = va_arg(*args, float *);
    }

    if (**str == '-') {
        sign = -1;
        (*str)++;
    } else if (**str == '+') {
        (*str)++;
    }

    int int_part = 0;
    parse_number(str, 10, &int_part, width);
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

    *num = (int_part + fraction) * pow(10, exp_sign * exponent);
    *num *= sign;
    // *double_ptr = (float)num;
    return 0;
}


int f_specifier(va_list *args, const char **str, char len_mod, int width) {
    
    float *num = NULL;
    double long *long_ptr;
    int sign = 1;

    if (len_mod == 'L') {
        long_ptr = va_arg(*args, double long *);
        num = (float *)long_ptr;
    } else {
        float *num = va_arg(*args, float *);
    }

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
    parse_number(str, 10, &int_part, width);
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
    *num *= sign;

    // *float_ptr = num;
    return 0;
}

int g_specifier(va_list *args, const char **str, char len_mod, int width) {
    check_e(*str) ? e_specifier(args, str, len_mod, width) : f_specifier(args, str, len_mod, width);
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


int x_specifier(va_list *args, const char **str, char len_mod, int width) {

    unsigned short int *short_ptr;
    unsigned long int *long_ptr;
    unsigned int *val = NULL;

    if (len_mod == 'h') {
        short_ptr = va_arg(*args, unsigned short int *);
        val = (unsigned int *)short_ptr;
    } else if (len_mod == 'l') {
        long_ptr = va_arg(*args,unsigned  long int *);
        val = (unsigned int *)long_ptr;
    } else {
        unsigned int *val = va_arg(*args, unsigned int *);
    }

    unsigned int res = 0;
    parse_number(str, 16, &res, width);
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