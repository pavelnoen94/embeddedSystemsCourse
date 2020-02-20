#ifndef ELEVATOR_ACTIONS_H
#define ELEVATOR_ACTIONS_H

/**
 * @file
 * @brief 
 * 
 */

void elevatorMove(Direction);
void elevatorMove();
void elevatorStop();    // rename to stopElevator
void elevatorMoveTo(int); // Used only by insideOrders
void clearAllOrders();
void clearOrdersAtThisFloor();

#endif