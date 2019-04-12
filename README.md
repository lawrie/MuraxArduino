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

If you select the 8Kb BRAM internal option, you get an 8kb device with a bootloader of just over 2kb, leaving just under 6kb for the Arduino sketch. The BRAM is mapped onto address 0x80000000. The BRAM could be increased to 12kb. Currently the top 4kb is is used for the stack and function pointers for interrupts. 

If you select the 512KB SRAM external option (the default) , you get the Blackice II external SRAM. The bootloader still runs in BRAM and the stack is still in BRAM, but the code and static data is in external SRAM which is mapped to address 0x90000000.

### Peripherals

#### GPIO

```
Pins 0-3  : Output: Blackice LEDs
Pins 4-7  : GPIO  : Pin 4 is used as trigger (Blackice pin 33) for a ping sensor. Pin 5 is multiplexed with the shiftIn clk 
                    pin (see below) and pins 6 and 7 are multiplexed with the shiftOut clk and data pins.
pins 8- 9 : Input : 8 and 9 are buttons 1 and 2.
pins 10-31: GPIO  : These correspond to the 4 switches (which double as SD card SPI pin), Blackice pins 87 and 89 on Pmod 2 
                    and the whole of  Pmods 3, 4, 5 and 6. Pins 10-13 and 18-21 and multiplexed with the second 7-segment 
                    display (see below).
```

This corresponds to Arduino pinMode, digitalRead and digitalWrite methods. The INPUT_PULLUP mode is not implemented and is treated as INPUT.

#### UART

Maps to the Blackice USB 2 connector on pins 85 and 88. Accesssed by Arduino Serial class. 

Output is sometimes misseed - more work on this is needed.

There is no flow control.

#### MachineTimer

A 32-bit microsecond machine timer is used for the implementation of the millis, micros, delay and delayMicroseconds methods.

#### Mux

There is a Mux peripheral (Mux.scala), which has 32 pins controlled by a 32-bit register. The pins are used in toplevel.v.
It allows FPGA pins to be multiplexed between different peripherals, ususally between GPIO and another peripheral.

3 muxes are currently used as follows:

```
Mux 0 : shiftIn clk if set, else GPIO pin 5.
Mux 1 : shiftOut clk and data if set, else GPIO pins 6 and 7.
Mux 2 : 7-segment display 1 if set, else GPIO pins 10-13 and 18-21
Mux 3 : Quadrature on pins Pmod 5 if set.
```

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

Available on BlackIce pin 94 and on BlackIce pins DBG1 and DONE.

Corresponds to Arduino analogWrite method. The pin number is the PWM channel.

And number (up to 64) PWM pins can be configured, but currently only 3 are used.

#### Tone

Available on Blackice pin 26.

Corresponds to Arduino tone() and notTone() methods. Pin number is ignored.

#### 7-segment LED display

7-segment display channel 0 maps to a Digilent PMODSSD on Pmods 7 and 9.
channel 1 is multiplexed with GPIO and maps to Pmods 3 and 5.

Supported by the SevenSegment library.

#### shiftIn

On BlackIce pins 31 and 32.

Corresponds to Arduino shiftIn method.

#### shiftOut

On BlackIce pins 21 and 22.

Corresponds to Arduino shiftOut method.

#### Interrupts

Timer interrupts are implemented usinfg the MsTimer2 library and the spinal.lib Timer pperipheral.

The atachInterrupt and detachInterrupt are supported, on up to 32 pins. Currentlyt only the two buttons are configured.

#### Quadrature

Supports encoders and encoder motorss.

Just one currently configured on Pmod 5, multiplexed with GPIO and the channel 1 7-segment display.

#### Servo

Up to 32 servos can be configured. 

There is currently just one on Blackice pin 25.

#### Jtag

A Jtag debugger for the Risc-V processor is supported on Pmod 8.

#### QSPI Analog

The 6 10-bit analog channels connected to gthe STM32 are supported via a QSPI peripheral - QSPIAnalog.scala.

The pins are on the Blackice Arduino header. 

An Arduino version of the Blackice iceboot firmware is required, which sends the analog values to the ice40, continuously.

### Libraries

SPI and Wire Arduino libraries are implemented, which use the spinal.lib SPI and I2C peripherals.

The SD library is supported using the Blackice SD card, whicg shares pins with the switches.

There is an implementation of the Servo library, which uses a Servo peripheral, currently just on one pin.

There is an implementation of the MsTimer2 third-party timer library, which can be used for millisecond resolution timer interrupts.

There is a simple SevenSegment library to display a hex character on a Digilent PMOD SSD.

There is a simple Quadrature library.

There is a version of the Firmata library, but it is not yet tested.

### Third-party libraries

The Adafruit BME280 and SSD1306 libraries have been tested in i2c, SPI hardware and SPI software modes.

The LiquidCrystal library has been tested.

### Not implemented

AnalogReference is a no op.

The analogReadResolution and analogWriteResolution methods are no ops.

The Stroing toFloat method is not supported.

USB classes are not supported.

Lots of other features have not been tested.
