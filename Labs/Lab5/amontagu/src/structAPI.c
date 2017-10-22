#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "struct.h"
#include "LinkedListAPI.h"
#include "structAPI.h"

#ifndef _STACK_SOURCE_
#define _STACK_SOURCE_

Stack* createStack (void (*printFunction)(void* toBePrinted), void (*deleteFunction)(void* toBeDeleted), int (*compareFunction)(const void *first, const void *second)) {

	Stack* newStack = malloc(sizeof(Stack));
	List* newList = initializeList(&printEntry, &deleteEntry, &compareEntry);	// Initializes stack with a list
	newStack->list = newList;

	return newStack;
}

void printEntry(void* printData) {

	printf(" %d ", *(int*)printData);	// Prints the integers

}

void deleteEntry(void* deleteData) {

	// Irrelevant in my way - I don't get why you need this

}

int compareEntry(const void* data1, const void* data2) { // num , previous


	if(*(int*)data1 < *(int*)data2) {
		return -1;
	}
	else if (*(int*)data1 == *(int*)data2) {
		return 0;
	}
	else if (*(int*)data1 > *(int*)data2) {
		return 1;
	}

	return 0;

}

void push(Stack* s, void* data) {	// add node to back
	
	insertBack(s->list, data);

}

void pop(Stack* s) {                // Why would you need to return anything to remove the top element from a stack?!?!
	removeBack(s->list);			
}

void* top(Stack* s) {
	return getFromBack(s->list);
}

int count(Stack* s) {
	return 0;
}

#endif