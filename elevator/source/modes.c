#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>
#include "headers/modes.h"
#include "headers/elevator.h"
#include "headers/hardware.h"
#include "headers/interface.h"
#include "headers/modeSelector.h"

static void sigHandler(int sig) {

	switch(sig){
		case SIGSEGV:
			printf("[Warning]: Recieved Segmentation fault.\n");
			return;
		default:
			printf("Resieved signal %d, Terminating elevator\n", sig);
			hardware_command_movement(HARDWARE_MOVEMENT_STOP);
			exit(0);
	}
}

void startUp(Elevator* elevator) {
	printf("\n");
	// connect to hardware
	int error = hardware_init();
	if (error != 0) {
		fprintf(stderr, "Unable to initialize hardware\n");
		exit(1);
	}

	// clear old data
	elevator->status = UNKNOWN;
	elevator->direction = NONE;
	elevator->emergencyState = false;
	elevatorStop();
	clearAllOrders(elevator);
	closeDoor();

	// crash handling
	printf("To terminalte program press ctrl+c or type 'kill -9 %d in terminal'\n", getpid());
	signal(SIGTERM, sigHandler);
	signal(SIGKILL, sigHandler);
	signal(SIGSEGV, sigHandler);

	// find floor
	readFloorSensors(elevator);
	if (!atSomeFloor()) {
		elevatorMoveUp();
		while (!atSomeFloor()) {
			readFloorSensors(elevator);
		}
	}

	printf("\ninit complete!\n");
	elevatorStop();
}

void idle(Elevator* elevator) {
	readFloorSensors(elevator);

	while (!elevator->hasOrders) {
		getOrders(elevator);

		if(readStop() || orderAt(elevator, elevator->lastKnownFloor)){
			return;
		}
	}
}

void running(Elevator* elevator) {

	while (elevator->hasOrders) {
		// update sensors and set direction

		readFloorSensors(elevator);
		getOrders(elevator);
		findTargetFloor(elevator);
		getDirection(elevator);

		// wait untill a floor with orders is reached
		while(!atTargetFloor(elevator)){

			if(((elevator->targetFloor > elevator->lastKnownFloor) && elevator->direction == DOWN ) || ((elevator->targetFloor < elevator->lastKnownFloor) && (elevator->direction == UP))){
				printf("[Warning]: Elevator is moving in opposite direction of order.\n");
				break;
			}

			if (elevator->direction == UP) {
				elevatorMoveUp();
			}

			if (elevator->direction == DOWN) {
				elevatorMoveDown();
			}

			getOrders(elevator);
			readFloorSensors(elevator);

			if(readStop()){
				return;
			}

			findTargetFloor(elevator);
		}

		elevatorStop();
		return;
	}
}

void serveFloor(Elevator* elevator){
	if(!atSomeFloor()){
		return;
	}
	readFloorSensors(elevator);
	clearAllOrdersAtThisFloor(elevator);
	elevatorStop();
	openDoor();

	// start a timer and hold the door open for a time without obstructions
	time_t startTime = clock() / CLOCKS_PER_SEC;
	time_t start = startTime;
	time_t endTime = startTime + DOOR_OPEN_TIME;

	while (startTime < endTime){
		getOrders(elevator);

		if(readObstruction() || readStop() || orderAt(elevator, elevator->lastKnownFloor)){
			if(readStop()){
				clearAllOrders(elevator);
			}
			// reset timer
			endTime = clock() / CLOCKS_PER_SEC + DOOR_OPEN_TIME;
			clearAllOrdersAtThisFloor(elevator);
		}
		startTime = clock()/ CLOCKS_PER_SEC;
	}
	printf("The door was open for %d seconds\n", (int)(endTime - start));
	closeDoor();
	return;

}

void emergency(Elevator* elevator) {
	elevator->emergencyState = true;
	clearAllOrders(elevator);
	elevatorStop();

	while(readStop()){

	}
	return;
}
