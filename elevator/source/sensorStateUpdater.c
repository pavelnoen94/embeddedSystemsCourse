#include <error.h>
#include <stdlib.h>

#include "hardware.h"
 
#include "sensorStateUpdater.h"

/**
 * @file
 * @brief Implementation of @c sensorStateUpdater.h
 * */

int checkFloorSensors(){
    activeFloorSensors = 0;
    int* stateBuffer = malloc(sizeof(int)*HARDWARE_NUMBER_OF_FLOORS);
    for (int i = 0; i < HARDWARE_NUMBER_OF_FLOORS; i++) {
        stateBuffer[i] = hardware_read_floor_sensor(i+1);
        if (stateBuffer[i] == 1) { activeFloorSensors += 1; }
    }
    if (activeFloorSensors > 1) {
        free(stateBuffer);
        return -1;
    }
    else if (activeFloorSensors == 1)
    {
        for (int i = 0; i < HARDWARE_NUMBER_OF_FLOORS; i++) {
            if (stateBuffer[i] == 1) {lastKnownElevatorPosition = (i + 1);}
        }
        free(stateBuffer);
        return 1;
    }
    else
    {
        free(stateBuffer);
        return 0;
    }
}

int updateObstructionState(){
    int* prevState = malloc(sizeof(int));
    *prevState = obstructionSignalState;
    obstructionSignalState = hardware_read_obstruction_signal();
    if (prevState != obstructionSignalState) {free(prevState); return 1;}
    else {free(prevState); return 0;}
}

int updateStopSignalState(){
    int* prevState = malloc(sizeof(int));
    *prevState = stopSignalState;
    stopSignalState = hardware_read_stop_signal();
    if (prevState != stopSignalState) {free(prevState); return 1;}
    else {free(prevState); return 0;}
}

int readAndAddOrders() {
    int newOrdersAdded = 0;

    for (int i = 0; i < HARDWARE_NUMBER_OF_FLOORS; i++) {

        // Check outside-orders for going UP
        if (hardware_read_order((i+1), HARDWARE_ORDER_UP) == 1){
            upQueue[i] = 1;
            newOrdersAdded++;
        }

        // Check outside-orders for going DOWN
        if (hardware_read_order((i+1), HARDWARE_ORDER_DOWN) == 1) {
            downQueue[i] = 1;
            newOrdersAdded++;
        }

        // Check orders from inside elevator
        if (hardware_read_order((i+1), HARDWARE_ORDER_INSIDE) == 1) {
            newOrdersAdded++;
            if (i > lastKnownElevatorPosition) { upQueue[i] = 1; }
            else if (i < lastKnownElevatorPosition) { downQueue[i]; }
            else {
                if (currentDirection == Down) { upQueue[i] = 1; }
                else if (currentDirection == Up) { downQueue[i] = 1; }
            }
        }
    }
}

/*
 HardwareOrders:
    HARDWARE_ORDER_UP,
    HARDWARE_ORDER_INSIDE,
    HARDWARE_ORDER_DOWN
*/