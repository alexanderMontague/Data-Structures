
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

	List* carListNorth = NULL;	    // Lists to hold car nodes for each direction
	List* carListEast = NULL;
	List* carListSouth = NULL;
	List* carListWest = NULL;

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

	carListNorth = initializeList(&printNode, &deleteListNode, &compare);
	carListEast = initializeList(&printNode, &deleteListNode, &compare);
	carListSouth = initializeList(&printNode, &deleteListNode, &compare);
	carListWest = initializeList(&printNode, &deleteListNode, &compare);
	
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

				if(tempCar->direction == 'N') {
					insertSorted(carListNorth, tempCar);
				}
				else if(tempCar->direction == 'E') {
					insertSorted(carListEast, tempCar);
				}
				else if(tempCar->direction == 'S') {
					insertSorted(carListSouth, tempCar);
				}
				else if(tempCar->direction == 'W') {
					insertSorted(carListWest, tempCar);
				}
			}
			fclose(carInputFP);

			// delete test
			// Car* delCar = malloc(sizeof(Car));
			// delCar->direction = 'E';
			// delCar->turnDirection = 'R';
			// delCar->arrivalTime = 20;
			//errorVal = deleteNodeFromList(carListNorth, delCar);
			
			if(errorVal == EXIT_FAILURE) {
				printf("Delete Node Failure - List is empty\n");
			}
			else if(errorVal == -1) {
				printf("Delete Node Failure - Node could not be found\n");
			}

			// printForward(carListNorth);
			// printf("---\n");
			// printForward(carListEast);
			// printf("---\n");
			// printForward(carListSouth);
			// printf("---\n");
			// printForward(carListWest);


			bool firstPrintInfo = true;
			double simulationTimer = 1.0;
			double lightTimer = 0;
			double interArrivalTime = 0;
			int lightDirection = 0; // North = 0, East = 1, South = 2, West = 3
			Node* currNode = NULL;
			Node* tempNode = NULL;
			Car* currCar = NULL;


			while(1) {

				if(carListNorth->head == NULL && carListEast->head == NULL && carListSouth->head == NULL && carListWest->head == NULL) {
					printf("All lists are empty. Exiting.\n");
					break;
				}

				if(lightDirection == 0) {			// NORTH
					currNode = carListNorth->head;
					tempNode = carListNorth->head;
					
					currCar = currNode->data;
					
					lightTimer = 1;

					while(lightTimer <= 14) {

						if(currCar->arrivalTime == lightTimer) {
							if(currCar->turnDirection == 'F' && lightTimer + 2 <= 14) {
								interArrivalTime = lightTimer;
								lightTimer = lightTimer + 2;
								simulationTimer = simulationTimer + 2;
								vehicleInfoPrint(currCar, firstPrintInfo, interArrivalTime, 2);
								deleteNodeFromList(carListNorth, currCar);
								if(currNode->next != NULL) {
									currNode = currNode->next;
									currCar = currNode->data;
								}
								firstPrintInfo = false;
							}
							else if(currCar->turnDirection == 'L' && lightTimer + 2.5 <= 14) {
								interArrivalTime = lightTimer;
								lightTimer = lightTimer + 2.5;
								simulationTimer = simulationTimer + 2.5;
								vehicleInfoPrint(currCar, firstPrintInfo, interArrivalTime, 2.5);
								deleteNodeFromList(carListNorth, currCar);
								if(currNode->next != NULL) {
									currNode = currNode->next;
									currCar = currNode->data;
								}
								firstPrintInfo = false;
							}
							else if(currCar->turnDirection == 'R' && lightTimer + 1 <= 14) {
								interArrivalTime = lightTimer;
								lightTimer = lightTimer + 1;
								simulationTimer = simulationTimer + 1;
								vehicleInfoPrint(currCar, firstPrintInfo, interArrivalTime, 1);
								deleteNodeFromList(carListNorth, currCar);
								if(currNode->next != NULL) {
									currNode = currNode->next;
									currCar = currNode->data;
								}
								firstPrintInfo = false;
							}
						}
						lightTimer = lightTimer + 0.5;

					}
					lightDirection++;
				}
				else if(lightDirection == 1) {		// EAST
				
				}
				else if(lightDirection == 2) {		// SOUTH
				
				}
				else if(lightDirection == 3) {		// WEST

				}

				if(lightDirection == 3) {
					lightDirection = 0;
				}
				//simulationTimer++;
			}



		// 	//DONT FORGET TO FREE
		}
	}

    return 0;
}

void vehicleInfoPrint(Car* printCar, bool firstPrint, double arrivalTime, double addOn) {
	
	if(printCar == NULL) {
		printf("Invalid Data Passed. Exiting.\n");
	}
	else {
		if(firstPrint == true) {
			printf("Initial Vehicle Information    Intersection Arrival Time    Completed at Time\n");
			
			if(arrivalTime >= 10) {
				printf("%c %c %d                         %.2f                         %.2f\n", printCar->direction, printCar->turnDirection, printCar->arrivalTime, arrivalTime, arrivalTime + addOn);
			}
			else {
				printf("%c %c %d                          %.2f                         %.2f\n", printCar->direction, printCar->turnDirection, printCar->arrivalTime, arrivalTime, arrivalTime + addOn);
			}
		}
		else {

			if(arrivalTime >= 10) {
				printf("%c %c %d                        %.2f                          %.2f\n", printCar->direction, printCar->turnDirection, printCar->arrivalTime, arrivalTime, arrivalTime + addOn);
			}
			else {
				printf("%c %c %d                         %.2f                          %.2f\n", printCar->direction, printCar->turnDirection, printCar->arrivalTime, arrivalTime, arrivalTime + addOn);
			}
		}
	}
}
