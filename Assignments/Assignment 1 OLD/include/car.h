#ifndef _CAR_HEADER_
#define _CAR_HEADER_

/**
 * Car struct that holds information for a specific car
 */
typedef struct car {
    char direction;	    /**< direction variable that holds the direction the car will be facing (North, East, South, West). */
    char turnDirection;	/**< turn direction variable that indicated where the car will be turning or not. (Forward, Left, Right). */
	int arrivalTime;    /**< arrival time variable that holds the specified time that the car arrives at the intersection. */
} Car;

void printNode(void *toBePrinted);

void deleteListNode(void *toBeDeleted);

int compare (const void *first, const void *second);

#endif