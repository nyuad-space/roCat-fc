#ifndef ROCAT_STATE_H
#define ROCAT_STATE_H

enum State
{
    PRELAUNCH,
    LAUNCH_READY,
    POWERED_FLIGHT,
    UNPOWERED_FLIGHT,
    POST_DROUGE,
    POST_MAIN,
    END,
    SD_WRITE
};

extern enum State current_state;

#endif
