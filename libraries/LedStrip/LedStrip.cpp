#include "LedStrip.h"
#include <Mux.h>

LedStrip::LedStrip(uint16_t n, uint8_t p) :
  brightness(0) {
  updateLength(n);
  setPin(p);
}

void LedStrip::begin(void) {
  pinMode(pin, OUTPUT);
  Mux.set(12);
}

void LedStrip::updateLength(uint16_t n) {
  numLEDs = n;
}

void LedStrip::show(void) {}

void LedStrip::setPixelColor( uint16_t n, uint8_t r, uint8_t g, uint8_t b) {
  setPixelColor(n, Color(r, g, b));
}

void LedStrip::setPixelColor(uint16_t n, uint32_t c) {
  LEDS_PIXEL = c;
  LEDS_ADDR  = n;
}

void LedStrip::fill(uint32_t c, uint16_t first, uint16_t count) {
  uint16_t i, end;

  if(first >= numLEDs) {
    return;
  }

  if(count == 0) {
    end = numLEDs;
  } else {
    end = first + count;
    if(end > numLEDs) end = numLEDs;
  }

  for(i = first; i < end; i++) {
    this->setPixelColor(i, c);
  }
}

void LedStrip::setPin(uint8_t p) {
  pin = p;
}

void LedStrip::setBrightness(uint8_t b) {
  brightness = b;
}

void LedStrip::clear(void) {
  LEDS_PIXEL = 0;
  for (int i=0;i<numLEDs;i++) LEDS_ADDR = i;
}

