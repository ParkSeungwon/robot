CC = g++
OBJ = explorerHat.o main.o 

robot : $(OBJ)
	$(CC) -o robot $(OBJ) -lwiringPi -lwiringPiDev

main.o : main.cc
	$(CC) -c -g main.cc
explorerHat.o : explorerHat.cc explorerHat.hpp
	$(CC) -c -g explorerHat.cc

