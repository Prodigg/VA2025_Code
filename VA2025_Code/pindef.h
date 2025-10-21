#pragma once
typedef int16_t pin_t;

namespace pins {
	constexpr pin_t neopixelPin = 6;
	constexpr pin_t buttonPin = 21;
	constexpr pin_t PS2_DAT = 16;     
	constexpr pin_t PS2_CMD = 19; 
	constexpr pin_t PS2_SEL = 17; 
	constexpr pin_t PS2_CLK = 18;

	constexpr pin_t M0_EN_PIN   = 7;
	constexpr pin_t M0_DIR_PIN  = 2;
	constexpr pin_t M0_STEP_PIN = 3;
	constexpr pin_t M0_CS_PIN   = 8;
	constexpr SerialUART* M0_SERIAL_PORT = &Serial1;

	constexpr pin_t M1_EN_PIN   = 12;
	constexpr pin_t M1_DIR_PIN  = 11;
	constexpr pin_t M1_STEP_PIN = 14;
	constexpr pin_t M1_CS_PIN   = 13;
	constexpr SerialUART* M1_SERIAL_PORT = &Serial2;

	constexpr pin_t M2_EN_PIN   = 27;
	constexpr pin_t M2_DIR_PIN  = 28;
	constexpr pin_t M2_STEP_PIN = 15;
	constexpr pin_t M2_CS_PIN   = 22;

}