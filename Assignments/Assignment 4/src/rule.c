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
	printf("Keyword: %s    Sentence: %s    Rating: %f\n", printRule->keyWord, printRule->keySentence, printRule->userRating);

}
