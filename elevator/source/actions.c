#include <stdlib.h>

void openDoor(){

}
void closeDoor(){

}

void moveElevatorUp(){

}

void moveElevatorDown(){

}
void stopElevator(){

}

void emergencyStop(){

}

void clearOrders(){
    
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

void harwareInit(){
    int error = hardware_init();
    if(error != 0){
        fprintf(stderr, "Unable to initialize hardware\n");
        exit(1);
    }
}

void findPosition(){
    // set direction upward and start moving
    hardware_command_movement(HARDWARE_MOVEMENT_UP);

    // wait for known position
    while(getCurrentFloor() == 0){

    }
    
    hardware_command_movement(HARDWARE_MOVEMENT_STOP);
}