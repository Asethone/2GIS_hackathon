BD=../build/
TD=#../tests/
CFLAGS=-c #-Wall -Wextra -Werror
LDFLAGS=#-Wall -Wextra -Werror
LCOVFLAGS=-fprofile-arcs -ftest-coverage
GTESTFLAGS=-lgtest
SRC=model.cpp controller.cpp view.cpp
OBJECTS=$(addprefix $(BD),$(SRC:.cpp=.o))
CC=g++
CC2=g++
OS:=$(shell uname -s)

ifeq ($(OS), Darwin)
	CC2+= -D OS_MAC
else
	CC2+= -D OS_LINUX
	CHECKFLAGS+= -lrt -lpthread -lm
endif

all: main

main: $(BD)main_exe
	./$(BD)main_exe

./$(BD)main_exe: $(OBJECTS) $(BD)main.o
	$(CC) $^ -o $@

debug: $(SRC) main.cpp
	$(CC) -g $^ -o $(BD)main_exe

./$(BD)%.o: %.cpp
	$(CC) $(CFLAGS) $< -o $@

#### TEST #####
test: $(BD)main_test_exe
	./$^

./$(BD)main_test_exe: $(BD)model.o $(BD)main_test.o
	$(CC2) $(LDFLAGS) $^ -o $@ $(GTESTFLAGS)

#### GCOV #####
gcov_report: $(BD)main_test.o
	$(CC) $(CFLAGS) $(LCOVFLAGS) model.cpp -o $(BD)model.o
	$(CC) $(LDFLAGS) $(LCOVFLAGS) $(BD)model.o $(BD)main_test.o -o $(BD)main_gcov_exe $(GTESTFLAGS)
	./$(BD)main_gcov_exe
	# mv *.gcda *.gcno ./$(BD)
	lcov -t "gcov_report" -o $(BD)gcov_report.info -c -d ./$(BD)
	genhtml -o $(BD)report $(BD)gcov_report.info
	open $(BD)report/$(PWD)/index.html

clean:
	rm -rf ./$(BD)*.o ./$(BD)*_exe ./$(BD)*.dSYM ./$(BD)report
	rm -rf ./$(BD)*.gcno ./$(BD)*.gcda ./$(BD)*.info report/

cppcheck:
	cppcheck --enable=all --suppress=missingIncludeSystem ../src/

cpplint:
	cp ../materials/linters/CPPLINT.cfg . && python3 ../materials/linters/cpplint.py --extensions=cpp *.cpp *.h
	rm -f CPPLINT.cfg

leaks:
	leaks --atExit -- ./$(BD)main_test_exe
