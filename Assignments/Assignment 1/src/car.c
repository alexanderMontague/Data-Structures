#ifndef _CAR_SOURCE_
#define _CAR_SOURCE_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "car.h"

void printNode(void *toBePrinted) {

	Car* c = (Car*)toBePrinted;

	if(c->turnDirection == 'R') {
		if(c->arrivalTime >= 10) {
			printf("%c %c %d   %d   %d\n", c->direction, c->turnDirection, c->arrivalTime, c->arrivalTime, (c->arrivalTime + 1));
		}
		else {
			printf("%c %c %d    %d    %d\n", c->direction, c->turnDirection, c->arrivalTime, c->arrivalTime, (c->arrivalTime + 1));
		}
	}
	else if(c->turnDirection == 'F') {
		if(c->arrivalTime >= 10) {
			printf("%c %c %d   %d   %d\n", c->direction, c->turnDirection, c->arrivalTime, c->arrivalTime, (c->arrivalTime + 2));
		}
		else {
			printf("%c %c %d    %d    %d\n", c->direction, c->turnDirection, c->arrivalTime, c->arrivalTime, (c->arrivalTime + 2));
		}
	}
	else if(c->turnDirection == 'L') {
		if(c->arrivalTime >= 10) {
			printf("%c %c %d   %d   %.1lf\n", c->direction, c->turnDirection, c->arrivalTime, c->arrivalTime, ((double)c->arrivalTime) + 2.5);
		}
		else {
			printf("%c %c %d    %d    %.1lf\n", c->direction, c->turnDirection, c->arrivalTime, c->arrivalTime, ((double)c->arrivalTime) + 2.5);
		}
	}
	else {
		printf("Invalid Data Entry\n");
	}
}

void deleteListNode(void *toBeDeleted) {
	
	toBeDeleted = NULL;
	free(toBeDeleted);

}

int compare(const void *first, const void *second) {

	Car* c1 = (Car*)first;
	Car* c2 = (Car*)second;

	if(c1->arrivalTime < c2->arrivalTime) {
		return -1;
	}
	else if (c1->arrivalTime == c2->arrivalTime) {
		return 0;
	}
	else if (c1->arrivalTime > c2->arrivalTime) {
		return 1;
	}

	return 0;
}

#endif