#ifndef ELEVATOR_MODES_H
#define ELEVATOR_MODES_H

/**
 * @file
 * @brief 
 * 
 */

void startUp();
void serving();
void idle();
void gotoFloor(int floor);
void openDoor();
void emergency();

#endif