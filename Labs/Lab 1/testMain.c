#include <stdio.h>
#include <stdlib.h>
#include "person.h"
#include "person.c"

int main(void) {

	Person personA;
	Person personB;

	printf("testMain.c File\n");

	personA.age = 65;
	personB.age = 100;

	strcpy(personA.name, "Will\n");
	strcpy(personB.name, "Stewart\n");

	printf("PersonA - Name: %s Age: %d", personA.name, personA.age);
	printf("PersonB - Name: %s Age: %d", personB.name, personB.age);

	return 0;
}
