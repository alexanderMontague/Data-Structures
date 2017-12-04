
// Alexander Montague
// 0959687
// amontagu@uoguelph.ca
// November 2017
// CIS 2520 Assignment 3

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <limits.h>
#include "hash.h"
#include "HashTableAPI.h"

char* allocatedPointer(char* oldString);

int main (int argc, char **argv)
{

	// Variable Decleration
	FILE* filePointer = NULL;
	FILE* filePointer2 = NULL;

	HTable* hashTable = NULL;

	char* tempString = NULL;

	char tempWord[100] = "NULL";
	char menuInput[100] = "NULL";
	char fileName[100] = "NULL";

	bool menuLoop = true;

	size_t numWords = 23; // Constant Size of Hash Table - Closest prime number to number of test elements - 20

	int tempKey = 0;
	int correctWords = 0;
	int incorrectWords = 0;
	

	if(argc != 2) {
		printf("Usage: ./program <dicitonaryName>\n");
		return 1;
	}
	else {
		filePointer = fopen(argv[1], "r");
	}

	hashTable = createTable(numWords, NULL, NULL, NULL);

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

	do {

		printf("\n1) Add a word to the Dictionary\n");
		printf("2) Remove a word from the Dictionary\n");
		printf("3) Spell Check a file\n");
		printf("4) Show Dictionary Words\n");
		printf("5) Quit\n");
		printf("Input: ");
		fgets(menuInput, 100, stdin);
		printf("\n");

		if(strcmp(menuInput, "1\n") == 0) {
			printf("Word: ");
			fgets(tempWord, 100, stdin);
			tempWord[strlen(tempWord) - 1] = '\0';
			tempString = allocatedPointer(tempWord);
			//tempString = strdup(tempWord);
			for(int i = 0; i < strlen(tempString); i++) {
				tempString[i] = tolower(tempString[i]);
			}
			tempString[0] = toupper(tempString[0]);
			tempKey = generateKey(tempString);
			if(inList(hashTable, tempKey) == false) {		// Get input, check if in hash map, add or dont add
				insertData(hashTable, tempKey, tempString);
				printf("Successfully added %s to the Dictionary!\n", tempString);
			}
			else {
				printf("This word is already in the Dictionary!\n");
			}
		}
		else if(strcmp(menuInput, "2\n") == 0) {
			printf("Word: ");
			fgets(tempWord, 100, stdin);
			tempWord[strlen(tempWord) - 1] = '\0';
			tempString = allocatedPointer(tempWord);
			//tempString = strdup(tempWord);
			for(int i = 0; i < strlen(tempString); i++) {
				tempString[i] = tolower(tempString[i]);
			}
			tempString[0] = toupper(tempString[0]);
			tempKey = generateKey(tempString);
			if(inList(hashTable, tempKey) == true) {		// Same idea, get input, check if word is valid to delete, delete word from hash table
				removeData(hashTable, tempKey);
				printf("Successfully deleted %s from the Dictionary!\n", tempString);
			}
			else {
				printf("This word is not in the Dictionary!\n");
			}
		}
		else if(strcmp(menuInput, "3\n") == 0) {
			incorrectWords = 0;
			correctWords = 0;
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
				printf("\nSummary:\n");
				printf("Correctly spelt words: %d\n", correctWords);
				printf("Incorrectly spelt words: %d\n", incorrectWords);
			}
			fclose(filePointer2);
		}
		else if(strcmp(menuInput, "4\n") == 0) {
			for(int i = 0; i < hashTable->size; i++) {
				if(hashTable->table[i] != NULL) {
					Node* tempNode = hashTable->table[i];
					while(tempNode != NULL) {
						tempKey = tempNode->key;
						printf("%d:%d:%s\n", i, tempKey, (char*)lookupData(hashTable, tempKey));
						tempNode = tempNode->next;
					}
				}
			}
		}
		else if(strcmp(menuInput, "5\n") == 0) {
			destroyTable(hashTable);
			menuLoop = false;
		}
		else {
			printf("Invalid option. Try again.\n");
		}

	}
	while(menuLoop == true);

    return 0;
}

char* allocatedPointer(char* oldString) {
	char* newPointer = NULL;
	newPointer = malloc((strlen(oldString) + 1) * sizeof(char));
	strncpy(newPointer, oldString, strlen(oldString) + 1);
	return newPointer;
}

