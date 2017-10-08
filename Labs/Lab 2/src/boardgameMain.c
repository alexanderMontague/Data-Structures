#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "boardgame.h"

/**
 * Create a struct pointer of type BoardGame and return pointer
 * @param  title - char *    brandTitle - char *    price - double
 * @return   BoardGame * bg - BoardGame struct pointer
 */
BoardGame* createBoardGame( char * title, char * brandTitle, double price )
{
    BoardGame* bg = malloc(sizeof(BoardGame));
    bg->price = price;
    bg->name = title;
    bg->brand = brandTitle;
    return bg;
}

/**
 * Accessor function to return the price of a boardgame
 * @param  bg - BoardGame *
 * @return   double price - double value for the price of a boardgame  
 */
double getBGPrice( BoardGame * bg ) 
{ 
    return bg->price;
}

/**
 * Mutator function to set a new price of a boardgame
 * @param  newPrice - double	 bg - BoardGame *
 */
void setBGPrice ( BoardGame * bg, double newPrice )
{
	bg->price = newPrice;
}

/**
 * Accessor function to return the name of the boardgame
 * @param  bg - BoardGame *
 * @return   char * name - string sentence for the name of a boardgame
 */
char* getBGName( BoardGame * bg )
{
    return bg->name;
}

/**
 * Mutator function to set a new name of a boardgame
 * @param  newBGName - char *	  bg - BoardGame *
 */
void setBGName ( BoardGame * bg, char * newBGName ) 
{
	bg->name = newBGName;
}

/**
 * Accessor function to return the brandname for the boardgame
 * @param  bg - BoardGame *
 * @return   char * brand - string sentence for the name of a boardgame
 */
char * getBrandName( BoardGame * bg )
{
    return bg->brand;
}

/**
 * Mutator function to set a new brandname of a boardgame
 * @param  newBrandName - char *	  bg - BoardGame *
 */
void setBrandName ( BoardGame * bg, char * newBrandName )
{
	bg->brand = newBrandName;
}

/**
 * Display the name, price and brandname for the specified boardgame
 * @param  bg - BoardGame *
 */
void printBoardGame( BoardGame * bg ) 
{
    printf("%s    %.2f    %s\n", getBGName(bg), getBGPrice(bg), getBrandName(bg) );
}
