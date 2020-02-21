#include <stdbool.h>
#include "hardware.h"

bool readObstruction(){
    return hardware_read_obstruction_signal();
}

bool readStop(){
    hardware_command_stop_light(hardware_read_stop_signal());
    return hardware_read_stop_signal();
}