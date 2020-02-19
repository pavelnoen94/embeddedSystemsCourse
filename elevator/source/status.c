#include <stdbool.h>
#include "hardware.h"
#include "elevator.h"
#include "status.h"

void init(){
    int error = hardware_init();
    if(error != 0){
        fprintf(stderr, "Unable to initialize hardware\n");
        exit(1);
    }

    signal(SIGINT, sigint_handler);

    clear_all_order_lights();
    elevatorMove(UP);
    while(!atSomeFloor){
        updateAllSensors();
    }
}
void running(){
    if(!hasOrders){
        direction = NONE;
        return;
    }
    if(direction == NONE){
        // direction unknown and we have an order
        elevatorMove(getDirection());
        while(!atSomeFloor){
            updateAllSensors();
        }
        // floor reached
        clearOrdersAtThisFloor();
        openDoor();
        return;
    }

    elevatorMove(direction);
    while(!atSomeFloor){
        updateAllSensors();
    }
    clearOrdersAtThisFloor();
    openDoor();

    // check if there is any orders left

    if(direction == UP){
        for(int i = lastKnownFloor + 1; i < HARDWARE_NUMBER_OF_FLOORS; i++){
            if(upOrders[i] || insideOrders[i]){
                return;
            }
        }
        for(int i = HARDWARE_NUMBER_OF_FLOORS - 1; i != 0; i--){
            if(downOrders[i] || insideOrders[i]){
                elevatorMoveTo(i);
                direction = DOWN;
                clearOrdersAtThisFloor();
                return;
            }
        }
    }
    if(direction == DOWN){
        if(i != 0){
            for(int i = lastKnownFloor - 1; i != 0; i--){
                if(downOrders[i] || insideOrders[i]){
                    return;
                }
            }
        }
        for(int i = 0; i < HARDWARE_NUMBER_OF_FLOORS; i++){
            if(upOrders[i] || insideOrders[i]){
                elevatorMoveTo(i);
                direction = UP;
                clearOrdersAtThisFloor();
                openDoor();
                return;
            }
        }
    }
    // no more orders. return
    return;
}
void idle(){
    while(!hasOrders){
        updateAllSensors();
    }
}
void openDoor(){

    elevatorStop();
    clearOrdersAtThisFloor();

    // start a timer and open the door open
    hardware_command_door_open(1);
    time_t timer_start = clock();
    time_t timer_end = clock();

    // wait 3 sec without obstruction
    while(DOOR_OPEN_TIME > ((timer_end - timer_start)/CLOCKS_PER_SEC)){
        readObstruction();
        readOrdersOnly();
        if(obstruction){
            timer_start = clock();
        }
        timer_end = clock();
    }

    // close the door
    hardware_command_door_open(0);
    return;

}
void stopped(){

    if(atSomeFloor){
        openDoor();
        return;
    }
    // between floors
    elevatorStop();
    clearAllOrders();
    while(!hasOrders){
        readOrdersOnlyInside();
    }
    for(int i = 0; i < HARDWARE_NUMBER_OF_FLOORS; i++){
        if(insideOrders[i]){
            elevatorMoveTo(i);
        }
    }
    openDoor();
    return;
}