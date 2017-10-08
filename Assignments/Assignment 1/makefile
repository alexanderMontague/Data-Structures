CC = gcc
CFLAGS = -Wall -g -std=c99

BIN = ./bin/
SRC = ./src/
LIB = ./lib/

program:
	$(CC) $(CFLAGS) $(SRC)main.c $(SRC)car.c -Iinclude -Ilib -o $(BIN)program

testProgram:
	$(CC) $(CFLAGS) $(SRC)bookMain.c $(SRC)boardgameMain.c $(SRC)storeMain.c $(SRC)testMain.c -Iinclude -Ilib $(LIB)libLinkedList.a -o $(BIN)testProgram

cls:
	clear

