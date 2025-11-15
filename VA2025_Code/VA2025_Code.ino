
#include "motor.h"
#include "global.h"
#include "ps2xController.h"

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
    
    unsigned long lastStartupMilis = millis();
    bool statusLEDToggle = false;
    while (!Serial) {
        if (millis() - lastStartupMilis >= 5000)
            break; // break out after 5s
        
        delay(500);
        statusLEDToggle = !statusLEDToggle;
        pixels.setPixelColor(config::generalStatusLED, statusLEDToggle == false ? pixels.Color(0, 0, 0) : pixels.Color(255, 255, 255));
        pixels.show();
    }
    pixels.setPixelColor(config::generalStatusLED, pixels.Color(0, 0, 0));
    pixels.show();
    motorInit();
}

unsigned long currentLEDMilis = 0;
unsigned long lastLEDMilis = 0;
bool LEDToggle = false;
bool controllerInit = false;

unsigned long currentComputationMilis = 0;
unsigned long lastComputationMilis = 0;

void loop() {
    
    currentLEDMilis = millis();
    if (currentLEDMilis - lastLEDMilis > config::LEDBlinkDelay) {
        lastLEDMilis = currentLEDMilis;
        LEDToggle = !LEDToggle;
        digitalWrite(LED_BUILTIN, LEDToggle);
    }

    currentComputationMilis = millis();
    if (currentComputationMilis - lastComputationMilis > config::ComputationDelay) {
        lastComputationMilis = currentComputationMilis;
        if (digitalRead(pins::buttonPin) == LOW) {
            Serial.println("battV: " + String(analogRead(pins::battVoltage)));
            delay(100);
        }
        if (!controllerInit) {
            controllerInit = initController();
        }

        if (!controllerInit) { // init not complete
            pixels.setPixelColor(config::generalStatusLED, pixels.Color(255, 0, 0));
            pixels.show();
            Serial.println("ERROR: Not able to initialize controller");
            delay(500);
            return; // continue looping from start
        }
        else
            pixels.setPixelColor(config::generalStatusLED, pixels.Color(0, 0, 0));

        ps2x.read_gamepad(false, false);

        motorValues = calculateMotorValues(ps2x.Analog(PSS_RY), ps2x.Analog(PSS_RX), config::psxAnalogMin, config::psxAnalogMax, config::moveMotorMappedMin, config::moveMotorMappedMax);

        //Serial.println(map(ps2x.Analog(PSS_LX), config::psxAnalogMin, config::psxAnalogMax, config::headMotorMappedMin, config::headMotorMappedMax));

        stepperM0.setSpeed(deadzone(motorValues.val1, config::motorDeadzoneZero, config::motorDeadzoneSize));
        stepperM1.setSpeed(deadzone(motorValues.val2, config::motorDeadzoneZero, config::motorDeadzoneSize));

        stepperM2.setSpeed(
            deadzone(
                map(ps2x.Analog(PSS_LX), config::psxAnalogMin, config::psxAnalogMax, config::headMotorMappedMin, config::headMotorMappedMax),
                config::motorDeadzoneZero,
                config::motorDeadzoneSize
            )
        );

        motorPowerSave(stepperM0, pixels, config::M0StatusLED);
        motorPowerSave(stepperM1, pixels, config::M1StatusLED);
        motorPowerSave(stepperM2, pixels, config::M2StatusLED);

        pixels.show();
    }

    stepperM0.runSpeed();
    stepperM1.runSpeed();
    stepperM2.runSpeed();

    //motorLoop();

   // Serial.println("loop");
    //delay(100);
}
