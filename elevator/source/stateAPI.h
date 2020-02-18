/**
 * @file
 * @brief Declarations of program-wide variables to be used the main program loop. 
 * */

#include "hardware.h" 
#include <stdbool.h>
/**
 * @brief Output signal of @p STOP. Polled by @c hardware_read_stop_signal(). Remains constant for an iteration of @c programLoop.
 **/
int stopSignalState = 0;

/**
 *  @brief Output signal of @p obstruction. Polled by @c hardware_read_obstruction_signal(). Remains constant for an iteration of @c programLoop.
 * */
int obstructionSignalState = 0;

/**
 * @brief Number of active floor sensors. Constant for an iteration of @c programLoop.
 * */
int activeFloorSensors = 0;

/**
 * @brief Last floor elevator was known to be at, as polled by @c hardware_read_floor_sensor().
 * */
int lastKnownElevatorPosition;

/**
 * @brief Movement type for keeping track on the elevator's current direction of movement.
 * */
typedef enum {
    Up,
    Down,
    None
} MovementDirection;

/**
 * @brief Variable of type @p MovementDirection containing elevator's current direction of movement.
 * */
MovementDirection currentDirection;

/**
 * @brief Integer array of floors with registered requests for going @p UP; index 0-3 corresponds to @p floor 1-4. Values to be interpreted as booleans. 
 * */
int upQueue[HARDWARE_NUMBER_OF_FLOORS] = {0};

/**
 * @brief Integer array of floors with registered requests for going @p DOWN; index 0-3 corresponds to @p floor 1-4. Values to be interpreted as booleans. 
 * */
int downQueue[HARDWARE_NUMBER_OF_FLOORS] = {0};

/**
 * @brief Has the elevator been initialized?
 * 
 */
bool initialized = false;
