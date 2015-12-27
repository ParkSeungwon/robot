CC = g++
OBJ = explorerHat.o main.o lcd.o touch.o range_finder.o stepper.o motor.o analog.o console.o funcs.o
OBJ_IR = irremote.o explorerHat.o stepper.o lcd.o motor.o
LIB = -lwiringPi -lwiringPiDev

all : robot irremote

robot : $(OBJ)
	$(CC) -o robot $(OBJ) $(LIB)
irremote : $(OBJ_IR)
	$(CC) -o irremote $(OBJ_IR) $(LIB) 

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
funcs.o :
console.o :

