#include "headers/elevator.h"
#include "headers/modeSelector.h"
#include "headers/modes.h"
#include "headers/interface.h"

void modeSelector(){

    startUp();
    status = IDLE;
    while(1){

        if(status == UNKNOWN){
            // find the perfect status
            

            continue;
        }
        if(status == IDLE){
            // loop
            idle();
            status = UNKNOWN;
            continue;
        }

        if(status == SERVING){
            // loop

            status = UNKNOWN;
            continue;
        }
        
        if(status == RUNNING) {
            // loop

            status = UNKNOWN;

            continue;
        }
        
        if(status == STOP) {
            // loop
            emergency();
            status = UNKNOWN;
            continue;
        }

        status = UNKNOWN;
    }
}

void selectorUnknown(){
    getOrders();
    
}
void selectorIdle(){

}
void selectorServing(){

}
void selectorMoving(){

}
void selectorStop(){

}


