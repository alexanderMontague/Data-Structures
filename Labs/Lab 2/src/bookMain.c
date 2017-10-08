#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "book.h"

/**
 * Create a struct pointer of type Book and return pointer
 * @param  title - char *    price - double
 * @return   Book * b - Book struct pointer
 */
Book * createBook( char * title, double price )
{
    Book* b = malloc(sizeof(Book));
    b->price  = price;
    b->name = title;
    return b;
}

/**
 * Return the price of a book
 * @param  b - Book *
 * @return   Double price - double value for price of book
 */
double getPrice( Book * b ) 
{ 
    return b->price;
}

/**
 * Mutator function to set a new price of a book
 * @param  newBookPrice - double      b - Book *
 */
void setPrice ( Book * b, double newBookPrice) 
{
	b->price = newBookPrice;
}

/**
 * Return a books name
 * @param  b - Book *
 * @return   char * - string of name of book
 */
char * getName( Book * b )
{
    return b->name;
}

/**
 * Mutator function to set a new name of a book
 * @param  newBookName - char *       b - Book *
 */
void setName ( Book * b, char * newBookName)
{
	b->name = newBookName;
}

/**
 * Display a book's name and price.
 * @param b - Book *
 */
void printBook( Book * b ) 
{
    printf("%s : %.2f\n", getName(b), getPrice(b) );
}