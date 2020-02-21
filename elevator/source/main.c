#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>
#include "hardware.h"
#include "routines.h"

static void sigint_handler(int sig){
    (void)(sig);
    printf("\nResieved terminating signal %d, Terminating elevator\n", sig);
    hardware_command_movement(HARDWARE_MOVEMENT_STOP);
    exit(0);
}

int main(){
    printf("\nmy pid is: %d\n", getpid());

    // termination and crash handlers
    signal(SIGINT, sigint_handler);
    signal(SIGTERM, sigint_handler);
    signal(SIGSEGV, sigint_handler);

    elevatorStop();
    int error = hardware_init();
    if(error != 0){
        fprintf(stderr, "Unable to initialize hardware\n");
        exit(1);
    }

    elevatorMoveUp();
    while(1){
        readFloorSensors();
        if(onFloor(3)){
            elevatorMoveDown();
        }
        if(onFloor(0)){
            elevatorMoveUp();
        }  
    }

    return 0;
}

