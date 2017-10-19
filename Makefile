all: tests
	g++ ./15_solver_cpp.cpp -o solver

tests: libgtest.a
	g++ -isystem ./googletest/include -pthread ./test_simple.cpp libgtest.a -o test
	./test
	rm test gtest-all.o libgtest.a

libgtest.a: gtest-all.o
	ar -rv libgtest.a gtest-all.o

gtest-all.o:
	g++ -isystem ./googletest/include -I./googletest -pthread -c ./googletest/src/gtest-all.cc