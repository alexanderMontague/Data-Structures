CC = gcc
CFLAGS = -Wall -g -std=c99

BIN = ./bin/
SRC = ./src/
LIB = ./lib/

program:
	$(CC) $(CFLAGS) $(SRC)main.c $(SRC)BinarySearchTree.c $(SRC)rule.c -Iinclude -Ilib -o $(BIN)program

testProgram:
	$(CC) $(CFLAGS) $(SRC)testMain.c $(SRC)hash.c $(SRC)HashTableAPI.c -w -Iinclude -Ilib -o $(BIN)program

cls:
	clear

