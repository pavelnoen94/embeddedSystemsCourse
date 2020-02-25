#include <stdbool.h>
#include "headers/hardware.h"
#include "headers/elevator.h"
#include "headers/interface.h"

bool readObstruction(){
    return hardware_read_obstruction_signal();
}

void clearAllOrders(){
    for(int i = 0; i < HARDWARE_NUMBER_OF_FLOORS; i++){
        upOrders[i] = false;
        downOrders[i] = false;
        insideOrders[i] = false;

        hardware_command_order_light(i,HARDWARE_ORDER_UP,0);
        hardware_command_order_light(i,HARDWARE_ORDER_DOWN,0);
        hardware_command_order_light(i,HARDWARE_ORDER_INSIDE,0);
    }
}

bool activeOrderThisFloor(){
    if(!atSomeFloor()){
        return false;
    }
    if(direction == UP){
        return upOrders[lastKnownFloor] || insideOrders[lastKnownFloor];
    }
    if(direction == DOWN){
        return downOrders[lastKnownFloor] || insideOrders[lastKnownFloor];
    }
    return false;
}


void clearOrders(int floor){
    if(!isValidFloor(floor)){
        printf("\nError: invalid param in clearOrders(%d)\n",floor);
    
    }
    int i = floor;
    upOrders[i] = false;
    downOrders[i] = false;
    insideOrders[i] = false;

    hardware_command_order_light(i,HARDWARE_ORDER_UP,0);
    hardware_command_order_light(i,HARDWARE_ORDER_DOWN,0);
    hardware_command_order_light(i,HARDWARE_ORDER_INSIDE,0);
}

void clearAllOrdersAtThisFloor(){
    if(!atSomeFloor()){
        return;
    }
    clearOrders(lastKnownFloor);
}

// retruns true if stop is pressed
bool readStop(){
    hardware_command_stop_light(hardware_read_stop_signal());
    return hardware_read_stop_signal();
}

void openDoor(){
    hardware_command_door_open(true);
}

void closeDoor(){
    hardware_command_door_open(false);
}

// working
void updateObstruction(){
    obstruction = readObstruction();
}

// working
void readFloorSensors(){
    for(int i = 0; i < HARDWARE_NUMBER_OF_FLOORS; i++){

        // read floor sensors. Set correct floor light
        if(hardware_read_floor_sensor(i)){
            lastKnownFloor = i;
            hardware_command_floor_indicator_on(i);
            return;
        }

    }
}

int getLastKnownFloor(){
    return lastKnownFloor;
}

int getTargetFloor(){
    return targetFloor;
}

void setTargetFloor(int floor){
    if(!isValidFloor(floor)){
        printf("Error: illeagal argument in setTargetFloor(%d)\n", floor);
    }
    targetFloor = floor;
}

// not tested
bool ordersInDirection(Direction dir, int fromFloor){
    if(dir == UP){
        for (int i = fromFloor; i < HARDWARE_NUMBER_OF_FLOORS; i++){
            if(upOrders[i] || insideOrders[i]){
                return true;
            }
        }
    }
    if(dir == DOWN){
        for (int i = fromFloor; i > 0; i++){
            if(downOrders[i] || insideOrders[i]){
                return true;
            }
        }
    }
    return false;
}

// should be working
Direction getDirection(int targetFloor){
    if(!isValidFloor(targetFloor)){
        printf("Error: illeagal argument in getDirection(%d)\n", targetFloor);
    }
    if(targetFloor == lastKnownFloor){
        return NONE;
    }

    if(targetFloor > lastKnownFloor){
        return UP;
    }
    return DOWN;
}

// working
void findTargetFloor(){
    if(direction == NONE){
        for(int i = 0; i < HARDWARE_NUMBER_OF_FLOORS; i++){
            if(upOrders[i] || downOrders[i] || insideOrders[i]){
                targetFloor = i;
                return;
            }
        }
    }

    if(direction == UP){
        for(int i = lastKnownFloor; i < HARDWARE_NUMBER_OF_FLOORS; i++){
            if(upOrders[i] || insideOrders[i]){
                targetFloor = i;
                return;
            }
        }
        for(int i = HARDWARE_NUMBER_OF_FLOORS - 1; i > 0; i--){
            if(downOrders[i] || insideOrders[i]){
                targetFloor = i;
                return;
            }
        }
    }

    if(direction == DOWN){
        for(int i = lastKnownFloor; i > 0; i--){
            if(downOrders[i] || insideOrders[i]){
                targetFloor = i;
                return;
            }
        }
        for(int i = 0; i < HARDWARE_NUMBER_OF_FLOORS - 1; i++){
            if(upOrders[i] || insideOrders[i]){
                
                targetFloor = i;

                return;
            }
        }
    }

}

// working
bool checkEmergency(){
    emergencyState = emergencyState || readStop();
    hardware_command_stop_light(emergencyState);
    return emergencyState;
}

// working
void resetEmergency(){
    emergencyState = false;
    hardware_command_stop_light(false);
}




bool orderAt(int floor){
    getOrders();
    return insideOrders[floor] || upOrders[floor] || downOrders[floor];
}

bool onFloor(int floor){
    return hardware_read_floor_sensor(floor);
}

// working
void elevatorStop(){
    hardware_command_movement(HARDWARE_MOVEMENT_STOP);
}

// working
void elevatorMoveUp(){
    hardware_command_movement(HARDWARE_MOVEMENT_UP);
}

// working
void elevatorMoveDown(){
    hardware_command_movement(HARDWARE_MOVEMENT_DOWN);
}

bool atSomeFloor(){
    for(int i = 0; i < HARDWARE_NUMBER_OF_FLOORS; i++){

        if(hardware_read_floor_sensor(i)){
            return true;
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



// working
void getOrders(){
    hasOrders = false;
    for(int i = 0; i < HARDWARE_NUMBER_OF_FLOORS; i++){

        // read order buttons
        upOrders[i] = upOrders[i] || hardware_read_order(i,HARDWARE_ORDER_UP);
        downOrders[i] = downOrders[i] || hardware_read_order(i,HARDWARE_ORDER_DOWN);
        insideOrders[i] = insideOrders[i] || hardware_read_order(i,HARDWARE_ORDER_INSIDE);

        // set correct light
        hardware_command_order_light(i,HARDWARE_ORDER_UP, upOrders[i]);
        hardware_command_order_light(i,HARDWARE_ORDER_INSIDE, insideOrders[i]);
        hardware_command_order_light(i,HARDWARE_ORDER_DOWN, downOrders[i]);

        // register orders
        hasOrders = hasOrders || upOrders[i] || downOrders[i] || insideOrders[i];
    }
}

bool atTargetFloor() {
    if(!atSomeFloor()){
        return false;
    }
    if (direction == UP) {
        if(ordersInCurrentDirection()){
            for (int i = 0; i < HARDWARE_NUMBER_OF_FLOORS; i ++) {      
                if ((upOrders[i] || insideOrders[i]) && onFloor(i)){    
                    return true;
                }
            }  
        }
        else{
            for (int i = 0; i < HARDWARE_NUMBER_OF_FLOORS; i ++) {      
                if ((downOrders[i] || insideOrders[i]) && onFloor(i)){
                    return true;
                }
            }
        }
    }

    if (direction == DOWN) {
        if(ordersInCurrentDirection()){
            for (int i = 0; i < HARDWARE_NUMBER_OF_FLOORS; i ++) {
                if ((downOrders[i] || insideOrders[i]) && onFloor(i)){
                    return true;
                }
            }
        }
        else{
            for (int i = 0; i < HARDWARE_NUMBER_OF_FLOORS; i ++) {      
                if ((upOrders[i] || insideOrders[i]) && onFloor(i)){
                    return true;
                }
            }
        }
    }
    return false;
}

bool ordersInCurrentDirection(){
    if (direction == UP) {
        for (int i = lastKnownFloor; i < HARDWARE_NUMBER_OF_FLOORS; i++) {
            if (upOrders[i] || insideOrders[i]) { 
                return true; 
            }
        }
    }
    if (direction == DOWN) {
        for (int i = lastKnownFloor; i > 0; i--) {
            if (downOrders[i] || insideOrders[i]) { 
                return true; 
            }
        }
    }
    return false;
}

void updateHasOrders(){
    hasOrders = false;
    for (int i; i < HARDWARE_NUMBER_OF_FLOORS; i++) {
        if (upOrders[i] || downOrders[i]) {
            hasOrders = true;
            return;
        }
    }
}
