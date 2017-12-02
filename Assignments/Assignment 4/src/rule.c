#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rule.h"

int compareF(const void* a, const void* b) {
	
	Rule* r1 = (Rule*)a;
	Rule* r2 = (Rule*)b;

	return strcmp(r1->keyWord, r2->keyWord);
}

void deleteF(void* data) {

}

void printF(void* data) {

	Rule* printRule = (Rule*)data;
	printf("%s\tRating: %.2f\tSystem: %.2f\tOccurences: %d\n", printRule->keyWord, printRule->userRating, printRule->systemRating, printRule->totalCount);

}
