#include "SevenSegment.h"

void
SevenSegmentClass::write(int data) {
  if (_channel == 0) {
    pinMode(SEVEN_SEGMENT_A_DIGIT_PIN, OUTPUT);
    for(int i=0;i<7;i++) pinMode(SEVEN_SEGMENT_A_SEG_PINS[i], OUTPUT);
    Mux.set(SEVEN_SEGMENT_A_MUX);
  } else if (_channel == 1) { 
    pinMode(SEVEN_SEGMENT_B_DIGIT_PIN, OUTPUT);
    for(int i=0;i<7;i++) pinMode(SEVEN_SEGMENT_B_SEG_PINS[i], OUTPUT);
    Mux.set(SEVEN_SEGMENT_B_MUX);
  }
 
  IO_SEVEN_SEGMENT[_channel * 0x2000] = data;
}

SevenSegmentClass SevenSegment(0);
