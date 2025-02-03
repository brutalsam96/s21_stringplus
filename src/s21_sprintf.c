#include "s21_sprintf.h"
#include "s21_utils.h"
#include <string.h>
#include <ctype.h>
#include <math.h>


//TODO NEED TO IMPLEMENT TYPE CHECKER FOR VARIADICS, IT CRASHES BECAUSE OF THAT


/*%
    ### [flags][width][.precision][length]specifier
    %
*/
int s21_sprintf(char *str, const char *format, ...) { // variadic
    int done;
    va_list args;
    va_start(args, format);
    done = proccess_string(str, format, &args);
    // printf("%d", done); // debug
    va_end(args); // for cleanup
    return done; // TODO need to test if it is returning correct amount of proccesed values
}

int proccess_string(char *str, const char *format, va_list *args) {
    /* flags, width and precision modifiers*/
    
    char symbol = '%';
    const char *current = format;
    int str_index = 0;

    while (*current != '\0') {
        const char *next_symbol = strchr(current, symbol);
        if (next_symbol) {
            int flags = 0, width = 0, precision = -1;   char length_modifier = '\0';
            while (current < next_symbol) {
                str[str_index++] = *current++;
            }
            current ++;
            parse_flags(&current, &flags);
            parse_width(&current, &width, args, &flags);
            parse_precision(&current, &precision, args);
            parse_length_modifiers(&current, &length_modifier);
            parse_type_spec(&current, str, args, &str_index, flags, precision, width, length_modifier);

        } else {
            while (*current != '\0') {
                // printf("%c\n", *current++);
                // printf("ran");
                str[str_index++] = *current++;
            }
        }
    }
    str[str_index] = '\0';
    return str_index; // returns amount of chars appended
}

int parse_flags(const char **current, int *flags){
    // printf("%c", *current);
    while (**current == '-' || **current == '+' || **current == ' ' || **current == '#' || **current == '0'){    
        switch (**current) {
            case '-': *flags |= FLAG_LEFT; break; //bitwise OR
            case '+': *flags |= FLAG_SIGN; break;
            case ' ': *flags |= FLAG_SPACE; break; 
            case '#': *flags |= FLAG_ALT; break; // TODO need implementation
            case '0': *flags |= FLAG_ZERO; break;
        }
        (*current)++;
    }


    if (*flags) {
        return 1; // flag found
    } else {
        return 0; // no flag found
    }
}

int parse_width(const char **current, int *width, va_list *args, int *flags){
    *width = 0;

    if (isdigit(**current)){
        while(isdigit(**current)){
            *width = *width * 10 + (**current - '0');
            (*current)++;
        }
        return 1;
    } 
    
    if (**current == '*') {
        (*current)++;
        *width = va_arg(*args, int);
        
        if(*width < 0) { // need a test case for this
            *flags |= FLAG_LEFT;
            *width = -(*width);
        }
        return 1;
    }
    return 0; // not found
}


int parse_precision(const char **current, int *precision, va_list *args){
    if (**current == '.') {
        (*current)++;
        *precision = 0;
        if (isdigit(**current)){
            while(isdigit(**current)){
                *precision = *precision * 10 + (**current - '0');
                (*current)++;
            }
        } else if (**current == '*') {
            (*current)++;
            *precision = va_arg(*args, int);
            if(*precision < 0) {
                *precision = -1;
            }
        }
    }
    if((*precision) == -1) {
        return 1; // no precision
    } else {
        return 0; // found precision modifier
    }
}

int parse_length_modifiers(const char **current, char *length_modifier){
    switch (**current)
    {
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
        return 0; // no length modifier
    }
    if(*length_modifier) {
        return 1; // found length_modifier
    } else {
        return 0; // no length modifier
    }
}

// can use ternary on uppercases to reduce function size if needed
int parse_type_spec(const char **current, char *str, va_list *args, int *index, int flags, int precision, int width, char length_modifiers) {
    union signed_value value = {0};
    union unsigned_value u_value = {0};
    int base = 10;
    double f_value;
    switch (**current)
    {
        case 'd': case 'i':
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
            
            proccess_signed_int(str, *current, args, &value, index, &flags, &width, &precision, length_modifiers);
            break;

        case 'u':
            // logic to proccess unsigned integers
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
                proccess_unsigned_int(str, *current, args, &u_value, index, &flags, &width, &precision, length_modifiers, base, 0);
            break;
        case 'o':
            // logic to proccess unsigned integers in base 8
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
                proccess_unsigned_int(str, *current, args, &value, index, &flags, &width, &precision, length_modifiers, base, 0);
            break;
        case 'X': case 'x':
            // logic to proccess unsigned integers in base 16, lowercase
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
                proccess_unsigned_int(str, *current, args, &u_value, index, &flags, &width, &precision, length_modifiers, base, **current == 'X');
            break;
        case 'F': case 'f':
            // logic to proccess scientific
            switch (length_modifiers) {
                    case 'L':
                        value.dll = va_arg(*args, long double);
                        break;
                    default:
                    value.db = va_arg(*args, double);
                }
            proccess_float(str, *current, args, &value, index, &flags, &width, &precision, length_modifiers, **current == 'F');
            break;
        case 'E': case 'e':
            // logic to proccess scientific uppercase
            switch (length_modifiers) {
                    case 'L':
                        value.dll = va_arg(*args, long double);
                        break;
                    default:
                    value.db = va_arg(*args, double);
                }
                proccess_scientific(str, *current, args, &value, index, &flags, &width, &precision, length_modifiers, **current == 'E'); // tricky operator comparision
            break;
        case 'g': case 'G':
            // logic to proccess scientific
            switch (length_modifiers) {
                    case 'L':
                        value.dll = va_arg(*args, long double);
                        break;
                    default:
                    value.db = va_arg(*args, double);
                }
            proccess_compact(str, *current, args, &value, index, &flags, &width, &precision, length_modifiers, **current == 'G');
            break;
        case 's':
            // logic to proccess strings
            proccess_string_arg(str, *current, args, index, &flags, &width, &precision, length_modifiers);
            break;
        case 'c':
            // logic to proccess chars
            proccess_char(str, *current, args, index, &flags, &width, &precision, length_modifiers);
            break;
        case 'p':
            // logic to process pointers
            proccess_pointer(str, *current, args, index, &flags, &width, &precision, length_modifiers);
            break;
        case 'n':
            // write number of characters written so far
            proccess_char_counter(str,*current, args, index, &flags, &width, &precision, length_modifiers);
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
        for (int i = 0; i < width; i++) {
            str[(*index)++] = ' ';
        }
    }
}

void handle_precision_padding(char *str, int *index, int precision, int value) {
    int val_width = 1, temp_val = value;
    for (val_width++; temp_val < 0;) {
        temp_val /= 10;
    }
    int new_precision = precision - val_width;
    for (int i = 0; i < new_precision; i++) {
        str[(*index)++] = '0';
    }
}

void handle_sign_space(char *str, int *index, int value, int flags) {
    if (value >= 0) {
        if (flags & FLAG_SIGN) {
            str[(*index)++] = '+';
        } else if (flags & FLAG_SPACE) {
            str[(*index)++] = ' ';
        }
    }  
    else if (value < 0) {
        str[(*index)++] = '-';
    }
}

int proccess_signed_int(char *str, const char *current, va_list *args, void *value, int *index, int *flags, int *width, int *precision, char length_modifier) {
    
    int val = 0;
    long long long_val = 0;
    char itc[BUFSIZ];
    int len;

    if (length_modifier == 'h') {
        val = *(short*)value;
        s21_itoa(val, itc, 10);
    } else if (length_modifier == 'l') {
        long_val = *(long*)value;
        s21_lltoa(long_val, itc, 10);
    } else {
        val = *(int*)value;
        s21_itoa(val, itc, 10);
    }

    len = strlen(itc);

    if (!(*flags & FLAG_LEFT) && !(*flags & FLAG_ZERO) && *width > len) {
        handle_width_padding(str, index, *width - len, *flags);
    }

    if (*flags & FLAG_SIGN || *flags & FLAG_SPACE || val < 0) {
        handle_sign_space(str, index, val, *flags);
    }

    if (!(*flags & FLAG_LEFT) && (*flags & FLAG_ZERO) && *width > len) {
        handle_width_padding(str, index, *width - (*flags & FLAG_SIGN ? len + 1: len), *flags);
    }


    if (*precision > len) {
        handle_precision_padding(str, index, *precision, val);
    }

    strcpy(&str[*index], itc);
    *index += len;

    if ((*flags & FLAG_LEFT) && *width > len) {
        handle_width_padding(str, index, *width - len, *flags);
    }

    return 0;
}


int proccess_unsigned_int(char *str, const char *current, va_list *args, void *u_value, int *index, int *flags, int *width, int *precision, char length_modifier, int base, int IsUpper){
    unsigned int val = 0;
    unsigned long long long_val = 0;
    char itc[BUFSIZ];
    int len;

    if (length_modifier == 'h') { // TODO GOTTA CHECK ALL LENGTH MODIFIERS
        // shorts and ints can use regular s21_itoa
        val = *(unsigned short*)u_value;
        s21_utoa(val, itc, base, IsUpper);
    } else if (length_modifier == 'l') {
        // long and long long use s21_ltoa
        long_val = *(unsigned long*)u_value;
        s21_llutoa(long_val, itc, base, IsUpper);
    } else {
        val = *(unsigned int*)u_value;
        s21_utoa(val, itc, base, IsUpper);
    }

    len = strlen(itc);

    if (!(*flags & FLAG_LEFT) && !(*flags & FLAG_ZERO) && *width > len) {
        handle_width_padding(str, index, *width - len, *flags);
    }

    if (!(*flags & FLAG_LEFT) && (*flags & FLAG_ZERO) && *width > len) {
        handle_width_padding(str, index, *width - (*flags & FLAG_SIGN ? len + 1: len), *flags);
    }


    if (*precision > len) {
        handle_precision_padding(str, index, *precision, val);
    }

    strcpy(&str[*index], itc);
    *index += len;

    if ((*flags & FLAG_LEFT) && *width > len) {
        handle_width_padding(str, index, *width - len, *flags);
    }
    return 0;
}

int proccess_float(char *str, const char *current, va_list *args, void *value, int *index, int *flags, int *width, int *precision, char length_modifier, int IsUpper){
    char itc[BUFSIZ];
    int len;
    long double val;
    
    if (*precision == -1) *precision = 6;
    
    if (length_modifier == 'L') {
        val = *(long double*)value;
        s21_lftoa(val, itc, *precision);
    } else {
        val = *(double*)value;
        s21_ftoa(val, itc, *precision);
    } 

    if (isinf(val)) {
        strcpy(&str[*index], (val < 0) ? IsUpper?"-INF":"-inf" : IsUpper?"INF":"inf");
        *index += (val < 0)? 4 : 3 ;
        return -1;
        }
    if (isnan(val)) {
        strcpy(&str[*index], IsUpper?"NAN":"nan");
        *index += 3;
        return -1;
    }




    len = strlen(itc);
    
    if (!(*flags & FLAG_LEFT) && !(*flags & FLAG_ZERO) && *width > len) {
        handle_width_padding(str, index, *width - len, *flags);
    }

    if (*flags & FLAG_SIGN || *flags & FLAG_SPACE || val < 0) {
        handle_sign_space(str, index, (val >= 0 ? 1 : - 1), *flags);
    }

    if (!(*flags & FLAG_LEFT) && (*flags & FLAG_ZERO) && *width > len) {
        handle_width_padding(str, index, *width - (*flags & FLAG_SIGN ? len + 1: len), *flags);
    }

    if (*precision > len) {
        handle_precision_padding(str, index, *precision, val);
    }
    

    strcpy(&str[*index], itc);
    *index += len;

    if ((*flags & FLAG_LEFT) && *width > len) {
        handle_width_padding(str, index, *width - len, *flags);
    }
    return 0;
}



int proccess_scientific(char *str, const char *current, va_list *args, void *value, int *index, int *flags, int *width, int *precision, char length_modifier, int IsUpper){
    
    char itc[BUFSIZ];
    int exponent = 0;
    int len;
    long double val;

    if (*precision == -1) *precision = 6;

    if (length_modifier == 'L') {
        val = *(long double*)value;
        // if (*precision == 0) val = roundl(val);
        
    } else {
        val = *(double*)value;
        // if (*precision == 0) val = roundl(val);
    }


    if (isinf(val)) {
        strcpy(&str[*index], (val < 0) ? IsUpper?"-INF":"-inf" : IsUpper?"INF":"inf");
        *index += (val < 0)? 4 : 3 ;
        return 0;
        }
    if (isnan(val)) {
        strcpy(&str[*index], IsUpper?"NAN":"nan");
        *index += 3;
        return 0;
    }

    // TODO handle case 0.0L here
    exponent = round_to_sig_digits (&val, precision, 0);
    // TODO need else block to handle value == 0

    s21_ftoa(fabsl(val), itc, *precision);

    len = strlen(itc);
    itc[len++] = IsUpper?'E':'e';
    itc[len++] = (exponent < 0) ? '-' : '+';
    if (fabs(exponent) < 10.0L) itc[len++] = '0';
    s21_itoa(fabs(exponent), &itc[len], 10);

    len = strlen(itc);

    if (!(*flags & FLAG_LEFT) && !(*flags & FLAG_ZERO) && *width > len) {
        handle_width_padding(str, index, *width - len, *flags);
    }

    if (*flags & FLAG_SIGN || *flags & FLAG_SPACE || val < 0) {
        handle_sign_space(str, index, (val >= 0 ? 1 : - 1), *flags);
    }

    if (!(*flags & FLAG_LEFT) && (*flags & FLAG_ZERO) && *width > len) {
        handle_width_padding(str, index, *width - (*flags & FLAG_SIGN ? len + 1: len), *flags);
    }

    if (*precision > len) {
        handle_precision_padding(str, index, *precision, val);
    }

    strcpy(&str[*index], itc);
    *index += len;

    if ((*flags & FLAG_LEFT) && *width > len) {
        handle_width_padding(str, index, *width - len, *flags);
    }

    return 0;

}

int proccess_compact(char *str, const char *current, va_list *args, void *value, int *index, int *flags, int *width, int *precision, char length_modifier, int IsUpper) {
    char itc[BUFSIZ];
    int exponent = 0;
    int len;
    long double val;


    if (*precision == -1) *precision = 6;    // Default precision
    else if (*precision == 0) *precision = 1; // %g with precision 0 → 1 sig digit

    if (length_modifier == 'L') {
        val = *(long double*)value;
    } else {
        val = *(double*)value;
    }

    if (isinf(val)) {
        strcpy(&str[*index], (val < 0) ? IsUpper?"-INF":"-inf" : IsUpper?"INF":"inf");
        *index += (val < 0)? 4 : 3 ;
        return 0;
        }
    if (isnan(val)) {
        strcpy(&str[*index], IsUpper?"NAN":"nan");
        *index += 3;
        return 0;
    }
    long double e_val = val;
    exponent = round_to_sig_digits(&e_val, precision, 1);
    int sign = (e_val < 0) ? -1 : 1;
    if (e_val == 0.0L) sign = 1; // Prevent negative zero

    // Determine if scientific notation is needed
    if ((exponent < -4 || exponent >= *precision)) {
        // Format for scientific notation
        s21_ftoa(fabsl(e_val), itc, *precision - 1); // Sig digs after decimal: precision-1
        if (!(*flags & FLAG_ALT)) {
            remove_trailing_zeroes(itc); // Remove insignificant zeros
        }
        len = strlen(itc);
        itc[len++] = IsUpper ? 'E' : 'e';
        itc[len++] = (exponent < 0) ? '-' : '+';
        if (fabs(exponent) < 10) itc[len++] = '0'; // Leading zero for single-digit exponents
        s21_itoa(fabs(exponent), &itc[len], 10);
    } else {
        // Fixed notation
        int decimal_places = *precision - 1 - exponent;
        if (decimal_places < 0) decimal_places = 0;
        long double original_val = e_val * powl(10, exponent);
        s21_ftoa(original_val, itc, decimal_places);
        if (!(*flags & FLAG_ALT)) remove_trailing_zeroes(itc); // Remove trailing zeros unless # flag is set
        
    }

   

    len = strlen(itc);

    if (!(*flags & FLAG_LEFT) && !(*flags & FLAG_ZERO) && *width > len) {
        handle_width_padding(str, index, *width - len, *flags);
    }

    if (*flags & FLAG_SIGN || *flags & FLAG_SPACE || val < 0) {
        handle_sign_space(str, index, (val >= 0 ? 1 : - 1), *flags);
    }

    if (!(*flags & FLAG_LEFT) && (*flags & FLAG_ZERO) && *width > len) {
        handle_width_padding(str, index, *width - (*flags & FLAG_SIGN ? len + 1: len), *flags);
    }

    if (*precision > len) {
        handle_precision_padding(str, index, *precision, val);
    }

    strcpy(&str[*index], itc);
    *index += len;

    if ((*flags & FLAG_LEFT) && *width > len) {
        handle_width_padding(str, index, *width - len, *flags);
    }

    return 0;
}

int proccess_string_arg(char *str, const char *current, va_list *args, int *index, int *flags, int *width, int *precision, char length_modifier){
    char *value = va_arg(*args, char *);
    strcpy(&str[*index], value);
    *index += strlen(value);
    return 0;
}

int proccess_char(char *str, const char *current, va_list *args, int *index, int *flags, int *width, int *precision, char length_modifier){
    char value = va_arg(*args, int);
    str[*index] = value;
    *index += 1;
    return 0;
}

int proccess_char_counter(char *str, const char *current, va_list *args, int *index, int *flags, int *width, int *precision, char length_modifier){
    int *value = va_arg(*args, int *);
    *value = *index;
    char itc[BUFSIZ];
    s21_itoa(*value, itc, 10);
    strcpy(&str[*index], itc);
    *index += strlen(itc);
    return 0;
}

int proccess_pointer(char *str, const char *current, va_list *args, int *index, int *flags, int *width, int *precision, char length_modifier) {
    char itc [BUFSIZ];
    void *value = va_arg(*args, void*);
    s21_uintptr_t addr = (s21_uintptr_t)value;
    s21_llutoa(addr, itc, 16, 0);
    strcpy(&str[*index], "0x");
    *index += 2;
    strcpy(&str[*index], itc);
    *index += strlen(itc);
    return 0;
}

int main () {
    char buff[256];
    char buff2[256];
    int n = 55;
    void *p = &n;
    // s21_sprintf(buff, "ab %g cd", 12454645.0348);
    // sprintf(buff2, "ab %g cd", 12454645.0348);
    // s21_sprintf(buff, "ab %.3g cd", 12345.67);
    // sprintf(buff2, "ab %.3g cd", 12345.67);

    // s21_sprintf(buff, "ab %p cd", p);
    // sprintf(buff2, "ab %p cd", p);

    s21_sprintf(buff, "ab %x cd", 351351351);
    sprintf(buff2, "ab %x cd", 351351351);

    // sprintf(buff2, "ab %.0g cd", 0.0042069);
    // s21_sprintf(buff, "ab %g cd", 1.435800);
    // sprintf(buff2, "ab %g cd", 1.435800);
    // s21_sprintf(buff, "ab %.e cd", -123.45);
    // sprintf(buff2, "ab %.e cd", -123.45);

    printf("%s\n", buff);
    printf("%s\n", buff2);
    return 0;
}
