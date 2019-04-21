#include "Mux.h"
#include <dev/io.h>

void
MuxClass::set(int pin) {
  (*(volatile uint32_t*)IO_MUX) |= (1 << pin);
}

void
MuxClass::unset(int pin) {
  (*(volatile uint32_t*)IO_MUX) &= ~(1 << pin);
}

MuxClass Mux;
