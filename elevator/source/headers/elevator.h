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

#ifndef DOXYGEN_SKIP
    typedef enum {
        UP,
        NONE,
        DOWN
    } Direction;
#endif

    typedef enum{
        IDLE,       ///< Idle
        SERVING,    ///< Serving a floor and the door is open
        RUNNING,    ///< Moving between floors
        STOP,       ///< Cabin has been stopped
        UNKNOWN     ///< Temporary status in transitions between other statuses.
    } Status;

/**
 * @brief Door open duration without obstructions.
 * 
 */
#define DOOR_OPEN_TIME 3

/**
 * @brief Stores elevators' properties.
 * 
 */
typedef struct{
    Direction direction;                            ///< Stores direction of the elevator
    int lastKnownFloor;                             ///< Stores last floor the elevator has passed
    bool emergencyState;                            ///< Active if elevator has been stopped between floors. Turns off at next door open
    Status status;                                  ///< Stores what state the elevator currently are in
    int targetFloor;                                ///< Stores the closest target floor in defined direction
    bool upOrders[HARDWARE_NUMBER_OF_FLOORS];       ///< Array of orders going up
    bool downOrders[HARDWARE_NUMBER_OF_FLOORS];     ///< Array of orders going down
    bool insideOrders[HARDWARE_NUMBER_OF_FLOORS];   ///< Array of orders from inside of the cabin
    bool hasOrders;                                 ///< Stores whenever the elevator has an order
}Elevator;

/**
 * @brief entry point for elevator API.
 * 
 * Call this to get started with the default behaviour.
 * @note If connection to hardware fails, the application will terminates.
 * @note Default behaviour is to terminate the elevator if any OS signal is passed to application.
 * Elevator will stop moving before terminating.
 * 
 * start() initializes a new instance of Elevator and start the elevator. No heap allocations are ever occurred in this program.
 * 
 */
inline void start(){
    modeSelector();
}

#endif
