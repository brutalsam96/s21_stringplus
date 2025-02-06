#include "s21_sscanf.h"


/* TASK LIST

void va_start(va_list ap, paramN) - This macro enables access to variadic function arguments
void va_arg(va_list ap, type) - This macro retrieves the next argument in the parameter list of the function
with the type type
void va_end(va_list p) This macro allows to end traversal of the variadic function arguments.

c - DONE
d - DONE
i - 
e 
E
f
g
G
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
    // char input[] = "h e l l o";
    char input[] = "this is new string";

    char str1[20], str2[20];

    int matched = s21_sscanf(input, "%s %s", str1, str2);
    printf("Matched: %d\n", matched);
    printf("a = %s, b = %s\n", str1, str2);

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

    while (isspace(**str)) {
        (*str)++;
    }

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

    while (isspace(**str)) {
        (*str)++;
    }

    while (**str != '\0' && !isspace(**str)) {
        buffer[i++] = **str;
        (*str)++;
    }

    buffer[i] = '\0';
}