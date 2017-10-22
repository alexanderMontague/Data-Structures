#include <stdio.h>
#include <stdlib.h>

#ifndef _STRUCT_HEADER_
#define _STRUCT_HEADER_

typedef struct stack {
	List* list;
} Stack;

// Creates the stack and initializes it
Stack* createStack (void (*printFunction)(void* toBePrinted), void (*deleteFunction)(void* toBeDeleted), int (*compareFunction)(const void *first, const void *second));

// Prints an element in the stack
void printEntry(void* printData);

// Supposed to delete an entry in a list
// Should have probably put deleteNodeFromList in here, but oh well
void deleteEntry(void* deleteData);

// Compares two nodes in a stack
// Takes two const void data pointers as parameters
// Returns an integer error code
int compareEntry(const void* data1, const void* data2);

// Adds a node to the top of a stack
// Takes a stack pointer, and void data pointer as parameters
// This makes use of insertBack and inserts the data into a node
void push(Stack* s, void* data);

// Removes the top node of a stack
// Takes a stack pointer as a parameter
void pop(Stack* s);

// Returns the data at the top of a stack
// Takes a stack pointer as parameter
// Returns a void pointer containing the data in the stack
void* top(Stack* s);

#endif