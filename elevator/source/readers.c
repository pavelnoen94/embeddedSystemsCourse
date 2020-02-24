#include "elevator.h"
#include "hardware.h"
#include "sensor.h"


void goToFloorReader(){
    for(int i = 0; i < HARDWARE_NUMBER_OF_FLOORS; i++){

        // read order buttons
        upOrders[i]     = upOrders[i]       || hardware_read_order(i,HARDWARE_ORDER_UP);
        downOrders[i]   = downOrders[i]     || hardware_read_order(i,HARDWARE_ORDER_DOWN);
        insideOrders[i] = insideOrders[i]   || hardware_read_order(i,HARDWARE_ORDER_INSIDE);

        // set correct light
        hardware_command_order_light(i,HARDWARE_ORDER_UP, upOrders[i]);
        hardware_command_order_light(i,HARDWARE_ORDER_INSIDE, insideOrders[i]);
        hardware_command_order_light(i,HARDWARE_ORDER_DOWN, downOrders[i]);

        // register orders
        hasOrders = hasOrders || upOrders[i] || downOrders[i] || insideOrders[i];
        
        // read floor sensor
        if(hardware_read_floor_sensor(i)){
            lastKnownFloor = i;
            hardware_command_floor_indicator_on(i);
            continue;
        }
    }
  
    readStop();
}

void emergencyReader(){
    for(int i = 0; i < HARDWARE_NUMBER_OF_FLOORS; i++){

        // read order buttons
        upOrders[i]     = upOrders[i]       || hardware_read_order(i,HARDWARE_ORDER_UP);
        downOrders[i]   = downOrders[i]     || hardware_read_order(i,HARDWARE_ORDER_DOWN);
        insideOrders[i] = insideOrders[i]   || hardware_read_order(i,HARDWARE_ORDER_INSIDE);

        // set correct light
        hardware_command_order_light(i,HARDWARE_ORDER_UP, upOrders[i]);
        hardware_command_order_light(i,HARDWARE_ORDER_INSIDE, insideOrders[i]);
        hardware_command_order_light(i,HARDWARE_ORDER_DOWN, downOrders[i]);

        // register orders
        hasOrders = hasOrders || upOrders[i] || downOrders[i] || insideOrders[i];
    }
}
