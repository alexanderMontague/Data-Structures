#ifndef _API_SOURCE_
#define _API_SOURCE_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedListAPI.h"
#include "car.h"

List *initializeList(void (*printFunction)(void *toBePrinted),void (*deleteFunction)(void *toBeDeleted),int (*compareFunction)(const void *first,const void *second)) {
	
	List* initList = NULL;

	initList = malloc(sizeof(List) * 50);
	initList->head = NULL;
	initList->tail = NULL;
	initList->deleteNode = deleteFunction;
	initList->compare = compareFunction;
	initList->printNode = printFunction;

	return initList;
}


Node *initializeNode(void *data) {
	
	Node* initNode = malloc(sizeof(Node));
	initNode->previous = NULL;
	initNode->next = NULL;
	initNode->data = data;

	if(data == NULL) {
		return NULL;
	}

	return (Node*)data;
}


void insertFront(List *list, void *toBeAdded) {
	
	Node* headNode = (Node*)toBeAdded;

	Car* testCar = headNode->data;
	printf("%c %c %d\n", testCar->direction, testCar->turnDirection, testCar->arrivalTime);

	if(list->head == NULL) {
		list->head = headNode;
		list->tail = headNode;
		headNode->next = NULL;
		headNode->previous = NULL;
	}
	else {
		list->tail = list->head;
		headNode->next = list->head;
		list->head = headNode;
		headNode->previous = NULL;
	}
}


void insertBack(List *list, void *toBeAdded) {
	//dummy
}


void deleteList(List *list) {
	// dummy
}


void insertSorted(List *list, void *toBeAdded) {
	//dummy
}


int deleteNodeFromList(List *list, void *toBeDeleted) {
	return 0;
}


void *getFromFront(List *list) {
	//dummy
	return list;
}

void *getFromBack(List *list) {
	//dummy
	return list;
}


void printForward(List *list) {
	
	Node* printForward = list->head;
	Car* printCar = printForward->data;
	
	//while(printForward != NULL) {
		//printNode((void*)printForward->data);
		//printf("%c %c %d\n", printCar->direction, printCar->turnDirection, printCar->arrivalTime);
		printForward = printForward->next;
		printf("test\n");
	//}

}


void printBackwards(List *list) {
	//dummy
}


#endif