#include <dev/io.h>

void tone(uint8_t _pin, unsigned int frequency, unsigned long duration)
{

    (*(volatile uint32_t *) IO_TONE_PERIOD) = 1000000 / frequency;
    (*(volatile uint32_t *) IO_TONE_DURATION) = duration; 
}

void noTone(uint8_t _pin)
{
    (*(volatile uint32_t *) IO_TONE_DURATION) = 0;
}

