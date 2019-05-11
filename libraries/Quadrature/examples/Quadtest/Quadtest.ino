#include <SevenSegment.h>
#include <Quadrature.h>

void setup() {
  pinMode(QUADRATURE_QUAD_A, INPUT);
  pinMode(QUADRATURE_QUAD_B, INPUT);
}

void loop() {
  SevenSegment.write(Quadrature.read());
}
