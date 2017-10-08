#ifndef _API_SOURCE_
#define _API_SOURCE_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedListAPI.h"

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
	return ((Node*)data);
}


void insertFront(List *list, void *toBeAdded) {
	//dummy
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
}

void *getFromBack(List *list) {
	//dummy
}


void printForward(List *list) {
	//dummy
}


void printBackwards(List *list) {
	//dummy
}


void deleteListNode(void *toBeDeleted) {
	//dummy
}


int compare(const void *first,const void *second) {
	return 0;
}


void printNode(void *toBePrinted) {
	//dummy
}


#endif