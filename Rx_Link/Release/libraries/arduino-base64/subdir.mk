################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
/home/gsjy/Arduino/libraries/arduino-base64/Base64.cpp 

LINK_OBJ += \
./libraries/arduino-base64/Base64.cpp.o 

CPP_DEPS += \
./libraries/arduino-base64/Base64.cpp.d 


# Each subdirectory must supply rules for building sources it contributes
libraries/arduino-base64/Base64.cpp.o: /home/gsjy/Arduino/libraries/arduino-base64/Base64.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"/opt/arduino-eclipse/eclipseArduino/arduinoPlugin/tools/arduino/avr-gcc/4.8.1-arduino5/bin/avr-g++" -c -g -Os -std=gnu++11 -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -MMD -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=10606 -DARDUINO_AVR_NANO -DARDUINO_ARCH_AVR     -I"/opt/arduino-eclipse/eclipseArduino/arduinoPlugin/packages/arduino/hardware/avr/1.6.11/cores/arduino" -I"/opt/arduino-eclipse/eclipseArduino/arduinoPlugin/packages/arduino/hardware/avr/1.6.11/variants/eightanaloginputs" -I"/opt/arduino-eclipse/eclipseArduino/arduinoPlugin/packages/arduino/hardware/avr/1.6.11/libraries/SoftwareSerial" -I"/opt/arduino-eclipse/eclipseArduino/arduinoPlugin/packages/arduino/hardware/avr/1.6.11/libraries/SoftwareSerial/src" -I"/opt/arduino-eclipse/eclipseArduino/arduinoPlugin/libraries/Servo/1.1.1" -I"/opt/arduino-eclipse/eclipseArduino/arduinoPlugin/libraries/Servo/1.1.1/src" -I"/home/gsjy/Arduino/libraries/arduino-base64" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"   -Wall
	@echo 'Finished building: $<'
	@echo ' '


