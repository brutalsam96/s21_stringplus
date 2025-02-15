CFLAGS = -Wall -Wextra -Werror -std=c11
GCOVFLAGS = -fprofile-arcs -ftest-coverage

HEADERS = s21_string.h
# SOURCES = $(wildcard *.c)
SOURCES = *.c

OBJ_LIBRARY := $(patsubst %.c, %.o, $(SOURCES))

%.o: %.c $(HEADER)
	gcc $(CFLAGS) -c $< -o $@

all: s21_string.a gcov_report test

s21_string.a: $(OBJ_LIBRARY) $(HEADERS)
	ar rcs s21_string.a $(OBJ_LIBRARY)
	ranlib s21_string.a
	rm -rf *.o