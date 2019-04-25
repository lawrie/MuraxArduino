
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

// Other pins
static const uint8_t PWM_PIN = 46;
static const uint8_t TONE_PIN = 47;
static const uint8_t SPI_START_PIN = 40;

// Muxes
static const uint8_t SHIFT_IN_MUX = 0;
static const uint8_t SHIFT_OUT_MUX = 1;
static const uint8_t SEVEN_SEGMENT_MUX1 = 2;
static const uint8_t SERVO_MUX = 3;
static const uint8_t SEVEN_SEGMENT_MUX0 = 4;
static const uint8_t SPI_MUX = 5;
static const uint8_t PWM_MUX = 6;
static const uint8_t TONE_MUX = 9;

#endif /* _f32c_variant_h */

