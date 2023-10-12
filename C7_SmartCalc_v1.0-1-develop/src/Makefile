.PHONY: all s21_smartcalc.a test gcov_report check rebuild clean test.o install uninstall dist dvi style update
CC = gcc
CFLAGS = -Wall -Werror -Wextra -std=c11 -g
GCOVFLAGS =  -fprofile-arcs -ftest-coverage 
LC = lcov -c -d .
C_FILES = ./Calculator/s21*.c
O_FILES = s21*.o
LIBS=-lcheck
LINUX=-lcheck -lm -lpthread -lrt -lsubunit
OS=$(shell uname -s)

all : install 
clean : 
	rm -rf *.o *.gcno *.gcda *.info smart_calc_test.out s21_smartcalc.a
	rm -rf ./report
	rm -rf *.dSYM
rebuild : clean all

$(O_FILES) :
	$(CC) $(CFLAGS) -c $(C_FILES) ./s21_smartcalc.h
test.o :
	$(CC) $(CFLAGS) -c -lcheck smart_calc_test.c
s21_smartcalc.a :
	$(CC) $(CFLAGS) -c $(C_FILES)
	ar r s21_smartcalc.a $(O_FILES)

test: s21_smartcalc.a smart_calc_test.c
ifeq ($(OS), Darwin)
	$(CC) $(CFLAGS) smart_calc_test.c s21_smartcalc.a -o smart_calc_test.out $(LIBS)
else
	$(CC) $(CFLAGS) smart_calc_test.c s21_smartcalc.a -o smart_calc_test.out $(LIBS) $(LINUX)
endif
	./smart_calc_test.out	

gcov_report : clean
	$(CC) $(CFLAGS) $(GCOVFLAGS) -o gcov_test -lcheck $(C_FILES) smart_calc_test.c
	./gcov_test 
	$(LC) -t "gcov_report" --no-external -o report.info
	genhtml -o gcov_report report.info
	rm -f *.gcno *.gcda *.info report.out *.gcov
	open ./gcov_report/index-sort-f.html

install: uninstall
	mkdir build
	cd build && qmake ../Calculator/ && make

uninstall:
	rm -rf build*

dist:
	rm -rf Archive_SmartCalc_v1.0-1/
	mkdir Archive_SmartCalc_v1.0-1/
	mkdir Archive_SmartCalc_v1.0-1/src
	mv ./build/s21_SmartCalc.app Archive_SmartCalc_v1.0-1/src/
	tar cvzf Archive_SmartCalc_v1.0-1.tgz Archive_SmartCalc_v1.0-1/
	rm -rf Archive_SmartCalc_v1.0-1/

dvi:
	open ../README.md


check:
	cp ../materials/linters/.clang-format ./
	clang-format -n ./*.c
	clang-format -n ./Calculator/*.cpp
	clang-format -n ./Calculator/*.c
	clang-format -n ./Calculator/*.h

style:
	cp ../materials/linters/.clang-format ./
	clang-format -i ./*.c
	clang-format -i ./Calculator/*.c
	clang-format -i ./Calculator/*.cpp
	clang-format -i ./Calculator/*.h
	rm -rf .clang-format

update:
	make clean
	make style
	git add .
	git commit -m "Update"
	git push origin develop
