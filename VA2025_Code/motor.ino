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

    driverM0.rms_current(600);    // Set stepper current to 600mA. The command is the same as command TMC2130.setCurrent(600, 0.11, 0.5);
    driverM1.rms_current(600);

    //driverM0.en_pwm_mode(1);      // Enable extremely quiet stepping
    //driverM1.en_pwm_mode(1);      // Enable extremely quiet stepping

    driverM0.pwm_autoscale(1);
    driverM1.pwm_autoscale(1);

    driverM0.microsteps(1);
    driverM1.microsteps(1);
    
    /************************ init stepper ***************************/

    stepperM0.setMaxSpeed(50 * steps_per_mm); // 100mm/s @ 80 steps/mm
    stepperM1.setMaxSpeed(50 * steps_per_mm); // 100mm/s @ 80 steps/mm
    stepperM2.setMaxSpeed(50 * steps_per_mm); // 100mm/s @ 80 steps/mm

    stepperM0.setAcceleration(1000 * steps_per_mm); // 2000mm/s^2
    stepperM1.setAcceleration(1000 * steps_per_mm); // 2000mm/s^2
    stepperM2.setAcceleration(1000 * steps_per_mm); // 2000mm/s^2

    stepperM0.setEnablePin(pins::M0_EN_PIN);
    stepperM1.setEnablePin(pins::M1_EN_PIN);
    stepperM2.setEnablePin(pins::M2_EN_PIN);

    stepperM0.setPinsInverted(false, false, true);
    stepperM1.setPinsInverted(false, false, true);
    stepperM2.setPinsInverted(false, false, true);

    stepperM0.enableOutputs();
    stepperM1.enableOutputs();
    stepperM2.enableOutputs();
}

void motorLoop() {
    if (stepperM0.distanceToGo() == 0) {
        Serial.println("stepper M0 distance reached 0");
        stepperM0.disableOutputs();
        delay(100);
        stepperM0.move(100 * steps_per_mm); // Move 100mm
        stepperM0.enableOutputs();
    }

    if (stepperM1.distanceToGo() == 0) {
        Serial.println("stepper M1 distance reached 0");
        stepperM1.disableOutputs();
        delay(100);
        stepperM1.move(100 * steps_per_mm); // Move 100mm
        stepperM1.enableOutputs();
    }

    if (stepperM2.distanceToGo() == 0) {
        Serial.println("stepper M2 distance reached 0");
        stepperM2.disableOutputs();
        delay(100);
        stepperM2.move(100 * steps_per_mm); // Move 100mm
        stepperM2.enableOutputs();
    }

    stepperM0.run();
    stepperM1.run();
    stepperM2.run();
}