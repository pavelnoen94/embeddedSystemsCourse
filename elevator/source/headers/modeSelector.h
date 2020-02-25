#pragma once
typedef enum{
    IDLE,
    SERVING,
    RUNNING,
    OPENDOOR,
    STOP,
    UNKNOWN
} Status;

static Status status = UNKNOWN;

void modeSelector();
void selectorUnknown();
void selectorIdle();
void selectorServing();
void selectorMoving();
void selectorStop();