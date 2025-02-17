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
e - 
E - 
f 
g - 
G - 
o
s - DONE
u
x - DONE
X - DONE
p - DONE
n - DONE
% - DONE

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


    const char *input = "Discount: 0x74fa";
    int discount;
    
    printf("%d\n", s21_sscanf(input, "Discount: %X", &discount));
    // printf("%d\n", sscanf(input, "Discount: %x", &discount));
    printf("Matched: %d\n", discount);

    

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
            current++; 
            if (*current == 'c') { c_specifier(args, &str); str_i++; }
            else if (*current == 'd') { d_specifier(args, &str) ? 0 : str_i++; }
            else if (*current == 'i') { i_specifier(args, &str) ? 0 : str_i++; }
            else if (*current == 'e') { e_specifier(args, &str) ? 0 : str_i++; }
            else if (*current == 'f') { f_specifier(args, &str) ? 0 : str_i++; }
            else if (*current == 's') { s_specifier(args, &str) ? 0 : str_i++; }
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

    while (isdigit(**str)) {
        num = num * 10 + (**str - '0');
        (*str)++;
    }

    *int_ptr = sign * num;
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

    while ((base == 10 && isdigit(**str)) ||
           (base == 8 && **str >= '0' && **str <= '7') ||
           (base == 16 && (isdigit(**str) || 
                           (**str >= 'a' && **str <= 'f') || 
                           (**str >= 'A' && **str <= 'F')))) {
        *num = (*num * base) +
               ((isdigit(**str)) ? (**str - '0') : 
                ((**str >= 'a' && **str <= 'f') ? (**str - 'a' + 10) :
                 (**str - 'A' + 10)));

        (*str)++;
    }

    *num *= sign;
    return 0;
}
 
int e_specifier(va_list *args, const char **str) {
    double *double_ptr = va_arg(*args, double *);
    double num = 0.0;
    int sign = 1;

    if (**str == '-') {
        sign = -1;
        (*str)++;
    } else if (**str == '+') {
        (*str)++;
    }

    double base = 0.0;
    while (isdigit(**str) || **str == '.') {
        if (**str == '.') {
            (*str)++;
            double decimal_place = 0.1;
            while (isdigit(**str)) {
                
                base += (int)(**str) * decimal_place;
                decimal_place /= 10;
                (*str)++;
            }
        } else {
            base = base * 10 + (**str - '0');
            (*str)++;
        }
    }

    num = base * sign;

    if (**str == 'e' || **str == 'E') {
        (*str)++;
        int exp_sign = 1;
        if (**str == '-') {
            exp_sign = -1;
            (*str)++;
        } else if (**str == '+') {
            (*str)++;
        }

        int exponent = 0;
        while (isdigit(**str)) {
            exponent = exponent * 10 + (**str - '0');
            (*str)++;
        }

        num *= pow(10, exp_sign * exponent);
    }
    *double_ptr = num;
    return 0;
}


int f_specifier(va_list *args, const char **str) {
    double *float_ptr = va_arg(*args, double *);  // Retrieve argument
    double num = 0.0;  // Initialize result
    int sign = 1;

    // Handle sign
    if (**str == '-') {
        sign = -1;
        (*str)++;
    } else if (**str == '+') {
        (*str)++;
    }

    // Parse integer part
    while (isdigit(**str)) {
        num = num * 10.0 + (**str - '0');
        (*str)++;
    }

    // Parse fractional part
    if (**str == '.') {
        (*str)++;  // Move past the decimal point
        double fractional = 0.0;
        double decimal_place = 1.0;

        while (isdigit(**str)) {
            fractional = fractional * 10.0 + (**str - '0');
            decimal_place *= 10.0;
            (*str)++;
        }

        num += fractional / decimal_place;
    }

    // Apply sign
    num *= sign;

    *float_ptr = num;
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
    while (isxdigit(**str)) {
        char ch = toupper(**str);
        int rem;
        if (**str == '0' && ((*str)[1] == 'x' || (*str)[1] == 'X')) {*str += 1;} // could bug out here
        if (ch >= '0' && ch <= '9') {
            rem = ch - '0';
        } else if (ch >= 'A' && ch <= 'F') {
            rem = ch - 'A' + 10;
        } else {
            continue;
        }
        res = res * 16 + rem;
        (*str)++;
    }
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