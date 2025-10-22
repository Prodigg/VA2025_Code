#include "global.h"

Adafruit_NeoPixel pixels(config::neopixelCount, pins::neopixelPin, NEO_GRB + NEO_KHZ800);
PS2X ps2x;

TMC2209Stepper driverM0 = TMC2209Stepper(pins::M0_SERIAL_PORT, config::R_SENSE, config::DRIVER_ADDRESS);
TMC2209Stepper driverM1 = TMC2209Stepper(pins::M1_SERIAL_PORT, config::R_SENSE, config::DRIVER_ADDRESS);

AccelStepper stepperM0 = AccelStepper(stepperM0.DRIVER, pins::M0_STEP_PIN, pins::M0_DIR_PIN);
AccelStepper stepperM1 = AccelStepper(stepperM1.DRIVER, pins::M1_STEP_PIN, pins::M1_DIR_PIN);
AccelStepper stepperM2 = AccelStepper(stepperM2.DRIVER, pins::M2_STEP_PIN, pins::M2_DIR_PIN);