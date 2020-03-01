/**
 * @file interface.h
 * @author Pavel Skipenes (pavelgs@stud.ntnu.no) , Sindre Øversveen 
 * @brief API for driver hardware
 * @version 0.1
 * @date 2020-03-01
 *  
 */
#ifndef ELEVATOR_INTERFACE_H
#define ELEVATOR_INTERFACE_H
#include "elevator.h"

/**
 * @brief Check if the cabin is at some floor
 * 
 * @return true if an elevator is next to some floor
 * @return false otherwise
 */
bool atSomeFloor();

/**
 * @brief Check if cabin has reached it's taget floor
 * 
 * @param elevatorInstance initialized elevator instacne
 * @return true if the targetFloor is reached.
 * @return false otherwise
 */
bool atTargetFloor(Elevator* elevatorInstance);

/**
 * @brief Checks given floor for orders
 * 
 * @param elevatorInstance initialized elevator instacne
 * @param floorNumber floor number
 * @note This function is not taking current direction in to account. 
 * @see @c findTargetFloor() 
 * @return true if an order is pressent for @p elevatorInstance at given @c floor
 * @return false otherwise
 */
bool orderAt(Elevator* elevatorInstance, int floorNumber);

/**
 * @brief Reads obstruction signal inside the cabin.
 * 
 * @return true if obstruction is active
 * @return false otherwise
 */
bool readObstruction();

/**
 * @brief Pulls the stop button. This function lights up the stop button when it's pressed.
 * 
 * @return true if the stop button is pressed.
 * @return false otherwise
 */
bool readStop();

/**
 * @brief Clear all orders for given @p elevatorInstance
 * 
 * @param elevatorInstance initialized elevator instacne
 */
void clearAllOrders(Elevator* elevatorInstance);

/**
 * @brief Checks current floor and clears all orders at that floor.
 * @note Will not clear any orders if the elevator is between floors.
 * 
 * @param elevatorInstance initialized elevator instacne
 */
void clearAllOrdersAtThisFloor(Elevator* elevatorInstance);

/**
 * @brief Closes the elevator door
 * @warning make sure that there are no obstructions and elevator is not moving before calling
 * @see @c readObstruction()
 * 
 */
void closeDoor();

/**
 * @brief Sends signal to motor to start moving down
 * 
 */
void elevatorMoveDown();

/**
 * @brief Sends signal to motor to start moving up
 * 
 */
void elevatorMoveUp();

/**
 * @brief Sends signal to motor to halt
 * 
 */
void elevatorStop();

/**
 * @brief Find target floor. This function takes direction in to accont. Make sure to call @c findTargetFloor(Elevator*) first
 * @see @c findTargetFloor(Elevator*)
 * 
 * @param elevatorInstance initialized elevator instacne
 */
void findTargetFloor(Elevator* elevatorInstance);

/**
 * @brief Updates current direction for @p elevatorInstance. Make sure to call @c updateOrders() before using this function
 * @see updateOrders()
 * 
 * @param elevatorInstance initialized elevator instacne
 */
void updateDirection(Elevator* elevatorInstance);

/**
 * @brief Reads all order buttons and stores them inside @p elevatorInstance
 * 
 * @param elevatorInstance initialized elevator instacne
 */
void updateOrders(Elevator* elevatorInstance);

/**
 * @brief Opens the door
 * @warning Make sure that elevator is not moving when calling this function.
 * @see elevatorStop()
 * 
 */
void openDoor();

/**
 * @brief Reads shaft sensors and updates the last known floor inside @p elevatorInstance
 * 
 * @param elevatorInstance initialized elevator instacne
 */
void updateLastFloor(Elevator* elevatorInstance);
#endif
