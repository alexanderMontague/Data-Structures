#ifndef _PATIENT_SOURCE_
#define _PATIENT_SOURCE_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "patient.h"

void printNode(void *data) {

	Patient* printPatient = (Patient*)data;

	printf("%s\t\t    %d\t\t    %s", printPatient->patientID, printPatient->priority, printPatient->illness);

}

void deleteListNode(void *toBeDeleted) {
	
	toBeDeleted = NULL;
	free(toBeDeleted);

}

int compare(const void *first, const void *second) {

	int p1 = *(int*)first;
	int p2 = *(int*)second;

	if(p1 < p2) {
		return -1;
	}
	else if (p1 == p2) {
		return 0;
	}
	else if (p1 > p2) {
		return 1;
	}

	return 0;
}

#endif