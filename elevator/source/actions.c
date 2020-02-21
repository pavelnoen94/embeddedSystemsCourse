#include <stdbool.h>
#include <time.h>
#include "hardware.h"
#include "elevator.h"
#include "sensor.h"
#include "actions.h"

void elevatorMoveTo(int targetFloor){
    if(lastKnownFloor == targetFloor){
        openDoor();
        return;
    }

    while(lastKnownFloor != targetFloor){
        targetFloor > lastKnownFloor ? elevatorMoveUp() : elevatorMoveDown();
    }
}

void elevatorMoveUp(){
    
    // move to next floor
    hardware_command_movement(HARDWARE_MOVEMENT_UP);
    int lastFloor = lastKnownFloor;
    while(lastFloor == lastKnownFloor){
            readStop();
        if(emergencyState){
            emergency();
            return;
        }else{
            
        
        readFloorSensors();
            readOrders();
        }
    }
    // floor reached
    if(insideOrders[lastKnownFloor] || downOrders[lastKnownFloor] || insideOrders[lastKnownFloor]){
        clearAllOrdersAtThisFloor();
        openDoor();
    }
    hardware_command_movement(HARDWARE_MOVEMENT_STOP);
}

void elevatorMoveDown(int numberOfFloors){
    if(numberOfFloors < 1){
        printf("Error: elevatorMoveDown called with illegal argument %d", numberOfFloors);
        exit(1);
    }
    
    hardware_command_movement(HARDWARE_MOVEMENT_DOWN);
    int targetFloor = lastKnownFloor - numberOfFloors;

    // move to next floor
    while(targetFloor != lastKnownFloor){
        readAll();
    }
    // floor reached
    
    if(insideOrders[lastKnownFloor] || downOrders[lastKnownFloor] || insideOrders[lastKnownFloor]){
        clearAllOrdersAtThisFloor();
        openDoor();
    }
    hardware_command_movement(HARDWARE_MOVEMENT_STOP);
}



void serveFloor(){
    if(!onAFloor()){
        return;
    }
    elevatorStop();
    openDoor();

    // start a timer and hold the door open for a time without obstructions
    time_t startTime = clock() * 1000 / CLOCKS_PER_SEC;
    time_t endTime = startTime + DOOR_OPEN_TIME*1000;
    while (startTime < endTime){
        getOrders();

        if(readObstruction() || readStop()){
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