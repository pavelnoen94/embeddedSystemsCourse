#include <stdbool.h>
#include <signal.h>
#include <time.h>
#include "hardware.h"
#include "elevator.h"
#include "modes.h"
#include "actions.h"
#include "sensor.h"
#include "routines.h"
#include "reader.h"

static void sigint_handler(int sig){
    (void)(sig);
    printf("\nResieved terminating signal %d, Terminating elevator\n", sig);
    hardware_command_movement(HARDWARE_MOVEMENT_STOP);
    exit(0);
}

void startUp(){
    // connect to hardware
    int error = hardware_init();
    if(error != 0){
        fprintf(stderr, "Unable to initialize hardware\n");
        exit(1);
    }

    elevatorStop();
    
    // crash handling
    printf("\nTo terminalte program press ctrl+c or type 'kill -9 %d'\n", getpid());
    signal(SIGINT, sigint_handler);
    signal(SIGTERM, sigint_handler);
    signal(SIGSEGV, sigint_handler);

    // find floor
    readFloorSensors();
    if(!atSomeFloor()){
        elevatorMoveUp();
        while(!atSomeFloor()){
            readFloorSensors();
        }
    }

    printf("\ninit complete!\n");
    elevatorStop();
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
    if(!isValidFloor(floor)){
        printf("\nError: invalid argument in gotoFloor(%d)\n", floor);
    }
    status = MOVING;

    setTargetFloor(floor);
    direction = getDirection(getTargetFloor());

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
        readFloorSensors();
        getOrders();

        if(lastKnownFloor == getTargetFloor()){
            targetReached = true;
            clearAllOrdersAtThisFloor();
            serveFloor();
        }


        if(atSomeFloor()){
            if(direction == UP && (upOrders[lastKnownFloor] || insideOrders[lastKnownFloor])){
                
            }
        }

    }
    elevatorStop();
    
}

void emergency(){

    if(atSomeFloor()){
        openDoor();
        return;
    }

    // between floors
    elevatorStop();
    status = STOP;
    clearAllOrders();

    while(!hasOrders){
        emergencyModeReader();
    }
    elevatorMoveTo(getTargetFloor());
    status = IDLE;
    return;
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