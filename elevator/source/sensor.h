#ifndef ELEVATOR_SENSOR_H
#define ELEVATOR_SENSOR_H

// <insert> ModeReader leser alle sensorere relevante til den tilstanden, og oppdaterer programvariablene.

/**
 * @file
 * @brief contains functions that reads sensors
 * 
 */

bool readObstruction();
bool readStop();
#endif
