#pragma once
#include <Adafruit_NeoPixel.h>

namespace LEDPatterns {
	class WalkingLight_t {
	public:
		WalkingLight_t(Adafruit_NeoPixel& neopixels) : _pixels(neopixels) {};
		inline WalkingLight_t& setPixelPattern(uint8_t pixelPatternArray, size_t size);

		inline WalkingLight_t& setDrawingTime(long long ms) { _drawingWaitTime = ms; return *this; };

		//inline WalkingLight_t& dotLength(uint8_t length, uint8_t* dotHistoryArray) { _dotLength = length; return *this; };

		inline WalkingLight_t& eraseBehind(bool erase) { _eraseBehind = erase; return *this; };

		inline WalkingLight_t& pixelOnColor(uint32_t color) { _pixelOnColor = color; return *this; };

		inline WalkingLight_t& pixelOffColor(uint32_t color) { _pixelOffColor = color; return *this; };

		inline WalkingLight_t& bounceLight(bool bounceLight) { _bounceLight = bounceLight; return *this; };

		/*!
		 * @brief the main draw function
		 */
		void draw();

	private:
		Adafruit_NeoPixel& _pixels;

		uint8_t* _pixelPatternArrayPtr = nullptr;
		size_t _pixelPatternArraySize = 0;


		long long _drawingWaitTime = 100;
		long long _previausDrawTime = 0;
		long long _currentMilis = 0;

		uint8_t _dotLength = 1;

		bool _eraseBehind = true;
		bool _bounceLight = false;

		uint32_t _pixelOnColor = 0;
		uint32_t _pixelOffColor = 0;

		uint8_t _pixelPatternIndex = 0;
		bool _pixelPatternReverse = false;

		uint8_t calcNextPixelPatternIndex(uint8_t currentPixelPatternIndex);
	};
}


