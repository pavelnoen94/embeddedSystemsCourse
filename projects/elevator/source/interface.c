#include <stdbool.h>
#include "headers/hardware.h"
#include "headers/elevator.h"
#include "headers/interface.h"
#include "headers/modes.h"

static void flipDir(Elevator* elevator);
static bool onFloor(int floor);

static void flipDir(Elevator* elevator){
    if(elevator->direction == UP){
        elevator->direction = DOWN;
        elevator->lastKnownFloor++;
        return;
    }

    elevator->direction = UP;
    elevator->lastKnownFloor--;
}

bool atSomeFloor(){
    for(int i = 0; i < HARDWARE_NUMBER_OF_FLOORS; i++){
        if(onFloor(i)){
            return true;
        }
    }

    return false;
}

bool atTargetFloor(Elevator* elevator) {
    return onFloor(elevator->targetFloor);
}

static bool onFloor(int floor){
    return hardware_read_floor_sensor(floor);
}

bool orderAt(Elevator* e, int floor){
    updateOrders(e);
    return e->insideOrders[floor] || e->upOrders[floor] || e->downOrders[floor];
}

bool readObstruction(){
    return hardware_read_obstruction_signal();
}

bool readStop(){
    hardware_command_stop_light(hardware_read_stop_signal());
    return hardware_read_stop_signal();
}

void updateDirection(Elevator* e){
    // target is on this floor
    if(e->targetFloor == e->lastKnownFloor && atSomeFloor()){
        e->direction = NONE;
        return;

    }

    // target is above
    if(e->targetFloor > e->lastKnownFloor){
        if(e->direction == DOWN){
            flipDir(e);
            return;

        }
        e->direction = UP;
        return;

    }

    // target is below
    if(e->targetFloor < e->lastKnownFloor){
        if(e->direction == UP){
            flipDir(e);
            return;

        }
        e->direction = DOWN;
        return;

    }

    // target is last floor
    if(e->emergencyState && e->targetFloor == e->lastKnownFloor){
        e->emergencyState = false;
        flipDir(e);
        return;

    }
}

void clearAllOrders(Elevator* e){
    for(int i = 0; i < HARDWARE_NUMBER_OF_FLOORS; i++){
        e->upOrders[i] = false;
        e->downOrders[i] = false;
        e->insideOrders[i] = false;

        hardware_command_order_light(i,HARDWARE_ORDER_UP,0);
        hardware_command_order_light(i,HARDWARE_ORDER_DOWN,0);
        hardware_command_order_light(i,HARDWARE_ORDER_INSIDE,0);
    }

    e->hasOrders = false;
}

void clearAllOrdersAtThisFloor(Elevator* e){
    e->upOrders[e->lastKnownFloor] = false;
    e->downOrders[e->lastKnownFloor] = false;
    e->insideOrders[e->lastKnownFloor] = false;
}

void closeDoor(){
    hardware_command_door_open(false);
}

void elevatorMoveDown(){
    hardware_command_movement(HARDWARE_MOVEMENT_DOWN);
}

void elevatorMoveUp(){
    hardware_command_movement(HARDWARE_MOVEMENT_UP);
}

void elevatorStop(){
    hardware_command_movement(HARDWARE_MOVEMENT_STOP);
}

void findTargetFloor(Elevator* elevator){
    // scan all floors on new search
    if(elevator->direction == NONE || elevator->emergencyState){
        for(int i = 0; i < HARDWARE_NUMBER_OF_FLOORS; i++){
            if(elevator->upOrders[i] || elevator->downOrders[i] || elevator->insideOrders[i]){
                elevator->targetFloor = i;
                return;
            }
        }
    return;

    }

    // scan floors upwards and then downwards
    if(elevator->direction == UP){
        for(int i = elevator->lastKnownFloor; i < HARDWARE_NUMBER_OF_FLOORS; i++){
            if(elevator->upOrders[i] || elevator->insideOrders[i]){
                elevator->targetFloor = i;
                return;
            }
        }
        for(int i = HARDWARE_NUMBER_OF_FLOORS - 1; i > 0; i--){
            if(elevator->downOrders[i] || elevator->insideOrders[i]){
                elevator->targetFloor = i;
            return;
            }
        }
    }

    // scan floors downwards and then upwards
    if(elevator->direction == DOWN){
        for(int i = elevator->lastKnownFloor; i > 0; i--){
            if(elevator->downOrders[i] || elevator->insideOrders[i]){
                elevator->targetFloor = i;
                return;
            }
        }
        for(int i = 0; i < HARDWARE_NUMBER_OF_FLOORS - 1; i++){
            if(elevator->upOrders[i] || elevator->insideOrders[i]){
                elevator->targetFloor = i;
                return;
            }
        }
    }
    elevator->direction = NONE;

}

void updateOrders(Elevator* e){
    e->hasOrders = false;
    for(int i = 0; i < HARDWARE_NUMBER_OF_FLOORS; i++){
        // read order buttons
        e->upOrders[i] = e->upOrders[i] || hardware_read_order(i,HARDWARE_ORDER_UP);
        e->downOrders[i] = e->downOrders[i] || hardware_read_order(i,HARDWARE_ORDER_DOWN);
        e->insideOrders[i] = e->insideOrders[i] || hardware_read_order(i,HARDWARE_ORDER_INSIDE);

        // set correct light
        hardware_command_order_light(i,HARDWARE_ORDER_UP, e->upOrders[i]);
        hardware_command_order_light(i,HARDWARE_ORDER_INSIDE, e->insideOrders[i]);
        hardware_command_order_light(i,HARDWARE_ORDER_DOWN, e->downOrders[i]);

        // register orders
        e->hasOrders = e->hasOrders || e->upOrders[i] || e->downOrders[i] || e->insideOrders[i];
    }
}

void openDoor(){
    hardware_command_door_open(true);
}

void updateLastFloor(Elevator* elevator){
    for(int i = 0; i < HARDWARE_NUMBER_OF_FLOORS; i++){
        if(onFloor(i)){
            elevator->lastKnownFloor = i;
            hardware_command_floor_indicator_on(i);
            return;
        }
    }
}