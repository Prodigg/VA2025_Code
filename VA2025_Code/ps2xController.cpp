#include "ps2xController.h"

bool initController() {
    byte controllerInit = ps2x.config_gamepad(pins::PS2_CLK, pins::PS2_CMD, pins::PS2_SEL, pins::PS2_DAT, false, false);
    if (controllerInit != 0)
        return false; // config failed
    

    if (ps2x.readType() == 1) {
        return true; // valid controller found
    }
        
    return false;
}
