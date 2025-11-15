#include "motor.h"

motorValues_t calculateMotorValues(int x, int y, int min, int max, int motorMin, int motorMax) {

    y = map(y, max, min, motorMin, motorMax);
    x = map(x, min, max, motorMax, motorMin);

    y = (y - x) / 2;
    x = (y + x) / 2;
    
   
    return { x, y };
}

void motorInit() {
    Serial.println("motor init");
    pinMode(pins::M0_CS_PIN, OUTPUT);
    pinMode(pins::M1_CS_PIN, OUTPUT);
    pinMode(pins::M2_CS_PIN, OUTPUT);

    digitalWrite(pins::M0_CS_PIN, HIGH);
    digitalWrite(pins::M1_CS_PIN, HIGH);
    digitalWrite(pins::M2_CS_PIN, HIGH);

    /************************ init drivers ***************************/

    driverM0.begin();
    driverM1.begin();

    driverM0.rms_current(config::movmentStepperRMSCurrent);    // Set stepper current to 600mA
    driverM1.rms_current(config::movmentStepperRMSCurrent);

    //driverM0.en_pwm_mode(1);      // Enable extremely quiet stepping
    //driverM1.en_pwm_mode(1);      // Enable extremely quiet stepping

    driverM0.pwm_autoscale(1);
    driverM1.pwm_autoscale(1);

    driverM0.microsteps(config::movmentStepperMicroStepps);
    driverM1.microsteps(config::movmentStepperMicroStepps);

    /************************ init stepper ***************************/

    stepperM0.setMaxSpeed(config::M0MaxSpeed);
    stepperM1.setMaxSpeed(config::M1MaxSpeed);
    stepperM2.setMaxSpeed(config::M2MaxSpeed);

    stepperM0.setAcceleration(config::M0Acceleration);
    stepperM1.setAcceleration(config::M1Acceleration);
    stepperM2.setAcceleration(config::M2Acceleration);

    stepperM0.setEnablePin(pins::M0_EN_PIN);
    stepperM1.setEnablePin(pins::M1_EN_PIN);
    stepperM2.setEnablePin(pins::M2_EN_PIN);

    stepperM0.setPinsInverted(config::M0DirInverted, config::M0StepInverted, config::M0EnInverted);
    stepperM1.setPinsInverted(config::M1DirInverted, config::M1StepInverted, config::M1EnInverted);
    stepperM2.setPinsInverted(config::M2DirInverted, config::M2StepInverted, config::M2EnInverted);

    stepperM0.enableOutputs();
    stepperM1.enableOutputs();
    stepperM2.enableOutputs();
}

void motorLoop() {
    if (stepperM0.distanceToGo() == 0) {
        Serial.println("stepper M0 distance reached 0");
        stepperM0.disableOutputs();
        delay(100);
        stepperM0.move(100 * config::M0steps_per_mm); // Move 100mm
        stepperM0.enableOutputs();
    }

    if (stepperM1.distanceToGo() == 0) {
        Serial.println("stepper M1 distance reached 0");
        stepperM1.disableOutputs();
        delay(100);
        stepperM1.move(100 * config::M1steps_per_mm); // Move 100mm
        stepperM1.enableOutputs();
    }

    if (stepperM2.distanceToGo() == 0) {
        Serial.println("stepper M2 distance reached 0");
        stepperM2.disableOutputs();
        delay(100);
        stepperM2.move(100 * config::M2steps_per_mm); // Move 100mm
        stepperM2.enableOutputs();
    }

    stepperM0.run();
    stepperM1.run();
    stepperM2.run();
}

int deadzone(int inputValue, int pointZero, int deadzoneSize) {
    if (abs(inputValue - pointZero) <= deadzoneSize)
        return pointZero;
    return inputValue;
}


bool motorPowerSave(AccelStepper& motor, Adafruit_NeoPixel& pixels, uint16_t statusLED) {
    if (motor.speed() == 0) {
        motor.disableOutputs();
        pixels.setPixelColor(statusLED, pixels.Color(0, 0, 0));
        return true;
    }
    else {
        motor.enableOutputs();
        pixels.setPixelColor(statusLED, pixels.Color(0, 0, 255));
        return false;
    }
}

bool motorInPowerSave(AccelStepper& motor) {
    return motor.speed() == 0;
}
