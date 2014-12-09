@echo off

REM ---------------------------------------------------------------------------
REM     compile.bat  -  by Md. Nazmul Islam  -  http://matlab-nsfwiki.csc.tntech.edu
REM     Arduino command-line build for Windows.
REM ---------------------------------------------------------------------------


C:\arduinoUpload\avr\bin\avr-g++ -c -g -Os -Wall -fno-exceptions -ffunction-sections -fdata-sections -mmcu=atmega328p -DF_CPU=16000000L -MMD -DUSB_VID=null -DUSB_PID=null -DARDUINO=101 -IC:\arduinoUpload\arduino\hardware\arduino\cores\arduino -IC:\arduinoUpload\arduino\hardware\arduino\variants\standard  -IC:\arduinoUpload\emlc  "C:\Program Files"\MATLAB\R2011b\eml2c\arduino_pro\Sources\main.c -o C:\arduinoUpload\emlc\main.c.o
            
			

C:\arduinoUpload\avr\bin\avr-g++ -c -g -Os -Wall -fno-exceptions -ffunction-sections -fdata-sections -mmcu=atmega328p -DF_CPU=16000000L -MMD -DUSB_VID=null -DUSB_PID=null -DARDUINO=101 -IC:\arduinoUpload\arduino\hardware\arduino\cores\arduino -IC:\arduinoUpload\arduino\hardware\arduino\variants\standard -IC:\arduinoUpload\arduino\libraries\GadgetShield -IC:\arduinoUpload\arduino\libraries\GadgetShield\utility C:\arduinoUpload\arduino\libraries\GadgetShield\GadgetShield.h -o C:\arduinoUpload\emlc\GadgetShield.h.o 
C:\arduinoUpload\avr\bin\avr-gcc -c -g -Os -Wall -ffunction-sections -fdata-sections -mmcu=atmega328p -DF_CPU=16000000L -MMD -DUSB_VID=null -DUSB_PID=null -DARDUINO=101 -IC:\arduinoUpload\arduino\hardware\arduino\cores\arduino -IC:\arduinoUpload\arduino\hardware\arduino\variants\standard -IC:\arduinoUpload\arduino\libraries\GadgetShield -IC:\arduinoUpload\arduino\libraries\GadgetShield\utility C:\arduinoUpload\arduino\libraries\GadgetShield\utility\gs_twi.c -o C:\arduinoUpload\emlc\gs_twi.c.o
			
C:\arduinoUpload\avr\bin\avr-gcc -c -g -Os -Wall -ffunction-sections -fdata-sections -mmcu=atmega328p -DF_CPU=16000000L -MMD -DUSB_VID=null -DUSB_PID=null -DARDUINO=101 -IC:\arduinoUpload\arduino\hardware\arduino\cores\arduino -IC:\arduinoUpload\arduino\hardware\arduino\variants\standard  C:\arduinoUpload\arduino\hardware\arduino\cores\arduino\WInterrupts.c -o C:\arduinoUpload\emlc\WInterrupts.c.o 
C:\arduinoUpload\avr\bin\avr-gcc -c -g -Os -Wall -ffunction-sections -fdata-sections -mmcu=atmega328p -DF_CPU=16000000L -MMD -DUSB_VID=null -DUSB_PID=null -DARDUINO=101 -IC:\arduinoUpload\arduino\hardware\arduino\cores\arduino -IC:\arduinoUpload\arduino\hardware\arduino\variants\standard  C:\arduinoUpload\arduino\hardware\arduino\cores\arduino\wiring.c -o C:\arduinoUpload\emlc\wiring.c.o 
C:\arduinoUpload\avr\bin\avr-gcc -c -g -Os -Wall -ffunction-sections -fdata-sections -mmcu=atmega328p -DF_CPU=16000000L -MMD -DUSB_VID=null -DUSB_PID=null -DARDUINO=101 -IC:\arduinoUpload\arduino\hardware\arduino\cores\arduino -IC:\arduinoUpload\arduino\hardware\arduino\variants\standard  C:\arduinoUpload\arduino\hardware\arduino\cores\arduino\wiring_analog.c -o C:\arduinoUpload\emlc\wiring_analog.c.o 
C:\arduinoUpload\avr\bin\avr-gcc -c -g -Os -Wall -ffunction-sections -fdata-sections -mmcu=atmega328p -DF_CPU=16000000L -MMD -DUSB_VID=null -DUSB_PID=null -DARDUINO=101 -IC:\arduinoUpload\arduino\hardware\arduino\cores\arduino -IC:\arduinoUpload\arduino\hardware\arduino\variants\standard  C:\arduinoUpload\arduino\hardware\arduino\cores\arduino\wiring_digital.c -o C:\arduinoUpload\emlc\wiring_digital.c.o 
C:\arduinoUpload\avr\bin\avr-gcc -c -g -Os -Wall -ffunction-sections -fdata-sections -mmcu=atmega328p -DF_CPU=16000000L -MMD -DUSB_VID=null -DUSB_PID=null -DARDUINO=101 -IC:\arduinoUpload\arduino\hardware\arduino\cores\arduino -IC:\arduinoUpload\arduino\hardware\arduino\variants\standard  C:\arduinoUpload\arduino\hardware\arduino\cores\arduino\wiring_pulse.c -o C:\arduinoUpload\emlc\wiring_pulse.c.o 
C:\arduinoUpload\avr\bin\avr-gcc -c -g -Os -Wall -ffunction-sections -fdata-sections -mmcu=atmega328p -DF_CPU=16000000L -MMD -DUSB_VID=null -DUSB_PID=null -DARDUINO=101 -IC:\arduinoUpload\arduino\hardware\arduino\cores\arduino -IC:\arduinoUpload\arduino\hardware\arduino\variants\standard  C:\arduinoUpload\arduino\hardware\arduino\cores\arduino\wiring_shift.c -o C:\arduinoUpload\emlc\wiring_shift.c.o 
C:\arduinoUpload\avr\bin\avr-g++ -c -g -Os -Wall -fno-exceptions -ffunction-sections -fdata-sections -mmcu=atmega328p -DF_CPU=16000000L -MMD -DUSB_VID=null -DUSB_PID=null -DARDUINO=101 -IC:\arduinoUpload\arduino\hardware\arduino\cores\arduino -IC:\arduinoUpload\arduino\hardware\arduino\variants\standard  C:\arduinoUpload\arduino\hardware\arduino\cores\arduino\CDC.cpp -o C:\arduinoUpload\emlc\CDC.cpp.o 
C:\arduinoUpload\avr\bin\avr-g++ -c -g -Os -Wall -fno-exceptions -ffunction-sections -fdata-sections -mmcu=atmega328p -DF_CPU=16000000L -MMD -DUSB_VID=null -DUSB_PID=null -DARDUINO=101 -IC:\arduinoUpload\arduino\hardware\arduino\cores\arduino -IC:\arduinoUpload\arduino\hardware\arduino\variants\standard  C:\arduinoUpload\arduino\hardware\arduino\cores\arduino\HardwareSerial.cpp -o C:\arduinoUpload\emlc\HardwareSerial.cpp.o 
C:\arduinoUpload\avr\bin\avr-g++ -c -g -Os -Wall -fno-exceptions -ffunction-sections -fdata-sections -mmcu=atmega328p -DF_CPU=16000000L -MMD -DUSB_VID=null -DUSB_PID=null -DARDUINO=101 -IC:\arduinoUpload\arduino\hardware\arduino\cores\arduino -IC:\arduinoUpload\arduino\hardware\arduino\variants\standard  C:\arduinoUpload\arduino\hardware\arduino\cores\arduino\HID.cpp -o C:\arduinoUpload\emlc\HID.cpp.o 
C:\arduinoUpload\avr\bin\avr-g++ -c -g -Os -Wall -fno-exceptions -ffunction-sections -fdata-sections -mmcu=atmega328p -DF_CPU=16000000L -MMD -DUSB_VID=null -DUSB_PID=null -DARDUINO=101 -IC:\arduinoUpload\arduino\hardware\arduino\cores\arduino -IC:\arduinoUpload\arduino\hardware\arduino\variants\standard  C:\arduinoUpload\arduino\hardware\arduino\cores\arduino\IPAddress.cpp -o C:\arduinoUpload\emlc\IPAddress.cpp.o 
C:\arduinoUpload\avr\bin\avr-g++ -c -g -Os -Wall -fno-exceptions -ffunction-sections -fdata-sections -mmcu=atmega328p -DF_CPU=16000000L -MMD -DUSB_VID=null -DUSB_PID=null -DARDUINO=101 -IC:\arduinoUpload\arduino\hardware\arduino\cores\arduino -IC:\arduinoUpload\arduino\hardware\arduino\variants\standard  C:\arduinoUpload\arduino\hardware\arduino\cores\arduino\main.cpp -o C:\arduinoUpload\emlc\main.cpp.o 
C:\arduinoUpload\avr\bin\avr-g++ -c -g -Os -Wall -fno-exceptions -ffunction-sections -fdata-sections -mmcu=atmega328p -DF_CPU=16000000L -MMD -DUSB_VID=null -DUSB_PID=null -DARDUINO=101 -IC:\arduinoUpload\arduino\hardware\arduino\cores\arduino -IC:\arduinoUpload\arduino\hardware\arduino\variants\standard  C:\arduinoUpload\arduino\hardware\arduino\cores\arduino\new.cpp -o C:\arduinoUpload\emlc\new.cpp.o 
C:\arduinoUpload\avr\bin\avr-g++ -c -g -Os -Wall -fno-exceptions -ffunction-sections -fdata-sections -mmcu=atmega328p -DF_CPU=16000000L -MMD -DUSB_VID=null -DUSB_PID=null -DARDUINO=101 -IC:\arduinoUpload\arduino\hardware\arduino\cores\arduino -IC:\arduinoUpload\arduino\hardware\arduino\variants\standard  C:\arduinoUpload\arduino\hardware\arduino\cores\arduino\Print.cpp -o C:\arduinoUpload\emlc\Print.cpp.o   
C:\arduinoUpload\avr\bin\avr-g++ -c -g -Os -Wall -fno-exceptions -ffunction-sections -fdata-sections -mmcu=atmega328p -DF_CPU=16000000L -MMD -DUSB_VID=null -DUSB_PID=null -DARDUINO=101 -IC:\arduinoUpload\arduino\hardware\arduino\cores\arduino -IC:\arduinoUpload\arduino\hardware\arduino\variants\standard  C:\arduinoUpload\arduino\hardware\arduino\cores\arduino\Stream.cpp -o C:\arduinoUpload\emlc\Stream.cpp.o 
C:\arduinoUpload\avr\bin\avr-g++ -c -g -Os -Wall -fno-exceptions -ffunction-sections -fdata-sections -mmcu=atmega328p -DF_CPU=16000000L -MMD -DUSB_VID=null -DUSB_PID=null -DARDUINO=101 -IC:\arduinoUpload\arduino\hardware\arduino\cores\arduino -IC:\arduinoUpload\arduino\hardware\arduino\variants\standard  C:\arduinoUpload\arduino\hardware\arduino\cores\arduino\Tone.cpp -o C:\arduinoUpload\emlc\Tone.cpp.o 
			
C:\arduinoUpload\avr\bin\avr-g++ -c -g -Os -Wall -fno-exceptions -ffunction-sections -fdata-sections -mmcu=atmega328p -DF_CPU=16000000L -MMD -DUSB_VID=null -DUSB_PID=null -DARDUINO=101 -IC:\arduinoUpload\arduino\hardware\arduino\cores\arduino -IC:\arduinoUpload\arduino\hardware\arduino\variants\standard  C:\arduinoUpload\arduino\hardware\arduino\cores\arduino\USBCore.cpp -o C:\arduinoUpload\emlc\USBCore.cpp.o 
C:\arduinoUpload\avr\bin\avr-g++ -c -g -Os -Wall -fno-exceptions -ffunction-sections -fdata-sections -mmcu=atmega328p -DF_CPU=16000000L -MMD -DUSB_VID=null -DUSB_PID=null -DARDUINO=101 -IC:\arduinoUpload\arduino\hardware\arduino\cores\arduino -IC:\arduinoUpload\arduino\hardware\arduino\variants\standard  C:\arduinoUpload\arduino\hardware\arduino\cores\arduino\WMath.cpp -o C:\arduinoUpload\emlc\WMath.cpp.o 
C:\arduinoUpload\avr\bin\avr-g++ -c -g -Os -Wall -fno-exceptions -ffunction-sections -fdata-sections -mmcu=atmega328p -DF_CPU=16000000L -MMD -DUSB_VID=null -DUSB_PID=null -DARDUINO=101 -IC:\arduinoUpload\arduino\hardware\arduino\cores\arduino -IC:\arduinoUpload\arduino\hardware\arduino\variants\standard  C:\arduinoUpload\arduino\hardware\arduino\cores\arduino\WString.cpp -o C:\arduinoUpload\emlc\WString.cpp.o 
C:\arduinoUpload\avr\bin\avr-ar rcs C:\arduinoUpload\emlc\core.a C:\arduinoUpload\emlc\WInterrupts.c.o 
C:\arduinoUpload\avr\bin\avr-ar rcs C:\arduinoUpload\emlc\core.a C:\arduinoUpload\emlc\wiring.c.o 
C:\arduinoUpload\avr\bin\avr-ar rcs C:\arduinoUpload\emlc\core.a C:\arduinoUpload\emlc\wiring_analog.c.o 
C:\arduinoUpload\avr\bin\avr-ar rcs C:\arduinoUpload\emlc\core.a C:\arduinoUpload\emlc\wiring_digital.c.o 
C:\arduinoUpload\avr\bin\avr-ar rcs C:\arduinoUpload\emlc\core.a C:\arduinoUpload\emlc\wiring_pulse.c.o 
C:\arduinoUpload\avr\bin\avr-ar rcs C:\arduinoUpload\emlc\core.a C:\arduinoUpload\emlc\wiring_shift.c.o 
C:\arduinoUpload\avr\bin\avr-ar rcs C:\arduinoUpload\emlc\core.a C:\arduinoUpload\emlc\CDC.cpp.o 
C:\arduinoUpload\avr\bin\avr-ar rcs C:\arduinoUpload\emlc\core.a C:\arduinoUpload\emlc\HardwareSerial.cpp.o 
C:\arduinoUpload\avr\bin\avr-ar rcs C:\arduinoUpload\emlc\core.a C:\arduinoUpload\emlc\IPAddress.cpp.o 
C:\arduinoUpload\avr\bin\avr-ar rcs C:\arduinoUpload\emlc\core.a C:\arduinoUpload\emlc\main.cpp.o 
C:\arduinoUpload\avr\bin\avr-ar rcs C:\arduinoUpload\emlc\core.a C:\arduinoUpload\emlc\new.cpp.o 
C:\arduinoUpload\avr\bin\avr-ar rcs C:\arduinoUpload\emlc\core.a C:\arduinoUpload\emlc\Print.cpp.o 
C:\arduinoUpload\avr\bin\avr-ar rcs C:\arduinoUpload\emlc\core.a C:\arduinoUpload\emlc\Stream.cpp.o 
C:\arduinoUpload\avr\bin\avr-ar rcs C:\arduinoUpload\emlc\core.a C:\arduinoUpload\emlc\Tone.cpp.o 
C:\arduinoUpload\avr\bin\avr-ar rcs C:\arduinoUpload\emlc\core.a C:\arduinoUpload\emlc\USBCore.cpp.o 
C:\arduinoUpload\avr\bin\avr-ar rcs C:\arduinoUpload\emlc\core.a C:\arduinoUpload\emlc\WMath.cpp.o 
C:\arduinoUpload\avr\bin\avr-ar rcs C:\arduinoUpload\emlc\core.a C:\arduinoUpload\emlc\WString.cpp.o 
C:\arduinoUpload\avr\bin\avr-gcc -Os -Wl,--gc-sections -mmcu=atmega328p -o C:\arduinoUpload\emlc\main.c.elf C:\arduinoUpload\emlc\main.c.o C:\arduinoUpload\emlc\core.a -LC:\arduinoUpload\emlc -lm 
C:\arduinoUpload\avr\bin\avr-objcopy -O ihex -j .eeprom --set-section-flags=.eeprom=alloc,load --no-change-warnings --change-section-lma .eeprom=0 C:\arduinoUpload\emlc\main.c.elf C:\arduinoUpload\emlc\main.c.eep 
C:\arduinoUpload\avr\bin\avr-objcopy -O ihex -R .eeprom C:\arduinoUpload\emlc\main.c.elf C:\arduinoUpload\emlc\main.c.hex
C:\arduinoUpload\avr\bin\avrdude -CC:\arduinoUpload\avr\etc\avrdude.conf -v -v -v -v -patmega328p -carduino -P\\.\COM5 -b115200 -D -V -Uflash:w:C:\arduinoUpload\emlc\main.c.hex:i
        




