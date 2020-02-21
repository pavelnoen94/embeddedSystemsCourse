#pragma once
#include "elevator.h"


void readAllSensors();

void initModeReader();
void idleModeReader();

void runningModeReader();

void emergencyModeReader();

void doorModeReader();
void elevatorStop();
void elevatorMoveUp();
void elevatorMoveDown();

void clearAllOrders();

void openDoor();

bool orderAt(int floor);

void closeDoor();

void clearAllOrdersAtThisFloor();

void clearOrders(int floor);

bool atSomeFloor();

bool activeOrderThisFloor();

int getLastKnownFloor();

int getTargetFloor();

void setTargetFloor(int floor);

bool isValidFloor(int floor);

bool onFloor(int floor);

Direction getDirection(int targetFloor);
void findTargetFloor();

bool checkEmergency();
void resetEmergency();
void updateObstruction();
void readFloorSensors();

void getOrders();
