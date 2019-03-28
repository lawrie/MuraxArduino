/*
 * Iceboot plus send analog values over QSPI
 */

#include <MyStorm.h>
#include <QSPI.h>

static bool debug = false;

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  QSPI.begin(10000000, QSPI.Mode3);
  Serial.begin(9600);
  // configure the FPGA
  digitalWrite(LED_BUILTIN, 1);
  myStorm.FPGAConfigure((const byte*)0x0801F000, 135100);
  digitalWrite(LED_BUILTIN, 0);
  QSPI.beginTransaction();
}

void loop() {
  short analog;
  short response;

  // Send 6 analog values to ice40 using QSPI
  for(int i=0;i<8;i++) {
    analog = (i == 0 ? 0xAAAA : i == 7 ? 0x0000 : analogRead(A0 + i - 1));
    if (debug) {
      Serial.print("Sending A");
      Serial.print(i);
      Serial.print(": ");
      Serial.println(analog, HEX);
    }
    response = 0;
    for(int j=0;j<2;j++) {
      if (!QSPI.write(((byte *) &analog) + j, 1))
        Serial.println("QSPI.transmit failed");
      if (!QSPI.read(((byte *) &response) + j, 1))
        Serial.println("QSPI.receive failed");        
    }
    if (debug) {
      Serial.print("Received: ");
      Serial.println(response, HEX);
      if (response != analog) {
        Serial.print("*** ERROR: sent: ");
        Serial.print(analog, HEX);
        Serial.print(" received: ");
        Serial.println(response, HEX);
      }
    }
    //delay(1);
  }

  // Check for bitstream
  if (!Serial.available()) return;
  
  digitalWrite(LED_BUILTIN, 1);
  if (myStorm.FPGAConfigure(Serial)) {
    while (Serial.available())
      Serial.read();
  }
  digitalWrite(LED_BUILTIN, 0);

}
