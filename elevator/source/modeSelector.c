#include "headers/elevator.h"
#include "headers/modeSelector.h"
#include "headers/modes.h"
#include "headers/interface.h"

void modeSelector(){

    startUp();
    static Status status = IDLE;   
    direction = NONE;
    while(1){

        if(status == UNKNOWN){
            // find the perfect status
            if(readStop()){
                status = STOP;
                continue;
            }
            getOrders();
            findTargetFloor();


            if(hasOrders && atTargetFloor()) {
                status = SERVING;
                continue;
            }
            if (hasOrders) {
                status = RUNNING;
                continue;
            }
            status = IDLE;
            continue;
        }
        if(status == IDLE){

            idle();
            status = UNKNOWN;
            continue;
        }

        if(status == SERVING){

            serveFloor();
            status = UNKNOWN;
            continue;
        }
        
        if(status == RUNNING) {

            running();
            status = UNKNOWN;

            continue; // direction is set and some floor is reached
        }
        
        if(status == STOP) {

            emergency();
            status = UNKNOWN;
            continue;
        }

        status = UNKNOWN;
    }
}
