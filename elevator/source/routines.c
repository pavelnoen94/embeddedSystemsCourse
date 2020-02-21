#include "elevator.h"

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

void elevatorStop(){
    hardware_command_movement(HARDWARE_MOVEMENT_STOP);
}
void elevatorMoveUp(){
    hardware_command_movement(HARDWARE_MOVEMENT_UP);
}
void elevatorMoveDown(){
    hardware_command_movement(HARDWARE_MOVEMENT_DOWN);
}

void clearAllOrders(){
    for(int i = 0; i < HARDWARE_NUMBER_OF_FLOORS; i++){
        upOrders[i] = false;
        downOrders[i] = false;
        insideOrders[i] = false;

        hardware_commareadObsnd_order_light(i,HARDWARE_ORDER_UP,0);
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
    if(!onAFloor()){
        return;
    }
    int i = lastKnownFloor;
    upOrders[i] = false;
    downOrders[i] = false;
    insideOrders[i] = false;

    hardware_command_order_light(i,HARDWARE_ORDER_UP,0);
    hardware_command_order_light(i,HARDWARE_ORDER_DOWN,0);
    hardware_command_order_light(i,HARDWARE_ORDER_INSIDE,0);
}

bool onAFloor(){
    for(int i = 0; i < HARDWARE_NUMBER_OF_FLOORS; i++){
        if(hardware_read_floor_sensor(i)){
            return true;
        }
    }
    return false;
}

bool activeOrderThisFloor(){
    if(onAFloor()){
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

bool isValidFloor(int floor){
    if(floor < 0 || floor > HARDWARE_NUMBER_OF_FLOORS){
        return false;
    }
    return true;
}

Direction getDirection(int targetFloor){
    if(!isValidFloor){
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

void findTargetFloor(){
    for(int i = 0; i < HARDWARE_NUMBER_OF_FLOORS; i++){
        if(upOrders[i] || downOrders[i] || insideOrders[i]){
            targetFloor = i;
            return;
        }
    }
}

bool checkEmergency(){
    emergencyState = emergencyState || readStop();
    hardware_command_stop_light(emergencyState);
    return emergencyState;
}

void resetEmergency(){
    emergencyState = false;
    hardware_command_stop_light(false);
}
void updateObstruction(){
    obstruction = readObstruction();
}

void readFloorSensors(){
    atSomeFloor = false;
    for(int i = 0; i < HARDWARE_NUMBER_OF_FLOORS; i++){

        // read floor sensors. Set correct floor light
        if(hardware_read_floor_sensor(i)){
            atSomeFloor = true;
            lastKnownFloor = i;
            hardware_command_floor_indicator_on(i);
            return;
        }

    }
}

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