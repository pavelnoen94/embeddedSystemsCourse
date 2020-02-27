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

static void sigHandler(int sig) {
  (void)(sig);
  printf("\nResieved signal %d, Terminating elevator\n", sig);
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
  signal(SIGINT, sigHandler);
  signal(SIGTERM, sigHandler);
  signal(SIGSEGV, sigHandler);

  // find floor
  updatePosition();
  if (!atSomeFloor()) {
    elevatorMoveUp();
    while (!atSomeFloor()) {
      updatePosition();
    }
  }

  printf("\ninit complete!\n");
  elevatorStop();
}

void idle() {

  while (!hasOrders) {
    getOrders();

    if(readStop() || orderAt(position.lastKnownFloor)){
      return;
    }
  }

}

void running() {

  while (hasOrders) {
    // update sensors and set direction
    getOrders();
    updatePosition();
    findTargetFloor();
    direction = getDirection(getTargetFloor());


    if (direction == UP) {
      elevatorMoveUp();
    }

    if (direction == DOWN) {
      elevatorMoveDown();
    }

    // wait untill a floor with orders is reached
    while(!atTargetFloor()){
    // while(!activeOrderThisFloor()){
      getOrders();
      updatePosition();
      if(readStop()){
        return;
      }

    }
    elevatorStop();
    return;
  }
}

void serveFloor(){
    if(!atSomeFloor()){
      return;
    }
    updatePosition();
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

    if (position.lastKnownFloor == getTargetFloor()) {
      targetReached = true;
      clearAllOrdersAtThisFloor();
      serveFloor();
    }

    if (atSomeFloor()) {
      if (direction == UP && (upOrders[position.lastKnownFloor] || insideOrders[position.lastKnownFloor])) {
      }
    }
  }
  elevatorStop();
}

void emergency() {
  clearAllOrders();
  elevatorStop();
  // find pos


  while(readStop()){

  }
  return;
}
