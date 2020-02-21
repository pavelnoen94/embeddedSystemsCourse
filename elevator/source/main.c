#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>
#include "hardware.h"
#include "routines.h"
#include "actions.h"
#include "modes.h"
#include "sensor.h"

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
    // signal(SIGTERM, sigint_handler);
    signal(SIGSEGV, sigint_handler);

    startUp();
    printf("\ninit complete!\n");
    printf("\ni know I'm at floor %d\n", lastKnownFloor + 1);

    while(1){
        
        idle();
        serving();

    }

    return 0;
}

