#include <stdbool.h>
#include "elevator.h"
#include "modes.h"
#include "sensor.h"

void Elevator(){
    init();
    while(true){
        updateAllSensors();
        
        if(stopButtonPressed){
            stopped();
            return;
        }
        if(!hasOrders){
            idle();
            return;
        }
        running();
    }
}