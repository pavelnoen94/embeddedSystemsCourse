#ifndef ELEVATOR_MODES_H
#define ELEVATOR_MODES_H

/**
 * @file
 * @brief 
 * 
 */

void startUp();
void running();
void idle();
void serveFloor();
void gotoFloor(int floor);
void emergency();

#endif