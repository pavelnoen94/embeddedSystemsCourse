#ifndef ELEVATOR_ACTIONS_H
#define ELEVATOR_ACTIONS_H

/**
 * @file
 * @brief Library of functions pertaining to actions the elevator can take, such as elevatorMove() or clearAllOrders()
 * 
 */

/**
 * @brief Commands elevator to move in input @p Direction
 * @param[in] Direction Direction elevator shall move in. 
 */
void elevatorMove(Direction);
void elevatorStop();    // rename to stopElevator
void elevatorMoveTo(int); // Used only by insideOrders
void clearAllOrders();
void clearOrdersAtThisFloor();
static void clear_all_order_lights();
#endif