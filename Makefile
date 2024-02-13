CC= g++ 
CFLAGS= -Wall -Wextra -Werror
STANDART= -std=c++17
TESTFLAGS=-lgtest
TESTFILES= tests/*.cc
OS := $(shell uname -s)

all: gcov_report

test: clean
	$(CC) $(CFLAGS) $(STANDART) $(TESTFILES) -o test $(TESTFLAGS)
	./test

style_check:
	clang-format -style=Google -n s21_containers/*.h *.h s21_containersplus/*.h

style_fix:
	clang-format -style=Google -i s21_containers/*.h *.h s21_containersplus/*.h

gcov_report: clean
	$(CC) $(CFLAGS) --coverage $(STANDART) $(TESTFILES) -o test $(TESTFLAGS)
	./test
	lcov -t "test" -o test.info -c -d . --no-external
	genhtml -o report test.info
	open report/index.html

clean:
	rm -rf *.out *.o *.a *.gcda *.gcno *.info test main mytests tree *.txt
	rm -rf report s21_containers/*.gch s21_containersplus/*.gch

leaks_test: clean test

ifeq ($(OS), Darwin)
	leaks --atExit -- test
else
	valgrind --leak-check=full --show-reachable=yes --show-leak-kinds=all --track-origins=yes --log-file=RESULT_VALGRIND.txt ./test
endif
