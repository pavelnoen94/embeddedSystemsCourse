#ifndef ELEVATOR_H
#define ELEVATOR_H
#include <stdbool.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include "hardware.h"

#define DOOR_OPEN_TIME 3

static bool upOrders[HARDWARE_NUMBER_OF_FLOORS] = {false};
static bool downOrders[HARDWARE_NUMBER_OF_FLOORS] = {false};
static bool insideOrders[HARDWARE_NUMBER_OF_FLOORS] = {false};
static bool emergencyState = false;
static bool hasOrders = false;
static bool doorTimerStarted = false;
static bool obstruction = false;
static bool atSomeFloor = false;
static bool floorSensor[HARDWARE_NUMBER_OF_FLOORS] = {false};
static int lastKnownFloor;
static unsigned int Iterations = 0;

// Elevator direction
typedef enum {
    UP,
    NONE,
    DOWN
} Direction;

Direction direction;
void Elevator();
#endif