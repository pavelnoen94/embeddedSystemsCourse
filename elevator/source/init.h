/**
 * @file
 * @brief Contains functions for initialization prosess.
 * 
 */


/**
 * @brief Prepare the elevator for usage
 * 
 */
void init();



/**
 * @brief Get the Current Floor object
 * 
 * @return 0 if no floor sensor is active. Returns the floor number if a sensor is triggered by the time the function is called. 
 */
int getCurrentFloor();
/**
 * @brief Move elevator untill the floor is known.
 * 
 */
void findPosition();
/**
 * @brief Turn all the lights on inside the elevator. Used by inti() to indicate that a initialization prosess is active.
 * 
 */
