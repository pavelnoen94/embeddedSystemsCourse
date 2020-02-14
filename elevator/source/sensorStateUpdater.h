

#include "highLevelProgramVariables.h"

// int hardware_read_floor_sensor(int floor);                           Yes/no, on 'is elevator currently at <floor>?'
// int hardware_read_order(int floor, HardwareOrder order_type);        Polls for order at floor, in direction. Returns 'yes/no'

/**
 * @brief Calls @c hardware_read_floor_sensor() for all floors in sequence. Updates @p activeFloorSensors and @p lastKnownElevatorPosition.
 * @return 0 if no sensors are active, 1 if one sensor is active and @p lastKnownElevatorPosition was changed.
 * @return -1 if more than one sensor was active (indicating hardware error).
 * */
int checkFloorSensors();


/**
 * @brief Checks value of obstruction signal, and assigns it to @p obstructionSignalState.
 * @return 1 if state was changed, 0 otherwise.
 * */
int updateObstructionState();

/**
 * @brief Checks value of stop signal, and assigns it to @p stopSignalState.
 * @return 1 if state was changed, 0 otherwise.
 * */
int updateStopSignalState();

/**
 * @brief Calls @c hardware_read_order() for every order button, and stores all orders in the appropriate queue.
 * @return number of new orders added (0 if no new orders).
 * */
int readAndAddOrders();