#include <stdio.h>
#include <stdlib.h>

#ifndef RULE_STRUCT
#define RULE_STRUCT

typedef struct rule {

	char* keyWord;
	char* keySentence;
	int totalCount;
	double userRating;
	double systemRating;

} Rule;

int compareF(const void* a, const void* b);

void deleteF(void* data);

void printF(void* data);

#endif
