CC = gcc
CFLAGS = -Wall -g -std=c99

BIN = ./bin/
SRC = ./src/
LIB = ./lib/

program:
	$(CC) $(CFLAGS) $(SRC)main.c $(SRC)LinkedListAPI.c $(SRC)QueueAPI.c $(SRC)patient.c -w -Iinclude -Ilib -o $(BIN)program

testProgram:
	$(CC) $(CFLAGS) $(SRC)QueueAPI.c $(SRC)patient.c $(SRC)LinkedListAPI.c $(SRC)testMain.c -w -Iinclude -Ilib  -o $(BIN)testProgram

cls:
	clear

