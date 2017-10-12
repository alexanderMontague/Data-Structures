
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
			bool listEmpty = false;
			bool northEmpty = false;
			bool eastEmpty = false;
			bool southEmpty = false;
			bool westEmpty = false;
			int lightDirection = 0; // North = 0, East = 1, South = 2, West = 3
			int simulationTimer = 1;
			int errorVal = 0;
			double lightTimer = 0;		// Real time for each direction (14s)
			double tempTimer = 0;		// Fake timer corresponds to lightTimer
			//double interArrivalTime = 0;
			
			//Node* currNode = NULL;
			//Node* tempNode = NULL;
			Car* currCar = NULL;


			while(northEmpty == false && eastEmpty == false && southEmpty == false && westEmpty == false) {
				if(carListNorth->head == NULL && carListEast->head == NULL && carListSouth->head == NULL && carListWest->head == NULL) {
					break;
				}

				if(lightDirection == 0) {									// NORTH

					listEmpty = false;
					lightTimer = simulationTimer;
					tempTimer = tempTimer + simulationTimer;
					errorVal = 0;
					if(carListNorth->head == NULL) {
							listEmpty = true;
							northEmpty = true;
					}
					else {
						currCar = getFromFront(carListNorth);
					}

					while(lightTimer <= simulationTimer + 10 && listEmpty == false) {
						if(currCar->arrivalTime == lightTimer) {
							if(currCar->turnDirection == 'R') {
								vehicleInfoPrint(currCar, firstPrintInfo, currCar->arrivalTime, 1);
								errorVal = deleteNodeFromList(carListNorth, currCar);
								tempTimer = tempTimer + 1;
								firstPrintInfo = false;
							}
							else if(currCar->turnDirection == 'F') {
								vehicleInfoPrint(currCar, firstPrintInfo, currCar->arrivalTime, 2);
								errorVal = deleteNodeFromList(carListNorth, currCar);
								tempTimer = tempTimer + 2;
								firstPrintInfo = false;
							}
							else if(currCar->turnDirection == 'L') {
								vehicleInfoPrint(currCar, firstPrintInfo, currCar->arrivalTime, 2.5);
								errorVal = deleteNodeFromList(carListNorth, currCar);
								tempTimer = tempTimer + 2.5;
								firstPrintInfo = false;
							}
						}
						
						if(errorVal == 69) {
							listEmpty = true;
							northEmpty = true;
						}
						else if(tempTimer <= simulationTimer + 10) {
							currCar = getFromFront(carListNorth);
						}
						else {
							//break;
						}

						lightTimer = lightTimer + 1;

					}
					if(lightTimer > simulationTimer + 10 && lightTimer <= simulationTimer + 14) {		// YELLOW
						
						if(currCar->turnDirection == 'L' && (2.5 + lightTimer <= (simulationTimer + 14))) {
							vehicleInfoPrint(currCar, firstPrintInfo, currCar->arrivalTime, 2.5);
							errorVal = deleteNodeFromList(carListNorth, currCar);
							tempTimer = tempTimer + 2.5;
							firstPrintInfo = false;
						}
						tempTimer = tempTimer + 2.5;
					}

					simulationTimer = simulationTimer + 14;
					lightDirection++;

				}
				if(lightDirection == 1) {		// EAST
					
					listEmpty = false;
					lightTimer = simulationTimer;
					tempTimer = tempTimer + simulationTimer;
					errorVal = 0;
					if(carListEast->head == NULL) {
							listEmpty = true;
							eastEmpty = true;
					}
					else {
						currCar = getFromFront(carListEast);
					}


					while(lightTimer <= simulationTimer + 10 && listEmpty == false) {
						if(currCar->arrivalTime == lightTimer) {
							if(currCar->turnDirection == 'R') {
								vehicleInfoPrint(currCar, firstPrintInfo, currCar->arrivalTime + tempTimer, 1);
								errorVal = deleteNodeFromList(carListEast, currCar);
								tempTimer = tempTimer + 1;
								firstPrintInfo = false;
							}
							else if(currCar->turnDirection == 'F') {
								vehicleInfoPrint(currCar, firstPrintInfo, currCar->arrivalTime + tempTimer, 2);
								errorVal = deleteNodeFromList(carListEast, currCar);
								tempTimer = tempTimer + 2;
								firstPrintInfo = false;
							}
							else if(currCar->turnDirection == 'L') {
								vehicleInfoPrint(currCar, firstPrintInfo, currCar->arrivalTime + tempTimer, 2.5);
								errorVal = deleteNodeFromList(carListEast, currCar);
								tempTimer = tempTimer + 2.5;
								firstPrintInfo = false;
							}
						}

						if(errorVal == 69) {
							listEmpty = true;
							eastEmpty = true;
						}
						else if(tempTimer <= simulationTimer + 10) {
							currCar = getFromFront(carListEast);
						}
						else {
							//break;
						}

						lightTimer = lightTimer + 1;

					}
					if(lightTimer > simulationTimer + 10 && lightTimer <= simulationTimer + 14) {		// YELLOW
						
						if(currCar->turnDirection == 'L' && (2.5 + lightTimer <= (simulationTimer + 14))) {
							vehicleInfoPrint(currCar, firstPrintInfo, currCar->arrivalTime + tempTimer, 2.5);
							errorVal = deleteNodeFromList(carListEast, currCar);
							tempTimer = tempTimer + 2.5;
							firstPrintInfo = false;
						}
						tempTimer = tempTimer + 2.5;
					}
					
					simulationTimer = simulationTimer + 14;
					lightDirection++;
				}
				if(lightDirection == 2) {		// SOUTH
					listEmpty = false;
					lightTimer = simulationTimer;
					tempTimer = tempTimer + simulationTimer;
					errorVal = 0;
					if(carListSouth->head == NULL) {
						listEmpty = true;
						southEmpty = true;
					}
					else {
						currCar = getFromFront(carListSouth);
					}

					while(lightTimer <= simulationTimer + 50 && listEmpty == false) {
						if(currCar->arrivalTime == lightTimer) {
							if(currCar->turnDirection == 'R') {
								vehicleInfoPrint(currCar, firstPrintInfo, currCar->arrivalTime + tempTimer, 1);
								errorVal = deleteNodeFromList(carListSouth, currCar);
								tempTimer = tempTimer + 1;
								firstPrintInfo = false;
							}
							else if(currCar->turnDirection == 'F') {
								vehicleInfoPrint(currCar, firstPrintInfo, currCar->arrivalTime + tempTimer, 2);
								errorVal = deleteNodeFromList(carListSouth, currCar);
								tempTimer = tempTimer + 2;
								firstPrintInfo = false;
							}
							else if(currCar->turnDirection == 'L') {
								vehicleInfoPrint(currCar, firstPrintInfo, currCar->arrivalTime + tempTimer, 2.5);
								errorVal = deleteNodeFromList(carListSouth, currCar);
								tempTimer = tempTimer + 2.5;
								firstPrintInfo = false;
							}
						}
						
						if(errorVal == 69) {
							listEmpty = true;
							southEmpty = true;
						}
						if(tempTimer <= simulationTimer + 10) {
							currCar = getFromFront(carListSouth);
						}
						else {
							//break;
						}

						lightTimer = lightTimer + 1;

					}
					if(lightTimer > simulationTimer + 10 && lightTimer <= simulationTimer + 14) {		// YELLOW
						
						if(currCar->turnDirection == 'L' && (2.5 + lightTimer <= (simulationTimer + 14))) {
							vehicleInfoPrint(currCar, firstPrintInfo, currCar->arrivalTime + tempTimer, 2.5);
							errorVal = deleteNodeFromList(carListSouth, currCar);
							tempTimer = tempTimer + 2.5;
							firstPrintInfo = false;
						}
						tempTimer = tempTimer + 2.5;
					}
					
					simulationTimer = simulationTimer + 14;
					lightDirection++;

				}
				if(lightDirection == 3) {		// WEST

					listEmpty = false;
					lightTimer = simulationTimer;
					tempTimer = tempTimer + simulationTimer;
					errorVal = 0;
					if(carListWest->head == NULL) {
							listEmpty = true;
							westEmpty = true;
					}
					else {
						currCar = getFromFront(carListWest);
					}
					while(lightTimer <= simulationTimer + 10 && listEmpty == false) {
						if(currCar->arrivalTime == lightTimer) {
							if(currCar->turnDirection == 'R') {
								vehicleInfoPrint(currCar, firstPrintInfo, currCar->arrivalTime + tempTimer, 1);
								errorVal = deleteNodeFromList(carListWest, currCar);
								tempTimer = tempTimer + 1;
								firstPrintInfo = false;
							}
							else if(currCar->turnDirection == 'F') {
								vehicleInfoPrint(currCar, firstPrintInfo, currCar->arrivalTime + tempTimer, 2);
								errorVal = deleteNodeFromList(carListWest, currCar);
								tempTimer = tempTimer + 2;
								firstPrintInfo = false;
							}
							else if(currCar->turnDirection == 'L') {
								vehicleInfoPrint(currCar, firstPrintInfo, currCar->arrivalTime + tempTimer, 2.5);
								errorVal = deleteNodeFromList(carListWest, currCar);
								tempTimer = tempTimer + 2.5;
								firstPrintInfo = false;
							}
						}
						
						if(errorVal == 69) {
							listEmpty = true;
							westEmpty = true;
						}
						else if(tempTimer <= simulationTimer + 10) {
							currCar = getFromFront(carListWest);
						}
						else {
							//break;
						}

						lightTimer = lightTimer + 1;

					}
					if(lightTimer > simulationTimer + 10 && lightTimer <= simulationTimer + 14) {		// YELLOW
						
						if(currCar->turnDirection == 'L' && (2.5 + lightTimer <= (simulationTimer + 14))) {
							vehicleInfoPrint(currCar, firstPrintInfo, currCar->arrivalTime + tempTimer, 2.5);
							errorVal = deleteNodeFromList(carListWest, currCar);
							tempTimer = tempTimer + 2.5;
							firstPrintInfo = false;
						}
						tempTimer = tempTimer + 2.5;
					}
					
					simulationTimer = simulationTimer + 14;
					lightDirection++;

				}

				if(lightDirection == 3) {
					lightDirection = 0;
				}
			
			} // WHILE END;



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
				printf("%c %c %d                         %.2f                        %.2f\n", printCar->direction, printCar->turnDirection, printCar->arrivalTime, arrivalTime, arrivalTime + addOn);
			}
			else {
				printf("%c %c %d                          %.2f                        %.2f\n", printCar->direction, printCar->turnDirection, printCar->arrivalTime, arrivalTime, arrivalTime + addOn);
			}
		}
		else {

			if(arrivalTime >= 10) {
				printf("%c %c %d                         %.2f                       %.2f\n", printCar->direction, printCar->turnDirection, printCar->arrivalTime, arrivalTime, arrivalTime + addOn);
			}
			else {
				printf("%c %c %d                          %.2f                        %.2f\n", printCar->direction, printCar->turnDirection, printCar->arrivalTime, arrivalTime, arrivalTime + addOn);
			}
		}
	}
}
