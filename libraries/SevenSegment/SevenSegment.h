#ifndef _SEVEN_SEGMENT_CLASS_
#define _SEVEN_SEGMENT_CLASS_

#define IO_SEVEN_SEGMENT (*(volatile uint32_t*)0xF0090000)

class SevenSegmentClass {
  public:
    void write(int data);
};

extern SevenSegmentClass SevenSegment;

#endif

