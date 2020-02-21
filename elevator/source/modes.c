#include <stdbool.h>
#include <time.h>
#include "hardware.h"
#include "elevator.h"
#include "modes.h"
#include "actions.h"
#include "sensor.h"

void startUp(){
/*
    elevatorStop();
    int error = hardware_init();
    if(error != 0){
        fprintf(stderr, "Unable to initialize hardware\n");
        exit(1);
    }

    // standard values
    for(int i =0; i < HARDWARE_NUMBER_OF_FLOORS; i++){
        upOrders[i] = false;
        downOrders[i] = false;
        insideOrders[i] = false;
    }
    

    emergencyState = false;
    hasOrders = false;
    obstruction = false;
    atSomeFloor = false;



    clearAllOrders();
    elevatorMove(UP);
    while(!atSomeFloor){
        initModeReader();
    }
    elevatorStop();
*/
}
void running(){
    /*
    status = RUN;

    if(!hasOrders){
        direction = NONE;
        return;
    }

    if(direction == NONE){
        // direction unknown and we have an order => first order.

        if(lastKnownFloor = getTargetFloor()){
            openDoor();
            return;
        }


        for(int i = 0; i < HARDWARE_NUMBER_OF_FLOORS; i++){
            if(insideOrders[i]){
                direction = getDirection(getTargetFloor());
                return;
            }
        }

        // 



        // set direction to the floor and return
        direction = getDirection(getTargetFloor());
        return;
    }

    if(direction == UP){

        // check for orders in current direction
        for(int i = lastKnownFloor + 1; i < HARDWARE_NUMBER_OF_FLOORS; i++){
            if(insideOrders[i] || upOrders[i]){

                elevatorMoveUp();
                return;
            }

        }
        // check for orders in opposite direction
        for(int i = HARDWARE_NUMBER_OF_FLOORS - 1; i != 0; i--){
            if(insideOrders[i] || downOrders[i]){
                elevatorMoveTo(i);

                clearAllOrdersAtThisFloor();
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
                clearAllOrdersAtThisFloor();
                openDoor();
                return;
            }
        }
    }
    // no more orders. return
    return;
    */
}
void idle(){
    /*
    status = IDLE;

    while(!hasOrders){
        if(emergencyState){
            emergency();
        }
        idleModeReader();
    }
    */
}

/*
void openDoor(){
    status = OPENDOOR;

    elevatorStop();
    clearAllOrdersAtThisFloor();


    // open door and start timer
    hardware_command_door_open(1);
    int startTime = clock() * 1000 / CLOCKS_PER_SEC;
    int endTime = startTime + DOOR_OPEN_TIME*1000;


    startTime = clock() * 1000 / CLOCKS_PER_SEC;

    while (startTime < endTime){
        doorModeReader();
        if(obstruction || emergencyPressed()){
            // reset timer
            startTime = clock() * 1000 / CLOCKS_PER_SEC;

            if(emergencyState){
                emergencyState = false;
            }
        }

        

    }
    // close the door
    hardware_command_door_open(0);
    return;
}
    */
void emergency(){
    /*
    status = STOP;

    if(atSomeFloor){
        emergencyState = false;
        openDoor();
        return;
    }
    // between floors
    elevatorStop();
    clearAllOrders();
    while(!hasOrders){
        emergencyModeReader();
    }
    elevatorMoveTo(getTargetFloor());
    emergencyState = false;
    return;
    */
}