#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void printFunction();
void priceFunction();
void nameFunction();

typedef struct {
    
    double price;
    char *name;
    
} Book;

int main()
{
    Book *harryPotter;
    
    harryPotter = malloc(sizeof(Book));
   
    priceFunction(harryPotter);
    nameFunction(harryPotter);
    printFunction(harryPotter);
    
    return 0;
}

void printFunction(Book *book) {
    printf("%s : %.2lf\n", book->name, book->price);
}
void priceFunction(Book *book) {
    book->price = 19.99;
}
void nameFunction(Book *book) {
    book->name = malloc(sizeof(char) * 50);
    strcpy(book->name, "Harry Potter And The Cursed Child");
}
