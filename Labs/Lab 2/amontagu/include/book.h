/**
 * Book struct that holds information for a specific book
 */
typedef struct book {
    double price;	/**< price variable that holds the double amount for the specified price. */
    char * name;	/**< name variable that holds the string title of the specified book. */
} Book;

Book* createBook( char * title, double price );

double getPrice( Book * b );

void setPrice ( Book * b, double newBookPrice);

char* getName( Book * b );

void setName ( Book * b, char * newBookName);

void printBook( Book * b );