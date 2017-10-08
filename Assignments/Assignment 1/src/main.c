
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "car.h"
#include "LinkedListAPI.h"

int main (int argc, char **argv)
{

	// --- Variable Decleration Section --- 

	FILE* carInputFP = NULL;

	Car tempCarStruct;				// Holds car data temporarily to put into struct array
	Car* carArray = NULL; 		    // Hold all car structs in here

	Node* nodeArray = NULL;		  // Node array to hold all list nodes

	List* carListNorth = NULL;	  // Lists to hold car nodes for each direction
	List* carListEast = NULL;
	List* carListSouth = NULL;
	List* carListWest = NULL;

	char tempString[100];
	char fileDirectory[100];
	char *tempToken;

	char tempDirection = '-';
	char tempTurnDirection = '-';

	int tokenCount = 1;
	int tempArrivalTime = 0;
	int carCount = 0;				// Do -1 when putting into arrays


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

				tempCarStruct.direction = tempDirection;
				tempCarStruct.turnDirection = tempTurnDirection;
				tempCarStruct.arrivalTime = tempArrivalTime;

				carArray = realloc(carArray, sizeof(Car) * carCount);
				carArray[carCount - 1] = tempCarStruct;

				printf("Direction:%c  Turn Direction:%c  Duration:%d\n", carArray[carCount - 1].direction, carArray[carCount - 1].turnDirection, carArray[carCount - 1].arrivalTime);

			}
			fclose(carInputFP);

			// TEST
			// printf("\n\n TESTING\n");
			// printNode(&carArray[6]);
			// printf("Return = %d\n", compare(&carArray[0], &carArray[1]));

			carListNorth = initializeList(&printNode, &deleteListNode, &compare);
		}
	}

    return 0;

}
