#pragma once
#define ON 1
#define OFF 0

HardwareOrder order_types[3] = {
        HARDWARE_ORDER_UP,
        HARDWARE_ORDER_INSIDE,
        HARDWARE_ORDER_DOWN
    };



void init();
void start();
void stop();

static void clear_all_order_lights();
static void sigint_handler(int sig);

