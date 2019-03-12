#include <Arduino.h>
#include "Servo.h"

Servo::Servo() {
}

uint8_t Servo::attach(int pin) {
  return 0;
}

uint8_t Servo::attach(int pin, int min, int max) {
  return 0;
}

void Servo::detach() {
  IO_SERVO_PULSE_LENGTH = 0;
}

void Servo::write(int value) {
  IO_SERVO_PULSE_LENGTH = map(value, 0, 180, MIN_PULSE_WIDTH,  MAX_PULSE_WIDTH);
}

void Servo::writeMicroseconds(int value) {
  IO_SERVO_PULSE_LENGTH = value;
}

int Servo::read() { // return the value as degrees 
  return map(IO_SERVO_PULSE_LENGTH, MIN_PULSE_WIDTH, MAX_PULSE_WIDTH, 0, 180);
}

int Servo::readMicroseconds() {
  return IO_SERVO_PULSE_LENGTH;
}

bool Servo::attached() {
  return true;
}

