#include <stdbool.h>
#include "sensor.h"
#include "hardware.h"
#include "elevator.h"


bool checkIfAtTargetFloor() {       // Returns true if elevator is currently at a floor where there is an order (so it should stop)
    if (direction == UP) {
        for (int i = 0; i < HARDWARE_NUMBER_OF_FLOORS; i ++) {      // Iterates through upOrders while polling floor sensor; 
            if (upOrders[i] && hardware_read_floor_sensor(i)){      // if both are high, the elevator is currently at a target floor.
                return true;
            }
        }
    }
    if (direction == DOWN) {
        for (int i = 0; i < HARDWARE_NUMBER_OF_FLOORS; i ++) {
            if (downOrders[i] && hardware_read_floor_sensor(i)){
                return true;
            }
        }
    }
    return false;
}

// careful not to call this before attending order at current floor. If ie called first when arriving at floor 4, will return false!
// not yet designed for properly handling direction == NONE
bool testForDirectionChange(){      // checks if the time is right for a direction change, by testing for
    if (direction == UP) {          // any unattended orders on floor above/below, based on current durection. Return true if there are none
        for (int i = lastKnownFloor; i <= HARDWARE_NUMBER_OF_FLOORS; i++) {
            if (upOrders[i] == true) { return false; }
        }
    }
    if (direction == DOWN) {
        for (int i = lastKnownFloor; i > 0; i--) {
            if (downOrders[i] == true) { return false; }
        }
    }
    if (direction == NONE) { return false; }
    return true;
}
