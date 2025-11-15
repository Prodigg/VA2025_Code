#pragma once
#include <Adafruit_NeoPixel.h>
#include "global.h"

namespace LEDPatterns {
	class WalkingLight_t {
	public:
		WalkingLight_t(Adafruit_NeoPixel& neopixels) : _pixels(neopixels) {};
		WalkingLight_t& setPixelPattern(const uint8_t* pixelPatternArray, size_t size);

		inline WalkingLight_t& setDrawingTime(long long ms) { _drawingWaitTime = ms; return *this; };

		//inline WalkingLight_t& dotLength(uint8_t length, uint8_t* dotHistoryArray) { _dotLength = length; return *this; };

		inline WalkingLight_t& eraseBehind(bool erase) { _eraseBehind = erase; return *this; };

		inline WalkingLight_t& pixelOnColor(uint32_t color) { _pixelOnColor = color; return *this; };

		inline WalkingLight_t& pixelOffColor(uint32_t color) { _pixelOffColor = color; return *this; };

		inline WalkingLight_t& bounceLight(bool bounceLight) { _bounceLight = bounceLight; return *this; };

		bool isAnimationAtEnd() { return _pixelPatternIndex >= _pixelPatternArraySize - 1; }

		/*!
		 * @brief the main draw function
		 */
		void draw();

	private:
		Adafruit_NeoPixel& _pixels;

		const uint8_t* _pixelPatternArrayPtr = nullptr;
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

	class pulsating_t {
	public:
		pulsating_t(Adafruit_NeoPixel& neopixels) : _pixels(neopixels) {};
		pulsating_t& setPixelPattern(const uint8_t* pixelPatternArray, size_t size);
		inline pulsating_t& setColor(uint16_t hue, uint8_t saturation) { _colorHue = hue; _colorSaturation = saturation; return *this; };
		inline pulsating_t& timeFactor(double timeFactor) { _timeFactor = timeFactor; return *this; };
		uint8_t currentColorBrightness() { return _colorBrightness; }

		void draw();
	private:
		Adafruit_NeoPixel& _pixels;

		const uint8_t* _pixelPatternArrayPtr = nullptr;
		size_t _pixelPatternArraySize = 0;

		uint16_t _colorHue = 0;
		uint8_t _colorSaturation = 0;
		uint8_t _colorBrightness = 0;
		uint32_t _color = 0;
		double _timeFactor = 1;
	};

	class rainbow_t {
	public:
		rainbow_t(Adafruit_NeoPixel& neopixels) : _pixels(neopixels) {};
		rainbow_t& setPixelPattern(const uint8_t* pixelPatternArray, size_t size);
		rainbow_t& setStepSize(uint8_t stepSize) { _stepSize = stepSize; return *this; }
		void draw();
	private:
		Adafruit_NeoPixel& _pixels;

		const uint8_t* _pixelPatternArrayPtr = nullptr;
		size_t _pixelPatternArraySize = 0;
		
		uint8_t _stepSize = 10;

		uint16_t _colorHue = 0;
		uint32_t _color = 0;
	};
}


