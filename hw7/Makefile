CXX = g++
CXX_FLAGS = -g -Wall -Wextra -std=c++11# -fsanitize=address
INC_FILES = doubll2d.hpp doubll2d-impl.hpp
SRC_FILES = main_copy.cpp

all: ${INC_FILES} ${SRC_FILES}
	${CXX} ${CXX_FLAGS} -o main ${SRC_FILES}

clean:
	rm -f main

.PHONY: clean