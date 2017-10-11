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

	return initNode;
}


void insertFront(List *list, void *toBeAdded) {
	
	Node* headNode = (Node*)toBeAdded;

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
	
	Node* tailNode = (Node*)toBeAdded;		// Actual Node
	Node* tempNode = list->head;			// Dummy Node to find position of head

	if(list->head == NULL) {
		tailNode->next = NULL;
		list->head = tailNode;
		list->tail = tailNode;
	}
	else {
		while(tempNode->next != NULL) {
			tempNode = tempNode->next;
		}
		tempNode->next = tailNode;
		tailNode->previous = tempNode;
	}
}


void deleteList(List *list) {
	
	Node* deleteNode = list->head;
	Node* tempNode = NULL;

	list->head = NULL;
	free(list->head);

	while(deleteNode->next != NULL) {
		tempNode = deleteNode->next;
		deleteNode->next = NULL;
		free(deleteNode->next);
		deleteNode = tempNode->next;
	}
	if(deleteNode->next == NULL) {
		deleteNode = NULL;
		tempNode = NULL;
		free(deleteNode);
		free(tempNode);
	}

	list = NULL;
	free(list);

}


void insertSorted(List *list, void *toBeAdded) {
	
	Node* toAddNode = (Node*)toBeAdded;
	Node* compareNode = NULL;
	Node* beforeNode = NULL;
	//Node* tempNode = NULL;
	int returnVal = 0;

	if(list->head == NULL) {
		insertFront(list, toAddNode->data);
		printf("in insert front\n");
	}
	else {
		do {
			returnVal = list->compare(toAddNode, compareNode);
			printf("return val = %d\n", returnVal);
			if(returnVal == -1 || returnVal == 0) {
				beforeNode = compareNode->previous;
				beforeNode->next = toAddNode;
				toAddNode->previous = beforeNode;
				toAddNode->next = compareNode;
				compareNode->previous = toAddNode;
			}
			else {
				printf("in insert back\n");
				insertBack(list, toAddNode->data);
			}

			compareNode = compareNode->next;

		} 
		while(compareNode->next != NULL || returnVal == -1 || returnVal == 0);
		printf("out of loop\n");
	}
}


int deleteNodeFromList(List *list, void *toBeDeleted) {
	
	Node* deleteNode = (Node*)toBeDeleted;
	Node* findDeleted = list->head;
	Node* tempNode = NULL;
	Node* tempNode2 = NULL;
	Node* tempNode3 = NULL;
	Car* deleteCar = deleteNode->data;
	Car* findDeleteCar = findDeleted->data;

	if(findDeleted == NULL) {
		return EXIT_FAILURE;
	}
	else if(deleteNode == NULL) {
		return -1;
	}
	while(findDeleted->next != NULL) {
		if(deleteCar->direction == findDeleteCar->direction && deleteCar->turnDirection == findDeleteCar->turnDirection && deleteCar->arrivalTime == findDeleteCar->arrivalTime) {
			if(findDeleted->previous == NULL) {		// If node is head case
				tempNode = findDeleted->next;
				list->head = tempNode;
				list->deleteNode(tempNode);
			}
			else {									// If node is in middle of list
				tempNode = findDeleted;
				tempNode2 = findDeleted->previous;
				tempNode3 = findDeleted->next;

				tempNode2->next = tempNode3;
				tempNode3->previous = tempNode2;
				list->deleteNode(tempNode);
			}
		}
		findDeleted = findDeleted->next;
		findDeleteCar = findDeleted->data;
	}
	if(findDeleted->next == NULL && (deleteCar->direction == findDeleteCar->direction && deleteCar->turnDirection == findDeleteCar->turnDirection && deleteCar->arrivalTime == findDeleteCar->arrivalTime)) {	// If node is tail case
		tempNode = findDeleted;
		tempNode2 = findDeleted->previous;
		tempNode2->next = NULL;
		list->deleteNode(tempNode);
	}
	
	printf("\n");
	return EXIT_SUCCESS;
}


void *getFromFront(List *list) {
	
	Node* headNode = list->head;
	Car* firstCar = headNode->data;

	return (void*)firstCar;

}

void *getFromBack(List *list) {
	
	Node* tailNode = list->head;;
	Car* lastCar = NULL;

	while(tailNode->next != NULL) {
		tailNode = tailNode->next;
	}
	lastCar = tailNode->data;
	
	return (void*)lastCar;
}


void printForward(List *list) {
	
	Node* printForward = list->head;
	Car* printCar = NULL;
	
	while(printForward != NULL) {
		printCar = (Car*)printForward->data;
		printNode((void*)printCar);
		printForward = printForward->next;
	}

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