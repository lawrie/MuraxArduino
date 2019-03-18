#ifndef _DIRTY_WORKAROUND_H_
#define _DIRTY_WORKAROUND_H_
#define __arm__

#if 1
#define SCK  10
#define SS   11
#define MOSI 13
#define MISO 8
#define softdelay()
#endif

#define SOFTWARE_SPI

#define cli() noInterrupts()
#define sei() interrupts()
#define fastDigitalWrite(a,b) digitalWrite(a,b)
#define fastDigitalRead(a) digitalRead(a)
#endif
