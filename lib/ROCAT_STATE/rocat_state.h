#ifndef ROCAT_STATE_H
#define ROCAT_STATE_H

enum State
{
    PRELAUNCH,
    LAUNCH_READY,
    POWERED_FLIGHT,
    UNPOWERED_FLIGHT,
    PRE_DROUGE,
    DROUGE,
    POST_DROUGE,
    MAIN,
    POST_MAIN,
    END,
    TEST
};

extern enum State current_state;

#endif
