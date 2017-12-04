
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

char* allocatedPointer(char* oldString);

int main (int argc, char **argv)
{

	// Variable Decleration
	FILE* filePointer = NULL;

	Tree* binSearchTree = NULL;

	Rule* tempRule = NULL;
	Rule* editRule = NULL;

	Rule staticRule;

	char tempWord[100] = "NULL";
	char tempAdd[100] = "NULL";
	char userInput[100] = "NULL";

	char* tempString = NULL;
	char* split = NULL;

	int line = 0;
	int i = 0;
	int x = 0;

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
				for(int i = 0; i < strlen(tempWord); i++) tempWord[i] = tolower(tempWord[i]);
				//tempString = strdup(tempWord);
				tempString = allocatedPointer(tempWord);
				tempRule->keyWord = tempString;
				tempRule->userRating = 0.5;
				tempRule->systemRating = 0.5;
				tempRule->totalCount = 0;
				line++;
			}
			else if(line == 2) {
				tempWord[strlen(tempWord) - 1] = '\0';
				//tempString = strdup(tempWord);
				tempString = allocatedPointer(tempWord);
				tempRule->keySentence = tempString;
				addToTree(binSearchTree, tempRule);
				line = line - 2;
			}
		}
		fclose(filePointer);	


		// TEST 1
		printf("\nTEST: Print the tree using in order traversal\n");
		printf("Expected: Keywords in the tree to be printed in alphabetical order\n");
		printf("Received: ");
		printInOrder(binSearchTree, &printF);

		// TEST 2
		printf("\nTEST: Print the tree using pre order traversal\n");
		printf("Expected: Keywords in the tree to be printed in pre order(ROOT LEFT RIGHT)\n");
		printf("Received: ");
		printPreOrder(binSearchTree, &printF);

		// TEST 3
		printf("\nTEST: Print the tree using post order traversal\n");
		printf("Expected: Keywords in the tree to be printed in post order(LEFT RIGHT ROOT)\n");
		printf("Received: ");
		printPostOrder(binSearchTree, &printF);

		// TEST 4
		printf("\nTEST: Print the Tree's height\n");
		printf("Expected: The largest string of nodes in the tree will be printed\n");
		printf("Received: %d\n", getHeight(binSearchTree->root));

		// TEST 5 - EDGE CASE
		Rule tempRule2;
		printf("\nTEST: Remove a ROOT node\n");
		printf("Expected: The original root 'happy' will be deleted\n");
		printf("Received: delete 'happy'\n");
		tempRule2.keyWord = malloc(500);
		strcpy(tempRule2.keyWord, "happy");
		removeFromTree(binSearchTree, &tempRule2);
		printf("Result: \n");
		printInOrder(binSearchTree, &printF);

		// TEST 6
		printf("\nTEST: Remove a leaf node\n");
		printf("Expected: The leaf node 'sports' will be deleted\n");
		tempRule2.keyWord = malloc(500);
		strcpy(tempRule2.keyWord, "sports");
		TreeNode* tempNode = inTree(binSearchTree, binSearchTree->root, &tempRule2);
		printf("Received: isLeaf? = %d\n", isLeaf(tempNode));
		removeFromTree(binSearchTree, &tempRule2);
		printf("Result: \n");
		printInOrder(binSearchTree, &printF);

		// TEST 7
		printf("\nTEST: Remove a node with one child\n");
		printf("Expected: The leaf node 'candy' will be deleted\n");
		tempRule2.keyWord = malloc(500);
		strcpy(tempRule2.keyWord, "candy");
		printf("Received: delete 'candy'\n");
		removeFromTree(binSearchTree, &tempRule2);
		printf("Result: \n");
		printInOrder(binSearchTree, &printF);

		// TEST 8
		printf("\nTEST: Add a Rule to the tree\n");
		printf("Expected: Rule Keyword: ");
		fgets(tempAdd, 100, stdin);
		tempAdd[strlen(tempAdd) - 1] = '\0';
		//tempRule2.keyWord = strdup(tempAdd);
		tempRule2.keyWord = allocatedPointer(tempAdd);

		printf("Enter the Rule Sentence: ");
		fgets(tempAdd, 100, stdin);
		tempAdd[strlen(tempAdd) - 1] = '\0';
		tempRule2.keySentence = allocatedPointer(tempAdd);

		printf("Enter the Rule Rating: ");
		fgets(tempAdd, 100, stdin);
		tempAdd[strlen(tempAdd) - 1] = '\0';
		while(atof(tempAdd) < 0 || atof(tempAdd) > 1) {
			printf("The rating must be between 0 and 1.0!\n");
			printf("Enter the Rule Rating: ");
			fgets(tempAdd, 100, stdin);
			tempAdd[strlen(tempAdd) - 1] = '\0';
		}
		tempRule2.userRating = atof(tempAdd);
		tempRule2.systemRating = atof(tempAdd);
		addToTree(binSearchTree, &tempRule2);
		printf("Result: \n");
		printInOrder(binSearchTree, &printF);

		// TEST 9
		printf("\nTEST: Change the rating of a rule\n");
		printf("Expected: change the rating for any rule\n");
		printf("\nEnter the Rule KeyWord: ");
		fgets(tempAdd, 100, stdin);
		for(int i = 0; i < strlen(tempAdd); i++) tempAdd[i] = tolower(tempAdd[i]);	// convert to lowercase for case insensitivity
		tempAdd[strlen(tempAdd) - 1] = '\0';
		//tempRule2.keyWord = strdup(tempAdd);	
		tempRule2.keyWord = allocatedPointer(tempAdd);
		editRule = findInTree(binSearchTree, &tempRule2);
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

		//TEST 10
		printf("\nTEST: Discuss with the personal asssistant\n");
		printf("Expected: The user will as a question\n");
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
		if(userInput[strlen(userInput) - 2] == '?' || userInput[strlen(userInput) - 2] == '!' || userInput[strlen(userInput) - 2] == '.') {
			
		}
		if(strcmp(userInput, "") == 0) {
			printf("You must enter a sentence!\n");
		}
		else {
			for(int i = 0; i < strlen(userInput); i++) userInput[i] = tolower(userInput[i]);	// convert to lowercase for case insensitivity
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
			printf("My response is: %s\n", priorityRule.keySentence);
			tempRule = findInTree(binSearchTree, &priorityRule);
			tempRule->totalCount++;
			while(1) {
				printf("Was this feedback helpful? 'y' or 'n': ");
				fgets(tempString, 100, stdin);
				if(strcmp(tempString, "y\n") == 0) {
					if((tempRule->systemRating + (tempRule->systemRating * 0.05 / tempRule->totalCount)) <= 1) {
						tempRule->systemRating = tempRule->systemRating + (tempRule->systemRating * 0.05 / tempRule->totalCount);
						break;
					}
					else {
						printf("The system rating cannot go over 1.0\n");
						break;
					}
				}
				else if(strcmp(tempString, "n\n") == 0) {
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

		// TEST 11
		printf("TEST: Delete the whole tree\n");
		printf("Expected: All nodes to be deleted\n");
		printf("Result: \n");
		destroyBinTree(binSearchTree);

	}
	else {
		printf("The file could not be found.\n");
		return 1;
	}

    return 0;
}

char* allocatedPointer(char* oldString) {
	char* newPointer = NULL;
	newPointer = malloc((strlen(oldString) + 1) * sizeof(char));
	strncpy(newPointer, oldString, strlen(oldString) + 1);
	return newPointer;
}
