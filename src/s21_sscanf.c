#include "s21_sscanf.h"


int s21_sscanf(const char *str, const char *format, ...) {
    va_list args;
    va_start(args, format);
    int count = 0;

    while (*format && *str) {
        if (*format == '%') {
            format++; // Move past '%'

            if (*format == 'd') {
                int *int_ptr = va_arg(args, int *);
                int num;
                if (sscanf(str, "%d", &num) == 1) {
                    *int_ptr = num;
                    count++;
                    while (isdigit(*str) || *str == '-') str++; // Skip number
                }
            } else if (*format == 'f') {
                float *float_ptr = va_arg(args, float *);
                float num;
                if (sscanf(str, "%f", &num) == 1) {
                    *float_ptr = num;
                    count++;
                    while (isdigit(*str) || *str == '.' || *str == '-') str++;
                }
            } else if (*format == 's') {
                char *char_ptr = va_arg(args, char *);
                while (*str && !isspace(*str)) {
                    *char_ptr++ = *str++;
                }
                *char_ptr = '\0';
                count++;
            }
        } else if (*format == *str) {
            str++; // Match literal character
        } else {
            break; // Mismatch
        }
        format++;
    }

    va_end(args);
    return count;
}


int main() {
    char input[] = "123 45.67 hello";
    int a;
    float b;
    char c[20];

    int matched = s21_sscanf(input, "%d %f %s", &a, &b, c);
    printf("Matched: %d\n", matched);
    printf("a = %d, b = %f, c = %s\n", a, b, c);

    return 0;
}

