#ifndef _CONFIG_h
#define _CONFIG_h

namespace config {
	constexpr uint8_t DRIVER_ADDRESS = 0b00;
	constexpr float R_SENSE = 0.11f;
	constexpr uint16_t movmentStepperMicroStepps = 1;
	constexpr uint16_t movmentStepperRMSCurrent = 600; // mA

	constexpr uint32_t M0steps_per_mm = 40;
	constexpr uint32_t M1steps_per_mm = 40;
	constexpr uint32_t M2steps_per_mm = 40;

	constexpr uint32_t M0MaxSpeed = 180 * M0steps_per_mm; // 50mm/s @ 80 steps/mm
	constexpr uint32_t M1MaxSpeed = 180 * M1steps_per_mm; // 50mm/s @ 80 steps/mm
	constexpr uint32_t M2MaxSpeed = 180 * M2steps_per_mm; // 50mm/s @ 80 steps/mm

	constexpr uint32_t M0Acceleration = 50 * config::M0steps_per_mm; // 2000mm/s^2
	constexpr uint32_t M1Acceleration = 50 * config::M1steps_per_mm; // 2000mm/s^2
	constexpr uint32_t M2Acceleration = 50 * config::M2steps_per_mm; // 2000mm/s^2

	constexpr bool M0DirInverted = false;
	constexpr bool M1DirInverted = false;
	constexpr bool M2DirInverted = false;

	constexpr bool M0StepInverted = false;
	constexpr bool M1StepInverted = false;
	constexpr bool M2StepInverted = false;

	constexpr bool M0EnInverted = true;
	constexpr bool M1EnInverted = true;
	constexpr bool M2EnInverted = true;

	constexpr uint16_t neopixelCount = 40;
	constexpr uint16_t generalStatusLED = 0; 
	constexpr uint16_t M0StatusLED = 1;
	constexpr uint16_t M1StatusLED = 2;
	constexpr uint16_t M2StatusLED = 3;

	constexpr unsigned long LEDBlinkDelay = 500;
	constexpr unsigned long ComputationDelay = 100;

	constexpr long psxAnalogMin = 0;
	constexpr long psxAnalogMax = 255;

	constexpr long moveMotorMappedMin = -180 * M0steps_per_mm; // 50mm/s @ 80 steps/mm
	constexpr long headMotorMappedMin = -40 * M2steps_per_mm; // 50mm/s @ 80 steps/mm

	constexpr long moveMotorMappedMax = 180 * M0steps_per_mm; // 50mm/s @ 80 steps/mm
	constexpr long headMotorMappedMax = 40 * M2steps_per_mm; // 50mm/s @ 80 steps/mm

	constexpr int motorDeadzoneZero = 0;
	constexpr int motorDeadzoneSize = 240;

}
#endif