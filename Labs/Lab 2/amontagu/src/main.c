
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "book.h"
#include "boardgame.h"
#include "store.h"

int main( int argc, char ** argv )
{

	Book *b1 = createBook("Harry Potter And The Cursed Child", 19.99);
	Book *b2 = createBook("Cracking The Coding Interview", 35.75);
	BoardGame *bg1 = createBoardGame("Parcheesi", "Parker Brothers", 25.50);
	BoardGame *bg2 = createBoardGame("Risk", "Hasbro", 22.69);
	Store *s = createStore(NULL, NULL);
    
	setStoreItem(s, b1);
	setStoreFunction(s, (void (*) (void * ))printBook);
	displayStore(s);
	setStoreItem(s, b2);
	setStoreFunction(s, (void (*) (void * ))printBook);
	displayStore(s);

	setStoreItem(s, bg1);
	setStoreFunction(s, (void (*) (void * ))printBoardGame);
	displayStore(s);
	setStoreItem(s, bg2);
	setStoreFunction(s, (void (*) (void * ))printBoardGame);
	displayStore(s);
    
    free(b1);
    free(b2);
    free(bg1);
    free(bg2);
    free(s);

    return 0;

}
