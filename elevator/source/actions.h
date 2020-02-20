#ifndef ELEVATOR_ACTIONS_H
#define ELEVATOR_ACTIONS_H

void elevatorMove(Direction);
void elevatorMove();
void elevatorStop();
void elevatorMoveTo(int); // Used only by insideOrders
void clearAllOrders();
void clearOrdersAtThisFloor();

#endif