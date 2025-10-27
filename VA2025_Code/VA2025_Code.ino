
#include "motor.h"
#include "global.h"

#include <Adafruit_NeoPixel.h>
#include <PS2X_lib.h>
#include <TMCStepper.h>
#include <AccelStepper.h>

motorValues_t motorValues{};

void setup() {
    pinMode(pins::buttonPin, INPUT);
    pinMode(LED_BUILTIN, OUTPUT);
    pixels.begin();

    for (int i = 0; i < config::neopixelCount; i++) {
        pixels.setPixelColor(i, pixels.Color(0, 0, 0));
    }
    pixels.setBrightness(100);
}

unsigned long currentLEDMilis = 0;
unsigned long lastLEDMilis = 0;
bool LEDToggle = false;

void loop() {
    
    currentLEDMilis = millis();
    if (currentLEDMilis - lastLEDMilis > config::LEDBlinkDelay) {
        lastLEDMilis = currentLEDMilis;
        LEDToggle = !LEDToggle;
        digitalWrite(LED_BUILTIN, LEDToggle);
    }

    if (digitalRead(pins::buttonPin) == HIGH) {
        Serial.println("battV: " + String(analogRead(pins::battVoltage)));
        delay(100);
    }

    motorValues = calculateMotorValues(ps2x.Analog(PSS_RX), ps2x.Analog(PSS_RY), config::psxAnalogMin, config::psxAnalogMax, -90, 90);

    stepperM0.setSpeed(motorValues.val1);
    stepperM1.setSpeed(motorValues.val2);

    stepperM2.setSpeed(map(ps2x.Analog(PSS_LX), config::psxAnalogMin, config::psxAnalogMax, -90, 90));

    stepperM0.runSpeed();
    stepperM1.runSpeed();
    stepperM2.runSpeed();

    pixels.show();
}
