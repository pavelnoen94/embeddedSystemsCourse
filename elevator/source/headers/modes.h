#ifndef ELEVATOR_MODES_H
#define ELEVATOR_MODES_H

/**
 * @file
 * @brief Library of mode functions.
 * @details Each mode function puts the elevator in the corresponding mode, by entering
 * a program loop containing sensor readers and actions appropriate for that mode.
 * Once certain conditions are met, the program loop will exit its mode and return 
 * to modeSelector() 
 */

// static void sigHandler(int sig);

/**
 * @brief Function performing the initialization procedure.
 * @details Hardware is initialized and the elevator
 * tries to reach a defined state (known position) by moving up. Once a floor is reached,
 * the elevator will stop and startUp() will exit its loop.
 * 
 * @warning Elevator will not respond to button inputs during initialization.
 * 
 * @see @c hardware.h
 * 
 */
void startUp();
/**
 * @brief 
 * 
 */
void running();
/**
 * @brief 
 * 
 */
void idle();
/**
 * @brief 
 * 
 */
void serveFloor();
/**
 * @brief 
 * 
 */
void emergency();

#endif