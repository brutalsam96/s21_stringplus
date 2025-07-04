# CFLAGS = -Wall -Wextra -Werror -std=c11
CFLAGS = -Wall -Wextra -Werror -std=c11
GCOVFLAGS = -fprofile-arcs -ftest-coverage

HEADERS = s21_string.h s21_sprintf.h
SOURCES = $(wildcard *.c)
GCOVPREFIX = report_sprintf.out-
GCOVPREFIX2 = report_s21string.out-
GCOVPREFIX3 = report_s21sscanf.out-
OBJ_LIBRARY := $(patsubst %.c, %.o, $(SOURCES))
# SOURCES = *.c

# OBJ_LIBRARY := $(gcc -c s21_sprintf.c s21_string.c s21_utils.c)

%.o: %.c $(HEADER)
	gcc $(CFLAGS) -c $< -o $@

all: s21_string.a test_sprintf test_string test_sscanf gcov_report

s21_string.a: $(OBJ_LIBRARY) $(HEADERS)
	ar rcs s21_string.a $(OBJ_LIBRARY)
	ranlib s21_string.a
	rm -rf *.o

test_sprintf: s21_string.a tests/sprintf/test_s21sprintf.c
	gcc -Wall -Wextra tests/sprintf/test_s21sprintf.c s21_string.a -o test_sprintf.out -lcheck -lm -lpthread -lsubunit
	./test_sprintf.out

test_string: s21_string.a tests/s21_string/test_s21string.c
	gcc -Wall -Wextra tests/s21_string/test_s21string.c s21_string.a -o test_s21string.out -lcheck -lm -lpthread -lsubunit
	./test_s21string.out

test_sscanf: s21_string.a tests/sscanf/test_s21sscanf.c
	gcc -Wall -Wextra tests/sscanf/test_s21sscanf.c s21_string.a -o test_s21sscanf.out -lcheck -lm -lpthread -lsubunit
	./test_s21sscanf.out

test: s21_string.a tests/sprintf/test_s21sprintf.c tests/s21_string/test_s21string.c tests/sscanf/test_s21sscanf.c
	$(MAKE) test_sprintf
	$(MAKE) test_string
	$(MAKE) test_sscanf

gcov_report: s21_string.a tests/s21_string/test_s21string.c
	gcc $(GCOVFLAGS) tests/s21_string/test_s21string.c $(SOURCES) -o ./report_sprintf.out -lcheck -lm -lpthread -lsubunit
	./report_sprintf.out
	
	gcc $(GCOVFLAGS) tests/sprintf/test_s21sprintf.c $(SOURCES) -o ./report_s21string.out -lcheck -lm -lpthread -lsubunit
	./report_s21string.out

	gcc $(GCOVFLAGS) tests/sscanf/test_s21sscanf.c $(SOURCES) -o ./report_s21sscanf.out -lcheck -lm -lpthread -lsubunit
	./report_s21sscanf.out

	gcov -f $(GCOVPREFIX)s21_sprintf.c $(GCOVPREFIX)s21_string.c $(GCOVPREFIX)s21_utils.c
	gcov -f $(GCOVPREFIX2)s21_sprintf.c $(GCOVPREFIX2)s21_string.c $(GCOVPREFIX2)s21_utils.c
	gcov -f $(GCOVPREFIX3)s21_sscanf.c
	
	lcov -t "gcov_report" -o Coverage_Report.info -c -d .
	genhtml -o ./report Coverage_Report.info
	rm -f *.gcno *.gcda *.info report.out *.gcov
	open ./report/index-sort-f.html


rebuild: clean all

clean:
	rm -f *.o *.a *.gcno *.gcda *.info *.out *.gcov
	rm -rf ./report
    