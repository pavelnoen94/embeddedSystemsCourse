#ifndef ELEVATOR_SENSOR_H
#define ELEVATOR_SENSOR_H

// <insert> ModeReader leser alle sensorere relevante til den tilstanden, og oppdaterer programvariablene.

/**
 * @file
 * @brief contains functions that reads sensors
 * 
 */

void initModeReader();
void idleModeReader();
void runningModeReader();
void emergencyModeReader();
void doorModeReader();
void readOrders();
void readObstruction();
void readStop();
void readFloorSensors();
inline bool activeOrderThisFloor();
void updateStopButtonLight();
Direction getDirection();
#endif
