#include <stdbool.h>
#include "hardware.h"
#include "elevator.h"
#include "sensor.h"

void updateAllSensors(){
    stopButtonPressed = stopButtonPressed || hardware_read_stop_signal();
    readObstruction();
    hasOrders = false;

    for(int i = 0; i < HARDWARE_NUMBER_OF_FLOORS; i++){

        // read order buttons
        upOrders[i] = upOrders[i] || hardware_read_order(i,HARDWARE_ORDER_UP);
        downOrders[i] = downOrders[i] || hardware_read_order(i,HARDWARE_ORDER_DOWN);
        insideOrders[i] = insideOrders[i] || hardware_read_order(i,HARDWARE_ORDER_INSIDE);

        // register orders
        hasOrders = hasOrders || upOrders[i];
        hasOrders = hasOrders || downOrders[i];
        hasOrders = hasOrders || insideOrders[i];

        // read floor sensors
        if(hardware_read_floor_sensor(i)){
            atSomeFloor = true;
            lastKnownFloor = i;
            hardware_command_floor_indicator_on(i);
        }else{
            atSomeFloor = false;
        }
    }
}

void readOrdersOnlyInside(){
    for(int i = 0; i < HARDWARE_NUMBER_OF_FLOORS; i++){
        insideOrders[i] = insideOrders[i] || hardware_read_order(i,HARDWARE_ORDER_INSIDE);
        hasOrders = hasOrders || insideOrders[i];
    }
}

void readOrdersOnly(){
    hasOrders = false;
    for(int i = 0; i < HARDWARE_NUMBER_OF_FLOORS; i++){
        // read order buttons
        upOrders[i] = upOrders[i] || hardware_read_order(i,HARDWARE_ORDER_UP);
        downOrders[i] = downOrders[i] || hardware_read_order(i,HARDWARE_ORDER_DOWN);
        insideOrders[i] = insideOrders[i] || hardware_read_order(i,HARDWARE_ORDER_INSIDE);

        // register orders
        hasOrders = hasOrders || upOrders[i];
        hasOrders = hasOrders || downOrders[i];
        hasOrders = hasOrders || insideOrders[i];
    }
}

inline void readObstruction(){
    obstruction = hardware_read_obstruction_signal();
}

inline bool activeOrderAtThisFloor(){
    return upOrders[lastKnownFloor] || downOrders[lastknownFloor] || insideOrders[lastKnownFloor];
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