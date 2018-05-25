CXX = g++-7
CXX_FLAGS = -Wall -Werror -std=c++1z
BUILD_FOLDER = build
MEMORY_DEBUG_FLAGS = -m32 -g -fno-inline -fno-omit-frame-pointer

TREE_TESTS_UNOPTIMIZED = tree_tests_unoptimized.x
TREE_TESTS_OPTIMIZED = tree_tests_optimized.x
VALGRIND_FLAGS = -v --leak-check=full --show-leak-kinds=all --error-exitcode=1 --show-leak-kinds=definite --errors-for-leak-kinds=definite

all:
	make tests
	make mem_check

tests: link
	./$(TREE_TESTS_UNOPTIMIZED)
	./$(TREE_TESTS_OPTIMIZED)

link:
	make compile_unoptimized
	$(CXX) $(CXX_FLAGS) -o $(TREE_TESTS_UNOPTIMIZED) ./$(BUILD_FOLDER)/tree_tests.o ./$(BUILD_FOLDER)/tree_testing_program.o -lcppunit
	make compile_optimized
	$(CXX) $(CXX_FLAGS) -o $(TREE_TESTS_OPTIMIZED) ./$(BUILD_FOLDER)/tree_tests.o ./$(BUILD_FOLDER)/tree_testing_program.o -lcppunit
	rm -rf ./$(BUILD_FOLDER)

compile_unoptimized:
	mkdir -p $(BUILD_FOLDER)
	$(CXX) $(CXX_FLAGS) -c -O0 ./tests/*.cpp
	mv ./*.o ./$(BUILD_FOLDER)

compile_optimized:
	mkdir -p $(BUILD_FOLDER)
	$(CXX) $(CXX_FLAGS) -c -O3 ./tests/*.cpp
	mv ./*.o ./$(BUILD_FOLDER)

mem_check: link
	valgrind $(VALGRIND_FLAGS) ./$(TREE_TESTS_UNOPTIMIZED)
	valgrind $(VALGRIND_FLAGS) ./$(TREE_TESTS_OPTIMIZED)

clean:
	rm -rf ./$(BUILD_FOLDER)
	rm -f *.x
	rm -rf *.dSYM
