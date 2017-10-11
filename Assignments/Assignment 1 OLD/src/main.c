
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
	Car* currCar = NULL;

	Node** nodeArray = NULL;		// Node array to hold all list nodes
	Node* currNode = NULL;
	Node* tempNode = NULL;

	List* carListNorth = NULL;	    // Lists to hold car nodes for each direction
	List* carListEast = NULL;
	List* carListSouth = NULL;
	List* carListWest = NULL;
	List* currList = NULL;

	char tempString[100];
	char fileDirectory[100];
	char *tempToken;

	char tempDirection = '-';
	char tempTurnDirection = '-';

	int tokenCount = 1;
	int tempArrivalTime = 0;
	int carCount = 0;				// Do -1 when putting into arrays
	int errorVal = 0;
	double simulationTimer = 1.0;
	double lightTimer = 0;
	int lightDirection = 0; // North = 0, East = 1, South = 2, West = 3

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

				carArray = realloc(carArray, sizeof(Car) * carCount);		// Allocating memory for struct array and putting information in
				carArray[carCount - 1] = tempCarStruct;

			}

			fclose(carInputFP);

			carListNorth = initializeList(&printNode, &deleteListNode, &compare);
			carListEast = initializeList(&printNode, &deleteListNode, &compare);
			carListSouth = initializeList(&printNode, &deleteListNode, &compare);
			carListWest = initializeList(&printNode, &deleteListNode, &compare);

			nodeArray = malloc(sizeof(Node) * carCount);

			for(int i = 0; i < carCount; i++) {
				nodeArray[i] = initializeNode(&carArray[i]);
				if(carArray[i].direction == 'N') {
					insertBack(carListNorth, &nodeArray[i]->data);
				}
				else if(carArray[i].direction == 'E') {
					insertBack(carListEast, &nodeArray[i]->data);
				}
				else if(carArray[i].direction == 'S') {
					insertBack(carListSouth, &nodeArray[i]->data);
				}
				else if(carArray[i].direction == 'W') {
					insertBack(carListWest, &nodeArray[i]->data);
				}
			}

			// printForward(carListNorth);
			// printf("---\n");
			// printForward(carListEast);
			// printf("---\n");
			// printForward(carListSouth);
			// printf("---\n");
			// printForward(carListWest);

			//insertFront(carListNorth, &nodeArray[0]->data);

			//printNode(&nodeArray[7]->data);			// How to send nodes to functions
			// insertFront(carListNorth, &nodeArray[0]->data);
			

			//errorVal = deleteNodeFromList(carListNorth, &nodeArray[10]->data);
			if(errorVal == EXIT_FAILURE) {
				printf("Delete Node Failure - List is empty\n");
			}
			else if(errorVal == -1) {
				printf("Delete Node Failure - Node could not be found\n");
			}

			// Car* carPointer = (Car*)getFromFront(carListNorth);
			// printf("\nHEAD CAR: %c %c %d\n", carPointer->direction, carPointer->turnDirection, carPointer->arrivalTime);

			// carPointer = (Car*)getFromBack(carListNorth);
			// printf("\nTAIL CAR: %c %c %d\n", carPointer->direction, carPointer->turnDirection, carPointer->arrivalTime);

			// printForward(carListNorth);

			currCar = (Car*)&nodeArray[0]->data;
			printf("\nTEST: %c %c %d\n", currCar->direction, currCar->turnDirection, currCar->arrivalTime);

			while(1) {

				if(carListNorth->head == NULL && carListEast->head == NULL && carListSouth->head == NULL && carListWest->head == NULL) {
					break;
				}

				if(lightDirection == 0) {			// NORTH
					currList = carListNorth;
					currNode = currList->head;
					tempNode = currList->head;
					currCar = currNode->data;
					lightTimer = 1;

					printForward(currList);

					while(lightTimer <= 14) {

						if(currCar->arrivalTime == lightTimer && lightTimer <= 11.5) {
							if(currCar->turnDirection == 'F') {
								lightTimer = lightTimer + 2;
								simulationTimer = simulationTimer + 2;
								printNode((void*)currCar);
								deleteNodeFromList(currList, currCar);
								currNode = currNode->next;
								currCar = currNode->data;
							}
							else if(currCar->turnDirection == 'L') {
								lightTimer = lightTimer + 2.5;
								simulationTimer = simulationTimer + 2.5;
								printNode((void*)currCar);
								deleteNodeFromList(currList, currCar);
							}
							else if(currCar->turnDirection == 'R') {
								lightTimer = lightTimer + 1;
								simulationTimer = simulationTimer + 1;
								printNode((void*)currCar);
								deleteNodeFromList(currList, currCar);
							}
						}
						lightTimer = lightTimer + 0.1;
					}
					lightDirection++;
				}
				else if(lightDirection == 1) {		// EAST
					currList = carListEast;
				}
				else if(lightDirection == 2) {		// SOUTH
					currList = carListSouth;
				}
				else if(lightDirection == 3) {		// WEST
					currList = carListWest;
				}

				if(lightDirection == 3) {
					lightDirection = 0;
				}
				//simulationTimer++;
			}



			//DONT FORGET TO FREE
		}
	}

    return 0;

}
