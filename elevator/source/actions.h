#ifndef ELEVATOR_ACTIONS_H
#define ELEVATOR_ACTIONS_H
#include "elevator.h"
/**
 * @file
 * @brief Library of functions pertaining to actions the elevator can take, such as elevatorMove() or clearAllOrders()
 * 
 */

/**
 * @brief Commands elevator to move in input @p Direction
 * @param[in] Direction Direction elevator shall move in. 
 */

void elevatorMoveTo(int targetFloor);

void elevatorMoveUp();

void elevatorMoveDown(int numberOfFloors);

void serveFloor();
#endif
