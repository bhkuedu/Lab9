CXX = g++
CXXFLAGS = -std=c++11 -Wall

all: matrix.o main

main: main.cpp matrix.hpp
	$(CXX) $(CXXFLAGS) -o main main.cpp matrix.hpp

clean:
	rm -f matrix.o main
