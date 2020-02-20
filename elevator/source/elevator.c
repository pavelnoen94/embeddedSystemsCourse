#include <stdbool.h>
#include "elevator.h"
#include "modes.h"
#include "sensor.h"

void Elevator(){
    startUp();
    while(true){
        updateAllSensors();
        
        if(stopButtonPressed){
            emergency();
            return;
        }
        if(!hasOrders){
            idle();
            return;
        }
        running();
    }
}