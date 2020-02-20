#ifndef ELEVATOR_H
#define ELEVATOR_H
#include <stdbool.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include "hardware.h"

#define DOOR_OPEN_TIME 3

bool upOrders[HARDWARE_NUMBER_OF_FLOORS] = {false};
bool downOrders[HARDWARE_NUMBER_OF_FLOORS] = {false};
bool insideOrders[HARDWARE_NUMBER_OF_FLOORS] = {false};
bool stopButtonPressed = false;
bool hasOrders = false;
bool doorTimerStarted = false;
bool obstruction = false;
bool atSomeFloor = false;
bool floorSensor[HARDWARE_NUMBER_OF_FLOORS] = {false};
int lastKnownFloor;

// Elevator status
typedef enum {
    IDLE,
    RUNNING,
    STOPPED,
    OPEN_DOOR // temporary status. Being called from other statuses
} Status;

// Elevator direction
typedef enum {
    UP,
    NONE,
    DOWN
} Direction;

Status status;
Direction direction;
void Elevator();
#endif