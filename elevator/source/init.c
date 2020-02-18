#include "hardware.h"
#include "init.h"

void init(){
    // initialize hardware
    int error = hardware_init();
    if(error != 0){
        fprintf(stderr, "Unable to initialize hardware\n");
        exit(1);
    }
    
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

void findPosition(){
    // set direction upward and start moving
    hardware_command_movement(HARDWARE_MOVEMENT_UP);

    // wait for known position
    while(getCurrentFloor() == 0){

    }
    
    hardware_command_movement(HARDWARE_MOVEMENT_STOP);
}

void allLightsOn(){
    for(int f = 0; f < HARDWARE_NUMBER_OF_FLOORS; f++){
        for(int i = 0; i < 3; i++){
            HardwareOrder type = order_types[i];
            hardware_command_order_light(f, type, on);
        }
    }
}

void allLightsOff(){
    for(int f = 0; f < HARDWARE_NUMBER_OF_FLOORS; f++){
        for(int i = 0; i < 3; i++){
            HardwareOrder type = order_types[i];
            hardware_command_order_light(f, type, 0);
        }
    }
}