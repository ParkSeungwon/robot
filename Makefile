CC = g++
OBJ = explorerHat.o main.o 
LIB = -lwiringPi -lwiringPiDev

robot : $(OBJ)
	$(CC) -o robot $(OBJ) -lwiringPi -lwiringPiDev
test : test.o
	$(CC) -o test test.o explorerHat.o $(LIB) 
test.o : test.cc
	$(CC) -c test.cc 
main.o : main.cc
	$(CC) -c -g main.cc
explorerHat.o : explorerHat.cc explorerHat.hpp
	$(CC) -c -g explorerHat.cc

