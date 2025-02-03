#include "s21_utils.h"



void reverse(char *str, int length){
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
char *s21_itoa(int value, char *buffer, int base){
    if (base < 2 || base > 36) { // returns empty string if base argument is invalid
        *buffer = '\0';
        return buffer;
    }

    int i = 0;
    int is_negative = 0;

    // Handle 0 value
    if (value == 0) {
        buffer[i++] = '0';
        buffer[i] = '\0';
        return buffer;
    }

    // Handle INT MIN specially
    if (value == INT_MIN && base == 10) {
        strcpy(buffer, "-2147483648");
        return buffer;
    }

    // negative numbers
    if (value < 0 && base == 10) {
        is_negative = 1;
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

    buffer[i] = '\0'; // null at the end

    // reverse string to restore original order
    reverse(buffer, i);

    return buffer;
}

char *s21_lltoa(long value, char *buffer, int base){
    if (base < 2 || base > 36) { // returns empty string if base argument is invalid
        *buffer = '\0';
        return buffer;
    }

    int i = 0;
    int is_negative = 0;

    // Handle LONG_MIN specially
    // TODO should i also check for LONG MAX ???
    if (value == LONG_MIN && base == 10) {
        strcpy(buffer, "-9223372036854775808");
        return buffer;
    }
    // Handle 0 value
    if (value == 0) {
        buffer[i++] = '0';
        buffer[i] = '\0';
        return buffer;
    }
    // negative numbers
    if (value < 0 && base == 10) {
        is_negative = 1;
        value = -value;
    }

    // Convert number to the given base
    while (value != 0) {
        int remainder = value % base;
        buffer[i++] = (remainder > 9) ? (remainder - 10) + 'a' : remainder + '0';
        value /= base;
    }

    // base 10 negative sign
    if (is_negative) {
        buffer[i++] = '-';
    }

    buffer[i] = '\0'; // null at the end

    // reverse string to restore original order
    reverse(buffer, i);

    return buffer;
}

char *s21_utoa(unsigned int value, char *buffer, int base, int IsUpper){
    if (base < 2 || base > 36) { // returns empty string if base argument is invalid
        *buffer = '\0';
        return buffer;
    }

    int i = 0;
    int is_negative = 0;

    // Handle 0 value
    if (value == 0) {
        buffer[i++] = '0';
        buffer[i] = '\0';
        return buffer;
    }
    // negative numbers
    if (value < 0 && base == 10) {
        is_negative = 1;
        value = -value;
    }

    // Convert number to the given base
    while (value != 0) {
        unsigned int remainder = value % base;
        buffer[i++] = (remainder > 9) ? (remainder - 10) + (IsUpper? 'A' : 'a') : remainder + '0';
        value /= base;
    }

    // // base 10 negative sign
    // if (is_negative) {
    //     buffer[i++] = '-';
    // }

    buffer[i] = '\0'; // null at the end

    // reverse string to restore original order
    reverse(buffer, i);

    return buffer;
}

char *s21_llutoa(unsigned long value, char *buffer, int base, int IsUpper){
    if (base < 2 || base > 36) { // returns empty string if base argument is invalid
        *buffer = '\0';
        return buffer;
    }

    int i = 0;
    int is_negative = 0;

    // Handle 0 value
    if (value == 0) {
        buffer[i++] = '0';
        buffer[i] = '\0';
        return buffer;
    }
    // negative numbers
    if (value < 0 && base == 10) {
        is_negative = 1;
        value = -value;
    }

    // Convert number to the given base
    while (value != 0) {
        unsigned int remainder = value % base;
        buffer[i++] = (remainder > 9) ? (remainder - 10) + (IsUpper? 'A' : 'a') : remainder + '0';
        value /= base;
    }

    // base 10 negative sign
    if (is_negative) {
        buffer[i++] = '-';
    }

    buffer[i] = '\0'; // null at the end

    // reverse string to restore original order
    reverse(buffer, i);

    return buffer;
}

char *s21_ftoa(double value, char *buffer, int precision) {
    char temp[30];
    double integral;
    double fractional = modf(value, &integral);

    if (value < 0) {
        integral = -integral;
        fractional = -fractional;
    } else {
        buffer[0] = '\0';
    }

    s21_itoa((int)integral, temp, 10);
    strcat(buffer, temp);
    int i = strlen(buffer);
    if (precision > 0) {
        // TODO precision = 2; it should set precision to 2 temproraly if there are zeroes after .
        buffer[i++] = '.';
        double multiplier = pow(10, precision);
        long frac_part = roundl(fractional * multiplier);
        frac_part = frac_part < 0 ? -frac_part : frac_part;
        
        // Convert fraction to string
        s21_lltoa(frac_part, temp, 10);

        int frac_len = strlen(temp);
        
        // Add leading zeros
        for (int j = 0; j < precision - frac_len; j++) {
            buffer[i++] = '0';
        }
        
        // Copy the fraction digits
        strcpy(&buffer[i], temp);
    }

    return buffer;
}

char *s21_lftoa(long double value, char *buffer, int precision) {
    char temp[60];
    long double integral;
    long double fractional = modfl(value, &integral);
    


    if (value < 0) {
        integral = -integral;
        fractional = -fractional;
    } else {
        buffer[0] = '\0';
    }

    s21_itoa((int)integral, temp, 10);
    strcat(buffer, temp);
    
    int i = strlen(buffer);
    

    if (precision > 0) {
        buffer[i++] = '.';
        long double multiplier = pow(10, precision);
        long frac_part = round(fractional * multiplier);
        frac_part = frac_part < 0 ? -frac_part : frac_part;
        
        // Convert fraction to string
        s21_lltoa(frac_part, temp, 10);
        int frac_len = strlen(temp);
        
        // Add leading zeros
        for (int j = 0; j < precision - frac_len; j++) {
            buffer[i++] = '0';
        }
        
        // Copy the fraction digits
        strcpy(&buffer[i], temp);
    }

    return buffer;
}


/*
test cases:
0.0000
*/
char *s21_etoa(double value, char *buffer, int precision) {
    char temp[100]; // temporary buffer to hold the integer part
    int e_width = 0;
    if (value < 1.0) {
        while (value < 1.0){
            value *= 10;
            e_width ++;
        }        
    } else {
        while (fmod(value, 10) >= 10) {
            value /= 10;
            e_width ++;
        }
    }
    s21_ftoa(value, buffer, precision);
    buffer[strlen(buffer)] = 'e';
    buffer[strlen(buffer)] = '\0';

    
    int int_part = (int)value; // separate part of float before fraction
    double frac_part = value - (double)int_part; // separate fraction from integer
    s21_itoa(int_part, temp, 10); // convert integer part to string

    int i = 0;
    while (temp[i] != '\0') { // copy integer part to buffer
        buffer[i] = temp[i];
        i++;
    }

    if (precision == -1) precision = 6;

    if (precision > 0) {
        buffer[i++] = '.'; // place dot before fraction
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
int round_to_sig_digits(long double *value, int *precision, int IsComp) {
    if (*value == 0.0L) return 0;

    int exponent = (int)floor(log10(fabsl(*value)));
    

    if (IsComp) {
        // %g: Round to 'precision' significant digits
        long double scale = powl(10, *precision - 1 - exponent);
        *value = roundl(*value * scale) / scale;
        
        // Recalculate exponent post-rounding
        if (*value != 0.0L) {
            exponent = (int)floor(log10(fabsl(*value)));
            long double norm_scale = powl(10, exponent);
            *value /= norm_scale;
            
            // Handle cases where rounding pushed value to 10.0 or 0.0999
            if (*value >= 10.0L) {
                *value /= 10.0L;
                exponent++;
            } else if (*value < 1.0L) {
                *value *= 10.0L;
                exponent--;
            }
        }
    } else {
        // %e: Normalize to [1.0, 10.0)
        long double scale = powl(10, -exponent);
        *value *= scale;
        if (*value >= 10.0L) {
            *value /= 10.0L;
            exponent++;
        }
    }
    // Adjust precision for numbers with leading zeros (e.g., 0.000123)
    if (exponent < 0 && (int)fabs(exponent) > *precision) {
        *precision = (int)fabs(exponent);
    }

    return exponent;
}



void remove_trailing_zeroes(char *itc) {
    int i_len = strlen(itc) - 1;
    while (i_len >= 0 && itc[i_len] == '0') {
      itc[i_len] = '\0';
      i_len--;
    }
    if (i_len >= 0 && itc[i_len] == '.') itc[i_len] = '\0';
}

