#include <EEPROM.h>
#include <Wire.h>

bool eeprom_check() {
    Wire.beginTransmission(EEPROM_ADDRESS);
    return (Wire.endTransmission() == 0);
}

uint8_t eeprom_read_byte(int idx) {
    Wire.beginTransmission(EEPROM_ADDRESS);
    Wire.write((byte) (idx >> 8)); // Set address
    Wire.write((byte) idx);
    Wire.endTransmission();

    Wire.requestFrom(EEPROM_ADDRESS, 1);

    return Wire.read();
}

void eeprom_write_byte(int idx, int in) {
    Wire.beginTransmission(EEPROM_ADDRESS);
    Wire.write((byte) (idx >> 8)); 
    Wire.write((byte) idx);
    Wire.write(in);
    Wire.endTransmission();
    delay(10);
}

EEPROMClass EEPROM;
