#include <stdbool.h>
#include "hardware.h"
#include "elevator.h"
#include "modes.h"
#include "actions.h"
#include "sensor.h"
#include <time.h>

void startUp(){
    int error = hardware_init();
    if(error != 0){
        fprintf(stderr, "Unable to initialize hardware\n");
        exit(1);
    }

    clear_all_order_lights();
    elevatorMove(UP);
    while(!atSomeFloor){
        initModeReader();
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
            runningModeReader();
            if(stopButtonPressed){
                emergency();
            }
        }
        // floor reached
        clearOrders();
        openDoor();
        return;
    }

    elevatorMove(direction);
    while(!atSomeFloor){
        runningModeReader();
        if(stopButtonPressed){
            emergency();
            return;
        }
    }
    clearOrders();
    openDoor();

    // check if there is any orders left

    if(direction == UP){
        // check for orders in current direction
        for(int i = lastKnownFloor + 1; i < HARDWARE_NUMBER_OF_FLOORS; i++){
            if(upOrders[i] || insideOrders[i]){
                return;
            }
        }
        // check for orders in oposite direction
        for(int i = HARDWARE_NUMBER_OF_FLOORS - 1; i != 0; i--){
            if(downOrders[i] || insideOrders[i]){
                elevatorMoveTo(i);
                direction = DOWN;
                clearOrders();
                return;
            }
        }
    }
    if(direction == DOWN){
        {
            // check for orders in current direction
            int i = lastKnownFloor - 1;
            if(i != 0){
                for( ; i != 0; i--){
                    if(downOrders[i] || insideOrders[i]){
                        return;
                        }
                    }
            }
        }
        // check for orders in oposite direction
        for(int i = 0; i < HARDWARE_NUMBER_OF_FLOORS; i++){
            if(upOrders[i] || insideOrders[i]){
                elevatorMoveTo(i);
                direction = UP;
                clearOrders();
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
        if(stopButtonPressed){
            emergency();
        }
        idleModeReader();
    }
}

void openDoor(){

    elevatorStop();
    clearOrders();

    // start a timer and open the door open
    hardware_command_door_open(1);
    time_t timer_start = clock();
    time_t timer_end = clock();

    // wait 3 sec without obstructions
    while(DOOR_OPEN_TIME > ((timer_end - timer_start)/CLOCKS_PER_SEC)){
        doorModeReader();
        if(obstruction || stopButtonPressed){
            if(stopButtonPressed){
                stopButtonPressed = false;
            }
            timer_start = clock();
        }
        timer_end = clock();
    }

    // close the door
    hardware_command_door_open(0);
    return;

}
void emergency(){

    if(atSomeFloor){
        stopButtonPressed = false;
        openDoor();
        return;
    }
    // between floors
    elevatorStop();
    clearAllOrders();
    while(!hasOrders){
        emergencyModeReader();
    }
    for(int i = 0; i < HARDWARE_NUMBER_OF_FLOORS; i++){
        if(insideOrders[i]){
            elevatorMoveTo(i);
        }
    }
    openDoor();
    return;
}