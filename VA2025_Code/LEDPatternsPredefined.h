#pragma once
#include "Arduino.h"

namespace predifined {
	inline constexpr uint8_t allLEDS[] = {
		4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37
	};
	
	inline constexpr uint8_t row1LEDs[] = {
		4, 5, 6, 7, 8, 9
	};

	inline constexpr uint8_t row2LEDs[] = {
		10, 11, 12, 13, 14, 15
	};

	inline constexpr uint8_t row3LEDs[] = {
		16, 17, 18, 19, 20, 21
	};

	inline constexpr uint8_t row4LEDs[] = {
		22, 23, 24, 25, 26, 27
	};
	
	inline constexpr uint8_t topLEDs[] = {
		28, 29, 30, 31, 32, 33, 34, 35, 36, 37
	};

	inline constexpr size_t allLEDS_size = sizeof(allLEDS) / sizeof(allLEDS[0]);
	inline constexpr size_t row1LEDs_size = sizeof(row1LEDs) / sizeof(row1LEDs[0]);
	inline constexpr size_t row2LEDs_size = sizeof(row2LEDs) / sizeof(row2LEDs[0]);
	inline constexpr size_t row3LEDs_size = sizeof(row3LEDs) / sizeof(row3LEDs[0]);
	inline constexpr size_t row4LEDs_size = sizeof(row4LEDs) / sizeof(row4LEDs[0]);
	inline constexpr size_t topLEDs_size = sizeof(topLEDs) / sizeof(topLEDs[0]);
}