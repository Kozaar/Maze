SHELL=/bin/sh
CC=g++
CFLAGS=
OS=$(shell uname)
ifeq ($(OS), Linux)
    CHECK_FLAGS=-lgtest -pthread -lrt -lm -lsubunit
else
    CHECK_FLAGS=-lgtest
endif
GCOVFLAGS=--coverage
HTML_CREATE=lcov --no-external -t a.out -o rep.info -c -d .; genhtml -o report rep.info
BUILD=maze_build
HOME=Maze
TEST_COMPILE=$(CC) $(CFLAGS) test.cpp Maze/Model/*.cpp $(CHECK_FLAGS)

all: install test

install: uninstall 
	mkdir $(BUILD)
	cd $(HOME); qmake
	make -C ./$(HOME)
	cd $(HOME); mv moc_* ui_* Maze.app Makefile ../$(BUILD)
	cd $(HOME); mv *.o ../$(BUILD); rm .qmake.stash

uninstall:
	rm -rf $(BUILD)

start:
	./$(BUILD)/Maze.app/Contents/MacOS/Maze

test:
	$(TEST_COMPILE)
	./a.out
	make clean

dvi:
	makeinfo --html doc.texi
	open doc/index*

dist:
	make clean
	tar -czvf maze.tar.gz Makefile $(HOME) test.cpp doc.texi 

linter: 
	cp ../materials/linters/CPPLINT.cfg ./
	python3 ../materials/linters/cpplint.py --extensions=cpp $(HOME)/*/* $(HOME)/*.cpp
	rm CPPLINT.cfg

clean:
	rm -rf doc *.g* *.info *.out build* *.txt *.cfg

gcov_report: clean
	$(TEST_COMPILE) $(WFLAGS) $(TEST_FLAGS) $(GCOVFLAGS)
	./a.out
	$(HTML_CREATE)
