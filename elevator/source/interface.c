#include <stdbool.h>
#include "headers/hardware.h"
#include "headers/elevator.h"
#include "headers/interface.h"
#include "headers/modes.h"

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

void clearAllOrdersAtThisFloor(){
    if(!atSomeFloor()){
        return;
    }
    upOrders[position.lastKnownFloor] = false;
    downOrders[position.lastKnownFloor] = false;
    insideOrders[position.lastKnownFloor] = false;
}

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

void readFloorSensors(){
    for(int i = 0; i < HARDWARE_NUMBER_OF_FLOORS; i++){
        if(hardware_read_floor_sensor(i)){
            position.lastKnownFloor = i;
            hardware_command_floor_indicator_on(i);
            return;
        }
    }
}

/*bool ordersInDirection(Direction dir, int fromFloor){
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
*/

Direction getDirection(int targetFloor){

    if(targetFloor == position.lastKnownFloor && atSomeFloor()){
        return NONE;
    }

    // elevator stopped. if new floor is in oposite direction flip the direction and change the last known floor.
    if(emergencyState && !atSomeFloor()){
        emergencyState = false;

        // elevator ordered back.
        if(targetFloor == position.lastKnownFloor){
            if(direction == UP){
                position.lastKnownFloor++;
                return DOWN;
            }

            position.lastKnownFloor--;
            return UP;
        }

        if(targetFloor > position.lastKnownFloor){
            return UP;
        }

        return DOWN;
        
    }
    emergencyState = false;

    if(targetFloor > position.lastKnownFloor){
        return UP;
    }
    return DOWN;
}

void findTargetFloor(){
    // scan all floors
    if(direction == NONE || emergencyState){
        for(int i = 0; i < HARDWARE_NUMBER_OF_FLOORS; i++){
            if(upOrders[i] || downOrders[i] || insideOrders[i]){
                targetFloor = i;
                return;
            }
        }
    }
    // scan floors upwards and then downwards
    if(direction == UP){
        for(int i = position.lastKnownFloor; i < HARDWARE_NUMBER_OF_FLOORS; i++){
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
    // scan floors downwards and then upwards
    if(direction == DOWN){
        for(int i = position.lastKnownFloor; i > 0; i--){
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

bool orderAt(int floor){
    getOrders();
    return insideOrders[floor] || upOrders[floor] || downOrders[floor];
}


bool onFloor(int floor){
    return hardware_read_floor_sensor(floor);
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
    if(direction == NONE){
        return position.lastKnownFloor == targetFloor ? true : false;
    }

    if (direction == UP) {
        if(ordersInCurrentDirection()){
            // Scan orders in up direction
            for (int i = 0; i < HARDWARE_NUMBER_OF_FLOORS; i ++) {      
                if ((upOrders[i] || insideOrders[i]) && onFloor(i)){    
                    return true;
                }
            }  
        }else{
            // scan orders in oposite direction starting at top floor
            for (int i = HARDWARE_NUMBER_OF_FLOORS - 1; i >= 0; i--) {
                if ((downOrders[i] || insideOrders[i])){
                    targetFloor = i;
                    if (onFloor(targetFloor)) {         
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

    if (direction == DOWN) {
        if(ordersInCurrentDirection()){
            // scan orders in down direction
            for (int i = 0; i < HARDWARE_NUMBER_OF_FLOORS; i ++) {
                if ((downOrders[i] || insideOrders[i]) && onFloor(i)){
                    return true;
                }
            }
        }else{
            // scan orders in oposite direction starting from the bottom
            for (int i = 0; i < HARDWARE_NUMBER_OF_FLOORS; i ++) {      
                if ((upOrders[i] || insideOrders[i])) {
                    targetFloor = i;
                    if (onFloor(targetFloor)) {
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

bool ordersInCurrentDirection(){
    if (direction == UP) {
        for (int i = position.lastKnownFloor; i < HARDWARE_NUMBER_OF_FLOORS; i++) {
            if (upOrders[i] || insideOrders[i]) { 
                return true; 
            }
        }
    }
    if (direction == DOWN) {
        for (int i = position.lastKnownFloor; i > 0; i--) {
            if (downOrders[i] || insideOrders[i]) { 
                return true; 
            }
        }
    }
    return false;
}