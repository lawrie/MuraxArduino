#include <SPI.h>
#include <Arduino.h>

SPIClass SPI;

SPIClass::SPIClass(uint8_t spi_bus)
    :_spi_num(spi_bus)
    ,_spi(NULL)
    ,_ss(-1)
    ,_divider(62) // default is minimum SPI speed, about 400 kHz
{}

void SPIClass::begin(int8_t ss)
{
    _ss = ss;
    _spi = (volatile uint32_t *)(0xF0060000 + (_spi_num * 0x100));
    _spi[3] = _divider;
    _spi[4] = 500; // setup
    _spi[5] = 500; // hold
    _spi[6] = 500; //disable
}

void SPIClass::end() {
}

void SPIClass::setClockDivider(uint32_t divider)
{
    _divider = divider;
    _spi[3] = _divider;
}

void SPIClass::setBitOrder(uint8_t bitOrder) {
}

void SPIClass::setDataMode(uint8_t dataMode) {
    _spi[2] = dataMode;
}

uint8_t SPIClass::transfer(uint8_t data)
{
    _spi[0] = (data | 0x01000000); // Send and push reply

    while(1) {
      uint32_t r = ((volatile uint32_t *)_spi)[0];
      if (!(r & SPI_RX_VALID)) return r & 0xff;
    }
}

void SPIClass::set_pin(uint8_t pin)
{
    if (_spi_num == SPI_EXT) {
        digitalWrite(pin, LOW);
    }
}

void SPIClass::unset_pin(uint8_t pin)
{
    if (_spi_num == SPI_EXT) {
        digitalWrite(pin, HIGH);
    }
}

void SPIClass::beginTransaction(SPISettings settings) {
    setClockDivider((F_CPU / settings._clock) / 2);
    beginTransaction();
}

void SPIClass::beginTransaction() {
    _spi[0] = 0x11000000;
}

void SPIClass::endTransaction() {
    _spi[0] = 0x10000000;
}
 
