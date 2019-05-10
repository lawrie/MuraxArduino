#ifndef _SEVEN_SEGMENT_CLASS_
#define _SEVEN_SEGMENT_CLASS_

#define IO_SEVEN_SEGMENT ((volatile uint32_t*) IO_SEVEN_SEGMENT_A)

class SevenSegmentClass {
  public:
    SevenSegmentClass(uint8_t channel) : _channel(channel) {}
    void write(int data);
  private:
    uint8_t _channel;
};

extern SevenSegmentClass SevenSegment;

#endif

