#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include "hardware.h"
#include "elevator.h"

static void clear_all_order_lights(){
    
    for(int f = 0; f < HARDWARE_NUMBER_OF_FLOORS; f++){
        for(int i = 0; i < 3; i++){
            HardwareOrder type = order_types[i];
            hardware_command_order_light(f, type, OFF);
        }
    }
}

static void sigint_handler(int sig){
    (void)(sig);
    printf("Terminating elevator\n");
    hardware_command_movement(HARDWARE_MOVEMENT_STOP);
    exit(0);
}

void init(){
    // Turn all the lights on

    for(int f = 0; f < HARDWARE_NUMBER_OF_FLOORS; f++){
        for(int i = 0; i < 3; i++){
            HardwareOrder type = order_types[i];
            hardware_command_order_light(f, type, ON);
        }
    }



}

void start(){
    if(!initalized){
        init();
    }


}