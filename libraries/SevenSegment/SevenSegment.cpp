#include "SevenSegment.h"
#include <dev/io.h>

void
SevenSegmentClass::write(int data) {
  if (_channel == 0) {
    // Channel 0 needs pins setting to output and mux 4 setting
    (*(volatile uint32_t*)IO_GPIOB_CTL) |= 0xFF;
    (*(volatile uint32_t*)IO_MUX) |= 0x10;
  } else if (_channel == 1) { 
    // Channel 1 needs the pins set to output and mux 2 setting
    (*(volatile uint32_t*)IO_GPIO_CTL) |= 0xF0F0000;
    (*(volatile uint32_t*)IO_MUX) |= 0x04;
  }
 
  IO_SEVEN_SEGMENT[_channel * 0x2000] = data;
}

SevenSegmentClass SevenSegment(0);
