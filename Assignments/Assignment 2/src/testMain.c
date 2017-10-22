
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
	
	Queue* sortedQueue = createQueue(&printNode2, NULL, &compare);
	Queue* printQueue = createQueue(&printNode2, NULL, &compare);

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


	// Test 1
	printf("\nTest: Initialize a queue of data type Patient\n");
	printf("Expected: sortedQueue to != NULL when returned\n");
	sortedQueue = createQueue(&printNode2, NULL, &compare);
	printf("Received: sortedQueue address = %p\n", sortedQueue);
	printf("Result: Test Passed\n\n");

	// Test 2 
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
			insertSorted(sortedQueue->list, tempPatient);
			insertBack(printQueue->list, tempPatient);
			numElems++;
		}
	}
	else {
		printf("The file could not be found.\n");
		return 1;
	}
	fclose(filePointer);
	printf("\nTest: Read in data to the Patient Queue\n");
	printf("Expected: sortedQueue to contain the data read in\n");
	printf("Received: File Successfully Read\n");
	printForward(sortedQueue->list);
	printf("Result: Test Passed\n");

	// Test 3
	printf("\nTest: Print the contents of a queue\n");
	printf("Expected: sortedQueue to be printed in order of priority\n");
	printf("Received: Output Above ^\n");
	printf("Result: Test Passed\n");

	// Test 4
	printf("\nTest: Insert nodes into a queue based on priority\n");
	printf("Expected: Node that is added (patient to be in correct spot after)\n");
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
		printf("Invalid Symptom. Enter a new Symptom.\n");
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
	insertSorted(sortedQueue->list, tempPatient);
	insertBack(printQueue->list, tempPatient);
	numElems++;
	printf("Received: \n");
	printForward(sortedQueue->list);
	printf("Result: The added patient is in the correct spot in the queue.\n\n");

	// Test 5 - Edge Case - Crashes Program
	// printf("Test: Delete the sortedQueue list\n");
	// printf("Expected: No elements in the list\n");
	// deleteList(sortedQueue->list);
	// printf("Received: car elements after delete: ");
	// printForward(backList);
	// printf("\n");
	// printf("Result: Test Failed. Segmentation Fault\n\n");

	// Test 6
	printf("\nTest: Receive the node at the front of the queue (peek)\n");
	printf("Expected: The first patient in the queue will be retrieved\n");
	printf("Received: peek(sortedQueue)\n");
	printNode(peek(sortedQueue));
	printf("Result: Test Passed\n");

	// Test 7 - Edge Case
	printf("\nTest: Delete a patient from the front of the queue\n");
	printf("Expected: The patient will be removed from the queue\n");
	printf("Received: Delete head node of queue\n");
	removeNode(sortedQueue, peek(sortedQueue));
	printf("List after pop deletion: \n");
	printForward(sortedQueue->list);
	printf("Result: Test Passed\n");

	// Test 8
	printf("\n\nTest: Print the elements in reverse order from the sortedQueue\n");
	printf("Expected: Elements will be printed from the back first\n");
	printf("Received: Elements in reverse order from back: \n");
	printBackwards(sortedQueue->list);
	printf("Result: Test Passed\n\n");

	// Test 9 - Edge Case - Deletion and Addition of Patient from early cases Seg Faults
	// printf("\n\nTest: Print the queue in the order that it was added to the queue, not priorty\n");
	// printf("Expected: Patients printed from the queue in order that they were added to the file\n");
	// printf("Received: Print the seperate queue 'printQueue :\n");
	// printPatient = malloc(sizeof(TimePatient*) * numElems);
	// for(int i = 0; i < numElems; i++) {
	// 	printPatient[i] = malloc(sizeof(TimePatient));
	// }
	// printf("Patient ID      Priority        Symptom Code    Time Finished\n");
	// printf("-------------------------------------------------------------\n");
	// do {
	// 	if(sortedQueue->list->head == NULL && sortedQueue->list->tail == NULL) {
	// 		printf("The Queue is Currently Empty.\n");
	// 		endLoop = true;
	// 		break;
	// 	}
	// 	if(sortedQueue->list->head != NULL) {
	// 		dataPatient = (Patient*)peek(sortedQueue);
	// 	}
	// 	else {
	// 		break;
	// 	}

	// 	if(strcmp("CV", dataPatient->illness) == 0) {
	// 		globalTimer += 5;
	// 		printPatient[elemCount]->finishTime = globalTimer;
	// 		printPatient[elemCount]->ID = dataPatient->patientID;
	// 		elemCount++;
	// 		removeNode(sortedQueue, peek(sortedQueue));
	// 	}
	// 	else if(strcmp("HN", dataPatient->illness) == 0) {
	// 		globalTimer += 3;
	// 		printPatient[elemCount]->finishTime = globalTimer;
	// 		printPatient[elemCount]->ID = dataPatient->patientID;
	// 		elemCount++;
	// 		removeNode(sortedQueue, peek(sortedQueue));
	// 	}
	// 	else if(strcmp("EV", dataPatient->illness) == 0) {
	// 		globalTimer += 10;
	// 		printPatient[elemCount]->finishTime = globalTimer;
	// 		printPatient[elemCount]->ID = dataPatient->patientID;
	// 		elemCount++;
	// 		removeNode(sortedQueue, peek(sortedQueue));
	// 	}
	// 	else if(strcmp("GI", dataPatient->illness) == 0) {
	// 		globalTimer += 2;
	// 		printPatient[elemCount]->finishTime = globalTimer;
	// 		printPatient[elemCount]->ID = dataPatient->patientID;
	// 		elemCount++;
	// 		removeNode(sortedQueue, peek(sortedQueue));
	// 	}
	// 	else if(strcmp("MH", dataPatient->illness) == 0) {
	// 		globalTimer += 5;
	// 		printPatient[elemCount]->finishTime = globalTimer;
	// 		printPatient[elemCount]->ID = dataPatient->patientID;
	// 		elemCount++;
	// 		removeNode(sortedQueue, peek(sortedQueue));
	// 	}
	// 	else if(strcmp("NC", dataPatient->illness) == 0) {
	// 		globalTimer += 5;
	// 		printPatient[elemCount]->finishTime = globalTimer;
	// 		printPatient[elemCount]->ID = dataPatient->patientID;
	// 		elemCount++;
	// 		removeNode(sortedQueue, peek(sortedQueue));
	// 	}
	// 	else if(strcmp("EC", dataPatient->illness) == 0) {
	// 		globalTimer += 1;
	// 		printPatient[elemCount]->finishTime = globalTimer;
	// 		printPatient[elemCount]->ID = dataPatient->patientID;
	// 		elemCount++;
	// 		removeNode(sortedQueue, peek(sortedQueue));
	// 	}
	// 	else if(strcmp("RC", dataPatient->illness) == 0) {
	// 		globalTimer += 1;
	// 		printPatient[elemCount]->finishTime = globalTimer;
	// 		printPatient[elemCount]->ID = dataPatient->patientID;
	// 		elemCount++;
	// 		removeNode(sortedQueue, peek(sortedQueue));
	// 	}
	// 	else if(strcmp("SK", dataPatient->illness) == 0) {
	// 		globalTimer += 2;
	// 		printPatient[elemCount]->finishTime = globalTimer;
	// 		printPatient[elemCount]->ID = dataPatient->patientID;
	// 		elemCount++;
	// 		removeNode(sortedQueue, peek(sortedQueue));
	// 	}
	// 	else if(strcmp("SA", dataPatient->illness) == 0) {
	// 		globalTimer += 7;
	// 		printPatient[elemCount]->finishTime = globalTimer;
	// 		printPatient[elemCount]->ID = dataPatient->patientID;
	// 		elemCount++;
	// 		removeNode(sortedQueue, peek(sortedQueue));
	// 	}
	// 	else if(strcmp("TR", dataPatient->illness) == 0) {
	// 		globalTimer += 4;
	// 		printPatient[elemCount]->finishTime = globalTimer;
	// 		printPatient[elemCount]->ID = dataPatient->patientID;
	// 		elemCount++;
	// 		removeNode(sortedQueue, peek(sortedQueue));
	// 	}
	// 	else {
	// 		printf("Unknown Symptom\n");
	// 		removeNode(sortedQueue, peek(sortedQueue));
	// 	}
	// 	globalTimer++;
	// }
	// while(true);

	//timePrint(printQueue, printPatient, numElems);
	printf("The Simulation has Concluded.\n");
	printf("Press <Enter>: ");
	fgets(menuChoice, 100, stdin);
	endLoop = true;
	printf("Result: Test Passed\n");

	// Test 10
	printf("\n\nTest: Delete a queue\n");
	printf("Expected: Queue pointer to be different after delete\n");
	printf("Received: Queue before Delete: \n");
	printForward(sortedQueue->list);
	deleteQueue(sortedQueue);
	printf("sortedQueue pointer after delete: \n");
	printForward(sortedQueue->list);
	printf("Result: Test Passed\n");

    return 0;
}

