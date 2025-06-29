# s21_string+

This project is an implementation of the C `string.h` library, with additional functionality including `sprintf` and `sscanf`. This project was completed as part of the School 21 curriculum.

## Table of Contents

- [s21_string.h](#s21_stringh)
- [s21_sprintf.h](#s21_sprintfh)
- [s21_sscanf.h](#s21_sscanfh)
- [Bonus Functions](#bonus-functions)
- [Building and Testing](#building-and-testing)

## s21_string.h

This library provides a custom implementation of the standard C `string.h` library.

### Functions

| Function | Description |
|---|---|
| `s21_memchr` | Searches for the first occurrence of a character in a block of memory. |
| `s21_memcmp` | Compares two blocks of memory. |
| `s21_memcpy` | Copies a block of memory. |
| `s21_memset` | Fills a block of memory with a specific value. |
| `s21_strncat` | Appends a specified number of characters from one string to another. |
| `s21_strchr` | Finds the first occurrence of a character in a string. |
| `s21_strncmp` | Compares a specified number of characters of two strings. |
| `s21_strncpy` | Copies a specified number of characters from one string to another. |
| `s21_strcspn` | Calculates the length of the initial segment of a string which consists entirely of characters not in another string. |
| `s21_strerror` | Returns a pointer to an error message string. |
| `s21_strlen` | Calculates the length of a string. |
| `s21_strpbrk` | Finds the first character in a string that matches any character in another string. |
| `s21_strrchr` | Finds the last occurrence of a character in a string. |
| `s21_strstr` | Finds the first occurrence of a substring in a string. |
| `s21_strtok` | Breaks a string into a series of tokens. |

## s21_sprintf.h

This library provides a custom implementation of the `sprintf` function.

### Supported Specifiers

| Specifier | Description |
|---|---|
| `c` | Character |
| `d`, `i` | Signed decimal integer |
| `f` | Decimal floating point |
| `s` | String of characters |
| `u` | Unsigned decimal integer |
| `%` | Character % |
| `g`, `G` | Uses the shortest representation of decimal floating point |
| `e`, `E` | Scientific notation |
| `x`, `X` | Unsigned hexadecimal integer |
| `o` | Unsigned octal |
| `p` | Pointer address |

### Supported Flags

| Flag | Description |
|---|---|
| `-` | Left-justify |
| `+` | Force sign |
| ` ` | Space before positive numbers |
| `#` | Alternative form |
| `0` | Zero-padding |

### Supported Width and Precision

- `(number)`: Minimum number of characters to be printed.
- `*`: Width is specified by an argument.
- `.(number)`: Minimum number of digits to be written.
- `.*`: Precision is specified by an argument.

### Supported Length Modifiers

| Modifier | Description |
|---|---|
| `h` | short int |
| `l` | long int |
| `L` | long double |

## s21_sscanf.h

This library provides a custom implementation of the `sscanf` function.

### Supported Specifiers

| Specifier | Description |
|---|---|
| `c` | Character |
| `d` | Signed decimal integer |
| `i` | Signed integer (decimal, octal, or hexadecimal) |
| `e`, `E`, `f`, `g`, `G` | Decimal floating point or scientific notation |
| `o` | Unsigned octal |
| `s` | String of characters |
| `u` | Unsigned decimal integer |
| `x`, `X` | Unsigned hexadecimal integer |
| `p` | Pointer address |
| `n` | Number of characters scanned |
| `%` | Character % |

## Bonus Functions

This project also includes a few bonus functions inspired by C# string manipulation methods:

| Function | Description |
|---|---|
| `s21_to_upper` | Converts a string to uppercase. |
| `s21_to_lower` | Converts a string to lowercase. |
| `s21_insert` | Inserts a string into another string at a specified index. |
| `s21_trim` | Removes leading and trailing occurrences of a set of characters from a string. |

## Credits

This project was a collaborative effort completed at [School 21](https://21-school.uz).

**Authors:**
- brutalsam
- teraxiom

## Building and Testing

To build the library and run the tests, you can use the provided `Makefile`.

### Targets

- `all`: Builds the `s21_string.a` library.
- `clean`: Removes all build artifacts.
- `test`: Builds and runs the unit tests.
- `gcov_report`: Generates a code coverage report using `gcov`.

### Example Usage

```bash
# Build the library
make all

# Run the tests
make test

# Generate a coverage report
make gcov_report
```
