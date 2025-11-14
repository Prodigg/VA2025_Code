#include "LEDPatterns.h"

inline LEDPatterns::WalkingLight_t& LEDPatterns::WalkingLight_t::setPixelPattern(uint8_t* pixelPatternArray, size_t size) {
  _pixelPatternArrayPtr = pixelPatternArray;
  _pixelPatternArraySize = size;
  return *this;
}

void LEDPatterns::WalkingLight_t::draw() {
  if (_pixelPatternArrayPtr == nullptr)
    return;

  _currentMilis = millis();
  if (_currentMilis >= _previausDrawTime + _drawingWaitTime) {
    _previausDrawTime = _currentMilis;
    
      if (_eraseBehind)
        _pixels.setPixelColor(_pixelPatternArrayPtr[_pixelPatternIndex], _pixelOffColor);
      _pixelPatternIndex = calcNextPixelPatternIndex(_pixelPatternIndex);
      _pixels.setPixelColor(_pixelPatternArrayPtr[_pixelPatternIndex], _pixelOnColor);
  }
  
}

uint8_t LEDPatterns::WalkingLight_t::calcNextPixelPatternIndex(uint8_t currentPixelPatternIndex) {
  if (currentPixelPatternIndex >= _pixelPatternArraySize) {
    if (_bounceLight) {
      _pixelPatternReverse = true;
      return _pixelPatternArraySize - 1;
    }
    else {
      return 0; // return start of array
    }
  }

  if (currentPixelPatternIndex == 0 && _pixelPatternReverse) {
    _pixelPatternReverse = false;
    return 1; // start at one
  }

  // if no special case is present, use default counter
  if (_pixelPatternReverse)
    return --currentPixelPatternIndex;
  else
    return ++currentPixelPatternIndex;
}

LEDPatterns::pulsating_t& LEDPatterns::pulsating_t::setPixelPattern(uint8_t* pixelPatternArray, size_t size) {
  _pixelPatternArrayPtr = pixelPatternArray;
  _pixelPatternArraySize = size;
  return *this;
}

void LEDPatterns::pulsating_t::draw() {
  if (_pixelPatternArrayPtr == nullptr)
    return;

  _colorBrightness = static_cast<uint8_t>(map<double>(sin(millis()), -1, 1, 0, 255));
  _color = Adafruit_NeoPixel::ColorHSV(_colorHue, _colorSaturation, _colorBrightness);

  for (size_t i = 0; i < _pixelPatternArraySize; i++) {
    _pixels.setPixelColor(_pixelPatternArrayPtr[i], _color);
  }
}

LEDPatterns::rainbow_t& LEDPatterns::rainbow_t::setPixelPattern(uint8_t* pixelPatternArray, size_t size) {
  _pixelPatternArrayPtr = pixelPatternArray;
  _pixelPatternArraySize = size;
  return *this;
}

void LEDPatterns::rainbow_t::draw() {
  if (_pixelPatternArrayPtr == nullptr)
    return;

  _colorHue += _stepSize;
  _color = Adafruit_NeoPixel::ColorHSV(_colorHue);

  for (size_t i = 0; i < _pixelPatternArraySize; i++) {
    _pixels.setPixelColor(_pixelPatternArrayPtr[i], _color);
  }
}