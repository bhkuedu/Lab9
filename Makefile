CXX = g++
CXXFLAGS = -std=c++11 -Wall

all: main

main: main.cpp matrix.o
	$(CXX) $(CXXFLAGS) -o main main.cpp matrix.o

matrix.o: matrix.cpp matrix.hpp
	$(CXX) $(CXXFLAGS) -c matrix.cpp

clean:
	rm -f matrix.o main
