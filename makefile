CXX = g++
CXX_FLAGS = -Wall -Werror -std=c++1z
BUILD_FOLDER = build
MEMORY_DEBUG_FLAGS = -m32 -g -fno-inline -fno-omit-frame-pointer

TREE_TESTS = tree_tests.x
VALGRIND_FLAGS = -v --leak-check=full --show-leak-kinds=all --error-exitcode=1 --show-leak-kinds=definite --errors-for-leak-kinds=definite

all:
	make tests
	make mem_check

tests: link
	./$(TREE_TESTS)

link: compile
	$(CXX) $(CXX_FLAGS) -o $(MATRIX_TESTS) ./$(BUILD_FOLDER)/tree_tests.o ./$(BUILD_FOLDER)/tree_testing_program.o -lcppunit
	rm -rf ./$(BUILD_FOLDER)

compile:
	mkdir -p $(BUILD_FOLDER)
	$(CXX) $(CXX_FLAGS) -c -O3 ./tests/*.cpp
	mv ./*.o ./$(BUILD_FOLDER)

mem_check: link
	valgrind $(VALGRIND_FLAGS) ./$(TREE_TESTS)

clean:
	rm -rf ./$(BUILD_FOLDER)
	rm -f *.x
	rm -rf *.dSYM
