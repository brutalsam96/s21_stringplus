#include "test_functions.h"

int main() {
  printf("TESTS\n");
  int test = 1;
  test_memchr(&test);
  test_memcmp(&test);
  test_memcpy(&test);
  test_strlen(&test);
  test_memset(&test);
  test_strncat(&test);
  test_strchr(&test);
  test_strncmp(&test);
  test_strncpy(&test);
  test_strcspn(&test);
  test_strerror(&test);
  test_strpbrk(&test);
  test_strrchr(&test);
  test_strstr(&test);
  test_strtok(&test);

  return 0;
}

void compareTwoString(char *string1, char *string2) {
  if (string1 == NULL && string2 == NULL) {
    printf("OK\n");
  } else if (strcmp(string1, string2) == 0) {
    printf("OK\n");
  } else {
    printf("FAIL\n");
  }
}

void compareTwoInteger(int a, int b) {
  if (a == b) {
    printf("OK\n");
  } else {
    printf("FAIL\n");
  }
}

void test_strtok(int *test) {
  printf("\nstrtok\n");

  char *token, *s21_token;

  char str[80] = "This is - www.tutorialspoint.com - website";
  const char s[2] = "-";
  token = strtok(str, s);
  s21_token = s21_strtok(str, s);
  printf("Test %d: ", *test);
  compareTwoString(token, s21_token);
  *test += 1;

  char str_1[] = "ttttt";
  char *str_2 = "tp";
  token = strtok(str_1, str_2);
  s21_token = s21_strtok(str_1, str_2);
  printf("Test %d: ", *test);
  compareTwoString(token, s21_token);
  *test += 1;
}

void test_strstr(int *test) {
  printf("\nstrstr\n");
  char *res, *s21_res;

  const char str[20] = "TutorialsPoint";
  const char substr[10] = "Point";
  res = strstr(str, substr);
  s21_res = s21_strstr(str, substr);
  printf("Test %d: ", *test);
  compareTwoString(res, s21_res);
  *test += 1;

  char str_1[100] = "Welcome to Tutorialspoint";
  char *str_res, *s21_str_res;
  str_res = strstr(str_1, "ials");
  s21_str_res = s21_strstr(str_1, "ials");
  printf("Test %d: ", *test);
  compareTwoString(str_res, s21_str_res);
  *test += 1;
}

void test_strrchr(int *test) {
  printf("\nstrchr\n");

  char *res, *s21_res;

  const char str[] = "Tutorialspoint";
  const char ch = '.';
  res = strchr(str, ch);
  s21_res = s21_strchr(str, ch);
  printf("Test %d: ", *test);
  compareTwoString(res, s21_res);
  *test += 1;

  const char *str1 = "Welcome to Tutorialspoint";
  char ch1 = 'u';
  res = strchr(str1, ch1);
  s21_res = s21_strchr(str1, ch1);
  printf("Test %d: ", *test);
  compareTwoString(res, s21_res);
  *test += 1;
}

void test_strpbrk(int *test) {
  printf("\nstrpbrk\n");
  char *res, *s21_res;

  const char str1[] = "abcde2fghi3jk4l";
  const char str2[] = "34";
  res = strpbrk(str1, str2);
  s21_res = s21_strpbrk(str1, str2);
  printf("Test %d: ", *test);
  compareTwoString(res, s21_res);
  *test += 1;

  const char str3[] = "Hello, World!";
  const char str4[] = "oW";
  res = strpbrk(str3, str4);
  s21_res = s21_strpbrk(str3, str4);
  printf("Test %d: ", *test);
  compareTwoString(res, s21_res);
  *test += 1;

  const char str5[] = "Our Tutorials";
  const char str6[] = "rT";
  res = strpbrk(str5, str6);
  s21_res = s21_strpbrk(str5, str6);
  printf("Test %d: ", *test);
  compareTwoString(res, s21_res);
  *test += 1;
}

void test_strerror(int *test) {
  printf("\nstrerror\n");
  FILE *res;

  res = fopen("file.txt", "r");
  if (res == NULL) {
    int err_code = errno;
    printf("Test %d: ", *test);
    compareTwoString(strerror(err_code), s21_strerror(err_code));
    *test += 1;
  }
}

void test_strcspn(int *test) {
  printf("\nstrcspn\n");

  int res, s21_res;

  const char *str1 = "Tutorialspoint";
  const char *str2 = "Textbook";
  res = strcspn(str1, str2);
  s21_res = s21_strcspn(str1, str2);
  printf("Test %d: ", *test);
  compareTwoInteger(res, s21_res);
  *test += 1;

  const char *str3 = "tutorialspoint";
  const char *str4 = "tutorial";
  res = strcspn(str3, str4);
  s21_res = s21_strcspn(str3, str4);
  printf("Test %d: ", *test);
  compareTwoInteger(res, s21_res);
  *test += 1;

  const char *str5 = "Welcome to Tutorialspoint Community";
  const char *str6 = "point";
  res = strcspn(str5, str6);
  s21_res = s21_strcspn(str5, str6);
  printf("Test %d: ", *test);
  compareTwoInteger(res, s21_res);
  *test += 1;
}

void test_strncpy(int *test) {
  printf("\nstrncpy\n");

  const char *src1 = "TutorialsPoint.com";
  char dest1[12] = {0};
  char s21_dest1[12] = {0};
  strncpy(dest1, src1, 10);
  s21_strncpy(s21_dest1, src1, 10);
  printf("Test %d: ", *test);
  compareTwoString(dest1, s21_dest1);
  *test += 1;

  const char *src2 = "Hello, Note!";
  char dest2[10] = {0};
  char s21_dest2[10] = {0};
  strncpy(dest2, src2 + 7, 4);
  s21_strncpy(s21_dest2, src2 + 7, 4);
  printf("Test %d: ", *test);
  compareTwoString(dest1, s21_dest1);
  *test += 1;
}

void test_strncmp(int *test) {
  printf("\nstrncmp\n");
  int res;
  int s21_res;

  const char str_1[] = "java";
  const char str_2[] = "java";
  res = strncmp(str_1, str_2, strlen(str_2));
  s21_res = s21_strncmp(str_1, str_2, strlen(str_2));
  printf("Test %d: ", *test);
  compareTwoInteger(res, s21_res);
  *test += 1;

  const char str_3[] = "abcdef";
  const char str_4[] = "ABCDEF";
  res = strncmp(str_3, str_4, strlen(str_4));
  s21_res = s21_strncmp(str_3, str_4, strlen(str_4));
  printf("Test %d: ", *test);
  compareTwoInteger(res, s21_res);
  *test += 1;
}

void test_strchr(int *test) {
  printf("\nstrchr\n");
  char *s21_res;
  char *res;

  const char *str1 = "TutorialsPoint";
  const char ch1 = '.';
  res = strchr(str1, ch1);
  s21_res = s21_strchr(str1, ch1);

  printf("Test %d: ", *test);
  compareTwoString(res, s21_res);
  *test += 1;

  const char *str2 = "Welcome to Tutorialspoint";
  const char ch2 = 'u';
  res = strchr(str2, ch2);
  s21_res = s21_strchr(str2, ch2);

  printf("Test %d: ", *test);
  compareTwoString(res, s21_res);
  *test += 1;

  const char *str3 = "This is simple string";
  const char ch3 = 's';
  res = strchr(str2, ch2);
  s21_res = s21_strchr(str2, ch2);

  printf("Test %d: ", *test);
  compareTwoString(res, s21_res);
  *test += 1;
}

void test_strncat(int *test) {
  printf("\nstrncat\n");

  char dest1[20] = "Hello, ";
  char s21_dest1[20] = "Hello, ";
  char src1[] = "Beautiful World!";
  strncat(dest1, src1 + 10, 5);
  s21_strncat(s21_dest1, src1 + 10, 5);
  printf("Test %d: ", *test);
  compareTwoString(dest1, s21_dest1);
  *test += 1;

  char dest2[20] = "";
  char s21_dest2[20] = "";
  char src2[] = "World!";
  strncat(dest2, src2, 5);
  s21_strncat(s21_dest2, src2, 5);
  printf("Test %d: ", *test);
  compareTwoString(dest2, s21_dest2);
  *test += 1;
}

void test_memset(int *test) {
  printf("\nmemset\n");

  char str1[20] = "Hello World";
  char s21_str1[20] = "Hello World";
  memset(str1, 'Z', 10);
  s21_memset(s21_str1, 'Z', 10);
  printf("Test %d: ", *test);
  compareTwoString(str1, s21_str1);
  *test += 1;

  int arr[10];
  memset(arr, 0, sizeof(arr));
  int s21_arr[10];
  s21_memset(s21_arr, 0, sizeof(s21_arr));

  printf("Test %d: ", *test);
  int flag = 0;
  for (int i = 0; i < 10; i++) {
    if (arr[i] != s21_arr[i]) {
      flag = 1;
      break;
    }
  }
  if (flag == 0) {
    printf("OK\n");
  } else {
    printf("FAIL\n");
  }
  *test += 1;
}

void test_strlen(int *test) {
  printf("\nstrlen\n");
  int s21_len, len;

  const char *word1 = "Tutorialspoint";
  s21_len = s21_strlen(word1);
  len = strlen(word1);
  printf("Test %d: ", *test);
  compareTwoInteger(s21_len, len);
  *test += 1;

  const char *word2 = "";
  s21_len = s21_strlen(word2);
  len = strlen(word2);
  printf("Test %d: ", *test);
  compareTwoInteger(s21_len, len);
  *test += 1;

  const char *word3 = "\n";
  s21_len = s21_strlen(word3);
  len = strlen(word3);
  printf("Test %d: ", *test);
  compareTwoInteger(s21_len, len);
  *test += 1;
}

void test_memcmp(int *test) {
  printf("\nmemcmp\n");
  int s21_res;
  int res;

  const char *str1 = "abcdef";
  const char *str2 = "ABCDEF";

  s21_res = s21_memcmp(str1, str2, 6);
  res = memcmp(str1, str2, 6);
  printf("Test %d: ", *test);
  compareTwoInteger(s21_res, res);
  *test += 1;

  int arr1[] = {1, 2, 3, 4, 5};
  int arr2[] = {1, 2, 3, 4, 6};

  s21_res = s21_memcmp(arr1, arr2, sizeof(arr1));
  res = memcmp(arr1, arr2, sizeof(arr1));
  printf("Test %d: ", *test);
  compareTwoInteger(s21_res, res);
  *test += 1;

  const char *str3 = "12345678901400345678";
  const char *str4 = "1234567";

  s21_res = s21_memcmp(str3, str4, 7);
  res = memcmp(str3, str4, 7);
  printf("Test %d: ", *test);
  compareTwoInteger(s21_res, res);
  *test += 1;
}

void test_memchr(int *test) {
  printf("\nmemchr\n");
  const char str1[] = "Tutorialspoint";
  const char ch1 = '.';

  char *string1 = (char *)s21_memchr(str1, ch1, strlen(str1));
  char *string2 = (char *)memchr(str1, ch1, strlen(str1));
  printf("Test %d: ", *test);
  compareTwoString(string1, string2);
  *test += 1;

  const char str2[] = "abcdef";
  const char ch2 = 'd';

  char *string3 = (char *)s21_memchr(str2, ch2, strlen(str2));
  char *string4 = (char *)memchr(str2, ch2, strlen(str2));
  printf("Test %d: ", *test);
  compareTwoString(string3, string4);
  *test += 1;

  const char str3[] = "Welcome to India";
  const char ch3 = 't';

  char *string5 = (char *)s21_memchr(str3, ch3, strlen(str3));
  char *string6 = (char *)memchr(str3, ch3, strlen(str3));
  printf("Test %d: ", *test);
  compareTwoString(string5, string6);
  *test += 1;

  const char str4[] = "t";
  const char ch4 = 't';

  char *string7 = (char *)s21_memchr(str4, ch4, strlen(str4));
  char *string8 = (char *)memchr(str4, ch4, strlen(str4));
  printf("Test %d: ", *test);
  compareTwoString(string7, string8);
  *test += 1;
}

void test_memcpy(int *test) {
  printf("\nmemcpy\n");
  const char src1[50] = "Tutorialspoint";
  char s21_dest1[50] = {0};
  char dest1[50] = {0};
  s21_memcpy(s21_dest1, src1, strlen(src1) + 1);
  memcpy(dest1, src1, strlen(src1) + 1);
  printf("Test %d: ", *test);
  compareTwoString(s21_dest1, dest1);
  *test += 1;

  const char src2[50] = "Point";
  char s21_dest2[50] = {0};
  char dest2[50] = {0};
  s21_memcpy(s21_dest2, src2, strlen(src2) + 1);
  memcpy(dest2, src2, strlen(src2) + 1);
  printf("Test %d: ", *test);
  compareTwoString(s21_dest2, dest2);
  *test += 1;

  const char src3[50] = "Valgrind safe test";
  char s21_dest3[50] = {0};
  char dest3[50] = {0};
  s21_memcpy(s21_dest3, src3, strlen(src3) + 1);
  memcpy(dest3, src3, strlen(src3) + 1);
  printf("Test %d: ", *test);
  compareTwoString(s21_dest3, dest3);
  *test += 1;
}
