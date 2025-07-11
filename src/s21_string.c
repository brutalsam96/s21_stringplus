#include "s21_string.h"

#define MAX_CHAR 100

s21_size_t s21_strlen(const char *str) {
  s21_size_t length = 0;
  while (str[length] != '\0') {
    length++;
  }
  return length;
}

void *s21_memchr(const void *str, int c, s21_size_t n) {
  if (str == S21_NULL) {
    return S21_NULL;
  }
  char *string = (char *)str;
  char target = (char)c;

  s21_size_t i = 0;
  while (i < n) {
    if (string[i] == target) {
      return (void *)(string + i);
    }
    i++;
  }
  return S21_NULL;
}

int s21_memcmp(const void *str1, const void *str2, s21_size_t n) {
  int value = 0;

  char *string1 = (char *)str1;
  char *string2 = (char *)str2;

  s21_size_t i = 0;
  while (i < n) {
    if (string1[i] == string2[i]) {
      i++;
      continue;
    }

    value = string1[i] - string2[i];
    break;
  }

  return value;
}

void *s21_memcpy(void *dest, const void *src, s21_size_t n) {
  char *destination = (char *)dest;
  char *sourceText = (char *)src;

  for (s21_size_t i = 0; i < n; i++) {
    destination[i] = sourceText[i];
  }
  return dest;
}

void *s21_memset(void *str, int c, s21_size_t n) {
  char *string = (char *)str;

  for (s21_size_t i = 0; i < n; i++) {
    string[i] = c;
  }
  return str;
}

char *s21_strncat(char *dest, const char *src, s21_size_t n) {
  s21_size_t dest_len = s21_strlen(dest);
  s21_size_t i = 0;

  while (src[i] != '\0' && i < n) {
    dest[dest_len + i] = src[i];
    i++;
  }

  dest[dest_len + i] = '\0';
  return dest;
}

char *s21_strchr(const char *str, int c) {
  if (str == S21_NULL) {
    return S21_NULL;
  }
  int i = 0;

  while (str[i] != '\0') {
    if (str[i] == c) {
      return (char *)str + i;
    }
    i++;
  }
  if (c == '\0') return (char *)str + i;
  return S21_NULL;
}

int s21_strncmp(const char *str1, const char *str2, s21_size_t n) {
  for (s21_size_t i = 0; i < n; i++) {
    if (str1[i] != str2[i]) {
      return str1[i] - str2[i];
    }
    if (str1[i] == '\0' || str2[i] == '\0') {
      break;
    }
  }
  return 0;
}

char *s21_strncpy(char *dest, const char *src, s21_size_t n) {
  s21_size_t i = 0;

  while (i < n && src[i] != '\0') {
    dest[i] = src[i];
    i++;
  }

  while (i < n) {
    dest[i] = '\0';
    i++;
  }
  return dest;
}

s21_size_t s21_strcspn(const char *str1, const char *str2) {
  s21_size_t i = 0;

  while (str1[i] != '\0') {
    const char *p = str2;
    while (*p != '\0') {
      if (str1[i] == *p) {
        return i;
      }
      p++;
    }
    i++;
  }

  return i;
}

char *s21_strerror(int errnum) {
#ifdef __linux__
#define _ERRSIZE 133
  ErrorCode error_codes[] = {
      {0, "Success"},
      {1, "Operation not permitted"},
      {2, "No such file or directory"},
      {3, "No such process"},
      {4, "Interrupted system call"},
      {5, "Input/output error"},
      {6, "No such device or address"},
      {7, "Argument list too long"},
      {8, "Exec format error"},
      {9, "Bad file descriptor"},
      {10, "No child processes"},
      {11, "Resource temporarily unavailable"},
      {12, "Cannot allocate memory"},
      {13, "Permission denied"},
      {14, "Bad address"},
      {15, "Block device required"},
      {16, "Device or resource busy"},
      {17, "File exists"},
      {18, "Invalid cross-device link"},
      {19, "No such device"},
      {20, "Not a directory"},
      {21, "Is a directory"},
      {22, "Invalid argument"},
      {23, "Too many open files in system"},
      {24, "Too many open files"},
      {25, "Inappropriate ioctl for device"},
      {26, "Text file busy"},
      {27, "File too large"},
      {28, "No space left on device"},
      {29, "Illegal seek"},
      {30, "Read-only file system"},
      {31, "Too many links"},
      {32, "Broken pipe"},
      {33, "Numerical argument out of domain"},
      {34, "Numerical result out of range"},
      {35, "Resource deadlock avoided"},
      {36, "File name too long"},
      {37, "No locks available"},
      {38, "Function not implemented"},
      {39, "Directory not empty"},
      {40, "Too many levels of symbolic links"},
      {41, "(null)"},
      {42, "No message of desired type"},
      {43, "Identifier removed"},
      {44, "Channel number out of range"},
      {45, "Level 2 not synchronized"},
      {46, "Level 3 halted"},
      {47, "Level 3 reset"},
      {48, "Link number out of range"},
      {49, "Protocol driver not attached"},
      {50, "No CSI structure available"},
      {51, "Level 2 halted"},
      {52, "Invalid exchange"},
      {53, "Invalid request descriptor"},
      {54, "Exchange full"},
      {55, "No anode"},
      {56, "Invalid request code"},
      {57, "Invalid slot"},
      {58, "(null)"},
      {59, "Bad font file format"},
      {60, "Device not a stream"},
      {61, "No data available"},
      {62, "Timer expired"},
      {63, "Out of streams resources"},
      {64, "Machine is not on the network"},
      {65, "Package not installed"},
      {66, "Object is remote"},
      {67, "Link has been severed"},
      {68, "Advertise error"},
      {69, "Srmount error"},
      {70, "Communication error on send"},
      {71, "Protocol error"},
      {72, "Multihop attempted"},
      {73, "RFS specific error"},
      {74, "Bad message"},
      {75, "Value too large for defined data type"},
      {76, "Name not unique on network"},
      {77, "File descriptor in bad state"},
      {78, "Remote address changed"},
      {79, "Can not access a needed shared library"},
      {80, "Accessing a corrupted shared library"},
      {81, ".lib section in a.out corrupted"},
      {82, "Attempting to link in too many shared libraries"},
      {83, "Cannot exec a shared library directly"},
      {84, "Invalid or incomplete multibyte or wide character"},
      {85, "Interrupted system call should be restarted"},
      {86, "Streams pipe error"},
      {87, "Too many users"},
      {88, "Socket operation on non-socket"},
      {89, "Destination address required"},
      {90, "Message too long"},
      {91, "Protocol wrong type for socket"},
      {92, "Protocol not available"},
      {93, "Protocol not supported"},
      {94, "Socket type not supported"},
      {95, "Operation not supported"},
      {96, "Protocol family not supported"},
      {97, "Address family not supported by protocol"},
      {98, "Address already in use"},
      {99, "Cannot assign requested address"},
      {100, "Network is down"},
      {101, "Network is unreachable"},
      {102, "Network dropped connection on reset"},
      {103, "Software caused connection abort"},
      {104, "Connection reset by peer"},
      {105, "No buffer space available"},
      {106, "Transport endpoint is already connected"},
      {107, "Transport endpoint is not connected"},
      {108, "Cannot send after transport endpoint shutdown"},
      {109, "Too many references: cannot splice"},
      {110, "Connection timed out"},
      {111, "Connection refused"},
      {112, "Host is down"},
      {113, "No route to host"},
      {114, "Operation already in progress"},
      {115, "Operation now in progress"},
      {116, "Stale file handle"},
      {117, "Structure needs cleaning"},
      {118, "Not a XENIX named type file"},
      {119, "No XENIX semaphores available"},
      {120, "Is a named type file"},
      {121, "Remote I/O error"},
      {122, "Disk quota exceeded"},
      {123, "No medium found"},
      {124, "Wrong medium type"},
      {125, "Operation canceled"},
      {126, "Required key not available"},
      {127, "Key has expired"},
      {128, "Key has been revoked"},
      {129, "Key was rejected by service"},
      {130, "Owner died"},
      {131, "State not recoverable"},
      {132, "Operation not possible due to RF-kill"},
      {133, "Memory page has hardware error"}};

#elif defined(__APPLE__)
#define _ERRSIZE 106
  ErrorCode error_codes[] = {
      {0, "Undefined error: 0"},
      {1, "Operation not permitted"},
      {2, "No such file or directory"},
      {3, "No such process"},
      {4, "Interrupted system call"},
      {5, "Input/output error"},
      {6, "Device not configured"},
      {7, "Argument list too long"},
      {8, "Exec format error"},
      {9, "Bad file descriptor"},
      {10, "No child processes"},
      {11, "Resource deadlock avoided"},
      {12, "Cannot allocate memory"},
      {13, "Permission denied"},
      {14, "Bad address"},
      {15, "Block device required"},
      {16, "Resource busy"},
      {17, "File exists"},
      {18, "Cross-device link"},
      {19, "Operation not supported by device"},
      {20, "Not a directory"},
      {21, "Is a directory"},
      {22, "Invalid argument"},
      {23, "Too many open files in system"},
      {24, "Too many open files"},
      {25, "Inappropriate ioctl for device"},
      {26, "Text file busy"},
      {27, "File too large"},
      {28, "No space left on device"},
      {29, "Illegal seek"},
      {30, "Read-only file system"},
      {31, "Too many links"},
      {32, "Broken pipe"},
      {33, "Numerical argument out of domain"},
      {34, "Result too large"},
      {35, "Resource temporarily unavailable"},
      {36, "Operation now in progress"},
      {37, "Operation already in progress"},
      {38, "Socket operation on non-socket"},
      {39, "Destination address required"},
      {40, "Message too long"},
      {41, "Protocol wrong type for socket"},
      {42, "Protocol not available"},
      {43, "Protocol not supported"},
      {44, "Socket type not supported"},
      {45, "Operation not supported"},
      {46, "Protocol family not supported"},
      {47, "Address family not supported by protocol family"},
      {48, "Address already in use"},
      {49, "Can't assign requested address"},
      {50, "Network is down"},
      {51, "Network is unreachable"},
      {52, "Network dropped connection on reset"},
      {53, "Software caused connection abort"},
      {54, "Connection reset by peer"},
      {55, "No buffer space available"},
      {56, "Socket is already connected"},
      {57, "Socket is not connected"},
      {58, "Can't send after socket shutdown"},
      {59, "Too many references: can't splice"},
      {60, "Operation timed out"},
      {61, "Connection refused"},
      {62, "Too many levels of symbolic links"},
      {63, "File name too long"},
      {64, "Host is down"},
      {65, "No route to host"},
      {66, "Directory not empty"},
      {67, "Too many processes"},
      {68, "Too many users"},
      {69, "Disc quota exceeded"},
      {70, "Stale NFS file handle"},
      {71, "Too many levels of remote in path"},
      {72, "RPC struct is bad"},
      {73, "RPC version wrong"},
      {74, "RPC prog. not avail"},
      {75, "Program version wrong"},
      {76, "Bad procedure for program"},
      {77, "No locks available"},
      {78, "Function not implemented"},
      {79, "Inappropriate file type or format"},
      {80, "Authentication error"},
      {81, "Need authenticator"},
      {82, "Device power is off"},
      {83, "Device error"},
      {84, "Value too large to be stored in data type"},
      {85, "Bad executable (or shared library)"},
      {86, "Bad CPU type in executable"},
      {87, "Shared library version mismatch"},
      {88, "Malformed Mach-o file"},
      {89, "Operation canceled"},
      {90, "Identifier removed"},
      {91, "No message of desired type"},
      {92, "Illegal byte sequence"},
      {93, "Attribute not found"},
      {94, "Bad message"},
      {95, "EMULTIHOP (Reserved)"},
      {96, "No message available on STREAM"},
      {97, "ENOLINK (Reserved)"},
      {98, "No STREAM resources"},
      {99, "Not a STREAM"},
      {100, "Protocol error"},
      {101, "STREAM ioctl timeout"},
      {102, "Operation not supported on socket"},
      {103, "Policy not found"},
      {104, "State not recoverable"},
      {105, "Previous owner died"},
      {106, "Interface output queue is full"}};
#endif

  if (errnum < 0 || errnum > _ERRSIZE) {
    static char buff[50];
#ifdef __apple__
    s21_sprintf(buff, "Unknown error: %d", errnum);
#else
    s21_sprintf(buff, "Unknown error %d", errnum);
#endif
    return (char *)buff;
  }
  for (int i = 0; i < _ERRSIZE; i++) {
    if (error_codes[i].error_code == errnum) {
      return (char *)error_codes[i].message;
    }
  }
  return S21_NULL;
}

char *s21_strpbrk(const char *str1, const char *str2) {
  if (str1 == S21_NULL || str2 == S21_NULL) {
    return S21_NULL;
  }

  for (int i = 0; str2[i] != '\0'; i++) {
    for (int j = 0; str1[j] != '\0'; j++) {
      if (str2[i] == str1[j]) {
        return (char *)&str1[j];
      }
    }
  }
  return S21_NULL;
}

char *s21_strrchr(const char *str, int c) {
  if (str == S21_NULL) {
    return S21_NULL;
  }

  const char *last_occurrence = S21_NULL;
  for (; *str != '\0'; str++) {
    if (*str == (char)c) {
      last_occurrence = str;
    }
  }

  if (c == '\0') return (char *)str;

  return (char *)last_occurrence;
}

char *s21_strstr(const char *haystack, const char *needle) {
  if (!haystack || !needle) {
    return S21_NULL;
  }

  if (*needle == '\0') {
    return (char *)haystack;
  }

  while (*haystack != '\0') {
    const char *h = haystack;
    const char *n = needle;

    while (*n != '\0' && *h == *n) {
      h++;
      n++;
    }

    if (*n == '\0') {
      return (char *)haystack;
    }

    haystack++;
  }

  return S21_NULL;
}

char *s21_strtok(char *str, const char *delim) {
  static char *next;

  if (str != S21_NULL) {
    next = str;
  }

  if (next == S21_NULL) {
    return S21_NULL;
  }

  char *start = next;
  while (*start && s21_strchr(delim, *start)) {
    start++;
  }

  if (*start == '\0') {
    next = S21_NULL;
    return S21_NULL;
  }

  char *end = start;
  while (*end && !s21_strchr(delim, *end)) {
    end++;
  }

  if (*end) {
    *end = '\0';
    next = end + 1;
  } else {
    next = S21_NULL;
  }

  return start;
}

char *s21_strcpy(char *dest, const char *src) {
  s21_size_t i = 0;
  while (src[i] != '\0') {
    dest[i] = src[i];
    i++;
  }
  dest[i] = '\0';
  return dest;
}

char *s21_strcat(char *dest, const char *src) {
  s21_size_t dest_len = s21_strlen(dest);
  s21_size_t i = 0;
  while (src[i] != '\0') {
    dest[dest_len + i] = src[i];
    i++;
  }
  // Terminate the concatenated string.
  dest[dest_len + i] = '\0';
  return dest;
}

// Bonus part C# Functions

void *s21_to_upper(const char *str) {
  if (!str) {
    return S21_NULL;
  }

  s21_size_t len = s21_strlen(str);
  char *upper_str =
      (char *)malloc(len + 1);  // WARNING CHECK for the memory leak

  for (s21_size_t i = 0; i < len; i++) {
    if (str[i] >= 'a' && str[i] <= 'z') {
      upper_str[i] = str[i] - 32;
    } else {
      upper_str[i] = str[i];
    }
  }

  upper_str[len] = '\0';

  return upper_str;
}

void *s21_to_lower(const char *str) {
  if (!str) {
    return S21_NULL;
  }

  s21_size_t len = s21_strlen(str);
  char *upper_str =
      (char *)malloc(len + 1);  // WARNING CHECK for the memory leak

  for (s21_size_t i = 0; i < len; i++) {
    if (str[i] >= 'A' && str[i] <= 'Z') {
      upper_str[i] = str[i] + 32;
    } else {
      upper_str[i] = str[i];
    }
  }

  upper_str[len] = '\0';

  return upper_str;
}

void *s21_insert(const char *src, const char *str, s21_size_t start_index) {
  if (!src || !str) {
    return S21_NULL;
  }

  s21_size_t len_src = s21_strlen(src);
  s21_size_t len_str = s21_strlen(str);

  if (start_index > len_src) {
    return S21_NULL;
  }

  s21_size_t combined_len = len_src + len_str;
  char *new_str = (char *)malloc((combined_len + 1) * sizeof(char));
  if (!new_str) {
    return S21_NULL;
  }

  s21_size_t i = 0;

  for (; i < start_index; i++) {
    new_str[i] = src[i];
  }

  for (s21_size_t j = 0; j < len_str; j++) {
    new_str[i + j] = str[j];
  }

  for (s21_size_t j = start_index; j < len_src; j++) {
    new_str[len_str + j] = src[j];
  }

  new_str[combined_len] = '\0';

  return new_str;
}

int is_trim_char(char c, const char *trim_chars) {
  while (*trim_chars) {
    if (*trim_chars == c) {
      return 1;
    }
    trim_chars++;
  }
  return 0;
}

char *s21_trim(const char *src, const char *trim_chars) {
  if (!src || !trim_chars) {
    return S21_NULL;
  }

  s21_size_t start_index = 0;
  while (src[start_index] && is_trim_char(src[start_index], trim_chars)) {
    start_index++;
  }

  s21_size_t end_index = s21_strlen(src);
  while (end_index > start_index &&
         is_trim_char(src[end_index - 1], trim_chars)) {
    end_index--;
  }

  if (end_index <= start_index) {
    return S21_NULL;
  }

  s21_size_t len = end_index - start_index;
  char *trimmed_str = (char *)malloc(len + 1);
  if (!trimmed_str) {
    return S21_NULL;
  }

  s21_strncpy(trimmed_str, src + start_index, len);
  trimmed_str[len] = '\0';

  return trimmed_str;
}
