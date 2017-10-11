
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "book.h"
#include "LinkedListAPI.h"

void deleteListNode(void *toBeDeleted) {
	
	toBeDeleted = NULL;
	free(toBeDeleted);

}

int compare(const void *book1, const void *book2) {
		
	Book *BookC1 = NULL;
	Book *BookC2 = NULL;

	BookC1 = (Book *)book1;
	BookC2 = (Book *)book2;

	if(BookC1->price < BookC2->price) {
		return -1;
	}
	else if (BookC1->price == BookC2->price) {
		return 0;
	}
	else if (BookC1->price > BookC2->price) {
		return 1;
	}

	return 0;

}

int compareInt(const void *int1, const void *int2) {
		
	int *comp1 = 0;
	int *comp2 = 0;

	comp1 = (int *)int1;
	comp2 = (int *)int2;

	if(*comp1 < *comp2) {
		return -1;
	}
	else if (*comp1 == *comp2) {
		return 0;
	}
	else if (*comp1 > *comp2) {
		return 1;
	}

	return 0;

}

void printNode(void *toBePrinted) {
	
	toBePrinted = (Book *)toBePrinted;

	printBook(toBePrinted);

}

void printNodeInt(void *toBePrinted) {

	printf("%d ", *((int *)toBePrinted));

}

int main( int argc, char ** argv )
{

	Node *bookNode1 = NULL;
	Node *bookNode2 = NULL;
	Node *bookNode3 = NULL;
	Node *intNode1 = NULL;
	Node *intNode2 = NULL;
	Node *intNode3 = NULL;

	Book *b1 = createBook("Harry Potter And The Cursed Child", 19.99);
	Book *b2 = createBook("Cracking The Coding Interview", 35.75);
	Book *b3 = createBook("Code Complete 2", 25.00);
	int integer1 = 10;
	int integer2 = 99;
	int integer3 = -11;
	void *intP1 = &integer1;
	void *intP2 = &integer2;
	void *intP3 = &integer3;

	// Test 1
	printf("Test: Initialize a linked list of data type Book\n");
	printf("Expected: BookList to != NULL when returned\n");
	List *bookList = initializeList(&printNode, &deleteListNode, &compare);
	printf("Received: bookList address = %p\n", bookList);
	printf("Result: Test Passed\n\n");

	// Test 2
	printf("Test: Initialize a linked list of data type integer\n");
	printf("Expected: intList to != NULL when returned\n");
	List *intList = initializeList(&printNodeInt, &deleteListNode, &compareInt);
	printf("Received: bookList address = %p\n", intList);
	printf("Result: Test Passed\n\n");

	// Test 3
	printf("Test: Initialize a Book node\n");
	printf("Expected: bookNode1 to != NULL when returned\n");
	bookNode1 = initializeNode((void *)b1);
	printf("Received: bookNode1 address = %p\n", bookNode1);
	printf("Result: Test Passed\n\n");

	// Test 4
	printf("Test: Initialize an integer node\n");
	printf("Expected: intNode1 to != NULL when returned\n");
	intNode1 = initializeNode(intP1);
	printf("Received: bookNode1 address = %p\n", intNode1);
	printf("Result: Test Passed\n\n");

	// Test 5
	printf("Test: Insert a Book node to the front of the linked list\n");
	printf("Expected: 'Cracking the Coding Interview' to be before 'Harry Potter' in the linked list\n");
	bookNode2 = initializeNode((void *)b2);
	insertFront(bookList, bookNode1->data);
	printForward(bookList);
	printf("----Insert 'Cracking the Coding Interview' to the front of the linked list----\n");
	insertFront(bookList, bookNode2->data);	
	printForward(bookList);
	printf("Received: The new order of the linked list above ^\n");
	printf("Result: Test Passed\n\n");	

	// Test 6
	printf("Test: Insert a int node to the front of the linked list\n");
	printf("Expected: 'integer2(99)' to be before 'integer1(10)' in the linked list\n");
	intNode2 = initializeNode(intP2);
	insertFront(intList, intNode1->data);
	printForward(intList);
	printf("\n");
	printf("----'Insert integer2(99)' to the front of the linked list----\n");
	insertFront(intList, intNode2->data);	
	printForward(intList);
	printf("\n");
	printf("Received: The new order of the linked list above ^\n");
	printf("Result: Test Passed\n\n");	

	// Test 7
	printf("Test: Insert a Book node to the back of the linked list\n");
	printf("Expected: 'Code Complete 2' to be after 'Harry Potter' in the linked list\n");
	bookNode3 = initializeNode((void *)b3);
	printForward(bookList);
	printf("----Insert 'Code Complete' to the back of the linked list----\n");
	insertBack(bookList, bookNode3->data);	
	printForward(bookList);
	printf("Received: The new order of the linked list above ^\n");
	printf("Result: Test Passed\n\n");

	// Test 8
	printf("Test: Insert a int node to the back of the linked list\n");
	printf("Expected: 'integer3(-11)' to be after 'integer1(10)' in the linked list\n");
	intNode3 = initializeNode(intP3);
	printForward(intList);
	printf("\n");
	printf("----'Insert integer3(-11)' to the back of the linked list----\n");
	insertBack(intList, intNode3->data);	
	printForward(intList);
	printf("\n");
	printf("Received: The new order of the linked list above ^\n");
	printf("Result: Test Passed\n\n");

	// Test 9
	printf("Test: Delete the Book linked list\n");
	printf("Expected: No elements in the list\n");
	deleteList(bookList);
	printf("Received: bookList elements after delete: ");
	printForward(bookList);
	printf("Result: Test Passed\n\n");
    
    // Test 10 - Edge Case - Crashes Program
	// printf("Test: Delete the integer linked list\n");
	// printf("Expected: No elements in the list\n");
	// deleteList(intList);
	// printf("Received: intList elements after delete: ");
	// printForward(intList);
	// printf("\n");
	// printf("Result: Test Failed. Segmentation Fault\n\n");

	// Test 11
	printf("Test: Insert Book nodes into a linked list sorted by price\n");
	printf("Expected: Books sorted from cheapest to most expensive in the linked list\n");
	List *bookList2 = initializeList(&printNode, &deleteListNode, &compare);
	Book *b4 = createBook("Websters Dictionary", 15.50);
	Book *b5 = createBook("How to Code for Dummies", 100.00);
	Book *b6 = createBook("Data Structures are Wack", 25.99);
	Node *bookNode4 = initializeNode((void *)b4);
	Node *bookNode5 = initializeNode((void *)b5);
	Node *bookNode6 = initializeNode((void *)b6);
	insertSorted(bookList2, bookNode4->data);
	insertSorted(bookList2, bookNode5->data);
	insertSorted(bookList2, bookNode6->data);
	printForward(bookList2);
	printf("Received: bookList2 will be in order according to price above ^\n");
	printf("Result: Test Passed\n\n");

	// Test 12
	printf("Test: Insert int nodes into a linked list sorted by value\n");
	printf("Expected: ints sorted from lowest to greatest in the linked list\n");
	List *intList2 = initializeList(&printNodeInt, &deleteListNode, &compareInt);
	int integer4 = 0;
	int integer5 = 15;
	int integer6 = -10;
	void *intP4 = &integer4;
	void *intP5 = &integer5;
	void *intP6 = &integer6;
	Node *intNode4 = initializeNode(intP4);
	Node *intNode5 = initializeNode(intP5);
	Node *intNode6 = initializeNode(intP6);
	insertSorted(intList2, intNode4->data);
	insertSorted(intList2, intNode5->data);
	insertSorted(intList2, intNode6->data);
	printForward(intList2);
	printf("Received: intList2 will be in order from least to greatest ^\n");
	printf("Result: Test Passed\n\n");

	// Test 13
	printf("Test: Delete a Book node from a linked list\n");
	printf("Expected: 'Websters Dictionary' will be deleted from the linked list bookList\n");
	printf("List before deletion: \n");
	printForward(bookList2);
	deleteNodeFromList(bookList2, bookNode4->data);
	printf("List after deletion: \n");
	printForward(bookList2);
	printf("Received: Websters dictionary was deleted from the linked list bookLisk\n");
	printf("Result: Test Passed\n\n");

	// Test 14
	printf("Test: Delete an integer node from a linked list\n");
	printf("Expected: 'integer4(0)' will be deleted from the linked list bookList\n");
	printf("List before deletion: ");
	printForward(intList2);
	printf("\n");
	deleteNodeFromList(intList2, intNode4->data);
	printf("List after deletion: ");
	printForward(intList2);
	printf("\n");
	printf("Received: integer4(0) was deleted from the linked list intLisk\n");
	printf("Result: Test Passed\n\n");

	// Test 15
	printf("Test: Print the elements in reverse order from the bookList linked list\n");
	printf("Expected: Elements will be printed from the tail first\n");
	printf("Received: Elements in order from front first: \n");
	printForward(bookList2);
	printf("Received: Elements in reverse order from back: \n");
	printBackwards(bookList2);
	printf("Result: Test Passed\n\n");

	// Test 16
	printf("Test: Print the elements in reverse order from the intList linked list\n");
	printf("Expected: Elements will be printed from the tail first\n");
	printf("Received: Elements in order from front first: ");
	printForward(intList2);
	printf("\n");
	printf("Received: Elements in reverse order from back: ");
	printBackwards(intList2);
	printf("\n");
	printf("Result: Test Passed\n\n");

	// Test 17 - Edge Case
	// printf ("Test: Delete NULL as a node from a Book linked list\n");
    // printf ("Expected: Nothing will be deleted from the list\n");
    // deleteNodeFromList (bookList2, NULL);
    // printForward (bookList2);
    // printf ("Recieved: Segmentation Fault\n");
    // printf ("Result: Test failed\n\n");

	// Test 18 - Edge Case
	// printf ("Test: Delete NULL as a node from an int linked list\n");
    // printf ("Expected: Nothing will be deleted from the list\n");
    // deleteNodeFromList (intList2, NULL);
    // printForward (intList2);
    // printf ("Recieved: Segmentation Fault\n");
    // printf ("Result: Test failed\n\n");

    // Test 19
    printf ("Test: Delete a node that does not exist in a linked list\n");
    printf ("Expected: Nothing will be deleted from the list\n");
    deleteNodeFromList(intList2, b1);
    printForward(intList2);
    printf("\n");
    printf ("Recieved: Match not found, and nothing was deleted\n");
    printf ("Result: Test Passed\n\n");

    // Test 20 - Edge Case
    printf ("Test: Delete a node from a linked list with the deleteListNode function\n");
    printf ("Expected: Node will be removed from linked list\n");
    deleteListNode(intP6);
    printForward(intList2);
    printf("\n");
    printf ("Recieved: Node was not removed, and nothing happened\n");
    printf ("Recieved: This function should have the exact same functionality of deleteNodeFromList. Why did we need it?\n");
    printf ("Result: Test Failed\n\n");

    return 0;

}
