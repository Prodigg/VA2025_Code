#ifndef _MOTOR_h
#define _MOTOR_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

#include "global.h"

struct motorValues_t {
    int val1;
    int val2;
};

motorValues_t calculateMotorValues(int x, int y, int min, int max, int motorMin, int motorMax);

void motorInit();

void motorLoop();

#endif
