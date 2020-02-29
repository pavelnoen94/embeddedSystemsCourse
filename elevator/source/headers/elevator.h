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

/**
 * @brief Time [s] elevator door is held open when openDoors() is called.
 * 
 */
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
 * @brief The previous floor the elevator was known to be at.
 * 
 */

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
 * @struct Position elevator.h "headers/elevator.h"
 * @brief Structure for storing information on the elevator's position.
 * @details Contains variables from which the elevator's position can be extrapolated.
 */
typedef struct{
    int lastKnownFloor;
} Position;
Position position;

/**
 * @brief Global variable; current elevator direction.
 * 
 */
Direction direction;

/**
 * @brief Current target floor; where the elevator is currently headed.
 */
int targetFloor;

typedef struct{
    Direction direction;
    int lastKnownFloor;
    bool emergencyState;
    int targetFloor;
    bool upOrders[HARDWARE_NUMBER_OF_FLOORS];
    bool downOrders[HARDWARE_NUMBER_OF_FLOORS];
    bool insideOrders[HARDWARE_NUMBER_OF_FLOORS];
    bool hasOrders;
}ElevatorData;
ElevatorData elevator;



#endif
