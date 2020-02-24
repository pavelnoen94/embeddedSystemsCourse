#include <stdbool.h>
#include <stdio.h>
#include <time.h>
#include <sys/types.h>
       #include <sys/wait.h>
#include "hardware.h"
#include "elevator.h"
#include "sensor.h"
#include "actions.h"
#include "routines.h"

void serveFloor(){
    if(!atSomeFloor()){
        return;
    }
    status = OPENDOOR;
    elevatorStop();
    openDoor();

    // start a timer and hold the door open for a time without obstructions
    time_t startTime = clock() / CLOCKS_PER_SEC;
    time_t start = startTime;
    time_t endTime = startTime + DOOR_OPEN_TIME;
    
    
    while (startTime < endTime){
        getOrders();

        if(readObstruction() || readStop() || orderAt(getLastKnownFloor())){
            // reset timer
            endTime = clock() / CLOCKS_PER_SEC + DOOR_OPEN_TIME;
            clearAllOrdersAtThisFloor();
        }
        startTime = clock()/ CLOCKS_PER_SEC;
        wait(2);
    }
    printf("The door was open for %d seconds\n", (int)(endTime - start));
    closeDoor();
    return;

}
