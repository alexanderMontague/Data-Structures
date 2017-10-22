CC = gcc
CFLAGS = -Wall -g -std=c99

BIN = ./bin/
SRC = ./src/
LIB = ./lib/

program:
	$(CC) $(CFLAGS) $(SRC)main.c $(SRC)LinkedListAPI.c $(SRC)QueueAPI.c $(SRC)patient.c -Iinclude -Ilib -o $(BIN)program

testProgram:
	$(CC) $(CFLAGS) $(SRC)car.c $(SRC)APIfunctions.c $(SRC)testMain.c -Iinclude -Ilib  -o $(BIN)testProgram

cls:
	clear

