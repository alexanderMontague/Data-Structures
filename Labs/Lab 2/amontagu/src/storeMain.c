#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "store.h"

/**
 * Create a struct pointer of type Store and return pointer
 * @param  typeOfProduct - void *	functionPointer - void * (Function Pointer)
 * @return   Store * s - struct pointer of type Store
 */
Store * createStore( void * typeOfProduct, void ( * functionPointer)(void * functionToRun) )
{
	Store *s = malloc(sizeof(Store));
	s->item = typeOfProduct;
	s->funcPtr = functionPointer;
	return s;
}

/**
 * Accessor function to return the item in the store at the time
 * @param  s - Store *
 * @return   void * item - whatever item is being sold in the store at the time held in a void pointer
 */
void * getStoreItem( Store * s ) {
	return s->item;
}

/**
 * Mutator function to set a new item for the store
 * @param  s - Store *	  newItem - void *
 */
void setStoreItem( Store * s, void * newItem ) {
	s->item = newItem;
}

/**
 * Accessor function to return the void function pointer for whatever function is passed into the store
 * @param  s - Store *
 * @return   void * funcPtr - function pointer to function being called in Store
 */
void * getStoreFunction( Store * s ) {
	return s->funcPtr;
}

/**
 * Mutator function to change the function being held in the Store struct
 * @param  s - Store *	  newFunctionPointer - void * (Function Pointer)
 */
void setStoreFunction( Store * s, void ( * newFunctionPointer) (void * newFunctionToRun) ) {
	s->funcPtr = newFunctionPointer;
}

/**
 * Display function that will print book or boardgame information depending on what is passed in
 * @param  s - Store *
 */
void displayStore (Store * s) {
	s->funcPtr(s->item);
}
