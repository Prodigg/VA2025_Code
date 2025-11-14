#include "LEDPatterns.h"

inline LEDPatterns::WalkingLight_t& LEDPatterns::WalkingLight_t::setPixelPattern(uint8_t pixelPatternArray, size_t size) {
  _pixelPatternArrayPtr = pixelPatternArray;
  _pixelPatternArraySize = size;
  return *this;
}

void LEDPatterns::WalkingLight_t::draw() {

  _currentMilis = millis();
  if (_currentMilis >= _previausDrawTime + _drawingWaitTime) {
    _previausDrawTime = _currentMilis;
    
      if (_eraseBehind)
        pixels.setPixelColor(_pixelPatternArrayPtr[_pixelPatternIndex], _pixelOffColor);
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
