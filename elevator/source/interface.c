#include <stdbool.h>
#include "headers/hardware.h"
#include "headers/elevator.h"
#include "headers/interface.h"
#include "headers/modes.h"

bool atSomeFloor(){
    for(int i = 0; i < HARDWARE_NUMBER_OF_FLOORS; i++){
        if(hardware_read_floor_sensor(i)){
            return true;
        }
    }
    return false;
}


bool atTargetFloor(ElevatorData* elevator) {
    if(!atSomeFloor()){
        return false;
    }
    if(elevator->direction == NONE){
        return elevator->lastKnownFloor == elevator->targetFloor ? true : false;
    }

    if (elevator->direction == UP) {
        if(ordersInCurrentDirection(elevator)){
            // Scan orders in up direction
            for (int i = 0; i < HARDWARE_NUMBER_OF_FLOORS; i ++) {      
                if ((elevator->upOrders[i] || elevator->insideOrders[i]) && onFloor(i)){    
                    return true;
                }
            }  
        }else{
            // scan orders in oposite direction starting at top floor
            for (int i = HARDWARE_NUMBER_OF_FLOORS - 1; i >= 0; i--) {
                if ((elevator->downOrders[i] || elevator->insideOrders[i])){
                    elevator->targetFloor = i;
                    if (onFloor(elevator->targetFloor)) {         
                        return true;
                    }
                    else                                       
                    {
                        return false;
                    }
                }
            }
        }
    }

    if (elevator->direction == DOWN) {
        if(ordersInCurrentDirection(elevator)){
            // scan orders in down direction
            for (int i = 0; i < HARDWARE_NUMBER_OF_FLOORS; i ++) {
                if ((elevator->downOrders[i] || elevator->insideOrders[i]) && onFloor(i)){
                    return true;
                }
            }
        }else{
            // scan orders in oposite direction starting from the bottom
            for (int i = 0; i < HARDWARE_NUMBER_OF_FLOORS; i ++) {      
                if ((elevator->upOrders[i] || elevator->insideOrders[i])) {
                    elevator->targetFloor = i;
                    if (onFloor(elevator->targetFloor)) {
                        return true;
                    }
                    else
                    {
                        return false;
                    }
                }
            }
        }
    }
    return false;
}

bool isValidFloor(int floor){
    if(floor > HARDWARE_NUMBER_OF_FLOORS || floor < 0){
        return false;
    }
    return true;
}


bool onFloor(int floor){
    return hardware_read_floor_sensor(floor);
}

bool orderAt(ElevatorData* elevator, int floor){
    getOrders(elevator);
    return elevator->insideOrders[floor] || elevator->upOrders[floor] || elevator->downOrders[floor];
}

bool ordersInCurrentDirection(ElevatorData* elevator){
    if (elevator->direction == UP) {
        for (int i = elevator->lastKnownFloor; i < HARDWARE_NUMBER_OF_FLOORS; i++) {
            if (elevator->upOrders[i] || elevator->insideOrders[i]) { 
                return true; 
            }
        }
    }
    if (elevator->direction == DOWN) {
        for (int i = elevator->lastKnownFloor; i > 0; i--) {
            if (elevator->downOrders[i] || elevator->insideOrders[i]) { 
                return true; 
            }
        }
    }
    return false;
}

bool readObstruction(){
    return hardware_read_obstruction_signal();
}


bool readStop(){
    hardware_command_stop_light(hardware_read_stop_signal());
    return hardware_read_stop_signal();
}


Direction getDirection(ElevatorData* elevator, int targetFloor){

    if(targetFloor == elevator->lastKnownFloor && atSomeFloor()){
        return NONE;
    }

    // elevator stopped. if new floor is in oposite direction flip the direction and change the last known floor.
    if(elevator->emergencyState && !atSomeFloor()){
        elevator->emergencyState = false;

        // elevator ordered back.
        if(elevator->targetFloor == elevator->lastKnownFloor){
            if(elevator->direction == UP){
                elevator->lastKnownFloor++;
                return DOWN;
            }

            elevator->lastKnownFloor--;
            return UP;
        }

        if(elevator->targetFloor > elevator->lastKnownFloor){
            return UP;
        }

        return DOWN;
        
    }
    elevator->emergencyState = false;

    if(elevator->targetFloor > elevator->lastKnownFloor){
        return UP;
    }
    return DOWN;
}


void clearAllOrders(ElevatorData* elevator){
    for(int i = 0; i < HARDWARE_NUMBER_OF_FLOORS; i++){
        elevator->upOrders[i] = false;
        elevator->downOrders[i] = false;
        elevator->insideOrders[i] = false;

        hardware_command_order_light(i,HARDWARE_ORDER_UP,0);
        hardware_command_order_light(i,HARDWARE_ORDER_DOWN,0);
        hardware_command_order_light(i,HARDWARE_ORDER_INSIDE,0);
    }
}

void clearAllOrdersAtThisFloor(ElevatorData* elevator){
    if(!atSomeFloor()){
        return;
    }
    elevator->upOrders[elevator->lastKnownFloor] = false;
    elevator->downOrders[elevator->lastKnownFloor] = false;
    elevator->insideOrders[elevator->lastKnownFloor] = false;
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

void findTargetFloor(ElevatorData* elevator){
    // scan all floors
    if(elevator->direction == NONE || elevator->emergencyState){
        for(int i = 0; i < HARDWARE_NUMBER_OF_FLOORS; i++){
            if(elevator->upOrders[i] || elevator->downOrders[i] || elevator->insideOrders[i]){
                elevator->targetFloor = i;
                return;
            }
        }
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

}

void getOrders(ElevatorData* elevator){
    elevator->hasOrders = false;
    for(int i = 0; i < HARDWARE_NUMBER_OF_FLOORS; i++){

        // read order buttons
        elevator->upOrders[i] = elevator->upOrders[i] || hardware_read_order(i,HARDWARE_ORDER_UP);
        elevator->downOrders[i] = elevator->downOrders[i] || hardware_read_order(i,HARDWARE_ORDER_DOWN);
        elevator->insideOrders[i] = elevator->insideOrders[i] || hardware_read_order(i,HARDWARE_ORDER_INSIDE);

        // set correct light
        hardware_command_order_light(i,HARDWARE_ORDER_UP, elevator->upOrders[i]);
        hardware_command_order_light(i,HARDWARE_ORDER_INSIDE, elevator->insideOrders[i]);
        hardware_command_order_light(i,HARDWARE_ORDER_DOWN, elevator->downOrders[i]);

        // register orders
        elevator->hasOrders = elevator->hasOrders || elevator->upOrders[i] || elevator->downOrders[i] || elevator->insideOrders[i];
    }
}

void openDoor(){
    hardware_command_door_open(true);
}

void readFloorSensors(ElevatorData* elevator){
    for(int i = 0; i < HARDWARE_NUMBER_OF_FLOORS; i++){
        if(hardware_read_floor_sensor(i)){
            elevator->lastKnownFloor = i;
            hardware_command_floor_indicator_on(i);
            return;
        }
    }
}