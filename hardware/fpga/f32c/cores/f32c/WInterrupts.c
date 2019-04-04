#include <Arduino.h>
#include <dev/io.h>
#include "wiring_private.h"

__BEGIN_DECLS

void attachInterrupt(uint32_t pin, void (*callback)(void), uint32_t mode) {
  (*(volatile uint32_t*)IO_PIN_INTERRUPT_MASKS) = 0xFFFFFFFF;
  (*(volatile uint32_t*)(IO_PIN_INTERRUPT + (pin << 2))) = callback;

  if (mode == RISING || mode == CHANGE) {
    (*(volatile uint32_t*)IO_PIN_INTERRUPT_RISING) |=  (1 << pin);
  }

  if (mode == FALLING || mode == CHANGE) {
    (*(volatile uint32_t*)IO_PIN_INTERRUPT_FALLING) |=  (1 << pin);
  }
}

void detachInterrupt(uint32_t pin) {
  (*(volatile uint32_t*)(IO_PIN_INTERRUPT + (pin << 2))) = 0;
  (*(volatile uint32_t*)IO_PIN_INTERRUPT_RISING) &= ~(1 << pin);
  (*(volatile uint32_t*)IO_PIN_INTERRUPT_FALLING) &= ~(1 << pin);
}

static uint32_t old_timer_masks;

void interrupts(void) {
  (*(volatile uint32_t*)IO_PIN_INTERRUPT_MASKS) = 0xFFFFFFFF;
  (*(volatile uint32_t*)IO_TIMER_INTERRUPT_MASKS) = old_timer_masks;
}

void noInterrupts(void) {
  old_timer_masks = (*(volatile uint32_t*)IO_TIMER_INTERRUPT_MASKS);
  (*(volatile uint32_t*)IO_PIN_INTERRUPT_MASKS) = 0;
  (*(volatile uint32_t*)IO_TIMER_INTERRUPT_MASKS) = 0;
}

   
__END_DECLS
