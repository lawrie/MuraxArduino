#!/bin/sh -e
ARCHIVE=/tmp/MuraxArduino.zip
ARDUINODIR=~/MuraxArduino
TOOLDIR=$(pwd)

cd /tmp
rm -rf arduino
ln -sf "${ARDUINODIR}" arduino

rm -f $ARCHIVE
zip -r $ARCHIVE arduino/libraries
rm -rf pack
mkdir -p pack
cd pack
ln -s ../arduino/hardware/fpga/f32c arduino
zip -r $ARCHIVE arduino/cores arduino/programmers.txt arduino/system  arduino/variants arduino/tools
cd ..
rm -rf pack2
mkdir -p pack2
cd pack2
ln -s ../arduino/hardware/fpga/f32c/tools/boards-manager arduino
zip -r $ARCHIVE arduino/platform.txt arduino/boards.txt
cd /tmp	
rm -rf arduino
unzip $ARCHIVE
rm -f $ARCHIVE
zip -r $ARCHIVE arduino
sha256sum $ARCHIVE
ls -al $ARCHIVE

