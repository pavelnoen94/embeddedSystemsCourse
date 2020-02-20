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
static bool upOrders[HARDWARE_NUMBER_OF_FLOORS] = {false};
/**
 * @brief Static boolean array, where index 0-3 represents floor 1-4, and value @c true represents an order in direction @c DOWN at that floor.
 * 
 */
static bool downOrders[HARDWARE_NUMBER_OF_FLOORS] = {false};
/**
 * @brief Static boolean array, where index 0-3 represents floor 1-4, and value @c true represents an order for that floor coming from inside the elevator.
 * 
 */
static bool insideOrders[HARDWARE_NUMBER_OF_FLOORS] = {false};
/**
 * @brief Boolean variable telling whether stop button input is high or not.
 * 
 */
static bool stopButtonPressed = false;
/**
 * @brief Boolean variable telling whether there are any unfulfilled orders or not.
 * 
 */
static bool hasOrders = false;
/**
 * @brief Boolean variable telling whether obstruction input is high or not.
 * 
 */
static bool obstruction = false;
/**
 * @brief Boolean variable telling whether the elevator is currently at a known floor. @c false if elevator is between floors.
 * 
 */
static bool atSomeFloor = false;
/**
 * @brief The previous floor the elevator was known to be at.
 * 
 */
static int lastKnownFloor;


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
void Elevator();
#endif