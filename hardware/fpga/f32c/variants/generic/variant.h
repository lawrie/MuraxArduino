
#ifndef _f32c_variant_h
#define _f32c_variant_h

#include <stdint.h>

/* LEDs */
#define PIN_LED_13           0
#define PIN_LED              0
#define LED_BUILTIN          0

#include "Arduino.h"
#ifdef __cplusplus
#include "UARTClass.h"
#endif

#ifdef __cplusplus
extern UARTClass Serial;
#endif

/*
 * Analog pins - currently dummies to make thing compile
 */
static const uint8_t A0  = 16;
static const uint8_t A1  = 17;
static const uint8_t A2  = 18;
static const uint8_t A3  = 19;
static const uint8_t A4  = 20;
static const uint8_t A5  = 21;

#endif /* _f32c_variant_h */

