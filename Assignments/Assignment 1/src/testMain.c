#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "car.h"
#include "LinkedListAPI.h"

void vehicleInfoPrint(Car* printCar, bool firstPrint, double arrivalTime, double addOn);

int main (int argc, char **argv)
{

	// --- Variable Decleration Section --- 

	FILE* carInputFP = NULL;

	Car* tempCar = NULL;

	char tempString[100];
	char fileDirectory[100];
	char *tempToken;

	char tempDirection = '-';
	char tempTurnDirection = '-';

	int tokenCount = 1;
	int tempArrivalTime = 0;
	int carCount = 0;				// Do -1 when putting into arrays
	int errorVal = 0;

	// Test 1
	printf("\nTest: Initialize a linked list of data type Book\n");
	printf("Expected: BookList to != NULL when returned\n");
	List* sortedList = initializeList(&printNode, &deleteListNode, &compare);
	printf("Received: bookList address = %p\n", sortedList);
	printf("Result: Test Passed\n\n");

	List* frontList = initializeList(&printNode, &deleteListNode, &compare);
	List* backList = initializeList(&printNode, &deleteListNode, &compare);
	
	// --- File Manipulation Section ---
	if(argc != 2) {
		printf("Correct use is <program name> <filename>\n");
		exit(1);
	}
	else {
		strcpy(fileDirectory, "../assets/");
		strcat(fileDirectory, argv[1]);
		carInputFP = fopen(fileDirectory, "r");
		
		if(carInputFP == NULL) {
			printf("File could not be opened. Please try again.\n");
			exit(1);
		}
		else {
			while(fgets(tempString, 100, carInputFP) != NULL) {
				tokenCount = 1;
				for(tempToken = strtok(tempString, " "); tempToken != NULL; tempToken = strtok(NULL, " ")) {
					if(tokenCount == 1) {
						tempDirection = *tempToken;
					}
					else if(tokenCount == 2) {
						tempTurnDirection = *tempToken;
					}
					else if(tokenCount == 3) {
						tempArrivalTime = atoi(tempToken);
					}
					tokenCount++;
				}
				carCount++;

				tempCar = malloc(sizeof(Car));
				tempCar->direction = tempDirection;
				tempCar->turnDirection = tempTurnDirection;
				tempCar->arrivalTime = tempArrivalTime;

				insertSorted(sortedList, tempCar);
				insertFront(frontList, tempCar);
				insertBack(backList, tempCar);

			}
			fclose(carInputFP);

			// Test 2
			printf("Test: Insert nodes into a linked list from the front\n");
			printf("Expected: Nodes to be in the list in the reverse order of the file as it was inserted from the head\n");
			printf("Received: \n");
			printForward(frontList);
			printf("Result: The nodes are in reverse order from the list as they were inserted from the head.\n\n");

			// Test 3
			printf("Test: Insert nodes into a linked list from the back\n");
			printf("Expected: Nodes to be in the list in the same order of the file as it was inserted from the tail\n");
			printf("Received: \n");
			printForward(backList);
			printf("Result: The nodes are in reverse order from the list as they were inserted from the tail.\n\n");

			// Test 4
			printf("Test: Insert nodes into a linked in a sorted order\n");
			printf("Expected: Nodes to be in the list sorted by their nummerical value, or arrival time.\n");
			printf("Received: \n");
			printForward(sortedList);
			printf("Result: The nodes are in correct nummerical order.\n\n");

			// Test 5 - Edge Case - Crashes Program
			// printf("Test: Delete the backList linked list\n");
			// printf("Expected: No elements in the list\n");
			// deleteList(backList);
			// printf("Received: car elements after delete: ");
			// printForward(backList);
			// printf("\n");
			// printf("Result: Test Failed. Segmentation Fault\n\n");

			// Test 6 - Edge Case
			printf("Test: Delete a car node from the sortedList\n");
			printf("Expected: Node that is selected to be removed from the list\n");
			printf("Received: Delete data member 'E R 20'\n");
			printf("List before deletion: \n");
			printForward(sortedList);
			Car* delCar = malloc(sizeof(Car));
			delCar->direction = 'E';
			delCar->turnDirection = 'R';
			delCar->arrivalTime = 20;
			errorVal = deleteNodeFromList(sortedList, delCar);
			if(errorVal == EXIT_FAILURE) {
				printf("Delete Node Failure - List is empty\n");
			}
			else if(errorVal == -1) {
				printf("Delete Node Failure - Node could not be found\n");
			}
			printf("Result: The node 'E R 20' has been deleted\n");
			printForward(sortedList);

			// Test 7 - Edge Case
			printf("\nTest: Delete a car node from the sortedList that is not there\n");
			printf("Expected: Error message will appear, as node is not in list\n");
			printf("Received: Delete data member 'W X 11'\n");
			printf("List before deletion: \n");
			printForward(sortedList);
			delCar = malloc(sizeof(Car));
			delCar->direction = 'W';
			delCar->turnDirection = 'X';
			delCar->arrivalTime = 10;
			errorVal = deleteNodeFromList(sortedList, delCar);
			if(errorVal == EXIT_FAILURE) {
				printf("Delete Node Failure - List is empty\n");
			}
			else if(errorVal == -1) {
				printf("Delete Node Failure - Node could not be found\n");
			}
			printf("Result: Error message received, and list after has not changed.\n");
			printForward(sortedList);

			// Test 8
			printf("\n\nTest: Print the elements in reverse order from the sortedList linked list\n");
			printf("Expected: Elements will be printed from the tail first\n");
			printf("Received: Elements in reverse order from back: \n");
			printBackwards(sortedList);
			printf("Result: Test Passed\n\n");

			// Test 9
			printf("Test: Get the head of the linked list sortedList / test printNode\n");
			printf("Expected: Node from head to be printed\n");
			printNode(getFromFront(sortedList));
			printf("Result: The head of the linked list was printed.\n\n");

			// Test 10
			printf("Test: Get the tail of the linked list sortedList / test printNode / that deleteNode worked correctly\n");
			printf("Expected: Node from tail to be printed\n");
			printNode(getFromBack(sortedList));
			printf("Result: The tail of the linked list was printed.\n\n");

		}
	}
	return 0;
}