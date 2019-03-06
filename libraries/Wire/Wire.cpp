/*
  TwoWire.cpp - TWI/I2C library for Wiring & Arduino
  Copyright (c) 2006 Nicholas Zambetti.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 
  Modified 2012 by Todd Krein (todd@krein.org) to implement repeated starts
*/

#include "Wire.h"

TwoWire::TwoWire()
{
}

void TwoWire::begin(void)
{
  I2C_SAMPLING_CLOCK_DIVIDER = 5;
  I2C_TIMEOUT = 50000;
  I2C_THIGH = 250;
  I2C_TLOW = 250;
  I2C_TBUF = 1000;
  I2C_TSU_DAT = 5;
}

void TwoWire::setClock(uint32_t frequency)
{
}

void TwoWire::begin(uint8_t address)
{
}

void TwoWire::beginTransmission(uint8_t address)
{
  I2C_TX_DATA = (address << 1) | I2C_TX_ENABLE | I2C_TX_VALID;
  I2C_TX_ACK = I2C_TX_VALID;
  I2C_MASTER_STATUS = I2C_MASTER_START;
  for(int i=0;i<MAX_TRIES && (I2C_TX_ACK & I2C_TX_VALID);i++) {};  // Wait for nack sent
}

size_t TwoWire::write(uint8_t data)
{
  I2C_TX_DATA = data | I2C_TX_ENABLE | I2C_TX_VALID;
  I2C_TX_ACK = I2C_TX_VALID;
  for(int i=0;i<MAX_TRIES && (I2C_TX_ACK & I2C_TX_VALID);i++) {};
  return 0;
}

size_t TwoWire::write(const uint8_t *data, size_t quantity)
{
	return 0;
}

void TwoWire::flush(void)
{
}

uint8_t TwoWire::endTransmission(uint8_t sendStop)
{
  for (int i = 0; i < 1000; i++) asm volatile ("");
  I2C_RX_DATA = 0;
  I2C_MASTER_STATUS = I2C_MASTER_STOP; 
  for(int i=0;i<MAX_TRIES && (I2C_MASTER_STATUS & I2C_MASTER_IS_BUSY);i++) {};
  return 0;
}

static int idx = 0, num = 0;
static char buf[I2C_MAX_READ+1];

uint8_t TwoWire::requestFrom(uint8_t address, uint8_t length, uint8_t sendStop)
{
  if (length > I2C_MAX_READ) return -1;
  
  I2C_TX_DATA = ((address << 1) | 0x01) | I2C_TX_ENABLE | I2C_TX_VALID;
  I2C_TX_ACK = I2C_TX_VALID;
  I2C_MASTER_STATUS = I2C_MASTER_START;
  for(int i=0;i<MAX_TRIES && (I2C_TX_ACK & I2C_TX_VALID);i++) {};  // Wait for nack sent
  
  idx = 0;
  num = 0;
  for (int i=0;i<length;i++) {
    I2C_TX_DATA = I2C_TX_VALID;
    I2C_TX_ACK = I2C_TX_VALID | I2C_TX_ENABLE;
    for(int i=0;i<MAX_TRIES && (I2C_TX_ACK & I2C_TX_VALID);i++) {};  // Wait for ack sent
    buf[i] = I2C_RX_DATA & 0xff;
    num++;
  }

  endTransmission();
  return num;
}

int TwoWire::available(void)
{
  return num - idx;
}

int TwoWire::read(void)
{
  if ((num - idx) > 0) {
    return buf[idx++];
  }
  return 0;
}

int TwoWire::peek(void)
{
	return 0;
}

// alternate function prototypes

uint8_t TwoWire::requestFrom(uint8_t address, uint8_t quantity)
{
  return requestFrom((uint8_t)address, (uint8_t)quantity, (uint8_t)true);
}

uint8_t TwoWire::requestFrom(int address, int quantity)
{
  return requestFrom((uint8_t)address, (uint8_t)quantity, (uint8_t)true);
}

uint8_t TwoWire::requestFrom(int address, int quantity, int sendStop)
{
  return requestFrom((uint8_t)address, (uint8_t)quantity, (uint8_t)sendStop);
}

void TwoWire::beginTransmission(int address)
{
	beginTransmission((uint8_t)address);
}

uint8_t TwoWire::endTransmission(void)
{
	return endTransmission(true);
}

void TwoWire::begin(int address)
{
	begin((uint8_t)address);
}

void TwoWire::onReceive( void (*function)(int) )
{
}

void TwoWire::onRequest( void (*function)(void) )
{
}

//TwoWire Wire = TwoWire();
TwoWire Wire;

