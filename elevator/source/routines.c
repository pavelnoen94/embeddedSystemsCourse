#include "elevator.h"
#include "hardware.h"
#include "sensor.h"
#include "routines.h"

void readAllSensors()
{
    readFloorSensors();
    readObstruction();
    getOrders();
    readStop();
}

void initModeReader(){
    readFloorSensors();
}

void idleModeReader(){
    getOrders();
    readStop();
}

void runningModeReader(){
    getOrders();
    readStop();
    readFloorSensors();
}

void emergencyModeReader(){
    getOrders();
    readStop();
}

void doorModeReader(){
    readObstruction();
    readStop();
    getOrders();
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

bool isValidFloor(int floor){
    if(floor < 0 || floor > HARDWARE_NUMBER_OF_FLOORS){
        return false;
    }
    return true;
}

void setTargetFloor(int floor){
    if(!isValidFloor(floor)){
        printf("Error: illeagal argument in setTargetFloor(%d)\n", floor);
    }
    targetFloor = floor;
}



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
    for(int i = 0; i < HARDWARE_NUMBER_OF_FLOORS; i++){
        if(upOrders[i] || downOrders[i] || insideOrders[i]){
            targetFloor = i;
            return;
        }
    }
}
bool atSomeFloor(){
    for(int i = 0; i < HARDWARE_NUMBER_OF_FLOORS; i++){
        if(onFloor(i)){
            return true;
        }
        
    }
    return false;
}
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