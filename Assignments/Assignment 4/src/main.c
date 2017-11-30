
// Alexander Montague
// 0959687
// amontagu@uoguelph.ca
// December 2017
// CIS 2520 Assignment 4

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "BinarySearchTreeAPI.h"
#include "rule.h"



int main (int argc, char **argv)
{

	// Variable Decleration
	FILE* filePointer = NULL;

	Tree* binSearchTree = NULL;

	Rule* tempRule = NULL;

	char tempWord[100] = "NULL";

	char* tempString = NULL;

	int line = 0;

	if(argc != 2) {
		printf("Usage: ./program <conversation file>\n");
		return 1;
	}
	else {
		filePointer = fopen(argv[1], "r");
	}
	
	binSearchTree = createBinTree(&compareF, &deleteF, &printF);

	if(filePointer != NULL) {
		while(fgets(tempWord, 100, filePointer) != NULL) {
			if(line == 0) {
				line = 1;
				tempRule = malloc(sizeof(Rule));
			}
			if(line == 1) {
				tempWord[strlen(tempWord) - 1] = '\0';
				tempString = strdup(tempWord);
				tempRule->keyWord = tempString;
				tempRule->userRating = 0.5;
				tempRule->systemRating = 0.5;
				line++;
			}
			else if(line == 2) {
				tempWord[strlen(tempWord) - 1] = '\0';
				tempString = strdup(tempWord);
				tempRule->keySentence = tempString;
				addToTree(binSearchTree, tempRule);
				line = line - 2;
			}
		}
		fclose(filePointer);	

		printPostOrder(binSearchTree, binSearchTree->printFunc);

	}
	else {
		printf("The file could not be found.\n");
		return 1;
	}

	

    return 0;
}

