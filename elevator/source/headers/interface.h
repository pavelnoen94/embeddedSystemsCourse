#ifndef ELEVATOR_INTERFACE_H
#define ELEVATOR_INTERFACE_H
#include "elevator.h"

bool atSomeFloor();
bool atTargetFloor(Elevator* elevatorInstance);
bool orderAt(Elevator* elevatorInstance, int floorNumber);
bool readObstruction();
bool readStop();
void clearAllOrders(Elevator* elevatorInstance);
void clearAllOrdersAtThisFloor(Elevator* elevatorInstance);
void closeDoor();
void elevatorMoveDown();
void elevatorMoveUp();
void elevatorStop();
void findTargetFloor(Elevator* elevatorInstance);
void updateDirection(Elevator* elevatorInstance);
void updateOrders(Elevator* elevatorInstance);
void openDoor();
void updateLastFloor(Elevator* elevatorInstance);
#endif
