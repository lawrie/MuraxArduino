/* EMARD */

#include "Arduino.h"
#include "wiring_analog.h"
#include <dev/io.h>

__BEGIN_DECLS

static uint8_t analog_write_resolution_bits = 8;
/* old arduino uses 490 Hz */
/* new arduino uses 980 Hz */
static uint32_t analog_write_frequency = 980;

/* todo: support analogWriteResolution(bits)
** default is 8 for old arduino,
** new arduino can use up to 12
*/
void analogWriteResolution(int res)
{
  analog_write_resolution_bits = res;
}

void analogWriteFrequency(int freq)
{
  analog_write_frequency = freq;
}

void analogWritePhase(uint32_t pin, uint32_t phase)
{
}

/* setup the common parameters (why isn't it called at startup?)
*/
void analogOutputInit( void )
{
}

void analogWrite(uint32_t ulPin, uint32_t ulValue)
{
    if (PWM_PINS[ulPin] >= 0) pinMode(PWM_PINS[ulPin], OUTPUT);
    (*(volatile uint32_t *)IO_MUX) |= (1 << (ulPin + PWM_MUX)); 
    (*(volatile uint32_t *) (IO_PWM_DUTY + (ulPin << 2))) = ulValue;
}

void analogReference( eAnalogReference ulMode ) 
{
}

uint32_t analogRead(uint32_t ulPin)
{
  return (*(volatile uint32_t *) (IO_ANALOG + ((ulPin - A0) << 2)));
}

/* input capture setting */
uint32_t setInputCapture(uint32_t ulPin)
{
  return 0;
}

__END_DECLS
