#ifndef ELEVATOR_INTERFACE_H
#define ELEVATOR_INTERFACE_H
#include "elevator.h"

bool atSomeFloor();
bool atTargetFloor(Elevator*);
bool isValidFloor(int);
bool onFloor(int);
bool orderAt(Elevator* elevator, int);
bool ordersInCurrentDirection(Elevator*);
bool readObstruction();
bool readStop();
void clearAllOrders(Elevator*);
void clearAllOrdersAtThisFloor(Elevator*);
void closeDoor();
void elevatorMoveDown();
void elevatorMoveUp();
void elevatorStop();
void findTargetFloor(Elevator*);
void getDirection(Elevator* elevator);
void getOrders(Elevator*);
void openDoor();
void readFloorSensors(Elevator*);
#endif
