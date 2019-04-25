#include <Arduino.h>
#include "Servo.h"

Servo::Servo() {
  _pin = -1;
}

uint8_t Servo::attach(int pin) {
  _pin = pin;

  (*(volatile uint32_t*)IO_MUX) |= (1 << SERVO_MUX);

  if (pin == 3) pinMode(SERVO_PIN, OUTPUT); 
  else if (pin == 2) pinMode(TONE_PIN, OUTPUT);
  else pinMode(SERVO_MUX_PINS - pin, OUTPUT);

  return pin;
}

uint8_t Servo::attach(int pin, int min, int max) {
  _pin = pin;
  return pin;
}

void Servo::detach() {
  if (_pin >= 0) IO_SERVO_PULSE_LENGTH[_pin] = 0;
}

void Servo::write(int value) {
  if (_pin >= 0) IO_SERVO_PULSE_LENGTH[_pin] = map(value, 0, 180, MIN_PULSE_WIDTH,  MAX_PULSE_WIDTH);
}

void Servo::writeMicroseconds(int value) {
  if (_pin >= 0) IO_SERVO_PULSE_LENGTH[_pin] = value;
}

int Servo::read() { // return the value as degrees 
  if (_pin < 0) return 0;
  return map(IO_SERVO_PULSE_LENGTH[_pin], MIN_PULSE_WIDTH, MAX_PULSE_WIDTH, 0, 180);
}

int Servo::readMicroseconds() {
  if (_pin < 0) return 0;
  return IO_SERVO_PULSE_LENGTH[_pin];
}

bool Servo::attached() {
  return (_pin >= 0);
}

