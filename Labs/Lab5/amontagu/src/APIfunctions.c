#ifndef _API_SOURCE_
#define _API_SOURCE_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "LinkedListAPI.h"

// Initializes a list
// Takes function pointers as parameters to put in list struct
// Returns a list pointer to initialize a list elsewhere
List *initializeList(void (*printFunction)(void *toBePrinted), void (*deleteFunction)(void *toBeDeleted), int (*compareFunction)(const void *first,const void *second)) {
	
	List* initList = NULL;

	initList = malloc(sizeof(List));
	initList->head = NULL;
	initList->tail = NULL;
	initList->deleteNode = deleteFunction;
	initList->compare = compareFunction;
	initList->printNode = printFunction;

	return initList;
}

// Initializes a node with data to be put into a list
// Takes a void pointer containing data to put in the node as a parameter
// Returns a node pointer to be put in a linked list
// Initializes all fields, and adds data or returns NULL if no data present
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

// Inserts the list at the front, or head of a list
// Takes a list and data for a node as a parameter
// Checks to see if it is the first node, or if to insert before the current head
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

// Insert a node into the back of a list, or at the tail
// Takes a list and data for a node as a parameter
// Checks to see if it is the first node, or if to insert behind the current tail
void insertBack(List *list, void *toBeAdded) {
	
	Node* tailNode = initializeNode(toBeAdded);		// Actual Node
	Node* tempNode = list->tail;

	if(list->head == NULL && list->tail == NULL) {
		list->head = tailNode;
		list->tail = tailNode;
		tailNode->next = NULL;
		tailNode->previous = NULL;
	}
	else {
		tempNode->next = tailNode;
		tailNode->previous = tempNode;
		list->tail = tailNode;
		tailNode->next = NULL;
	}
}

// Delete the list
// Takes a list as a parameter
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

// Inserts a node into the list by the order of their data
// Takes a list and data for a node as a parameter
// Iterates through the list to find the correct spot to insert the node
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

// Remove a node from the back of a list
// Takes a list in as a parameter
// Checks to see where the node is, then removes it.
void removeBack(List *l) {
	Node* tempNode = l->tail;

	if(tempNode->previous == NULL) {
		tempNode = NULL;
		l->tail = NULL;
		l->head = NULL;
		free(tempNode);
	}
	else {
		l->tail = tempNode->previous;
		l->tail->next = NULL;
		tempNode = NULL;
		free(tempNode);
	}
}

// Deletes a node from the list
// Takes in a list, and the data to be deleted as a parameter
// Returns an integer error code
// Checks to see where the deleted node is located, then does the appropriate node arranging
int deleteNodeFromList(List* list, void* toBeDeleted) {

	Node* findNode = list->head;
	Node* tempNode = NULL;
	Node* tempNode2 = NULL;
	Node* tempNode3 = NULL;

	while(findNode != NULL) {
		if(*(int*)findNode->data == *(int*)toBeDeleted) {
			tempNode = findNode;
			if(tempNode->previous == NULL) {
				list->head = tempNode->next;
				list->head->previous = NULL;
				tempNode = NULL;
				free(tempNode);
				return EXIT_SUCCESS;
			}
			else {
				tempNode2 = tempNode->previous;
				tempNode3 = tempNode3->next;
				tempNode2->next = tempNode3;
				tempNode3->previous = tempNode2;
				tempNode = NULL;
				free(tempNode);
				return EXIT_SUCCESS;
			}
		}
		findNode = findNode->next;
	}
	return 0;
}

// int deleteNodeFromList(List *list, void *toBeDeleted) {
// 	Node* deleteNode = initializeNode(toBeDeleted);
// 	Node* findDeleted = list->head;
// 	Node* tempNode = NULL;
// 	Node* tempNode2 = NULL;
// 	Node* tempNode3 = NULL;
// 	Car* deleteCar = deleteNode->data;
// 	Car* findDeleteCar = findDeleted->data;
// 	bool inDel = false;

// 	if(findDeleted == NULL) {
// 		return EXIT_FAILURE;
// 	}
// 	if(findDeleted->next == NULL && findDeleted->previous == NULL) {
// 		return 69;
// 	}
// 	while(findDeleted->next != NULL) {
// 		if(deleteCar->direction == findDeleteCar->direction && deleteCar->turnDirection == findDeleteCar->turnDirection && deleteCar->arrivalTime == findDeleteCar->arrivalTime) {
// 			if(findDeleted->previous == NULL) {		// If node is head case
// 				tempNode = findDeleted->next;
// 				list->head = tempNode;
// 				list->deleteNode(tempNode);
// 				inDel = true;
// 			}
// 			else {									// If node is in middle of list
// 				tempNode = findDeleted;
// 				tempNode2 = findDeleted->previous;
// 				tempNode3 = findDeleted->next;

// 				tempNode2->next = tempNode3;
// 				tempNode3->previous = tempNode2;
// 				list->deleteNode(tempNode);
// 				inDel = true;
// 			}
// 		}
// 		findDeleted = findDeleted->next;
// 		findDeleteCar = findDeleted->data;
// 	}
// 	if(findDeleted->next == NULL && (deleteCar->direction == findDeleteCar->direction && deleteCar->turnDirection == findDeleteCar->turnDirection && deleteCar->arrivalTime == findDeleteCar->arrivalTime)) {	// If node is tail case
// 		tempNode = findDeleted;
// 		tempNode2 = findDeleted->previous;
// 		tempNode2->next = NULL;
// 		list->tail = tempNode2;
// 		list->deleteNode(tempNode);
// 		inDel = true;
// 	}
// 	else if(inDel == false) {
// 		return -1;
// 	}
	
// 	return EXIT_SUCCESS;
// }

// Returns the data from the node at the head, or front of list
// Takes a list in as a parameter
// Returns a void pointer containing the node data
void *getFromFront(List *list) {

	return (list->head)->data;

}

// Returns the data from the node at the tail, or back of list
// Takes a list in as a parameter
// Returns a void pointer containing the node data
void *getFromBack(List *list) {
	
	return (list->tail)->data;
}

// Prints the list starting at the head to the tail
// Takes a list in as a parameter
// Iterates through each node and prints it
void printForward(List *list) {
	
	Node* printForward = list->head;
	
	while(printForward != NULL) {
		list->printNode(printForward->data);
		printForward = printForward->next;
	}
}

// Prints the list starting at the tail to the head
// Takes a list in as a parameter
// Iterates through each node and prints it
void printBackwards(List *list) {
	
	Node* printBackwards = list->tail;

	while(printBackwards != NULL) {
		list->printNode(printBackwards->data);
		printBackwards = printBackwards->previous;
	}
}


#endif