/**
* Store struct that holds information needed to display what item is in the store	
*/
typedef struct store {
    void * item;					/**< item variable that holds a void pointer to whatever type of product will be displayed in the store. */
    void ( * funcPtr)(void * );		/**< funcPtr variable that holds a void function pointer to whatever function needs to be executed for the specific product in the store. */
} Store;

Store * createStore( void * typeOfProduct, void ( * functionPointer) (void * functionToRun) );

void * getStoreItem( Store * s );

void setStoreItem( Store * s, void * newItem );

void * getStorefunction( Store * s );

void setStoreFunction( Store * s, void ( * newFunctionPointer) (void * newFunctionToRun) );

void displayStore (Store * s);