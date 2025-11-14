#ifndef _GLOBAL_h
#define _GLOBAL_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

#include <Adafruit_NeoPixel.h>
#include <PS2X_lib.h>
#include <TMCStepper.h>
#include <AccelStepper.h>

#include "pindef.h"
#include "config.h"

extern Adafruit_NeoPixel pixels;
extern PS2X ps2x;
extern TMC2209Stepper driverM0;
extern TMC2209Stepper driverM1;

extern AccelStepper stepperM0;
extern AccelStepper stepperM1;
extern AccelStepper stepperM2;

template<typename T>
T map(T val, T fromLow, T fromHigh, T toLow, T toHigh) {
	return toLow + ((toHigh - toLow) / (fromHigh - fromLow)) * (val - fromLow);
}

#endif