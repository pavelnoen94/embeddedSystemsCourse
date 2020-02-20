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
void readAll()
{
    readObstruction();
    readOrders();
    readStop();
    updateStopButtonLight();
    readFloorSensors();
}

void readOrders(){
    for(int i = 0; i < HARDWARE_NUMBER_OF_FLOORS; i++){

        // read order buttons
        upOrders[i] = upOrders[i] || hardware_read_order(i,HARDWARE_ORDER_UP);
        downOrders[i] = downOrders[i] || hardware_read_order(i,HARDWARE_ORDER_DOWN);
        insideOrders[i] = insideOrders[i] || hardware_read_order(i,HARDWARE_ORDER_INSIDE);

        hardware_command_order_light(i,HARDWARE_ORDER_UP, upOrders[i]);
        hardware_command_order_light(i,HARDWARE_ORDER_INSIDE, insideOrders[i]);
        hardware_command_order_light(i,HARDWARE_ORDER_DOWN, downOrders[i]);


        // register orders
        hasOrders = hasOrders || upOrders[i] || insideOrders[i] || downOrders[i];
    }
}

void readObstruction(){
    obstruction = hardware_read_obstruction_signal();
}

void readStop(){
    emergencyState = emergencyState || hardware_read_stop_signal();
}

void readFloorSensors(){
    atSomeFloor = false;
    for(int i = 0; i < HARDWARE_NUMBER_OF_FLOORS; i++){

        // read floor sensors
        if(hardware_read_floor_sensor(i)){
            printf("i'm at floor %i\n", i+1);
            atSomeFloor = true;
            lastKnownFloor = i;
            hardware_command_floor_indicator_on(i);
            return;
        }

    }
}
//************************************//

inline bool activeOrderThisFloor(){
    return upOrders[lastKnownFloor] || downOrders[lastKnownFloor] || insideOrders[lastKnownFloor];
}

void updateStopButtonLight(){
    hardware_command_stop_light(emergencyState = false);
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