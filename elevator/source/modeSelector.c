#include "headers/elevator.h"
#include "headers/modeSelector.h"
#include "headers/modes.h"
#include "headers/interface.h"

void modeSelector(){
    Elevator elevator;
    startUp(&elevator);

    while(1){
        if(elevator.status == UNKNOWN){
            getOrders(&elevator);
            findTargetFloor(&elevator);

            if(readStop() && atSomeFloor()){
                clearAllOrders(&elevator);
                elevator.status = SERVING;
                continue;
            }

            if(readStop()){
                elevator.status = STOP;
                continue;
            }

            if(elevator.hasOrders && atTargetFloor(&elevator)) {
                elevator.status = SERVING;
                continue;
            }

            if (elevator.hasOrders) {
                elevator.status = RUNNING;
                continue;
            }

            elevator.status = IDLE;
            continue;
        }

        if(elevator.status == IDLE){
            idle(&elevator);
            elevator.status = UNKNOWN;
            continue;
        }

        if(elevator.status == SERVING){
            serveFloor(&elevator);
            elevator.status = UNKNOWN;
            continue;
        }

        if(elevator.status == RUNNING){
            running(&elevator);
            elevator.status = UNKNOWN;
            continue;
        }

        if(elevator.status == STOP){
            emergency(&elevator);
            elevator.status = UNKNOWN;
            continue;
        }

    elevator.status = UNKNOWN;
    }
}
