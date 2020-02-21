#include <stdbool.h>
#include "elevator.h"
#include "modes.h"
#include "sensor.h"
#include "actions.h"

void Elevator(){
    startUp();
    readOrders();
    readStop();

    while(true){
        readAll();
        if(emergencyState){
            emergency();
        }
        if(!hasOrders){
            idle();
        }
        running();
    }
}