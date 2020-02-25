#pragma once
typedef enum{
    IDLE,
    SERVING,
    RUNNING,
    OPENDOOR,
    STOP,
    UNKNOWN
} Status;

void modeSelector();