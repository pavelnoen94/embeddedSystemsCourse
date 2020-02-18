/**
 * @file triggers.c
 * @author Pavel Skipenes (pavelgs@stud.ntnu.no)
 * @brief Contians triggers and calls functions inside actions.h
 * @version 0.1
 * @date 2020-02-18
 * 
 */

#include "triggers.h"
#include "actions.h"
#include "hardware.h"
#include "highLevelProgramVariables.h"

if(stopSignalState && activeFloorSensors){
    stopElevator();
    openDoor();
}
if(stopSignalState && (activeFloorSensors == 0)){
    stopElevator();
    clearOrders();
}

if(currentDirection == Up){
    for(int i = lastKnownElevatorPosition; i < HARDWARE_NUMBER_OF_FLOORS; i++){
        upQueue[i];
    }
}