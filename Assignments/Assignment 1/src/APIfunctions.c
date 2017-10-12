#ifndef _API_SOURCE_
#define _API_SOURCE_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "LinkedListAPI.h"
#include "car.h"

List *initializeList(void (*printFunction)(void *toBePrinted),void (*deleteFunction)(void *toBeDeleted),int (*compareFunction)(const void *first,const void *second)) {
	
	List* initList = NULL;

	initList = malloc(sizeof(List));
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

	return initNode;
}


void insertFront(List *list, void *toBeAdded) {
		
	Node* headNode = initializeNode(toBeAdded);
	
	if(list->head == NULL) {
		list->head = headNode;
		list->tail = headNode;
		headNode->next = NULL;
		headNode->previous = NULL;
	}
	else {
		headNode->next = list->head;
		list->head = headNode;
		headNode->previous = NULL;
	}
}


void insertBack(List *list, void *toBeAdded) {
	
	Node* tailNode = initializeNode(toBeAdded);		// Actual Node
	Node* tempNode = list->head;

	if(list->head == NULL) {
		list->head = tailNode;
		list->tail = tailNode;
		tailNode->next = NULL;
	}
	else {
		while(tempNode->next != NULL) {
			tempNode = tempNode->next;
		}
		tempNode->next = tailNode;
		tailNode->previous = tempNode;
		list->tail = tailNode;
	}
}


void deleteList(List *list) {
	
	Node* deleteNode = list->head;
	Node* tempNode = NULL;
	Node* tempNode2 = NULL;

	list->head = NULL;
	free(list->head);

	while(deleteNode != list->tail || tempNode2 != NULL) {
		tempNode = deleteNode->next;
		deleteNode = NULL;
		free(deleteNode);

		deleteNode = tempNode->next;
		tempNode2 = tempNode;
		tempNode = NULL;
		free(tempNode);
	}
	if(deleteNode == list->tail) {
		deleteNode = NULL;
		tempNode = NULL;
		free(deleteNode);
		free(tempNode);
	}

	tempNode2 = NULL;
	list->tail = NULL;
	list = NULL;
	free(tempNode2);
	free(list->tail);
	free(list);

}


void insertSorted(List *list, void *toBeAdded) {
	
	Node* toAddNode = initializeNode(toBeAdded);
	Node* compareNode = NULL;
	Node* beforeNode = NULL;
	int returnVal = 0;
	bool inList = false;

	if(list->head == NULL) {
		insertFront(list, toAddNode->data);
	}
	else {
		compareNode = list->head;
		do {
			returnVal = list->compare(toAddNode->data, compareNode->data);
			if(returnVal == -1 || returnVal == 0) {
				beforeNode = compareNode->previous;
				beforeNode->next = toAddNode;
				toAddNode->previous = beforeNode;
				toAddNode->next = compareNode;
				compareNode->previous = toAddNode;
				inList = true;
			}
			else if(returnVal == 1) {
				if(compareNode->next == NULL) {
					insertBack(list, toAddNode->data);
					inList = true;
				}
				else {
					compareNode = compareNode->next;
				}
			}
		}
		while(inList == false);
	}
}


int deleteNodeFromList(List *list, void *toBeDeleted) {
	Node* deleteNode = initializeNode(toBeDeleted);
	Node* findDeleted = list->head;
	Node* tempNode = NULL;
	Node* tempNode2 = NULL;
	Node* tempNode3 = NULL;
	Car* deleteCar = deleteNode->data;
	Car* findDeleteCar = findDeleted->data;
	bool inDel = false;

	if(findDeleted == NULL) {
		return EXIT_FAILURE;
	}
	if(findDeleted->next == NULL && findDeleted->previous == NULL) {
		return 69;
	}
	while(findDeleted->next != NULL) {
		if(deleteCar->direction == findDeleteCar->direction && deleteCar->turnDirection == findDeleteCar->turnDirection && deleteCar->arrivalTime == findDeleteCar->arrivalTime) {
			if(findDeleted->previous == NULL) {		// If node is head case
				tempNode = findDeleted->next;
				list->head = tempNode;
				list->deleteNode(tempNode);
				inDel = true;
			}
			else {									// If node is in middle of list
				tempNode = findDeleted;
				tempNode2 = findDeleted->previous;
				tempNode3 = findDeleted->next;

				tempNode2->next = tempNode3;
				tempNode3->previous = tempNode2;
				list->deleteNode(tempNode);
				inDel = true;
			}
		}
		findDeleted = findDeleted->next;
		findDeleteCar = findDeleted->data;
	}
	if(findDeleted->next == NULL && (deleteCar->direction == findDeleteCar->direction && deleteCar->turnDirection == findDeleteCar->turnDirection && deleteCar->arrivalTime == findDeleteCar->arrivalTime)) {	// If node is tail case
		tempNode = findDeleted;
		tempNode2 = findDeleted->previous;
		tempNode2->next = NULL;
		list->tail = tempNode2;
		list->deleteNode(tempNode);
		inDel = true;
	}
	else if(inDel == false) {
		return -1;
	}
	
	return EXIT_SUCCESS;
}


void *getFromFront(List *list) {

	return (list->head)->data;

}

void *getFromBack(List *list) {
	
	return (list->tail)->data;
}


void printForward(List *list) {
	
	Node* printForward = list->head;
		
	while(printForward != list->tail) {
		list->printNode(printForward->data);
		printForward = printForward->next;
	}
	list->printNode(list->tail->data);

}


void printBackwards(List *list) {
	
	Node* printBackwards = list->head;
	Car* printCar = NULL;

	while(printBackwards->next != NULL) {
		printBackwards = printBackwards->next;	// printBackwards is now Tail
	}

	while(printBackwards != NULL) {
		printCar = printBackwards->data;
		printNode((void*)printCar);
		printBackwards = printBackwards->previous;
	}
}


#endif