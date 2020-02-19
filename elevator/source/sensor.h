#ifndef ELEVATOR_SENSOR_H
#define ELEVATOR_SENSOR_H

void updateAllSensors();
void readOrdersOnlyInside();
void readOrdersOnly();
inline void readObstruction();
inline bool activeOrderAtThisFloor();
Direction getDirection();

#endif