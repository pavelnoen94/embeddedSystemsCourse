#ifndef ELEVATOR_H
#define ELEVATOR_H
#include <stdbool.h>
#include "hardware.h"
#include "modeSelector.h"

#define DOOR_OPEN_TIME 3

typedef enum {
    UP,
    NONE,
    DOWN
} Direction;

typedef enum{
    IDLE,
    SERVING,
    RUNNING,
    OPENDOOR,
    STOP,
    UNKNOWN
} Status;

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
#endif
