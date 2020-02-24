#include "elevator.h"
#include "hardware.h"
#include "sensor.h"
#include "routines.h"

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

void openDoor(){
    hardware_command_door_open(true);
}

void closeDoor(){
    hardware_command_door_open(false);
}

void clearAllOrdersAtThisFloor(){
    if(!atSomeFloor()){
        return;
    }
    clearOrders(lastKnownFloor);
}

void clearOrders(int floor){
    if(!isValidFloor(floor)){
        printf("Error: invalid param in clearOrdersAtFloor(%d)",floor);
    
    }
    int i = floor;
    upOrders[i] = false;
    downOrders[i] = false;
    insideOrders[i] = false;

    hardware_command_order_light(i,HARDWARE_ORDER_UP,0);
    hardware_command_order_light(i,HARDWARE_ORDER_DOWN,0);
    hardware_command_order_light(i,HARDWARE_ORDER_INSIDE,0);
}

bool activeOrderThisFloor(){
    if(atSomeFloor()){
        return upOrders[lastKnownFloor] || downOrders[lastKnownFloor] || insideOrders[lastKnownFloor];
    }
    return -1;
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
// should be working
bool isValidFloor(int floor){
    if(floor < 0 || floor > HARDWARE_NUMBER_OF_FLOORS){
        return false;
    }
    return true;
}
// working
void findTargetFloor(){
    for(int i = 0; i < HARDWARE_NUMBER_OF_FLOORS; i++){
        if(upOrders[i] || downOrders[i] || insideOrders[i]){
            targetFloor = i;
            return;
        }
    }
}
// should be working
bool atSomeFloor(){
    for(int i = 0; i < HARDWARE_NUMBER_OF_FLOORS; i++){
        if(onFloor(i)){
            return true;
        }
        
    }
    return false;
}
// should be working
bool orderAt(int floor){
    getOrders();
    return insideOrders[floor] || upOrders[floor] || downOrders[floor];
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

// working
bool onFloor(int floor){
    return hardware_read_floor_sensor(floor);
}

// working
bool checkEmergency(){
    emergencyState = emergencyState || readStop();
    hardware_command_stop_light(emergencyState);
    return emergencyState;
}

// wokring
void resetEmergency(){
    emergencyState = false;
    hardware_command_stop_light(false);
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