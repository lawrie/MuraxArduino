#include <Arduino.h>

void tone(uint8_t _pin, unsigned int frequency, unsigned long duration)
{
    pinMode(TONE_PIN, OUTPUT); // Make Tone pin output
    (*(volatile uint32_t *) IO_MUX) &= ~(1 << SERVO_MUX); // Switch off servo mux
    (*(volatile uint32_t *) IO_MUX) |= (1 << TONE_MUX);   // Switch on Tone mux
    (*(volatile uint32_t *) IO_TONE_PERIOD) = 1000000 / frequency;
    (*(volatile uint32_t *) IO_TONE_DURATION) = duration; 
}

void noTone(uint8_t _pin)
{
    (*(volatile uint32_t *) IO_TONE_DURATION) = 0;
    (*(volatile uint32_t *) IO_MUX) &= ~(1 << TONE_MUX); // Switch off tone mux
}

