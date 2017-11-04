#include <stdio.h>
#include <stdlib.h>

#ifndef _PATIENT_HEADER_
#define _PATIENT_HEADER_

typedef struct patient {
	
	char* patientID;
	char* illness;
	int priority;

} Patient;

typedef struct timePatient {

	char* ID;
	int finishTime;

} TimePatient;


#endif