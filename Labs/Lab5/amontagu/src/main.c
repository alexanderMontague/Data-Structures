
// Alexander Montague
// 0959687
// amontagu@uoguelph.ca
// October 2017

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "LinkedListAPI.h"
#include "structAPI.h"

int main (int argc, char **argv)
{

	char userInput[100] = "NULL";
	char* string = NULL;
	int* num = NULL;
	int cmpNum = 0;
	Stack* mainStack = createStack(&printEntry, NULL, NULL);
	
	while(true) {

		printf("Input: ");
		fgets(userInput, 100, stdin);
		string = strtok(userInput, " ");
		
		if(atoi(string) < 0) {
			break;
		}
		
		while(string != NULL) {
			num = malloc(sizeof(int));			  // Allocate new mem for every new integer
			*num = atoi(string);

			if(mainStack->list->tail == NULL) {	  // If first in stack
				push(mainStack, (void*)num);
			}
			else {
												  // in stack list, get tail node
				cmpNum = compareEntry((void*)num, mainStack->list->tail->data);
				if(cmpNum == 1) {	 			  // num - new tail   |   data - tail
					printEntry((void*)num);
					printf("Squashed");
					printEntry(mainStack->list->tail->data);
					printf("\n");
					pop(mainStack);
					push(mainStack, (void*)num);
				}
				else if(cmpNum == -1) {
					push(mainStack, (void*)num);
				}																																		
				if(mainStack->list->tail->previous != NULL) {  // This could have totally been eliminated if I used a while loop at the start
					cmpNum = compareEntry((void*)num, mainStack->list->tail->previous->data);
					if(cmpNum == 1) {						   // Just checks for the instance of if lowest number is in the middle of higher numbers
						printEntry((void*)num);
						printf("Squashed");
						printEntry(mainStack->list->tail->previous->data);
						printf("\n");
						deleteNodeFromList(mainStack->list, mainStack->list->tail->previous->data);
					}
				}						 
			}
			string = strtok(NULL, " ");
		}
	}
	printf("Remaining:");
	printBackwards(mainStack->list);
	printf("\n");

    return 0;
}

