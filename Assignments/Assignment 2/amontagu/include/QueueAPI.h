#include <stdio.h>
#include <stdlib.h>
#include "patient.h"

#ifndef _QUEUE_HEADER_
#define _QUEUE_HEADER_

typedef struct queue {
	
	List* list;

} Queue;

typedef struct queueNode {

	Node* Node;
	int priority;

} qNode;

// Creates the stack and initializes it
Queue* createQueue(void (*printFunction)(void* toBePrinted), void (*deleteFunction)(void* toBeDeleted), int (*compareFunction)(const void *first, const void *second));

// Initializes a Queue Node
// Takes a void data pointer as a parameter
// Returns a qNode pointer fully initialized with data
qNode* initializeQueueNode(void* data);

// Deletes a queue
void deleteQueue(Queue* q);

// Inserts a node to the Queue in the correct order based on priority
// Takes a queue and data pointer as a parameter
void insert(Queue* q, void* data);

// Returns the data at the top of a stack
// Takes a stack pointer as parameter
// Returns a void pointer containing the data in the stack
void* peek(Queue* q);

// Removes the node from the queue based on the data passed in
void removeNode(Queue* q, void* data);

// Prints the queue in the order in which it was input
void timePrint(Queue* q, TimePatient** printStruct, size_t numElems);

void printNode2(void *data);

#endif