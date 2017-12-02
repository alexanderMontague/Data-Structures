
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
	Rule* editRule = NULL;

	char tempWord[100] = "NULL";
	char menuInput[100] = "NULL";
	char tempAdd[100] = "NULL";

	char* tempString = NULL;

	int line = 0;

	bool menuLoop = true;

	if(argc != 2) {
		printf("Usage: ./program <conversation file>\n");
		return 1;
	}
	else {
		filePointer = fopen(argv[1], "r");
	}
	
	binSearchTree = createBinTree(&compareF, &deleteF);

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
				tempRule->totalCount = 0;
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

		while(menuLoop == true) {
			printf("\n1) Add a new rule\n");
			printf("2) Remove a rule\n");
			printf("3) Display rules\n");
			printf("4) Modify rule Rating\n");
			printf("5) Discuss\n");
			printf("9) Quit\n");
			printf("Input: ");
			fgets(menuInput, 100, stdin);

			if(strcmp(menuInput, "1\n") == 0) {
				tempRule = malloc(sizeof(Rule));
				printf("\nEnter the Rule KeyWord: ");
				fgets(tempAdd, 100, stdin);
				tempAdd[strlen(tempAdd) - 1] = '\0';
				tempRule->keyWord = strdup(tempAdd);

				printf("Enter the Rule Sentence: ");
				fgets(tempAdd, 100, stdin);
				tempAdd[strlen(tempAdd) - 1] = '\0';
				tempRule->keySentence = strdup(tempAdd);

				printf("Enter the Rule Rating: ");
				fgets(tempAdd, 100, stdin);
				tempAdd[strlen(tempAdd) - 1] = '\0';
				while(atof(tempAdd) < 0 || atof(tempAdd) > 1) {
					printf("The rating must be between 0 and 1.0!\n");
					printf("Enter the Rule Rating: ");
					fgets(tempAdd, 100, stdin);
					tempAdd[strlen(tempAdd) - 1] = '\0';
				}
				tempRule->userRating = atof(tempAdd);
				tempRule->systemRating = atof(tempAdd);

				addToTree(binSearchTree, tempRule);
			}
			else if(strcmp(menuInput, "2\n") == 0) {
				tempRule = malloc(sizeof(Rule));		// Creating a dummy struct to just hold keyWord to search
				printf("\nEnter the Rule KeyWord: ");
				fgets(tempAdd, 100, stdin);
				tempAdd[strlen(tempAdd) - 1] = '\0';
				tempRule->keyWord = strdup(tempAdd);	
				removeFromTree(binSearchTree, tempRule);
			}
			else if(strcmp(menuInput, "3\n") == 0) {
				printf("\n");
				printInOrder(binSearchTree, &printF);
			}
			else if(strcmp(menuInput, "4\n") == 0) {
				tempRule = malloc(sizeof(Rule));		// Creating a dummy struct to just hold keyWord to search
				printf("\nEnter the Rule KeyWord: ");
				fgets(tempAdd, 100, stdin);
				tempAdd[strlen(tempAdd) - 1] = '\0';
				tempRule->keyWord = strdup(tempAdd);	
				editRule = findInTree(binSearchTree, tempRule);
				if(editRule == NULL) {
					printf("The Rule could not be Found!\n");
				}
				else {
					printf("The current User Rating is: %.2f\n", editRule->userRating);
					printf("Enter a new User Rating: ");
					fgets(tempAdd, 100, stdin);
					while(atof(tempAdd) < 0 || atof(tempAdd) > 1) {
						printf("The rating must be between 0 and 1.0!\n");
						printf("Enter the Rule Rating: ");
						fgets(tempAdd, 100, stdin);
					}
					tempAdd[strlen(tempAdd) - 1] = '\0';
					editRule->userRating = atof(tempAdd);
				}
			}
			else if(strcmp(menuInput, "5\n") == 0) {

			}
			else if(strcmp(menuInput, "9\n") == 0) {
				menuLoop = false;
			}
			else {
				printf("\nInvalid Input! Ex. '1' or '2' \n");
			} 	




		}

		printf("In Order:\n");
		printInOrder(binSearchTree, &printF);
		printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");

		printf("Pre Order:\n");
		printPreOrder(binSearchTree, &printF);
		printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");

		printf("Post Order:\n");
		printPostOrder(binSearchTree, &printF);
		printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");

		printf("Max Height = %d\n", getHeight(binSearchTree->root));

	}
	else {
		printf("The file could not be found.\n");
		return 1;
	}
	
    return 0;
}

