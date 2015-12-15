CC = g++
OBJ = explorerHat.o main.o test.o

robot : $(OBJ)
	$(CC) -o robot $(OBJ) -lwiringPi -lwiringPiDev

main.o : main.cc
	$(CC) -c -g main.cc
test : test.cc
	$(CC) -o test -g test.cc -lwiringPi -lwiringPiDev
explorerHat.o : explorerHat.cc explorerHat.hpp
	$(CC) -c -g explorerHat.cc

