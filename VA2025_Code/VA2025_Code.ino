
#include "motor.h"
#include "global.h"

#include <Adafruit_NeoPixel.h>
#include <PS2X_lib.h>
#include <TMCStepper.h>
#include <AccelStepper.h>

motorValues_t motorValues{};

void setup() {
    pinMode(pins::buttonPin, INPUT);
    pixels.begin();
}

void loop() {
    for (int i = 0; i < 4; i++) {
        if (digitalRead(pins::buttonPin) == HIGH) {
            pixels.setPixelColor(i, pixels.Color(0, 0, 255));
        }
        else
            pixels.setPixelColor(i, pixels.Color(255, 0, 0));
    }
    pixels.setBrightness(100); 

    if (digitalRead(pins::buttonPin) == HIGH) {
        Serial.println("battV: " + String(analogRead(pins::battVoltage)));
        delay(100);
    }

    motorValues = calculateMotorValues(ps2x.Analog(PSS_RX), ps2x.Analog(PSS_RY), 0, 1270, -90, 90);

    stepperM0.setSpeed(motorValues.val1);
    stepperM1.setSpeed(motorValues.val2);

    stepperM2.setSpeed(map(ps2x.Analog(PSS_LX), 0, 1270, -90, 90));

    stepperM0.runSpeed();
    stepperM1.runSpeed();
    stepperM2.runSpeed();

    pixels.show();
}
