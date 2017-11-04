
// Alexander Montague
// 0959687
// amontagu@uoguelph.ca
// October 2017
// 2520 Assignment 2

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "LinkedListAPI.h"
#include "QueueAPI.h"
#include "patient.h"

int main (int argc, char **argv)
{

	// Variable Decleration
	FILE* filePointer = NULL;

	Patient* tempPatient = NULL;
	Patient* dataPatient = NULL;

	TimePatient** printPatient = NULL;
	
	Queue* sortedQueue = createQueue(&printNode, NULL, &compare);
	Queue* printQueue = createQueue(&printNode, NULL, &compare);

	int menuInt = 0;
	int tempPriority = -1;
	int globalTimer = 1;
	int numElems = 0;

	size_t elemCount = 0;

	bool menuLoop = true;
	bool endLoop = false;
	
	char menuChoice[100];
	char tempString[100];
	char* tempID = NULL;
	char* tempPriorityString = NULL;
	char* tempIllness = NULL;

	if(argc != 2) {
		printf("Usage: ./program <fileName>\n");
		return 1;
	}
	filePointer = fopen(argv[1], "r");

	if(filePointer != NULL) {
		while(fgets(tempString, 100, filePointer) != NULL) {

			tempID = malloc(sizeof(char) * 100);
			tempIllness = malloc(sizeof(char) * 100);
			sscanf(tempString, "%[^ ] %d %[^\n]", tempID, &tempPriority, tempIllness);
			tempPatient = malloc(sizeof(Patient));
			tempPatient->patientID = strdup(tempID);
			tempPatient->priority = tempPriority;
			tempPatient->illness = strdup(tempIllness);
			insertBack(printQueue->list, tempPatient);
			insertSorted(sortedQueue->list, tempPatient);
			numElems++;
		}
	}
	else {
		printf("The file could not be found.\n");
		return 1;
	}
	fclose(filePointer);

	do {
		if(endLoop == true) {
			break;
		}
		printf("\nWelcome to the Patient Priority Queue Program.\n");
		printf("Please Select a Number Option: \n");
		printf("1) Enter Patients\n");
		printf("2) Run the Simulation\n");
		printf("3) Exit the Program\n");
		printf("Number Selection: ");
		fgets(menuChoice, 100, stdin);
		if(strcmp("1\n", menuChoice) == 0 || strcmp("2\n", menuChoice) == 0 || strcmp("3\n", menuChoice) == 0) {
			menuInt = atoi(menuChoice);
		}
		else {
			strcpy(menuChoice, "-1");
			menuInt = atoi(menuChoice);
		}

		if(menuInt == 1) {
			printf("\n--- ADD PATIENT ---\n");
			printf("Patient ID: ");
			tempID = malloc(sizeof(char) * 100);
			fgets(tempID, 100, stdin);
			tempID[strlen(tempID) - 1] = '\0';
			printf("Priority: ");
			tempPriorityString = malloc(sizeof(char) * 100);
			fgets(tempPriorityString, 100, stdin);
			tempPriorityString[strlen(tempPriorityString) - 1] = '\0';
			tempPriority = atoi(tempPriorityString);
			printf("Patient Symptom: ");
			tempIllness = malloc(sizeof(char) * 100);
			fgets(tempIllness, 100, stdin);
			tempIllness[strlen(tempIllness) - 1] = '\0';
			while(strcmp(tempIllness, "CV") != 0 || strcmp(tempIllness, "HN") != 0 || strcmp(tempIllness, "EV") != 0 || strcmp(tempIllness, "GI") != 0 || strcmp(tempIllness, "MH") != 0 || strcmp(tempIllness, "NC") != 0 || strcmp(tempIllness, "EC") != 0 || strcmp(tempIllness, "RC") != 0 || strcmp(tempIllness, "SK") != 0 || strcmp(tempIllness, "SA") != 0 || strcmp(tempIllness, "TR") != 0) {
				printf("Invalid Symptom. Enter a new Symptom. (If valid just enter again)\n");
				printf("Patient Symptom: ");
				fgets(tempIllness, 100, stdin);
				tempIllness[strlen(tempIllness) - 1] = '\0';
				if(strcmp(tempIllness, "CV") == 0 || strcmp(tempIllness, "HN") == 0 || strcmp(tempIllness, "EV") == 0 || strcmp(tempIllness, "GI") == 0 || strcmp(tempIllness, "MH") == 0 || strcmp(tempIllness, "NC") == 0 || strcmp(tempIllness, "EC") == 0 || strcmp(tempIllness, "RC") == 0 || strcmp(tempIllness, "SK") == 0 || strcmp(tempIllness, "SA") == 0 || strcmp(tempIllness, "TR") == 0) {
					break;
				}
			}
			tempPatient = malloc(sizeof(Patient));
			tempPatient->patientID = strdup(tempID);
			tempPatient->priority = tempPriority;
			tempPatient->illness = strdup(tempIllness);
			insertBack(printQueue->list, tempPatient);
			insertSorted(sortedQueue->list, tempPatient);
			numElems++;
		}
		else if(menuInt == 2) {

			printPatient = malloc(sizeof(TimePatient*) * numElems);
			for(int i = 0; i < numElems; i++) {
				printPatient[i] = malloc(sizeof(TimePatient));
			}

			printf("Patient ID      Priority        Symptom Code    Time Finished\n");
			printf("-------------------------------------------------------------\n");
			do {
				if(sortedQueue->list->head == NULL && sortedQueue->list->tail == NULL) {
					printf("The Queue is Currently Empty.\n");
					endLoop = true;
					break;
				}
				if(sortedQueue->list->head != NULL) {
					dataPatient = (Patient*)peek(sortedQueue);
				}
				else {
					break;
				}

				if(strcmp("CV", dataPatient->illness) == 0) {
					globalTimer += 5;
					printPatient[elemCount]->finishTime = globalTimer;
					printPatient[elemCount]->ID = dataPatient->patientID;
					elemCount++;
					removeNode(sortedQueue, peek(sortedQueue));
				}
				else if(strcmp("HN", dataPatient->illness) == 0) {
					globalTimer += 3;
					printPatient[elemCount]->finishTime = globalTimer;
					printPatient[elemCount]->ID = dataPatient->patientID;
					elemCount++;
					removeNode(sortedQueue, peek(sortedQueue));
				}
				else if(strcmp("EV", dataPatient->illness) == 0) {
					globalTimer += 10;
					printPatient[elemCount]->finishTime = globalTimer;
					printPatient[elemCount]->ID = dataPatient->patientID;
					elemCount++;
					removeNode(sortedQueue, peek(sortedQueue));
				}
				else if(strcmp("GI", dataPatient->illness) == 0) {
					globalTimer += 2;
					printPatient[elemCount]->finishTime = globalTimer;
					printPatient[elemCount]->ID = dataPatient->patientID;
					elemCount++;
					removeNode(sortedQueue, peek(sortedQueue));
				}
				else if(strcmp("MH", dataPatient->illness) == 0) {
					globalTimer += 5;
					printPatient[elemCount]->finishTime = globalTimer;
					printPatient[elemCount]->ID = dataPatient->patientID;
					elemCount++;
					removeNode(sortedQueue, peek(sortedQueue));
				}
				else if(strcmp("NC", dataPatient->illness) == 0) {
					globalTimer += 5;
					printPatient[elemCount]->finishTime = globalTimer;
					printPatient[elemCount]->ID = dataPatient->patientID;
					elemCount++;
					removeNode(sortedQueue, peek(sortedQueue));
				}
				else if(strcmp("EC", dataPatient->illness) == 0) {
					globalTimer += 1;
					printPatient[elemCount]->finishTime = globalTimer;
					printPatient[elemCount]->ID = dataPatient->patientID;
					elemCount++;
					removeNode(sortedQueue, peek(sortedQueue));
				}
				else if(strcmp("RC", dataPatient->illness) == 0) {
					globalTimer += 1;
					printPatient[elemCount]->finishTime = globalTimer;
					printPatient[elemCount]->ID = dataPatient->patientID;
					elemCount++;
					removeNode(sortedQueue, peek(sortedQueue));
				}
				else if(strcmp("SK", dataPatient->illness) == 0) {
					globalTimer += 2;
					printPatient[elemCount]->finishTime = globalTimer;
					printPatient[elemCount]->ID = dataPatient->patientID;
					elemCount++;
					removeNode(sortedQueue, peek(sortedQueue));
				}
				else if(strcmp("SA", dataPatient->illness) == 0) {
					globalTimer += 7;
					printPatient[elemCount]->finishTime = globalTimer;
					printPatient[elemCount]->ID = dataPatient->patientID;
					elemCount++;
					removeNode(sortedQueue, peek(sortedQueue));
				}
				else if(strcmp("TR", dataPatient->illness) == 0) {
					globalTimer += 4;
					printPatient[elemCount]->finishTime = globalTimer;
					printPatient[elemCount]->ID = dataPatient->patientID;
					elemCount++;
					removeNode(sortedQueue, peek(sortedQueue));
				}
				else {
					printf("Unknown Symptom\n");
					removeNode(sortedQueue, peek(sortedQueue));
				}
				globalTimer++;
			}
			while(true);

			timePrint(printQueue, printPatient, numElems);
			printf("The Simulation has Concluded.\n");
			printf("Press <Enter>: ");
			fgets(menuChoice, 100, stdin);
			endLoop = true;

		}
		else if(menuInt == 3) {
			menuLoop = false;
		}
		else {
			printf("Invalid option, try again!\n");
		}
	}
	while(menuLoop == true);

    return 0;
}

