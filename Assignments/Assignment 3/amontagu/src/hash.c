#ifndef _HASH_SOURCE_
#define _HASH_SOURCE_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "HashTableAPI.h"


int generateKey(char* value) {		// variation of the lose lose algorithm
	unsigned int hash = 33;			// Referenced from: http://www.cse.yorku.ca/~oz/hash.html
	int i = 1;

	while(value[i] != '\0') {
		hash = hash + (unsigned int)(value[i - 1] * i);
		i++;
	}

    return hash;
}

int generateIndex(int key, size_t tableSize) {

	return key % tableSize;

}

bool inList(HTable* table, int key) {
	int index = generateIndex(key, table->size);

	if(table->table[index] == NULL) {
		return false;
	}
	else {
		if(table->table[index]->key == key) {
			return true;
		}
		Node* tempNode = table->table[index]->next;
		while(tempNode != NULL) {
			if(tempNode->key == key) {
				return true;
			}
			tempNode = tempNode->next;
		}
		return false;
	}
	return false;
}

#endif