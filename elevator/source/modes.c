#include <signal.h>
#include <stdbool.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>
#include "headers/modes.h"
#include "headers/elevator.h"
#include "headers/hardware.h"
#include "headers/modeReaders.h"
#include "headers/interface.h"
#include "headers/modeSelector.h"

static void sigint_handler(int sig) {
  (void)(sig);
  printf("\nResieved terminating signal %d, Terminating elevator\n", sig);
  hardware_command_movement(HARDWARE_MOVEMENT_STOP);
  exit(0);
}

void startUp() {
  // connect to hardware
  int error = hardware_init();
  if (error != 0) {
    fprintf(stderr, "Unable to initialize hardware\n");
    exit(1);
  }

  elevatorStop();
  clearAllOrders();
  closeDoor();

  // crash handling
  printf("\nTo terminalte program press ctrl+c or type 'kill -9 %d in terminal'\n", getpid());
  signal(SIGINT, sigint_handler);
  signal(SIGTERM, sigint_handler);
  signal(SIGSEGV, sigint_handler);

  // find floor
  readFloorSensors();
  if (!atSomeFloor()) {
    elevatorMoveUp();
    while (!atSomeFloor()) {
      readFloorSensors();
    }
  }
  
  printf("\ninit complete!\n");
  elevatorStop();
}

void idle() {

  while (!hasOrders) {
    getOrders();
    
    if(readStop() || orderAt(lastKnownFloor)){
      return;
    }
  }
  
}

void running() {

  while (hasOrders) {
    getOrders();
    readFloorSensors();
    findTargetFloor();
    //gotoFloor(targetFloor);

    direction = getDirection(getTargetFloor());

    if (direction == UP) {
      elevatorMoveUp();
    }

    if (direction == DOWN) {
      elevatorMoveDown();
    }

    if (direction == NONE) {
      return;
    }

    while(!atSomeFloor()){
      runningModeReader();
      if(readStop()){
        return;
      }

    }
    return;
  }
}

void serveFloor(){
    if(!atSomeFloor()){
      return;
    }
    readFloorSensors();
    clearAllOrdersAtThisFloor();
    elevatorStop();
    openDoor();

    // start a timer and hold the door open for a time without obstructions
    time_t startTime = clock() / CLOCKS_PER_SEC;
    time_t start = startTime;
    time_t endTime = startTime + DOOR_OPEN_TIME;
    
    
    while (startTime < endTime){
        getOrders();

        if(readObstruction() || readStop() || orderAt(getLastKnownFloor())){
            // reset timer
            endTime = clock() / CLOCKS_PER_SEC + DOOR_OPEN_TIME;
            clearAllOrdersAtThisFloor();
        }
        startTime = clock()/ CLOCKS_PER_SEC;
    }
    printf("The door was open for %d seconds\n", (int)(endTime - start));
    closeDoor();
    return;

}

void gotoFloor(int floor) {
  if (!isValidFloor(floor)) {
    printf("\nError: invalid argument in gotoFloor(%d)\n", floor);
  }

  setTargetFloor(floor);
  direction = getDirection(getTargetFloor());

  if (direction == UP) {
    elevatorMoveUp();
  }

  if (direction == DOWN) {
    elevatorMoveDown();
  }

  if (direction == NONE) {
    serveFloor();
  }

  bool targetReached = false;
  while (!targetReached) {
    readFloorSensors();
    getOrders();

    if (lastKnownFloor == getTargetFloor()) {
      targetReached = true;
      clearAllOrdersAtThisFloor();
      serveFloor();
    }

    if (atSomeFloor()) {
      if (direction == UP && (upOrders[lastKnownFloor] || insideOrders[lastKnownFloor])) {
      }
    }
  }
  elevatorStop();
}

void emergency() {
  clearAllOrders();
  elevatorStop();
  while(readStop()){

  }
  return;
}
