#ifndef ELEVATOR_SENSOR_H
#define ELEVATOR_SENSOR_H

// <insert> ModeReader leser alle sensorere relevante til den tilstanden, og oppdaterer programvariablene.

/**
 * @file
 * @brief 
 * 
 */

void updateAllSensors();
void readOrdersOnlyInside();
void readOrders();
inline void readObstruction();
inline bool activeOrderAtThisFloor();
Direction getDirection();

#endif