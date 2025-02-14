#include "s21_sscanf.h"


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
x
X
p
n
%

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

    const char *input = "3.14 -0.001 42.0";
    float num1, num2, num3;

    int matched = s21_sscanf(input, "%f %f %f", &num1, &num2, &num3);
    printf("Matched: %d\n", matched);
    printf("num1 = %f num2 = %f num3 = %f\n", num1, num2, num3);

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
    const char *current = format;
    int count = 0;

    while (*current && *str) {
        if (*current == '%') {
            current++; // Move past '%'

            int i = 0;
            while (specifier_map[i].flag != '\0') {
                if (specifier_map[i].flag == *current) {
                    while (isspace(*str)) {
                        (str)++;
                    }
                    specifier_map[i].function(args, &str);
                    count++; // Increment count after a match
                    break;
                }
                i++;
            }
            current++;
        } else if (isspace(*current)) {
            while (isspace(*current)) {
                current++;
            }
            while (isspace(*str)) {
                str++;
            }
        } else if (*current == *str) {
            current++;
            str++;
        } else {
            break;
        }
    }

    return count;
}

void c_specifier(va_list *args, const char **str) {
    char *char_ptr = va_arg(*args, char *);
    *char_ptr = **str;
    (*str)++;
}


void d_specifier(va_list *args, const char **str) {
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
}


void s_specifier(va_list *args, const char **str) {
    char *buffer = va_arg(*args, char *);
    int i = 0;

    while (**str != '\0' && !isspace(**str)) {
        buffer[i++] = **str;
        (*str)++;
    }

    buffer[i] = '\0';
}


void i_specifier(va_list *args, const char **str) {
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
}
 
void e_specifier(va_list *args, const char **str) {
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
}


void f_specifier(va_list *args, const char **str) {
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
}