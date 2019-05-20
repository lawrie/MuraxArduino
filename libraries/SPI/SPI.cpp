#include <SPI.h>
#include <Arduino.h>

SPIClass SPI;

#if defined(IO_SPI_MASTER_A)
SPIClass SPI1(1);
#endif

SPIClass::SPIClass(uint8_t spi_bus)
    :_spi_num(spi_bus)
    ,_spi(NULL)
    ,_ss(-1)
    ,_divider(5)
{}

void SPIClass::begin(int8_t ss)
{
    int start_pin = SPI_MASTER_SCLK;
    int spi_mux = SPI_MASTER_MUX;

#if defined(IO_SPI_MASTER_A)
    if (_spi_num == 1) {
      start_pin = SPI_MASTER_A_SCLK;
      spi_mux = SPI_MASTER_A_MUX;
    }
#endif

    // Set SPI pins
    for(int i=0;i<4;i++) pinMode(start_pin + i, (i == 2 ? INPUT : OUTPUT));

    // Set Mux 5
    (*(volatile uint32_t*)IO_MUX) |= (1 << spi_mux);

    // Initialise SPI peripheral
    _ss = ss;
    _spi = (volatile uint32_t *)(IO_SPI_MASTER + (_spi_num * 0x1000));
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

void SPIClass::beginTransaction(SPISettings settings) {
    setClockDivider((F_CPU / settings._clock) / 2);
    setDataMode(settings._dataMode);
    beginTransaction();
}

void SPIClass::beginTransaction() {
    _spi[0] = 0x11000000;
}

void SPIClass::endTransaction() {
    _spi[0] = 0x10000000;
}
 
