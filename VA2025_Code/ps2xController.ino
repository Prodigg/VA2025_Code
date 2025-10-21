
void initController() {
    byte error = -1;

    while (error != 0) {
        error = ps2x.config_gamepad(pins::PS2_CLK, pins::PS2_CMD, pins::PS2_SEL, pins::PS2_DAT, false, false);

        if (error == 0) { }
        else if (error == 1) {
            Serial.println("No controller found");
            delay(3000);
        }
        else if (error == 2)
            Serial.println("Controller found but not accepting commands.");

        else if (error == 3)
            Serial.println("Controller refusing to enter Pressures mode");
    

        switch (ps2x.readType()) {
        case 0:
            Serial.print("Unknown Controller type found");
            error = -1;
            break;
        case 1: // valid controller, continue
            break;
        case 2:
            Serial.print("Unsuported Controller found");
            error = -1;
            break;
        case 3:
            Serial.print("Unsuported Controller found");
            error = -1;
            break;
        }
    }
}

void loopController() {
    
   ps2x.read_gamepad(false, false);

   if (ps2x.Button(PSB_START))         //will be TRUE as long as button is pressed
       Serial.println("Start is being held");
   if (ps2x.Button(PSB_SELECT))
       Serial.println("Select is being held");

   if (ps2x.Button(PSB_PAD_UP)) {      
       Serial.println("Up held this hard: ");
   }
   if (ps2x.Button(PSB_PAD_RIGHT)) {
       Serial.println("Right held this hard: ");
   }
   if (ps2x.Button(PSB_PAD_LEFT)) {
       Serial.println("LEFT held this hard: ");
   }
   if (ps2x.Button(PSB_PAD_DOWN)) {
       Serial.println("DOWN held this hard: ");
   }

   if (ps2x.NewButtonState()) {        //will be TRUE if any button changes state (on to off, or off to on)
       if (ps2x.Button(PSB_L3))
           Serial.println("L3 pressed");
       if (ps2x.Button(PSB_R3))
           Serial.println("R3 pressed");
       if (ps2x.Button(PSB_L2))
           Serial.println("L2 pressed");
       if (ps2x.Button(PSB_R2))
           Serial.println("R2 pressed");
       if (ps2x.Button(PSB_TRIANGLE))
           Serial.println("Triangle pressed");
   }

   if (ps2x.ButtonPressed(PSB_CIRCLE))               //will be TRUE if button was JUST pressed
       Serial.println("Circle just pressed");
   if (ps2x.NewButtonState(PSB_CROSS))               //will be TRUE if button was JUST pressed OR released
       Serial.println("X just changed");
   if (ps2x.ButtonReleased(PSB_SQUARE))              //will be TRUE if button was JUST released
       Serial.println("Square just released");

   if (ps2x.Button(PSB_L1) || ps2x.Button(PSB_R1)) { //print stick values if either is TRUE
       Serial.print("Stick Values:");
       Serial.print(ps2x.Analog(PSS_LY), DEC); //Left stick, Y axis. Other options: LX, RY, RX  
       Serial.print(",");
       Serial.print(ps2x.Analog(PSS_LX), DEC);
       Serial.print(",");
       Serial.print(ps2x.Analog(PSS_RY), DEC);
       Serial.print(",");
       Serial.println(ps2x.Analog(PSS_RX), DEC);
   }
}