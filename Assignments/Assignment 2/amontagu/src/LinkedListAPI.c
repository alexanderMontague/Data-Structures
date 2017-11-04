#ifndef _API_SOURCE_
#define _API_SOURCE_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "LinkedListAPI.h"
#include "QueueAPI.h"
#include "patient.h"

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
	Patient* tempPatient = (Patient*)data;
	initNode->previous = NULL;
	initNode->next = NULL;
	initNode->data = data;
	initNode->priority = tempPatient->priority;

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
		list->head->previous = headNode;
		list->head = headNode;
		headNode->previous = NULL;
	}
}

// Insert a node into the back of a list, or at the tail
// Takes a list and data for a node as a parameter
// Checks to see if it is the first node, or if to insert behind the current tail
void insertBack(List *list, void *toBeAdded) {
	
	qNode* newQN = initializeQueueNode(toBeAdded);
	Node* tailNode = newQN->Node;		// Actual Node
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
	
	Node* tempNode = NULL;

	if(list->head == NULL) {
		free(list);
	}
	else {
		while(list->head != NULL) {
			tempNode = list->head->next;
			free(list->head);
			list->head = NULL;
			list->head = tempNode;
		}
		free(list);
		list = NULL;
	}
}

// Inserts a node into the list by the order of their data
// Takes a list and data for a node as a parameter
// Iterates through the list to find the correct spot to insert the node
void insertSorted(List *list, void *toBeAdded) {
	
	qNode* newQN = initializeQueueNode(toBeAdded);
	Node* toAddNode = newQN->Node;	// Regular Node is initialzed in initializeQN with data
	Node* compareNode = NULL;
	Node* beforeNode = NULL;
	int returnVal = 0;
	bool inList = false;

	if(list->head == NULL) {
		insertFront(list, toAddNode->data);
	}
	else {
		compareNode = list->head;
		while(inList == false) {
			returnVal = list->compare(&toAddNode->priority, &compareNode->priority);
			if(returnVal == -1) {
				if(compareNode->previous == NULL) {
					insertFront(list, toAddNode->data);
					inList = true;
				}
				else {
					beforeNode = compareNode->previous;
					toAddNode->previous = beforeNode;
					compareNode->previous = toAddNode;
					beforeNode->next = toAddNode;
					toAddNode->next = compareNode;
					inList = true;
				}
			}
			else if(returnVal == 1 || returnVal == 0) {
				if(compareNode->next == NULL) {
					insertBack(list, toAddNode->data);
					inList = true;
				}
				else {
					compareNode = compareNode->next;
				}
			}
		}
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
		if(findNode->data == toBeDeleted) {
			tempNode = findNode;
			if(tempNode->previous == NULL && tempNode->next == NULL) {
				list->head = NULL;
				deleteList(list);
			}
			else if(tempNode->previous == NULL) {
				list->head = tempNode->next;
				list->head->previous = NULL;
				free(tempNode);
				tempNode = NULL;
				return EXIT_SUCCESS;
			}
			else {
				tempNode2 = tempNode->previous;
				tempNode3 = tempNode3->next;
				tempNode2->next = tempNode3;
				tempNode3->previous = tempNode2;
				free(tempNode);
				tempNode = NULL;
				return EXIT_SUCCESS;
			}
		}
		findNode = findNode->next;
	}
	return 0;
}

void removeFront(List* list) {
	
	Node* tempNode = NULL;

	if(list->head->next == NULL) {
		free(list->head);
		list->head = NULL;
		deleteList(list);
	}
	else {
		list->head->next = tempNode;
		list->head = tempNode;
		list->head->previous = NULL;
		free(tempNode);
		tempNode = NULL;
	}
}

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