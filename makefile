CC = g++
CXX = g++
CXXFLAGS = -Werror -Wall -Wextra -O2 -funroll-loops -ffast-math -ftree-vectorize -mtune=native -std=c++14 -Wconversion -g

all: disjoint_tests

disjoint_tests: tests.o | disjoint_set.hpp

clean:
		rm -f disjoint_tests.o
