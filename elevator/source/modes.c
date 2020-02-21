#include <stdbool.h>
#include <time.h>
#include "hardware.h"
#include "elevator.h"
#include "modes.h"
#include "actions.h"
#include "sensor.h"
#include "routines.h"
#include "reader.h"

void startUp(){
    elevatorStop();
    int error = hardware_init();
    if(error != 0){
        fprintf(stderr, "Unable to initialize hardware\n");
        exit(1);
    }

    // init
    readFloorSensors();
    if(!atSomeFloor()){
        elevatorMoveUp();
        while(!atSomeFloor()){
            readFloorSensors();
        }
    }
    elevatorStop(); // location known, init complete
}

void idle(){
    printf("idle()");
    status = IDLE;
    while(!hasOrders){
        getOrders();
        readStop();
    }
}

void serving(){
    printf("serving()\n");
    status = SERVING;
    while(hasOrders){
        getOrders();
        findTargetFloor();        
        gotoFloor(targetFloor);
        clearAllOrdersAtThisFloor();
        readStop();
    }
}

void gotoFloor(int floor){
    printf("gotoFloor(%d)\n",floor);
    status = MOVING;
    if(!isValidFloor(floor)){
        printf("Error: invalid argument in gotoFloor(%d)\n", floor);
    }
    targetFloor = floor;
    direction = getDirection(targetFloor);

    if(direction == UP){
        elevatorMoveUp();
    }
    if(direction == DOWN){
        elevatorMoveDown();
    }
    if(direction == NONE){
        return;
    }
    bool targetReached = false;
    while(!targetReached){
       goToFloorReader();

        if(lastKnownFloor == targetFloor){
            targetReached = true;
        }

        if(atSomeFloor()){
            clearAllOrdersAtThisFloor();
        }

    }
    elevatorStop();
    
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