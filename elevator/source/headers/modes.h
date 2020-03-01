/**
 * @file modes.h
 * @author Pavel Skipenes (pavelgs@stud.ntnu.no) , Sindre Øversveen 
 * @brief Modes in whitch the elevator can be operated in
 * @version 0.1
 * @date 2020-03-01
 *  
 */
#ifndef ELEVATOR_MODES_H
#define ELEVATOR_MODES_H

/**
 * @brief Enter emergency mode.
 * 
 * Stops the elevator and clears all orders.
 * Will stay in emergency mode untill a new order is given. 
 * @note make sure to call @c startUp() before using this function 
 * @return Function returns when a new order is detected
 * 
 */
void emergency();

/**
 * @brief Idle mode waiting for new orders.
 * 
 * @return function returns when it detects orders or stop button is pressed.
 * @note make sure to call @c startUp() before using this function 
 * 
 */
void idle();

/**
 * @brief Running mode runs while there is active orders and the cabin are not at target floor.
 * 
 * @note make sure to call @c startUp() before using this function 
 * 
 */
void running();

/**
 * @brief Start serving a floor
 * 
 * @note Make sure that @c startUp() has been called before using this function
 * 
 * This function serves a floor by opening the cabin at current floor and letting people on and off.
 * All orders at that floor are then cleared. When the door are closed this function returns.
 */
void serveFloor();

/**
 * @brief Initializer
 * 
 * Call this before entering other modes.
 * This function will return successfully if connection to hardware is succeessfull
 */
void startUp();
#endif
