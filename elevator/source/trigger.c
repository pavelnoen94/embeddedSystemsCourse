#include <stdbool.h>
#include "elevator.h"
#include "status.h"
#include "trigger.h"

void mainLoop(){
    init();
    while(1){
        UpdateAllSensors();
        findStatus();
        callStatus();
    }
}

void findStatus(){
    if(stopButtonPressed){
        status = STOPPED;
        return;
    }
    if(!hasOrders){
        status = IDLE;
        return;
    }
    status = RUNNING;
}

void callStatus(){
    if(status == IDLE){
        idle();
        return;
    }
    if(status == RUNNING){
        running();
        return;
    }
    if(status == OPEN_DOOR){
        openDoor();
        return;
    }
    if(status == STOPPED){
        stopped();
        return;
    }
}