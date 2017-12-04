
// Alexander Montague
// 0959687
// amontagu@uoguelph.ca
// November 2017
// CIS 2520 Assignment 3
// TEST MAIN

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <limits.h>
#include "hash.h"
#include "HashTableAPI.h"


void addWord(HTable* hashTable);

void printHash(HTable* hashTable);

void delWord(HTable* hashTable);

char* allocatedPointer(char* oldString);

int main (int argc, char **argv)
{

	// Variable Decleration
	FILE* filePointer = NULL;
	FILE* filePointer2 = NULL;

	HTable* hashTable = NULL;

	char* tempString = NULL;

	char tempWord[100] = "NULL";
	char fileName[100] = "NULL";


	size_t numWords = 23; // Constant Size of Hash Table - Closest prime number to number of test elements - 20

	int tempKey = 0;
	int correctWords = 0;
	int incorrectWords = 0;
	
	// TEST 1
	printf("\nTEST: Open dictionary file from command line\n");
	printf("Expected: If specified correct path and file, load into hash map without error\n");
	printf("Received: ");
	if(argc != 2) {
		printf("Usage: ./program <dicitonaryName>\n");
		return 1;
	}
	else {
		filePointer = fopen(argv[1], "r");
	}
	printf("Result: Success!\n");

	// TEST 2
	printf("\nTEST: Create and Initialize a Hash Table\n");
	printf("Expected: hashTable pointer to be allocated\n");
	printf("Received: *hashTable before creation: %p\n", hashTable);
	hashTable = createTable(numWords, NULL, NULL, NULL);
	printf("Received: *hashTable after creation: %p\n", hashTable);


	// TEST 3
	printf("\nTEST: Load data from dictionary file\n");
	printf("Expected: hashTable to be filled with data\n");
	printf("Received: Loading data if file is valid, or ending program\n");
	if(filePointer != NULL) {
		while(fgets(tempWord, sizeof(tempWord), filePointer) != NULL) {
			tempWord[strlen(tempWord) - 1] = '\0';
			tempString = allocatedPointer(tempWord);
			//tempString = strdup(tempWord);
			for(int i = 0; i < strlen(tempString); i++) {
				tempString[i] = tolower(tempString[i]);
			}
			tempString[0] = toupper(tempString[0]);
			insertData(hashTable, generateKey(tempString), tempString);		// Add words from file to hash map
		}
		fclose(filePointer);					
	}
	else {
		printf("The file could not be found.\n");
		return 1;
	}
	printf("Result: \n");
	printHash(hashTable);

	// TEST 3
	printf("\nTEST: Add a valid data entry to the dictionary in the program\n");
	printf("Expected: Word successfully added to dictionary!\n");
	printf("Received: Add: TEST\n");
	printf("Result: \n");
	addWord(hashTable);
	printHash(hashTable);

	// TEST 4
	printf("\nTEST: Add an invalid data entry to the dictionary in the program\n");
	printf("Expected: Word unsuccessfully added to dictionary!\n");
	printf("Received: Add: TEST - this word is already in the dictionary\n");
	printf("Result: \n");
	addWord(hashTable);
	printHash(hashTable);

	// TEST 5
	printf("\nTEST: Remove a valid data entry from the dictionary in the program\n");
	printf("Expected: Word successfully removed from dictionary!\n");
	printf("Received: Remove: PuRpLe\n");
	printf("Result: \n");
	delWord(hashTable);
	printHash(hashTable);

	// TEST 6
	printf("\nTEST: Remove an invalid data entry from the dictionary in the program\n");
	printf("Expected: Word not removed from dictionary!\n");
	printf("Received: Remove: testtest\n");
	printf("Result: \n");
	delWord(hashTable);
	printHash(hashTable);

	// TEST 7
	printf("\nTEST: Search a file for words in the dicitonary\n");
	printf("Expected: Words from the file that are not in the dicitonary\n");
	printf("Received: Input Filename\n");
	printf("Enter a filename to be spell checked!\n");
	printf("File Name: ");
	fgets(fileName, 100, stdin);
	fileName[strlen(fileName) - 1] = '\0';
	filePointer2 = fopen(fileName, "r");
	if(filePointer2 == NULL) {
		printf("File could not be found.\n");
	}
	else {
		printf("\nFile processed by Spell Check %s:\n", fileName);
		char tempWord[100] = "NULL";
		while(fgets(tempWord, 100, filePointer2) != NULL) {
			tempWord[strlen(tempWord) - 1] = '\0';
			tempString = allocatedPointer(tempWord);
			//tempString = strdup(tempWord);
			for(int i = 0; i < strlen(tempString); i++) {
				tempString[i] = tolower(tempString[i]);
			}
			tempString[0] = toupper(tempString[0]);
			tempKey = generateKey(tempString);
			if(inList(hashTable, tempKey) == false) {
				printf("%s was not found in the dictionary\n", tempWord);
				incorrectWords++;
			}
			else {
				correctWords++;
			}
		}
		printf("Result: \n");
		printf("\nSummary:\n");
		printf("Correctly spelt words: %d\n", correctWords);
		printf("Incorrectly spelt words: %d\n", incorrectWords);
	}
	fclose(filePointer2);

	// TEST 8
	// EDGE CASE
	printf("\nTEST: Remove the first word in the first element of the hash table\n");
	printf("Expected: word will be deleted successfully\n");
	printf("Received: (Because order changes, delete whatever word is first)\n");
	delWord(hashTable);
	printf("Result: \n");
	printHash(hashTable);

	// TEST 9
	// EDGE CASE
	printf("\nTEST: Remove the last word in the last element of the hash table\n");
	printf("Expected: word will be deleted successfully\n");
	printf("Received: (Because order changes, delete whatever word is last)\n");
	delWord(hashTable);
	printf("Result: \n");
	printHash(hashTable);

	// TEST 10
	printf("\nTEST: test the case insensitivity when deleting \n");
	printf("Expected: word will be deleted successfully\n");
	printf("Received: (delete whatever word is left with jumbled case. Ex. eXaMpLe)\n");
	delWord(hashTable);
	printf("Result: \n");
	printHash(hashTable);

	// TEST 11
 	// Delete the Hash Table
 	destroyTable(hashTable);

    return 0;
}

void printHash(HTable* hashTable) {
	for(int i = 0; i < hashTable->size; i++) {
		if(hashTable->table[i] != NULL) {
			Node* tempNode = hashTable->table[i];
			while(tempNode != NULL) {
				int tempKey = tempNode->key;
				printf("%d:%d:%s\n", i, tempKey, (char*)lookupData(hashTable, tempKey));
				tempNode = tempNode->next;
			}
		}
	}
}

void addWord(HTable* hashTable) {
	char tempWord[100];
	printf("Word: ");
	fgets(tempWord, 100, stdin);
	tempWord[strlen(tempWord) - 1] = '\0';
	char* tempString = allocatedPointer(tempWord);
	//char* tempString = strdup(tempWord);
	for(int i = 0; i < strlen(tempString); i++) {
		tempString[i] = tolower(tempString[i]);
	}
	tempString[0] = toupper(tempString[0]);
	int tempKey = generateKey(tempString);
	if(inList(hashTable, tempKey) == false) {
		insertData(hashTable, tempKey, tempString);
		printf("Successfully added %s to the Dictionary!\n", tempString);
	}
	else {
		printf("This word is already in the Dictionary!\n");
	}
}

void delWord(HTable* hashTable) {
	char tempWord[100];
	printf("Word: ");
	fgets(tempWord, 100, stdin);
	tempWord[strlen(tempWord) - 1] = '\0';
	char* tempString = allocatedPointer(tempWord);
	//char* tempString = strdup(tempWord);
	for(int i = 0; i < strlen(tempString); i++) {
		tempString[i] = tolower(tempString[i]);
	}
	tempString[0] = toupper(tempString[0]);
	int tempKey = generateKey(tempString);
	if(inList(hashTable, tempKey) == true) {
		removeData(hashTable, tempKey);
		printf("Successfully deleted %s from the Dictionary!\n", tempString);
	}
	else {
		printf("This word is not in the Dictionary!\n");
	}
}

char* allocatedPointer(char* oldString) {
	char* newPointer = NULL;
	newPointer = malloc((strlen(oldString) + 1) * sizeof(char));
	strncpy(newPointer, oldString, strlen(oldString) + 1);
	return newPointer;
}
