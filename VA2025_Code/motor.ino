void motorInit() {
    Serial.begin(9600);
    while (!Serial);
    Serial.println("Start...");
    pinMode(CS_PIN, OUTPUT);
    digitalWrite(CS_PIN, HIGH);
    driver.begin();             // Initiate pins and registeries
    driver.rms_current(600);    // Set stepper current to 600mA. The command is the same as command TMC2130.setCurrent(600, 0.11, 0.5);
    //driver.en_pwm_mode(1);      // Enable extremely quiet stepping
    driver.pwm_autoscale(1);
    driver.microsteps(1);

    stepper.setMaxSpeed(50 * steps_per_mm); // 100mm/s @ 80 steps/mm
    stepper.setAcceleration(1000 * steps_per_mm); // 2000mm/s^2
    stepper.setEnablePin(EN_PIN);
    stepper.setPinsInverted(false, false, true);
    stepper.enableOutputs();
    Serial.println("Start done");
}

void motorLoop() {
    if (stepper.distanceToGo() == 0) {
        Serial.println("stepper distance reached 0");
        stepper.disableOutputs();
        delay(100);
        stepper.move(100 * steps_per_mm); // Move 100mm
        stepper.enableOutputs();
    }
    stepper.run();
}