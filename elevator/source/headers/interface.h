#pragma once
#include "elevator.h"

/**
 * @file 
 * @brief Library of high level functions pertaining to commanding and inquiring about the elevator.
 * @details Collection of polling, check and variable-setting functions to be used as
 * parts of the program loops. Abstracts the interface with @c hardware.h to increase code readability.
 * 
 */

bool activeOrderThisFloor();
bool atSomeFloor();
bool checkEmergency();
bool isValidFloor(int floor);
bool onFloor(int floor);
bool orderAt(int floor);
bool readObstruction();
bool readStop();
Direction getDirection(int targetFloor);
int getLastKnownFloor();
int getTargetFloor();
void clearAllOrders();
void clearAllOrdersAtThisFloor();
void clearOrders(int floor);
void closeDoor();
void doorModeReader();
void elevatorMoveDown();
void elevatorMoveUp();
void elevatorStop();
//void emergencyModeReader();   // Se modeReaders.h
void findTargetFloor();
void getOrders();
void initModeReader();
void openDoor();
// void readAllSensors();       // Not used anywhere
void readFloorSensors();
void resetEmergency();
// void runningModeReader(); // Se modeReaders.h
void setTargetFloor(int floor);
void updateObstruction();
void updateHasOrders();
bool atTargetFloor();
bool ordersInCurrentDirection();
void updatePosition();
