#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"person.h"

int main( int argc, char ** argv )
{
	printf("STARTING THE TEST MAIN\n");
	Person * p = (Person*)malloc(sizeof(Person));
	free(p);
	return 0;
}
