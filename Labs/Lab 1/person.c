#include <stdio.h>
#include <stdlib.h>
#include "person.h"

void printPerson(Person *p) {

	printf("Age: %d Name: %s\n", p->age, p->name);

}

void addBirthday(Person *p) {

	p->age++;

}

int compareAges(const Person *a, const Person *b) {

	if(a->age < b->age) {
		return -1;
	}
	else if(b->age < a->age) {
		return 1;
	}
	else if(a->age == b->age) {
		return 0;
	}
	else {
		printf("WRONG\n");
	}

}