#pragma once
#include "elevator.h"

/**
 * @file 
 * @brief Library of high level functions pertaining to commanding and inquiring about the elevator.
 * @details Collection of polling, check and variable-setting functions to be used as
 * parts of the program loops. Abstracts the interface with @c hardware.h to increase code readability.
 * 
 */
bool atSomeFloor();
bool atTargetFloor(ElevatorData*);
bool isValidFloor(int);
bool onFloor(int);
bool orderAt(ElevatorData* elevator, int);
bool ordersInCurrentDirection(ElevatorData*);
bool readObstruction();
bool readStop();
void getDirection(ElevatorData* elevator);
void clearAllOrders(ElevatorData*);
void clearAllOrdersAtThisFloor(ElevatorData*);
void closeDoor();
void elevatorMoveDown();
void elevatorMoveUp();
void elevatorStop();
void findTargetFloor(ElevatorData*);
void getOrders(ElevatorData*);
void openDoor();
void readFloorSensors(ElevatorData*);