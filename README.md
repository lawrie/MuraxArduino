# MuraxArduino

[MuraxArduino](https://github.com/lawrie/VexRiscv/blob/master/src/main/scala/vexriscv/demo/MuraxArduino.scala) is an implementation of an Arduino board for open source FPGAs. It uses a [RISC-V](https://en.wikipedia.org/wiki/RISC-V) CPU. It currently only supports the [mystorm BlackIce II ice40 board](https://github.com/mystorm-org/BlackIce-II/wiki/Getting-Started). 

It allows the FPGA to be programmed using the [Arduino IDE](https://www.arduino.cc/en/Main/Software), the [Arduino API](https://www.arduino.cc/reference/en/) and standard [Arduino libraries](https://www.arduino.cc/en/Reference/Libraries), but it makes use of the FPGA to provide accelerated hardware peripherals.

It allows you to configure as many peripherals such UART, SPI, I2C, PWM, timers, pin interrupts etc. as you need for your application, and is not limited by a small number of such hardware peripherals that hard-wired microcontrollers typically support. You do not need to resort to slow CPU-intensive bit-banged versions of such peripherals.

It can drive peripherals such as LED panels, LED strips, VGA, HDMI, ADC, etc., much faster than microcontrollers can, and all without CPU involvement. (Not all of these are implemented yet).

It is a version of [f32c/arduino](https://github.com/f32c/arduino) that works with the [SpinalHDL](https://github.com/SpinalHDL/SpinalHDL)  [Vexriscv](https://github.com/SpinalHDL/VexRiscv) [Murax SoC](https://github.com/SpinalHDL/VexRiscv/blob/master/src/main/scala/vexriscv/demo/Murax.scala).

## BlackIce II implementation

There is Arduino Board Manager support.

In File->Preferences->Additional Boards Manager URLs enter:

    https://raw.githubusercontent.com/lawrie/MuraxArduino/master/package_murax_core_index.json

Select pull down menu Tools->Board->Board Manager and install Murax Arduino.

Then select, Board: Blackice Murax FPGA board, CPU Speed: 50 Mhz, RAM Size: 512KB SRAM external, port /dev/tyyUSB0

The SpinalHDL scripts including the Makefile, pcf file and top level Verilog files are at https://github.com/lawrie/VexRiscv/tree/master/scripts/Murax/BlackIce, 
but there is a copy of the BlackIce II [binary](https://github.com/lawrie/MuraxArduino/blob/master/fpga/Blackice/bin/toplevel.bin) and the [pcf file](https://github.com/lawrie/MuraxArduino/blob/master/fpga/Blackice/toplevel.pcf) in the MuraxArduino repository, so you can try MuraxArduino out without installing SpinalHDL, by doing

```
git clone https://github.com/lawrie/MuraxArduino
cd MuraxArduino/fpga/BlackIce
stty -F /dev/ttyACM0 raw
cat bin/toplevel.bin /dev/ttyACM0
```

You need both USB connections to the Blackice II board, as /dev/ttyUSB0 is used for uploading programs from the Arduino IDE and for the Arduino console.

As with other implementations of Arduino, the CPU is reset and the Arduino program restarts when a program is uploaded, an Arduino console is opened, or another connection is made to /dev/ttyUSB0, but the syncronisation with the Arduino console is not perfect -see "Bugs" below.

### CPU

The CPU is the Vexriscv Risc-V 32-bit SpinalHDL implementation running at 50Mhz. See [MuraxArduino.scala](https://github.com/lawrie/VexRiscv/blob/master/src/main/scala/vexriscv/demo/MuraxArduino.scala) for the configuration used for the CPU.

The CPU speed is set by the pll in [toplevel_pll.v](https://github.com/lawrie/VexRiscv/tree/master/scripts/Murax/BlackIce/toplevel_pll.v).

### Memory

If you select the 8Kb BRAM internal option, you get an 8kb device with a [bootloader](https://github.com/lawrie/VexRiscvSocSoftware/blob/master/projects/murax/boothex/src/main.c)  of just over 2kb, leaving just under 6kb for the Arduino sketch. The BRAM is mapped onto address 0x80000000. The BRAM could be increased to 12kb, but currently the top 4kb is just used for the stack and function pointers for interrupts. The BRAM version may not currently be fully working.

The SRAM implementation is [MuraxSram.scala](https://github.com/lawrie/VexRiscv/blob/master/src/main/scala/vexriscv/demo/MuraxSram.scala).

If you select the 512KB SRAM external option (the default) , you get the Blackice II external SRAM. The bootloader still runs in BRAM and the stack is still in BRAM, but the code and static data is in external SRAM which is mapped to address 0x90000000. The heap size is currently fixed as 64kb. 

It is recommended that SRAM is used as the BRAM implementation is not very robust or well tested.

### Peripherals

#### GPIO A

There are currently two 32-bit GPIO peripherals, GPIO A and GPIO B..

GPIO corresponds to Arduino digital pins 0 - 31, mapped to Blackice pins as follows:

```
Pin 0     :  LED 1 (Red)
Pin 1     :  LED 2 (Yellow)
Pin 2     :  LED 3 (Green)
Pin 3     :  LED 4 (Blue)
Pin 4     :  Blackice pin 33 on Pmod 11
Pin 5     :  Blackice pin 21 on Pmod 11
Pin 6     :  Blackice Pin 31 on Pmod 12
Pin 7     :  Blackice Pin 32 on Pmod 12
Pin 8     :  Button 1
Pin 9     :  Button 2
Pin 10    :  Switch 1
Pin 11    :  Switch 2
Pin 12    :  Switch 3
Pin 13    :  Switch 4
Pin 14    :  Blackice pin 87 on Pmod 2
Pin 15:   :  Blackice pin 90 on Pmod 2
Pins 16-19:  Pmod 5
Pins 20-23:  Pmod 6
Pins 24-27:  Pmod 3
Pins 28-31:  Pmod 4
```

#### GPIO B

GPIO B corresponfds to Arduino digital pins 32 - 59 and is mapped to Blackice pins as follows:

```
Pins 32-35:  Pmod 7
Pins 36-39:  Pmod 9
Pins 40-43:  Pmod 10
Pin 44    :  Blackice pin 34 on Pmod 11
Pin 45    :  Blackice pin 22 on Pmod 11
Pin 46    :  Blackice pin 94 on Pmod 1
Pin 47    :  Blackice pin 26 on Pmod 12
Pin 48    :  Blackice Pin 25 on Pmod 12

The following pins are read-only:

Pin 49    :  System clock (100Mhz)
Pins 50-53:  QSPI data pins
Pin 54    :  I2C SDA
Pin 55    :  I2C SCL
Pin 56    :  QSPI QSS
Pin 57    :  QSPI QCK
Pin 58    :  Main 50Mhz clock
Pin 59    :  GRESET (UART RTS)
Pin 60    :  UART RX#
Pin 61    :  Jtag TCK
Pin 62    :  Jtag TMS
Pin 63    :  Jtag TDI
```

Various pins can be multiplexed with peripherals - see Mux below.

The GPIO pins are accessed using the Arduino pinMode, digitalRead and digitalWrite functions. The INPUT_PULLUP mode is not implemented and is treated as INPUT.

The GPIO peripheral is implemented by the spinal.lib TristateBuffer. The SB_IO instances are in [toplevel.v](https://github.com/lawrie/VexRiscv/tree/master/scripts/Murax/BlackIce/toplevel.v).

#### UART

There is currently a single UART peripheral that maps to the Blackice USB 2 connector on pins 85 and 88. It is accesssed using the Arduino Serial class. There is no flow control.

The UART peripheral uses the [spinal.lib implementation](https://github.com/SpinalHDL/SpinalHDL/tree/dev/lib/src/main/scala/spinal/lib/com/uart).

#### MachineTimer

A 32-bit microsecond machine timer is used for the implementation of the millis, micros, delay and delayMicroseconds methods.

MachineTimer is implemented by [MachineTimer.scala](https://github.com/lawrie/VexRiscv/blob/master/src/main/scala/vexriscv/demo/MachineTimer.scala).

#### Mux

There is a Mux peripheral which has 32 pins controlled by a 32-bit register. The mux pins are implemented in [toplevel.v](https://github.com/lawrie/VexRiscv/tree/master/scripts/Murax/BlackIce/toplevel.v).

It allows FPGA pins to be multiplexed between different peripherals, such as  between GPIO and another peripheral.

10 muxes are currently used as follows:

```
Mux 0 : shiftIn clk on Blackice pin 21
Mux 1 : shiftOut clk and data on Blackice pins 31 and 32
Mux 2 : 7-segment display 1 on Pmods 5 and 9
Mux 3 : 4 servos on Pmod 12
Mux 4 : 7-segment display 0 on Pmods 3 and 5
Mux 5 : SPI on Pmod 10
Mux 6 : PWM on Blackice pin 95
Mux 7 : PWM on DEBUG pin
Mux 8 : PWM on DBG1 pin 
Mux 9 : Tone on Blackice Pin 26
```

The Mux is implemented by [Mux.scala](https://github.com/lawrie/VexRiscv/blob/master/src/main/scala/vexriscv/demo/Mux.scala).

#### I2C 

There is a single I2C peripheral on Blackice pins 95 (SDA) and 93 (SCL). 

It is accessed using the Arduino Wire class.

Both master and slave are supported, but only master has been tested, and the current Wire library does not support it.

The I2c peripheral uses the [spinal.lib implementation](https://github.com/SpinalHDL/SpinalHDL/tree/dev/lib/src/main/scala/spinal/lib/com/i2c).

Here is the I2C master being used to drive an ssd1306 OLED display using Arduino Examples/SSD1306/ssd1306_128x64_i2c:

![i2c test](https://github.com/lawrie/lawrie.github.io/blob/master/images/i2c.jpg)

#### SPI

There is a single SPI master peripheral on Pmod 10. SPI slave is not currently supported.

The SPI peripheral uses the [spinal.lib implementation](https://github.com/SpinalHDL/SpinalHDL/tree/dev/lib/src/main/scala/spinal/lib/com/spi).

Here is harware SPI driving an SSD1306 display using Arduino Examples/SSD1306/ssd1306_128x64_spi with hardware SPI selected:

![Hardware SPI](https://github.com/lawrie/lawrie.github.io/blob/master/images/spi.jpg)

#### PulseIn

There is a single PulseIn peripheral with two pulseIn pins on BlackIce pins 34 and 22. It can be used in combination with a trigger pin to drive an HC-SR04 ping sensor.

It is accessed using the Arduino pulseIn and pulseInLong methods. The pin number is the channel (0 or 1).

The PulseIn peripheral is implemented by [PulseIn.scala](https://github.com/lawrie/VexRiscv/blob/master/src/main/scala/vexriscv/demo/PulseIn.scala).

Here is the PulseIn peripheral used with a 3.3v HC-SR04 Ping sensor, reading the display to the nearest object and displaying in in hex centimeters on a 7-segment display:

![Ping test](https://github.com/lawrie/lawrie.github.io/blob/master/images/ping.jpg)

#### PWM

There are currently 3 PWM pins available on BlackIce pin 94 and on thes DBG1 and DONE LED pins.

The  PWM duty cycle is set using the Arduino analogWrite method. The pin number is the PWM channel.

Any number (up to 64) of PWM pins can be configured, but currently only 3 are used.

The PWM is peripheral is implemented by [PWM.scala](https://github.com/lawrie/VexRiscv/blob/master/src/main/scala/vexriscv/demo/PWM.scala).

#### Tone

There is a single Tone peripheral available on Blackice Pmod 12, pin 26.

It corresponds to the Arduino tone() and notTone() methods. The pin number on these methods is ignored.

The Tone is peripheral is implemented by [Tone.scala](https://github.com/lawrie/VexRiscv/blob/master/src/main/scala/vexriscv/demo/Tone.scala).

#### 7-segment LED display

There are two 7-segment peripherals designed to be used with Digilent Pmods, [Pmod SSD](https://store.digilentinc.com/pmod-ssd-seven-segment-display/).

The first (channel 0) is accessed by the SevenSegment class and is on Blackice Pmods 7 and 9.

The second (channel 1) is multiplexed with GPIO and is on Blackice Pmods 3 and 5.

These are supported by the SevenSegment library. You need to declare "SevenSegmentClass SevenSegment(1);" to access the channel 1 instance. 

The 7-segment peripheral is implemented by [SevenSegment.scala](https://github.com/lawrie/VexRiscv/blob/master/src/main/scala/vexriscv/demo/SevenSegment.scala).

Here are two 7-segment displays being used:

![7-segment test](https://github.com/lawrie/lawrie.github.io/blob/master/images/7segment.jpg)

#### shiftIn

There is a single ShiftIn peripheral on BlackIce Pmod 11, pins 31 and 32.

It is accessed using the Arduino shiftIn function.

As the ShiftIn clk pin is muxed with GPIO pin 5, mux 0 is set by the shiftIn method and can only be unset by direct use of the Mux peripheral.

The ShiftIn peripheral  is implemented by [ShiftIn.scala](https://github.com/lawrie/VexRiscv/blob/master/src/main/scala/vexriscv/demo/ShiftIn.scala).

Here is the ShiftIn peripheral being using with a CD4021BE 8-stage static shift register following the [Arduino tutotrial](https://www.arduino.cc/en/Tutorial/ShiftIn):

![ShiftIn test](https://github.com/lawrie/lawrie.github.io/blob/master/images/shiftin.jpg)

#### shiftOut

There is a single ShiftOut peripheral on BlackIce Pmod 12, pins 21 and 22.

It is accessed using the Arduino shiftOut function.

As the ShiftOut clk and data pins are muxed with GPIO pins 6 and 7, mux 1 is set by the shiftOut method and can only be unset by direct use of the Mux peripheral.

The ShiftOut peripheral is implemented by [ShiftOut.scala](https://github.com/lawrie/VexRiscv/blob/master/src/main/scala/vexriscv/demo/ShiftOut.scala).

Here is the ShiftOut peripheral driving a 74HC595 8-Bit Shift Register following the [Arduino tutorial](https://www.arduino.cc/en/Tutorial/ShiftOut):

![Shiftout test](https://github.com/lawrie/lawrie.github.io/blob/master/images/shiftout.jpg)

#### Interrupts

Timer interrupts are implemented usinfg the MsTimer2 library and the spinal.lib Timer implementation.

The Arduino atachInterrupt and detachInterrupt functions are supported on up to 32 pins. Currently only the two Blackice buttons are support on interrupts 0 and 1.

The PinInterrupt peripheral is implemented by [PinInterrupt.scala](https://github.com/lawrie/VexRiscv/blob/master/src/main/scala/vexriscv/demo/PinInterrupt.scala).

Interrupts currently go to an [interrupt function](https://github.com/lawrie/VexRiscvSocSoftware/blob/master/projects/murax/boothex/src/main.c#L152) in the bootloader, which determines the type of interrupt and calls the appropriate interrupt function.

#### Quadrature

There is a single quadrature peripheral on Pmod 5 that supports encoders and encoder motors.

The Quadrature peripheral is multiplexed with GPIO pins 16 and 17 and with the channel 1 7-segment display.

The encoder position is read using the read method of the Quadrature library. Using this method sets mux 3 and it can only be unset by direct use of the Mux peripheral.

The Quadrature peripheral is implemented by [Quadrature.scala](https://github.com/lawrie/VexRiscv/blob/master/src/main/scala/vexriscv/demo/Quadrature.scala).

Here is a rotary encoder using the Quadrature peripheral, and displaying an 8-bit position on a 7-segment display:

![Quad test](https://github.com/lawrie/lawrie.github.io/blob/master/images/quad.jpg)

#### Servo

The [Servo](https://github.com/lawrie/VexRiscv/blob/master/src/main/scala/vexriscv/demo/Servo.scala) peripheral supports up to 32 servos.

There is currently one instance with 4 servos on Pmod 12.  A [Digilent CON3 R/C Servo connectors](https://store.digilentinc.com/pmod-con3-r-c-servo-connectors/) can be used.

Here is a servo being driven using the Digilent Pmod and Arduino Examples/Servo/Sweep:

![Servo test](https://github.com/lawrie/lawrie.github.io/blob/master/images/servo.jpg)

#### Jtag

A Jtag debugger for the Risc-V processor is supported on Blackice Pmod 8. Most USB Jtag devices are supported. It has been tested wiith an Anlogic Lychee Tang device.

Jtag uses the [spinal.lib implementation](https://github.com/SpinalHDL/SpinalHDL/tree/dev/lib/src/main/scala/spinal/lib/com/jtag).

You need to clone and build the [Risc-V version of open ocd](https://github.com/SpinalHDL/openocd_riscv).

To run openocd, do:

```
cd openocd_risc
src/openocd -f tcl/interface/ftdi/li -c 'set MURAX_CPU0_YAML ../VexRiscv/cpu0.yaml' -f tcl/target/murax.cfg
```

It responds with:

```
Open On-Chip Debugger 0.10.0+dev-01202-gced8dcd (2019-02-22-18:40)
Licensed under GNU GPL v2
For bug reports, read
	http://openocd.org/doc/doxygen/bugs.html
adapter speed: 1000 kHz
../VexRiscv/cpu0.yaml
adapter speed: 800 kHz
adapter_nsrst_delay: 260
Info : auto-selecting first available session transport "jtag". To override use 'transport select <transport>'.
jtag_ntrst_delay: 250
Info : set servers polling period to 50ms
Info : clock speed 800 kHz
Info : JTAG tap: fpga_spinal.bridge tap/device found: 0xc8001fff (mfg: 0x7ff (<invalid>), part: 0x8001, ver: 0xc)
Warn : JTAG tap: fpga_spinal.bridge       UNEXPECTED: 0xc8001fff (mfg: 0x7ff (<invalid>), part: 0x8001, ver: 0xc)
Error: JTAG tap: fpga_spinal.bridge  expected 1 of 1: 0x10001fff (mfg: 0x7ff (<invalid>), part: 0x0001, ver: 0x1)
Error: Trying to use configured scan chain anyway...
Warn : Bypassing JTAG setup events due to errors
Info : Listening on port 3333 for gdb connections
requesting target halt and executing a soft reset
Info : Listening on port 6666 for tcl connections
Info : Listening on port 4444 for telnet connections
```

Then to run gdb, do:

```
/opt/riscv/bin/riscv64-unknown-elf-gdb ~/VexRiscv/smallest.ino.elf
target remote localhost:3333
monitor reset halt
load
continue
```

That responds with:

```
GNU gdb (GDB) 8.0.50.20170724-git
Copyright (C) 2017 Free Software Foundation, Inc.
License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.  Type "show copying"
and "show warranty" for details.
This GDB was configured as "--host=x86_64-pc-linux-gnu --target=riscv64-unknown-elf".
Type "show configuration" for configuration details.
For bug reporting instructions, please see:
<http://www.gnu.org/software/gdb/bugs/>.
Find the GDB manual and other documentation resources online at:
<http://www.gnu.org/software/gdb/documentation/>.
For help, type "help".
Type "apropos word" to search for commands related to "word"...
Reading symbols from /home/lawrie/VexRiscv/smallest.ino.elf...(no debugging symbols found)...done.
(gdb) target remote localhost:3333
Remote debugging using localhost:3333
0x00000002 in ?? ()
(gdb) monitor reset halt
JTAG tap: fpga_spinal.bridge tap/device found: 0xc8001fff (mfg: 0x7ff (<invalid>), part: 0x8001, ver: 0xc)
JTAG tap: fpga_spinal.bridge       UNEXPECTED: 0xc8001fff (mfg: 0x7ff (<invalid>), part: 0x8001, ver: 0xc)
JTAG tap: fpga_spinal.bridge  expected 1 of 1: 0x10001fff (mfg: 0x7ff (<invalid>), part: 0x0001, ver: 0x1)
Trying to use configured scan chain anyway...
(gdb) load
Loading section .init, size 0x58 lma 0x90000000
Loading section .text, size 0x20 lma 0x90000058
Loading section .sdata, size 0x4 lma 0x90000078
Start address 0x90000000, load size 124
Transfer rate: 9 KB/sec, 41 bytes/write.
(gdb) continue
Continuing.
```

Here is a Anlogic Lychee Tang USB FTDI adapter being used to run a prtogram using ddb and openocd:

![Jtag debugging](https://forum.mystorm.uk/uploads/default/optimized/1X/06c68dd75fc9211d2693a73475e9c9e1388c6672_1_690x388.jpg)

#### QSPI Analog

The 6 10-bit analog channels connected to the Blackice STM32 co-processor are supported via a QspiAnalog peripheral.

The analog pins are on the Blackice Arduino header. 

An [Arduino version of the Blackice iceboot firmware](https://github.com/lawrie/MuraxArduino/tree/master/firmware/QSPIanalog) is required, which sends the analog values to the ice40, continuously.

The QspiAnalog peripheral is implemented by [QspiAnalog.scala](https://github.com/lawrie/VexRiscv/blob/master/src/main/scala/vexriscv/demo/QspiAnalog.scala).

Here is a Grove analog potentiometer being read using the QSPI Analog sensor and displaying values on a 7-segment display:

![QSPI Analog](https://forum.mystorm.uk/uploads/default/original/1X/92e6d4b50f39754bb0d42011950e8f174aaa3362.jpg)

#### SD card

The Blackice SD card can be accessed using the SD library. It is currently set up to use software SPI, with pins SCK = 10, SS = 11, MOSI = 13 and MISO = 8. The first 3 correspond to the switches on the Blackice II board, and the switches must be in the OFF (inward) position for the SD card to work. Pin 8 is button 1, so this must not be used when the SD card is in use.

The Arduino Examples/SD/Cardinfo example can be used to test the SD card with a FAT32 card in the slot. The chip select pin should be changed to 11 and the button pin to 9.

### Libraries

Custom versions odf the Arduino [SPI](https://github.com/lawrie/MuraxArduino/tree/master/libraries/SPI) and [Wire](https://github.com/lawrie/MuraxArduino/tree/master/libraries/Wire) libraries are implemented, which use the spinal.lib SPI and I2C peripheral implementations.

The [SD](https://github.com/lawrie/MuraxArduino/tree/master/libraries/SD) library is supported using the Blackice SD card, which shares pins with the switches and buttons. It currently uses software SPI.

There is a custom implementation of the [Servo](https://github.com/lawrie/MuraxArduino/tree/master/libraries/Servo) library, which uses the Servo peripheral.

There is a custom implementation of the [MsTimer2](https://github.com/lawrie/MuraxArduino/tree/master/libraries/MsTimer2) third-party timer library, which can be used for millisecond resolution timer interrupts.

There is a simple [SevenSegment](https://github.com/lawrie/MuraxArduino/tree/master/libraries/SevenSegment) library to display a hex character on a Digilent Pmod SSD.

There is a simple [Quadrature](https://github.com/lawrie/MuraxArduino/tree/master/libraries/Quadrature) library.

There is a version of the [Firmata](https://github.com/lawrie/MuraxArduino/tree/master/libraries/Firmata) library, but it is not yet tested.

There is a [Mux](https://github.com/lawrie/MuraxArduino/tree/master/libraries/Mux) library for setting and unsetting the mux pins.

There is a custom version of the [EEPROM](https://github.com/lawrie/MuraxArduino/tree/master/libraries/EEPROM) library, which needs an i2c EEPROM module attached to the hardware i2c pins on Blackice Pmod 2.

Here is an EEPROM module connected to the I2C master:

![EEPROM test](https://github.com/lawrie/lawrie.github.io/blob/master/images/eeprom.jpg)

### Third-party libraries

The Adafruit BME280 and SSD1306 libraries have been tested. The latter in i2c, SPI hardware and SPI software modes.

The LiquidCrystal library has been tested.

Here it is driving a text LCD:

![Text LCD](https://forum.mystorm.uk/uploads/default/optimized/1X/a4d718e5f3e881bc6e1d540c0552d09771016cfb_1_690x388.jpg)

### Not implemented

The analogReadResolution, analogWriteResolution and analogReference methods are no ops.

The String toFloat method is not supported.

USB classes are not supported.

Lots of other features have not been tested.

### Bugs

The Arduino console is not synchronised correctly with rebooting the CPU, so if the console is open when an Arduino program is uploaaded, the program is started and you see some console output, which is then cut short, and the CPU is rebooted and you see the full output.

