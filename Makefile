CC = g++
OBJ = explorerHat.o main.o lcd.o touch.o range_finder.o stepper.o motor.o analog.o
LIB = -lwiringPi -lwiringPiDev

all : robot irremote

robot : $(OBJ)
	$(CC) -o robot $(OBJ) -lwiringPi -lwiringPiDev
irremote : irremote.o explorerHat.o stepper.o lcd.o 
	$(CC) -o irremote $(OBJ) $(LIB) 

irremote.o : irremote.cc 
	$(CC) -c irremote.cc 
main.o : main.cc
	$(CC) -c -g main.cc
explorerHat.o : explorerHat.cc explorerHat.hpp
	$(CC) -c -g explorerHat.cc

range_finder.o : 
touch.o :
lcd.o :
stepper.o :
motor.o :
analog.o :
