CC = gcc -std=c11 -g
FLAGS = -Wall -Werror -Wextra
OS = $(shell uname)
LIBSOURCES=matrix.c foo.c tests.c

ifeq ($(OS), Linux)
	CHECKFLAGS=-lcheck -lm -lpthread -lrt -lsubunit
else
	CHECKFLAGS=-lcheck -lm -lpthread -fprofile-arcs -ftest-coverage
endif

all: gcov_report

matrix.a: matrix.o foo.o
	ar -crs matrix.a matrix.o foo.o 
	ranlib matrix.a

test: tests.o
	$(CC) $(FLAGS) $(LIBSOURCES) -o run $(CHECKFLAGS) -lgcov --coverage
	./run

test_val:
	$(CC) $(FLAGS) $(LIBSOURCES) -o run $(CHECKFLAGS) -lgcov --coverage
	sh valgrind.sh ./run
	make clean

gcov_report: test
	lcov -t "test" -o report.info -c -d .
	genhtml -o report report.info
	open ./report/index.html

tests.o: tests.c
	$(CC) $(FLAGS) -c tests.c

matrix.o: matrix.c
	$(CC) $(FLAGS) -c matrix.c

foo.o: foo.c
	$(CC) $(FLAGS) -c foo.c

clang:
	cp ../materials/linters/.clang-format ../src/.clang-format; \
	clang-format -style=Google -n *.c *.h;
	
clean:
	rm -rf *.o \
	*.a \
	result \
	report.info \
	run \
	foo.gcda \
	foo.gcno \
	matrix.gcda \
	matrix.gcno \
	tests.gcda \
	tests.gcno \
	./report \
	./run-* \
	run.dSYM \

