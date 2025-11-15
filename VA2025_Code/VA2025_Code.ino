
#include "motor.h"
#include "global.h"
#include "ps2xController.h"
#include "LEDPatterns.h"
#include "LEDPatternsPredefined.h"

#include <Adafruit_NeoPixel.h>
#include <PS2X_lib.h>
#include <TMCStepper.h>
#include <AccelStepper.h>

motorValues_t motorValues{};
LEDPatterns::rainbow_t* rainbowLEDs;
LEDPatterns::WalkingLight_t* walkingLight;
LEDPatterns::pulsating_t* pulsatingLEDs;

void setup() {
    pinMode(pins::buttonPin, INPUT);
    pinMode(LED_BUILTIN, OUTPUT);
    pixels.begin();
    
    rainbowLEDs = new LEDPatterns::rainbow_t(pixels);
    rainbowLEDs->setPixelPattern(predifined::allLEDS, predifined::allLEDS_size - 10);
    rainbowLEDs->setStepSize(5000);

    walkingLight = new LEDPatterns::WalkingLight_t(pixels);
    walkingLight->pixelOffColor(Adafruit_NeoPixel::Color(0, 0, 0));
    walkingLight->pixelOnColor(Adafruit_NeoPixel::Color(0, 255, 0));
    walkingLight->setPixelPattern(predifined::topLEDs, predifined::topLEDs_size);
    walkingLight->bounceLight(true);

    pulsatingLEDs = new LEDPatterns::pulsating_t(pixels);
    pulsatingLEDs->setPixelPattern(predifined::allLEDS, predifined::allLEDS_size - 10)
        .setColor(random((uint16_t)0, (uint16_t)-1), 255);

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

    // startup animation
    LEDPatterns::WalkingLight_t walkingLightStart(pixels);
    walkingLightStart.setPixelPattern(predifined::startupPattern, predifined::startupPattern_size)
        .pixelOffColor(Adafruit_NeoPixel::Color(0, 255, 0))
        .pixelOnColor(Adafruit_NeoPixel::Color(0, 0, 255));

    stepperM0.disableOutputs();
    stepperM1.disableOutputs();
    stepperM2.disableOutputs();

    while (!walkingLightStart.isAnimationAtEnd()) {
        walkingLightStart.draw();
        pixels.show();
        delay(50);
    }

    stepperM0.enableOutputs();
    stepperM1.enableOutputs();
    stepperM2.enableOutputs();
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

        if (motorInPowerSave(stepperM0) && motorInPowerSave(stepperM1) && motorInPowerSave(stepperM2)) {
            rainbowLEDs->draw();
        }
        else {
            if (pulsatingLEDs->currentColorBrightness() < 5)
                pulsatingLEDs->setColor(random((uint16_t)0, (uint16_t)-1), 255);
            pulsatingLEDs->draw();
        }
            
        walkingLight->draw();
        pixels.show();
    }

    stepperM0.runSpeed();
    stepperM1.runSpeed();
    stepperM2.runSpeed();

    //motorLoop();

   // Serial.println("loop");
   //delay(100);
}
