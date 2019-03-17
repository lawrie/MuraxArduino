#include <Arduino.h>
#include <dev/io.h>
#include "wiring_private.h"

__BEGIN_DECLS

void attachInterrupt(uint32_t pin, void (*callback)(void), uint32_t mode) {
  (*(volatile uint32_t*)IO_PIN_INTERRUPT) = callback;
  (*(volatile uint32_t*)IO_PIN_INTERRUPT_CONFIG) = (mode == FALLING ? 2 : 0) | (mode == RISING ? 1 : 0);
}

void detachInterrupt(uint32_t pin) {
  (*(volatile uint32_t*)IO_PIN_INTERRUPT) = 0;
  (*(volatile uint32_t*)IO_PIN_INTERRUPT_CONFIG) = 0;
}
 
__END_DECLS
