// Alexander Montague
// 0959687
// amontagu@uoguelph.ca
// November 2017

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/**
 * Create a typedef for a  Compare Function 
 */
typedef int (*CompareFunc)(void* a, void* b);

/**
 * Create a typedef for a Sort Algorithm of an array
 */
typedef void (*SortAlgorithm) (int* container, int length,  CompareFunc cf);

/**
 * Print an array of integers with a specific length.
 */
void printArray(int* arr, int length) {
	for(int i = 0; i < length; i++) 
		printf("%d ", arr[i]);
	printf("\n");
}

/***
 * NOTE: You will implement this function, it will be used to call all sorting algorithms. 
 *      It will also output the all the information required by the output section of the lab.
 *       
 * menuSelection is the text for the menu option that was selected.
 * sorter -> is the sorting function
 * array -> is the input array given by the user
 * length-> is the length of the array
 * compare -> is a comparison function pointer.
 */
void sort(char* menuSelection, SortAlgorithm sorter, int* array, int length, CompareFunc compare);

int compareIncreasing(void* a, void* b);

int compareDecreasing(void* a, void* b);

void bubbleAlgorithm(int* container, int length, CompareFunc cf);

void selectionAlgorithm(int* container, int length, CompareFunc cf);

int main (int argc, char** argv)
{

	bool runMenu = true;
	char userInput[100] = "NULL";
	char* tempChar = NULL;
	char* menuChoice = malloc(sizeof(char) * 100);
	size_t element = 0;
	int numElems = 0;
	int tempInt = 0;
	int* intArray = malloc(sizeof(int) * 20);
	CompareFunc CF = NULL;
	SortAlgorithm SA = NULL;

	do {

		element = 0;
		printf("\nPlease input the number of integers in the array\n");
		printf("Number of Integers: ");
		fgets(userInput, 100, stdin);
		numElems = atoi(userInput);
		printf("\nPlease input the %d integers\n", numElems);
		printf("Enter Integers: ");
		fgets(userInput, 100, stdin);
		printf("\nSorting Menu System\n");
		printf("1) Bubble Sort (Increasing Order)\n");
		printf("2) Bubble Sort (Decreasing Order)\n");
		printf("3) Bubble Sort (Increasing Order - Even Numbers Before Odd Numbers)\n");
		printf("4) Selection Sort (Increasing Order)\n");
		printf("5) Selection Sort (Decreasing Order)\n");
		printf("6) Selection Sort (Increasing Order - Even Numbers Before Odd Numbers)\n");
		printf("7) Quit\n");
		printf("Menu Selection: ");
		fgets(menuChoice, 100, stdin);

		if(atoi(menuChoice) >= 1 && atoi(menuChoice) <= 3) {
			SA = &bubbleAlgorithm;
			if(atoi(menuChoice) == 1) {
				CF = &compareIncreasing;
			}
			else if(atoi(menuChoice) == 2) {
				CF = &compareDecreasing;
			}
			else if(atoi(menuChoice) == 3) {
				CF = &compareIncreasing;
			}
		}
		else if(atoi(menuChoice) >= 4 && atoi(menuChoice) <= 6) {
			SA = &selectionAlgorithm;
			if(atoi(menuChoice) == 4) {
				CF = &compareIncreasing;
			}
			else if(atoi(menuChoice) == 5) {
				CF = &compareDecreasing;
			}
			else if(atoi(menuChoice) == 6) {
				CF = &compareIncreasing;
			}
		}
		else if(atoi(menuChoice) == 7) {
			break;
		}

		tempChar = strtok(userInput, " ");
		while(tempChar != NULL && element < numElems) {	
			element++;
			tempInt = atoi(tempChar);
			printf("num = %d\n", tempInt);
			intArray[element - 1] = tempInt;
			tempChar = strtok(NULL, " ");
		}

		printf("Initial Array: ");
		printArray(intArray, element);
		sort(menuChoice, SA, intArray, element, CF);
	
	}
	while(runMenu == true);	
	free(intArray);
	return 0;
}

void sort(char* menuSelection, SortAlgorithm sorter, int* array, int length, CompareFunc compare) {
	
	int menuChoice = atoi(menuSelection);
	int even = 0;
	int odd = 0;
	int* evenArray = malloc(sizeof(int) * 20);
	int* oddArray = malloc(sizeof(int) * 20);

	if(menuChoice == 1) {
		sorter(array, length, compare);
		printf("Result Array: ");
		printArray(array, length);
	}
	else if(menuChoice == 2) {
		sorter(array, length, compare);
		printf("Result Array: ");
		printArray(array, length);
	}
	else if(menuChoice == 3) {
		
	}
	else if(menuChoice == 4) {
		sorter(array, length, compare);
		printf("Result Array: ");
		printArray(array, length);
	}
	else if(menuChoice == 5) {
		sorter(array, length, compare);
		printf("Result Array: ");
		printArray(array, length);
	}
	else if(menuChoice == 6) {
				
	}
	else {
		printf("Invalid Selection!\n");
	}
	free(evenArray);
	free(oddArray);
}

void bubbleAlgorithm(int* container, int length, CompareFunc cf) {

	int temp = 0;
	for(int i = 0; i < length - 1; i++) {
		for(int j = 0; j < length - i - 1 ; j++) {
			if((cf((void*)&container[j], (void*)&container[j + 1])) == 1) {
				temp = container[j];
				container[j] = container[j + 1];
				container[j + 1] = temp;
			}
		}
	}
}

void selectionAlgorithm(int* container, int length, CompareFunc cf) {

	int temp = 0;
	int min = 0;
	for(int i = 0; i < length - 1; i++) {
		min = i;
		for(int j = i + 1; j < length; j++) {
			if((cf((void*)&container[j], (void*)&container[min])) == -1) {
				min = j;
			}
		}
		temp = container[min];
		container[min] = container[i];
		container[i] = temp;
	}

}

int compareIncreasing(void* a, void* b) {
	
	if(*(int*)a < *(int*)b) {
		return -1;
	}	
	else if(*(int*)a > *(int*)b) {
		return 1;
	}

	return 0;
}

int compareDecreasing(void* a, void* b) {

	if(*(int*)a > *(int*)b) {
		return -1;
	}
	else if(*(int*)a < *(int*)b) {
		return 1;
	}
	return 0;
}

