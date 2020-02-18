/**
 * @file actions.h
 * @author Pavel Skipenes (pavelgs@stud.ntnu.no)
 * @brief 
 * @version 0.1
 * @date 2020-02-18
 * 
 * 
 */

void stopElevator();
void openDoor();
void closeDoor();
void moveElevatorUp();
void moveElevatorDown();
void emergencyStop();
void clearOrders();
void allLightsOn();
void allLightsOff();
#ifndef DOXYGEN_SKIP
/**
 * @brief Checks the connection with the hardware. Terminates the program on communication error.
 * 
 */
#endif
void hardwareInit();
#ifndef DOXYGEN_SKIP
/**
 * @brief Finds the position of the elevator. Called interanlly on Boot
 * 
 */
#endif
void findPosition();