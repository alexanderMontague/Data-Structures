/**
* BoardGame struct that holds information for a specific boardgame
*/
typedef struct boardgame {
    double price;	/**< price variable that holds the double amount for the specified price. */
    char * name;	/**< name variable that holds the string sentence for the specified name. */
    char * brand;	/**< brand variable that holds the string sentence for the specified brand. */
} BoardGame;

BoardGame* createBoardGame( char * title, char * brandTitle, double price );

double getBGPrice( BoardGame * bg );

void setBGPrice ( BoardGame * bg, double newPrice );

char * getBGName( BoardGame * bg );

void setBGName ( BoardGame * bg, char * newBGName );

char * getBrandName( BoardGame * bg );

void setBrandName ( BoardGame * bg, char * newBrandName );

void printBoardGame( BoardGame * bg );