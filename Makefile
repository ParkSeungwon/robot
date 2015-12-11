CC = g++
OBJ = explorerHat.o main.o

robot : $(OBJ)
	$(CC) -o robot $(OBJ) -lwiringPi -lwiringPiDev

main.o : main.cc
	$(CC) -c main.cc
explorerHat.o : explorerHat.cc
	$(CC) -c explorerHat.cc

