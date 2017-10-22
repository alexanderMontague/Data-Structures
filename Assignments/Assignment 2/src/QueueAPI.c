#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedListAPI.h"
#include "QueueAPI.h"
#include "patient.h"

#ifndef _QUEUE_SOURCE_
#define _QUEUE_SOURCE_

// Creates the stack and initializes it
Queue* createQueue (void (*printFunction)(void* toBePrinted), void (*deleteFunction)(void* toBeDeleted), int (*compareFunction)(const void *first, const void *second)) {

	Queue* newQueue = malloc(sizeof(Queue));
	List* newList = initializeList(printFunction, NULL, compareFunction);	// Initializes stack with a list
	newQueue->list = newList;

	return newQueue;
}

qNode* initializeQueueNode(void* data) {
	
	qNode* newQN = malloc(sizeof(qNode));		//QN = Queue Node
	newQN->Node = initializeNode(data);
	Patient* addPatient = malloc(sizeof(Patient));
	addPatient = (Patient*)data;
	newQN->priority = addPatient->priority;	

	return newQN;

}

// Deletes a queue
void deleteQueue(Queue* q) {
	
	deleteList(q->list);
	q = NULL;
	free(q);

}

// Inserts a node to the Queue in the correct order based on priority
// Takes a queue and data pointer as a parameter
void insert(Queue* q, void* data) {

	insertSorted(q->list, data);

}

// Returns the data at the top of a stack
// Takes a stack pointer as parameter
// Returns a void pointer containing the data in the stack
void* peek(Queue* q) {

	return getFromFront(q->list);
}

// Removes the node from the queue based on the data passed in
void removeNode(Queue* q, void* data) {

	deleteNodeFromList(q->list, data);

}

void timePrint(Queue* q, TimePatient** printStruct, size_t numElems) {

	Node* printNode = q->list->head;
	
	while(printNode != NULL) {
		Patient* printPatient = (Patient*)printNode->data;
		q->list->printNode(printNode->data);
		for(int i = 0; i < numElems; i++) {
			if(strcmp(printPatient->patientID, printStruct[i]->ID) == 0) {
				printf("\t\t    %d\n", printStruct[i]->finishTime);
			}
		}
		printNode = printNode->next;
	}

}

void printNode2(void *data) {

	Patient* printPatient = (Patient*)data;

	printf("%s\t\t    %d\t\t    %s\n", printPatient->patientID, printPatient->priority, printPatient->illness);

}

#endif