#ifndef _HASH_HEADER_
#define _HASH_HEADER_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "HashTableAPI.h"

/**Function that generates a unique key for a specified string given
*@return integer key value
*@param value that is being hashed (string)
**/
int generateKey(char* value);

/**Function that generates a index based on the given key that is within the hash map's array size
*@return integer index in Node Array
*@param integer key that was generated for the specified string
*@param size of the hash map's array in order to generate a valid index
**/
int generateIndex(int key, size_t tableSize);

/**Function that will check to see if a specified key is in the hash table 
*@return boolean "true" if the key is contained in the hash map, boolean "false" if the key is not contained
*@param pointer to the hash table that is being checked for a key
*@param integer key that is being checked in the hash table
**/
bool inList(HTable* table, int key);

#endif