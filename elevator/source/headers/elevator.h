/**
 * @file elevator.h
 * @author Pavel Skipenes (pavelgs@stud.ntnu.no) , Sindre Øversveen 
 * @brief API for elevator library
 * @version 0.1
 * @date 2020-03-01
 * 
 * @see <a href="https://github.com/pavelnoen94/EmbeddedSystemsCourse" target="_blank">Github repo</a>
 *  
 */
#ifndef ELEVATOR_H
#define ELEVATOR_H
#include <stdbool.h>
#include "hardware.h"
#include "modeSelector.h"

/**
 * @brief Door open duration without obstructions.
 * 
 */
#define DOOR_OPEN_TIME 3

typedef enum {
    UP,
    NONE,
    DOWN
} Direction;

/**
 * @brief Elevator status.
 * 
 */
typedef enum{
    IDLE,
    SERVING,
    RUNNING,
    OPENDOOR,
    STOP,
    UNKNOWN
} Status;

/**
 * @brief Stores elevators' properties.
 * 
 */
typedef struct{
    Direction direction;
    int lastKnownFloor;
    bool emergencyState;
    Status status;
    int targetFloor;
    bool upOrders[HARDWARE_NUMBER_OF_FLOORS];
    bool downOrders[HARDWARE_NUMBER_OF_FLOORS];
    bool insideOrders[HARDWARE_NUMBER_OF_FLOORS];
    bool hasOrders;
}Elevator;

/**
 * @brief entry point for elevator API.
 * 
 * Call this to get started with the default behaviour.
 * @note If connection to hardware fails, the application will terminates.
 * @note Default behaviour is to terminate the elevator if any OS signal is passed to application.
 * Elevator will stop moving before terminating.
 * 
 * start() initializes a new instance of Elevator and start the elevator. No heap allocations are ever occoured in this program.
 * 
 */
inline void start(){
    modeSelector();
}

#endif
