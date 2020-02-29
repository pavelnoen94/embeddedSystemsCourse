#pragma once
#include "elevator.h"

/**
 * @file 
 * @brief Library of high level functions pertaining to commanding and inquiring about the elevator.
 * @details Collection of polling, check and variable-setting functions to be used as
 * parts of the program loops. Abstracts the interface with @c hardware.h to increase code readability.
 * 
 */
bool readObstruction();
void clearAllOrders();
void clearAllOrdersAtThisFloor();
bool readStop();
void openDoor();
void closeDoor();
void readFloorSensors();
bool orderAt(int);
Direction getDirection(int targetFloor);
bool ordersInCurrentDirection();
bool onFloor(int);
void elevatorStop();
void elevatorMoveUp();
void elevatorMoveDown();
bool atSomeFloor();
bool isValidFloor();
void getOrders();
bool atTargetFloor();
void findTargetFloor();