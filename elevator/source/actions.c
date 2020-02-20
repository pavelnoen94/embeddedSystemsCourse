#include <stdbool.h>
#include "hardware.h"
#include "elevator.h"
#include "sensor.h"
#include "actions.h"

void elevatorMove(Direction direction){
    if(direction == DOWN){
        hardware_command_movement(HARDWARE_MOVEMENT_DOWN);
        return;
    }
    if(direction == UP){
        hardware_command_movement(HARDWARE_MOVEMENT_UP);
        return;
    }
    if(direction == NONE){
        elevatorStop();
        return;
    }
}

void elevatorStop(){
    hardware_command_movement(HARDWARE_MOVEMENT_STOP);
}

void elevatorMoveTo(int targetFloor){
    if(targetFloor < 0 || targetFloor > HARDWARE_NUMBER_OF_FLOORS){
        printf("error inside elevatorMoveTo. Floor does not exsist. Requested floor: %i", targetFloor);
        exit(1);
    }
    if(lastKnownFloor == targetFloor){
        return; //TODO: not nessesarry at this floor
    }
    if(lastKnownFloor > targetFloor){
        elevatorMove(DOWN);
        while(!atSomeFloor){
            updateAllSensors();
        }
        elevatorMoveTo(targetFloor);
        return;
    }
    if(lastKnownFloor < targetFloor){
        elevatorMove(UP);
        while(!atSomeFloor){
            updateAllSensors();
        }
        elevatorMoveTo(targetFloor);
        return;
    }
}

void clearAllOrders(){
    for(int i = 0; i < HARDWARE_NUMBER_OF_FLOORS; i++){
        upOrders[i] = false;
        downOrders[i] = false;
        insideOrders[i] = false;

        hardware_command_order_light(i,HARDWARE_ORDER_UP,0);
        hardware_command_order_light(i,HARDWARE_ORDER_DOWN,0);
        hardware_command_order_light(i,HARDWARE_ORDER_INSIDE,0);
    }
}

void clearOrdersAtThisFloor(){
    // kill order lights inside
    hardware_command_order_light(lastKnownFloor,HARDWARE_ORDER_INSIDE,0);
    insideOrders[lastKnownFloor] = false;

    if(direction == DOWN){
        hardware_command_order_light(lastKnownFloor,HARDWARE_ORDER_DOWN,0);
        downOrders[lastKnownFloor] = false;
        return;
    }
    if(direction == UP){
        hardware_command_order_light(lastKnownFloor,UP,0);
        upOrders[lastKnownFloor] = false;
        return;
    }
    if(direction == NONE){
        hardware_command_order_light(lastKnownFloor,HARDWARE_ORDER_UP,0);
        hardware_command_order_light(lastKnownFloor,HARDWARE_ORDER_DOWN,0);
        upOrders[lastKnownFloor] = false;
        downOrders[lastKnownFloor] = false;
    }
}
static void clear_all_order_lights(){
    HardwareOrder order_types[3] = {
        HARDWARE_ORDER_UP,
        HARDWARE_ORDER_INSIDE,
        HARDWARE_ORDER_DOWN
    };

    for(int f = 0; f < HARDWARE_NUMBER_OF_FLOORS; f++){
        for(int i = 0; i < 3; i++){
            HardwareOrder type = order_types[i];
            hardware_command_order_light(f, type, 0);
        }
    }
}