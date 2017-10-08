#include <stdio.h>
#include <stdlib.h>
#include "person.h"
#include "person.c"

int main(void) {

	Person personA;
	Person personB;

	printf("main.c File\n");

	personA.age = 19;
	personB.age = 21;

	strcpy(personA.name, "Alex\n");
	strcpy(personB.name, "Jason\n");

	printf("PersonA - Name: %s Age: %d", personA.name, personA.age);
	printf("PersonB - Name: %s Age: %d", personB.name, personB.age);

	return 0;
}
