
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

	Rule staticRule;

	char tempWord[100] = "NULL";
	char menuInput[100] = "NULL";
	char tempAdd[100] = "NULL";
	char userInput[100] = "NULL";

	char* tempString = NULL;
	char* split = NULL;

	int line = 0;
	int i = 0;
	int x = 0;

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
				for(int i = 0; i < strlen(tempWord); i++) {
					tempWord[i] = tolower(tempWord[i]);
				}
				tempString = strdup(tempWord);
				tempRule->keyWord = tempString;
				tempRule->userRating = 0.5;
				tempRule->systemRating = 0.5;
				tempRule->totalCount = 0;
				line++;
			}
			else if(line == 2) {
				tempWord[strlen(tempWord) - 1] = '\0';
				for(int i = 0; i < strlen(tempWord); i++) {
					tempWord[i] = tolower(tempWord[i]);
				}
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
				while(strcmp(tempAdd, "\n") == 0) {
					printf("You must enter a valid keyword!\n");
					fgets(tempAdd, 100, stdin);
				}
				tempAdd[strlen(tempAdd) - 1] = '\0';
				for(int i = 0; i < strlen(tempAdd); i++) {
					tempAdd[i] = tolower(tempAdd[i]);
				}				
				tempRule->keyWord = strdup(tempAdd);

				printf("Enter the Rule Sentence: ");
				fgets(tempAdd, 100, stdin);
				while(strcmp(tempAdd, "\n") == 0) {
					printf("You must enter a valid keyword!\n");
					fgets(tempAdd, 100, stdin);
				}
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
				for(int i = 0; i < strlen(tempAdd); i++) {
					tempAdd[i] = tolower(tempAdd[i]);
				}
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
				for(int i = 0; i < strlen(tempAdd); i++) {
					tempAdd[i] = tolower(tempAdd[i]);
				}
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
				char tempRating[100];
				char userInputArray[100][100];
				Rule ruleArray[100];
				Rule priorityRule;
				double priority = 0;
				double highestPriority = 0;
				i = 0;
				x = 0;
				printf("\nI am your personal assistant!\n");
				printf("Ask me something: ");
				fgets(userInput, 100, stdin);		// get sentence from user
				userInput[strlen(userInput) - 1] = '\0';
				if(userInput[strlen(userInput) - 1] == '?' || userInput[strlen(userInput) - 1] == '!' || userInput[strlen(userInput) - 1] == '.') {
					userInput[strlen(userInput) - 1] = '\0';
				}
				if(strcmp(userInput, "") == 0) {
					printf("You must enter a sentence!\n");
				}
				else {
					for(int i = 0; i < strlen(userInput); i++) {
						userInput[i] = tolower(userInput[i]);
					}
					split = strtok(userInput, " ");
					while(split != NULL) {
						strcpy(userInputArray[i], split);	// put each word in sentence in an array
						split = strtok(NULL, " ");
						i++;
					}
					for(int j = 0; j < i; j++) {
						staticRule.keyWord = malloc((strlen(userInputArray[j]) * sizeof(char)) + 1);	// temp static Rule struct to hold a word in the sentence
						strcpy(staticRule.keyWord, userInputArray[j]);			// copy word from sentence into temp struct to search
						tempRule = findInTree(binSearchTree, &staticRule);		// search the tree for the word
						if(tempRule != NULL) {
							ruleArray[x] = *tempRule;							// if the word is in the tree, add to the struct array
							x++;
						}
					}
					if(x != 0) {						// if there is at least one rule in the array, or one word in the sentence in the rule tree
						highestPriority = ruleArray[0].userRating + ruleArray[0].systemRating;
						priorityRule = ruleArray[0];	// set the default highest priority to the first rule to compare
					}
					for(int k = 0; k < x; k++) {
						priority = ruleArray[k].userRating + ruleArray[k].systemRating;
						if(priority >= highestPriority) {
							priorityRule = ruleArray[k];
						}
					}
					if(x != 0) {
						tempRule = findInTree(binSearchTree, &priorityRule);
						printf("My response is: %s\n", tempRule->keySentence);
						tempRule->totalCount++;
						while(1) {
							printf("Was this feedback helpful? 'y' or 'n': ");
							fgets(tempRating, 100, stdin);
							if(strcmp(tempRating, "y\n") == 0) {
								if((tempRule->systemRating + (tempRule->systemRating * 0.05 / tempRule->totalCount)) <= 1) {
									tempRule->systemRating = tempRule->systemRating + (tempRule->systemRating * 0.05 / tempRule->totalCount);
									break;
								}
								else {
									printf("The system rating cannot go over 1.0\n");
									break;
								}
							}
							else if(strcmp(tempRating, "n\n") == 0) {
								if(tempRule->systemRating - (tempRule->systemRating * 0.05 / tempRule->totalCount) >= 0) {
									tempRule->systemRating = tempRule->systemRating - (tempRule->systemRating * 0.05 / tempRule->totalCount);
									break;
								}
								else {
									printf("The system rating cannot go below 0.0\n");
									break;
								}
							}
							else {
								printf("Enter 'y' or 'n'!\n");
							}
						}
					}
					else {
						printf("I do not have anything to say for your sentence!\n");
					}
				}
			}
			else if(strcmp(menuInput, "9\n") == 0) {
				menuLoop = false;
				printf("\nTree Delete Status:\n");
				destroyBinTree(binSearchTree);
			}
			else {
				printf("\nInvalid Input! Ex. '1' or '2' ... \n");
			} 	
		}

	}
	else {
		printf("The file could not be found.\n");
		return 1;
	}

    return 0;
}

