typedef struct {

	int age;
	char name[30];

} Person;


/**
*
* A Function that displays all information about the person to the console
*
* Will accept a pointer to a Person struct that contains the information needed.
* This function will then print the person's age and name to the console.
*
* @param *p struct pointer of type Person that contains the contact's information
*
*/
void printPerson(Person *p);

/**
*
* A Function that will add one year to the contact's age
*  
* This function will accept a pointer to a Person struct that contains the information needed.
* The fucntion will then add one year to the integer age contained in the struct passed in.
*
* @param *p struct pointer of type Person that contains the contact's information
*
*/
void addBirthday(Person *p);

/**
*
* A Function that will compare two person's ages and return a value stating which person is younger, or the same age.
*
* This function will accept a pointer to a Person struct that contains the information needed.
* This function will then compare both ages of the contacts passed into the function.
* Depending on who is younger, it will then return a value that corresponds with the format below.
*
* @param *a struct pointer of type Person that contains the first contact's information
* @param *b struct pointer of type Person that contains the second contact's information
* 
* @return -1 will be returned if contact a has an age less than contact b
* @return  1 will be returned if contact b has an age less than contact a
* @return  0 will be returned if both contacts have the same age
*
*/
int compareAges(const Person *a, const Person *b);

