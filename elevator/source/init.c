#include "hardware.h"
#include "init.h"
#include "actions.h"


void init(){
    hardwareInit();
    
    // Check if position is known at boot
    if(getCurrentFloor() != 0){
       hardware_command_floor_indicator_on(lastKnownElevatorPosition);
       return;
    }

    allLigthsOn();
    findPosition();
    allLightsOff();
    hardware_command_floor_indicator_on(lastKnownElevatorPosition);

}

int getCurrentFloor(){
    int knownFloor = 0;
    for(int i = 1; i < HARDWARE_NUMBER_OF_FLOORS; i++){
        knownFloor = hardware_read_floor_sensor(i);
        if(knownFloor != 0){
            lastKnownElevatorPosition = knownFloor;
            return knownFloor;
        }
    }

    return 0; // floor unknown
}

