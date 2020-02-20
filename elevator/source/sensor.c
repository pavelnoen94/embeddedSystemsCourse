#include <stdbool.h>
#include "hardware.h"
#include "elevator.h"
#include "sensor.h"

void initModeReader(){
    readFloorSensors();
    updateStopButtonLight();
}

void idleModeReader(){
    readOrders();
    readStop();
    updateStopButtonLight();
}

void runningModeReader(){
    readOrders();
    readStop();
    readFloorSensors();
    updateStopButtonLight();
}

void emergencyModeReader(){
    readOrders();
    readStop();
    updateStopButtonLight();
}

void doorModeReader(){
    readObstruction();
    readStop();
    updateStopButtonLight();
}

//************************************//

void readOrders(){
    for(int i = 0; i < HARDWARE_NUMBER_OF_FLOORS; i++){

        // read order buttons
        upOrders[i] = upOrders[i] || hardware_read_order(i,HARDWARE_ORDER_UP);
        downOrders[i] = downOrders[i] || hardware_read_order(i,HARDWARE_ORDER_DOWN);
        insideOrders[i] = insideOrders[i] || hardware_read_order(i,HARDWARE_ORDER_INSIDE);

        // register orders
        hasOrders = hasOrders || upOrders[i] || insideOrders[i] || downOrders[i];
    }
}

void readObstruction(){
    obstruction = hardware_read_obstruction_signal();
}

void readStop(){
    stopButtonPressed = stopButtonPressed || hardware_read_stop_signal(); // TODO: Change variable name to stopSignalSet
}

void readFloorSensors(){
    for(int i = 0; i < HARDWARE_NUMBER_OF_FLOORS; i++){

        // read floor sensors
        if(hardware_read_floor_sensor(i)){
            atSomeFloor = true;
            lastKnownFloor = i;
            hardware_command_floor_indicator_on(i);
        }
    }
}
//************************************//

inline bool activeOrderThisFloor(){
    return upOrders[lastKnownFloor] || downOrders[lastKnownFloor] || insideOrders[lastKnownFloor];
}

void updateStopButtonLight(){
    hardware_command_stop_light(stopButtonPressed);
}

Direction getDirection(){
    for(int i = 0; i < HARDWARE_NUMBER_OF_FLOORS; i++){
        if(upOrders[i] || downOrders[i] || insideOrders[i]){
            if(lastKnownFloor < i){
                return UP;
            }
            return DOWN;
        }
    }
    return NONE;
}