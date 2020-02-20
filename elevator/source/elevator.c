#include <stdbool.h>
#include "elevator.h"
#include "modes.h"
#include "sensor.h"
#include "actions.h"

void Elevator(){
    startUp();
    while(true){
        readAll();
        
        if(emergencyState){
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