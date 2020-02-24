/**
 * @file
 * @brief Library containing program variables, and the main program loop Elevator()
 * 
 */

#ifndef ELEVATOR_H
#define ELEVATOR_H
#include <stdbool.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include "hardware.h"

#define DOOR_OPEN_TIME 3

/**
 * @brief Static boolean array, where index 0-3 represents floor 1-4, and value @c true represents an order in direction @c UP at that floor.
 * 
 */
bool upOrders[HARDWARE_NUMBER_OF_FLOORS];
/**
 * @brief Static boolean array, where index 0-3 represents floor 1-4, and value @c true represents an order in direction @c DOWN at that floor.
 * 
 */
bool downOrders[HARDWARE_NUMBER_OF_FLOORS];
/**
 * @brief Static boolean array, where index 0-3 represents floor 1-4, and value @c true represents an order for that floor coming from inside the elevator.
 * 
 */
bool insideOrders[HARDWARE_NUMBER_OF_FLOORS];
/**
 * @brief Boolean variable telling whether the elevator is in the emergency state.
 * @see emergency()
 * 
 */
bool emergencyState;
/**
 * @brief Boolean variable telling whether there are any unfulfilled orders or not.
 * 
 */
bool hasOrders;
/**
 * @brief Boolean variable telling whether obstruction input is high or not.
 * 
 */
bool obstruction;

/**
 * @brief The previous floor the elevator was known to be at.
 * 
 */
int lastKnownFloor;


/**
 * @brief The different movement directions the elevator can have.
 * 
 */
typedef enum {
    UP,
    NONE,
    DOWN
} Direction;



/**
 * @brief Structure to remember if the elevator above or below a sertain floor
 * 
 */
typedef struct{
    int lastKnownFloor;
    bool above;
} Position;
Position position;

/**
 * @brief Global variable; current elevator direction.
 * 
 */
Direction direction;

/**
 * @brief Main program loop. Call to initiate and run elevator control logic.
 * 
 * @code
 * //Example:
 * 
 * #include <elevator.h>
 * 
 * int main(){
 *     Elevator();
 * }
 * @endcode
 * 
 */

int targetFloor;

#endif
