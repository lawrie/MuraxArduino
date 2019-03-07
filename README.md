# MuraxArduino
A version of [f32c/arduino](https://github.com/f32c/arduino) that works with the SpinalHDL Vexriscv Murax SoC

We have preliminary Boards Manager support.
In File->Preferences->Additional Boards Manager URLs enter:

    https://raw.githubusercontent.com/lawrie/MuraxArduino/master/package_murax_core_index.json

Select pull down menu Tools->Board->Board Manager
and install Murax Arduino.

Then select, Board: Generic Murax FPGA board, CPU Speed: 50 Mhz, RAM Size: 32KB BRAM internal, port /dev/tyyUSB0

The Murax configuration needed is at https://github.com/lawrie/VexRiscv/tree/master/scripts/Murax/BlackIce, 
but there is a copy of the BlackIce II binary at fpga/Blackice/bin/toplevel.bin and the pcf file is
at fpga/BlackIce/toplevel.pcf, so you can try MuraxArduino out without installing SpinalHDL.

