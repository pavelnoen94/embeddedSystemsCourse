#pragma once
#include "elevator.h"

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
void emergencyModeReader();
void findTargetFloor();
void getOrders();
void initModeReader();
void openDoor();
void readAllSensors();
void readFloorSensors();
void resetEmergency();
void runningModeReader();
void setTargetFloor(int floor);
void updateObstruction();
bool atTargetFloor();
bool ordersInCurrentDirection();