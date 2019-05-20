
#ifndef _f32c_variant_h
#define _f32c_variant_h

#include <stdint.h>

/* LEDs */
#define PIN_LED_13           3
#define PIN_LED              3
#define LED_BUILTIN          3

#include "Arduino.h"
#ifdef __cplusplus
#include "UARTClass.h"
#endif

#ifdef __cplusplus
extern UARTClass Serial;

#if defined(IO_SIO_A_BYTE) 
extern UARTClass Serial1;
#endif

#if defined(IO_SIO_B_BYTE) 
extern UARTClass Serial2;
#endif
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

static const int8_t PIN_INTERRUPT_PINS[] = {8,9};
static const int8_t PWM_PINS[] = {46,-1,-1,12,13};
static const uint8_t SEVEN_SEGMENT_A_DIGIT_PIN = 35;
static const int8_t SEVEN_SEGMENT_A_SEG_PINS[] = {32,33,34,36,37,38,39};
static const uint8_t SEVEN_SEGMENT_B_DIGIT_PIN = 27;
static const int8_t SEVEN_SEGMENT_B_SEG_PINS[] = {24,25,26,16,17,18,19};
static const uint8_t SPI_MASTER_MISO = 42;
static const uint8_t SPI_MASTER_MOSI = 41;
static const uint8_t SPI_MASTER_SCLK = 40;
static const uint8_t SPI_MASTER_SS = 43;
static const uint8_t SPI_MASTER_A_MISO = 30;
static const uint8_t SPI_MASTER_A_MOSI = 29;
static const uint8_t SPI_MASTER_A_SCLK = 28;
static const uint8_t SPI_MASTER_A_SS = 31;
static const uint8_t UART_A_RXD = 16;
static const uint8_t UART_A_TXD = 17;
static const uint8_t WS2811_DOUT = 44;

static const uint8_t SHIFT_IN_DATA_PIN = -1;
static const uint8_t SHIFT_IN_CLOCK_PIN = -1;



static const uint8_t SHIFT_OUT_DATA_PIN = -1;
static const uint8_t SHIFT_OUT_CLOCK_PIN = -1;



static const uint8_t TONE_PIN = -1;



static const uint8_t PULSE_IN_PINS[] = {};



#define SPI_SCLK SPI_MASTER_SCLK
#define SPI_MOSI SPI_MASTER_MOSI
#define SPI_MISO SPI_MASTER_MISO
#define SPI_SS SPI_MASTER_SS
#define SPI_START_PIN SPI_SCLK



// Muxes

static const uint8_t SEVEN_SEGMENT_A_MUX = 4;
static const uint8_t SEVEN_SEGMENT_B_MUX = 2;
static const uint8_t SPI_MASTER_MUX = 5;
static const uint8_t SPI_MASTER_A_MUX = 14;
static const uint8_t UART_A_MUX = 13;
static const uint8_t WS2811_MUX = 12;

static const uint8_t SHIFT_IN_MUX = 0;



static const uint8_t SHIFT_OUT_MUX = 0;



static const uint8_t TONE_MUX = 0;



static const uint8_t PWM_MUX = 6;

#endif /* _f32c_variant_h */

