# MuraxArduino

A version of [f32c/arduino](https://github.com/f32c/arduino) that works with the [SpinalHDL](https://github.com/SpinalHDL/SpinalHDL)  [Vexriscv](https://github.com/SpinalHDL/VexRiscv) [Murax SoC](https://github.com/SpinalHDL/VexRiscv/blob/master/src/main/scala/vexriscv/demo/Murax.scala).

## BlackIce II implementation

There is Arduino Board Manager support.

In File->Preferences->Additional Boards Manager URLs enter:

    https://raw.githubusercontent.com/lawrie/MuraxArduino/master/package_murax_core_index.json

Select pull down menu Tools->Board->Board Manager and install Murax Arduino.

Then select, Board: Blackice Murax FPGA board, CPU Speed: 50 Mhz, RAM Size: 512KB SRAM external, port /dev/tyyUSB0

The Murax configuration needed is at https://github.com/lawrie/VexRiscv/tree/master/scripts/Murax/BlackIce, 
but there is a copy of the BlackIce II binary at fpga/Blackice/bin/toplevel.bin and the pcf file is
at fpga/BlackIce/toplevel.pcf, so you can try MuraxArduino out without installing SpinalHDL.

### CPU

The CPU is the Vexriscv Risc-V 32-bit SpinalHDL implementation running at 50Mhz.

### Memory

If you select the 8Kb BRAM internal option, you get an 8kb device with a bootloader of just over 2kb, leaving just under 6kb for the Arduino sketch. The BRAM could be increased to 12kb.

If you select the 512KB SRAM external option, you get the Blackice II external SRAM. The bootloader still runs in BRAM and the stack is still in BRAM, but the code and static data is in external SRAM which is mapped to address 0x90000000.

###Peripherals

#### GPIO

```
Pins 0-3  : Output: Blackice LEDs
Pins 4-7  : GPIO  : Pin 4 is used as trigger (Blackice pin 33) for ping sensor. Others are not used.
pins 8-15 : Input : 8 and 9 are buttons 1 and 2, 10-13 are the 4 switches
pins 16-31: GPIO  : These corresspond to Pmods 3, 4, 5 and 6.
```

This corresponds to Arduino pinMode, digitalRead and digitalWrite methods. The INPUT_PULLUP mode is not implemented and is treated as INPUT.

#### UART

Maps to the Blackice USB 2 connector on pins 85 and 88. Accesssed by Arduino Serial class. 

Output is sometimes misseed - more work on this is needed.

There is no flow control.

#### MachineTimer

A 32-bit microsecond machine timer is used for the implementation of the millis, micros, delay and delayMicroseconds methods.

#### I2C 

On pins 95 (SDA) and 93 (SCL). 

Accessed by the Arduino Wire class.

Both master and slave are supported, but only master tested.

#### SPI

Only master supported. 

Only parrtially tested.

On Pmod 10.

#### PulseIn

Used to drive ping sensor. On BlackIce pin 34.

Corresponds to Arduino pulseIn and pulseInLong methods.

#### PWM

Only available on BlackIce pin 94.

Corresponds to Arduino analogWrite method. The pin number is ignored.

#### Tone

Available on Blackice pin 26.

Corresponds to Arduino tone() and notTone() methods. Pin number is ignored.

#### 7-segment LED display

Uses a Digilent PMODSSD on pmods 7 and 9.

Supported by the SevenSegment library.

#### shiftIn

On BlackIce pins 31 and 32.

Corresponds to Arduino shiftIn method.

#### shiftOut

On BlackIce pins 21 and 22.

Corresponds to Arduino shiftOut method.

#### Interrupts

Timer interrupts are implemented usinfg the MsTimer2 library and the spinal.lib Timer pperipheral.

The atachInterrupt and detachInterrupt are supported,\but currently on a single pin.

#### Mux

The are 32 muxes that can be switched with a register and camn be used in toplevel.v to switch between peripherals and GPIO on output pins.

### Libraries

SPI and Wire Arduino libraries are implemented, which use the spinal.lib SPI and I2C peripherals.

The SD library is not yet working.

There is an implementation of the Servo library, which uses a Servo peripheral, currently just on one pin.

There is an implementation of the MsTimer2 third-party timer library, which can be used for millisecond resolution timer interrupts.

There is a simple SevenSegment library to display a hex character obn a Digilent PMOD SSD.

### Third-party libraries

The Adafruit BME280 and SSD1306 libraries have been tested in i2c mode only.

### Not implemented

The interrupts and noInterrupts methods are currently no ops.

The analogRead method is not implemented. AnalogReference is a no op.

The analogReadResolution and analogWriteResolution methods are no ops.

There are some String methods and constructors that aren't currently supported.

USB classes are not supported.
