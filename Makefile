CC = g++
OBJ = explorerHat.o main.o 
LIB = -lwiringPi -lwiringPiDev

all : robot irremote
robot : $(OBJ)
	$(CC) -o robot $(OBJ) -lwiringPi -lwiringPiDev
irremote : irremote.o explorerHat.o
	$(CC) -o irremote irremote.o explorerHat.o $(LIB) 
irremote.o : irremote.cc 
	$(CC) -c irremote.cc 
main.o : main.cc
	$(CC) -c -g main.cc
explorerHat.o : explorerHat.cc explorerHat.hpp
	$(CC) -c -g explorerHat.cc

