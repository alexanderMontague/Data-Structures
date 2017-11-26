#ifndef _HASH_SOURCE_
#define _HASH_SOURCE_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "HashTableAPI.h"
#include "hash.h"

HTable *createTable(size_t size, int (*hashFunction)(size_t tableSize, int key),void (*destroyData)(void *data),void (*printNode)(void *toBePrinted)) {

	HTable* newHash = malloc(sizeof(HTable));
	newHash->size = size;
	newHash->table = malloc(sizeof(Node*) * newHash->size);

	for(int i = 0; i < newHash->size; i++) {
		newHash->table[i] = NULL;
	}

	return newHash;

}

Node *createNode(int key, void *data) {

	Node* tempNode = malloc(sizeof(Node));

	tempNode->key = key;
	tempNode->data = data;
	tempNode->next = NULL;

	return tempNode;

}

void destroyTable(HTable *hashTable) {
	// Node* tempNode = NULL;
	// Node* nextNode = NULL;
	// for(int i = 0; i < hashTable->size; i++) {
	// 	tempNode = hashTable->table[i];
	// 	while(tempNode != NULL) {
	// 		nextNode = hashTable->table[i]->next;
	// 		free(tempNode->data);		// trying to free each individual node 
	// 		tempNode = NULL;			// says that the memory has not been 
	// 		tempNode = nextNode;		// allocated? Not too sure why but this should
	// 	}								// be the logic to free each node, then the array, then the table
	// }
	free(hashTable->table);
	free(hashTable);
	hashTable->table = NULL;
	hashTable = NULL;
}

void insertData(HTable *hashTable, int key, void *data) {
	Node* addNode = createNode(key, data);
	int index = generateIndex(key, hashTable->size);
	if(hashTable->table[index] == NULL) {
		hashTable->table[index] = addNode;
	}
	else {
		Node* tempNode = hashTable->table[index];
		while(tempNode->next != NULL) {
			tempNode = tempNode->next;
		}
		tempNode->next = addNode;
	}
}

void removeData(HTable *hashTable, int key) {
	int index = generateIndex(key, hashTable->size);

	if((hashTable->table[index])->key == key) {	// if key is at head 
		Node* head = hashTable->table[index];
		Node* next = head->next;
		free(head);
		head = NULL;
		hashTable->table[index] = next;	
	}
	else {
		Node* tempNode = hashTable->table[index];
		while(tempNode != NULL) {
			if(tempNode->next->key == key && tempNode->next->next != NULL) {	// if key is in middle
				Node* delNode = tempNode->next;
				tempNode->next = tempNode->next->next;
				free(delNode);
				delNode = NULL;
				break;
			}
			else if(tempNode->next->key == key && tempNode->next->next == NULL) {	// if key is at tail
				free(tempNode->next);
				tempNode->next = NULL;
				break;
			}
			tempNode = tempNode->next;
		}
	}
}

void *lookupData(HTable *hashTable, int key) {
	int index = generateIndex(key, hashTable->size);

	if((hashTable->table[index])->key == key) {			// if key is at head
		return (hashTable->table[index])->data;
	}
	else {
		if(hashTable->table[index] != NULL) {			// if key is not at head, iterate through
			Node* tempNode = hashTable->table[index];
			while(tempNode != NULL) {
				tempNode = tempNode->next;
				if(tempNode->key == key) {
					return tempNode->data;
				}
			}
		}
		else {
			return NULL;
		}
	}
	return NULL;
}
#endif