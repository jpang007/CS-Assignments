
#makefile

#variables
G = g++

all: 
	$(G) -o myassignment TestCuckooHashTable.cpp CuckooHashTable.cpp

Q: QuadraticProbing.cpp QuadraticProbing.h
	$(G)  QuadraticProbing.cpp TestQuadraticProbing.cpp
	
S: SeparateChaining.cpp SeparateChaining.h
	$(G)  SeparateChaining.cpp TestSeparateChaining.cpp
	
Test: main.cpp QuadraticProbing.cpp QuadraticProbing.h SeparateChaining.h
	$(G) -o myassignment main.cpp QuadraticProbing.cpp SeparateChaining.cpp
	
