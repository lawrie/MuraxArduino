/*
  Copyright (c) 2011 Arduino.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
  See the GNU Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include "Arduino.h"
//#include "wiring_private.h"


/* Measures the length (in microseconds) of a pulse on the pin; state is HIGH
 * or LOW, the type of pulse to measure.  Works on pulses from 2-3 microseconds
 * to 3 minutes in length, but must be called at least a few dozen microseconds
 * before the start of the pulse. */
extern uint32_t
pulseIn(uint32_t pin, bool state, uint32_t timeout)
{
  uint32_t index = pin * 4; // 4 words per channel

  pinMode(PULSE_IN_PIN, INPUT);

  ((volatile uint32_t *)IO_PULSE_TIMEOUT)[index] = timeout;
  ((volatile uint32_t *)IO_PULSE_VALUE)[index] = state;

  uint32_t pulse; 

  for(int i=0;i<100000;i++) {
    pulse = ((volatile uint32_t *)IO_PULSE_LENGTH)[index];
    if (pulse != 0) return pulse;
  }

  return 0;
}

extern uint32_t
pulseInLong(uint32_t pin, bool state, uint32_t timeout)
{
  return pulseIn(pin, state, timeout);
}

