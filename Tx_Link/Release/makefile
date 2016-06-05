################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -f

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include libraries/arduino-base64/subdir.mk
-include libraries/SoftwareSerial/src/subdir.mk
-include libraries/Servo/src/samd/subdir.mk
-include libraries/Servo/src/sam/subdir.mk
-include libraries/Servo/src/avr/subdir.mk
-include core/core/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(INO_DEPS)),)
-include $(INO_DEPS)
endif
ifneq ($(strip $(PDE_DEPS)),)
-include $(PDE_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
AR += \
arduino.ar \

ELF += \
Tx_Link.elf \

EEP += \
Tx_Link.eep \

FLASH_IMAGE += \
Tx_Link.hex \


# All Target
all: Tx_Link

# Tool invocations
Tx_Link: $(FLASH_IMAGE)
	@echo 'Building target: $@'
	@echo 'Printing size:'
	"/opt/arduino-eclipse/eclipseArduino/arduinoPlugin/tools/arduino/avr-gcc/4.8.1-arduino5/bin/avr-size" -A "/home/gsjy/src/embedded/Arduino/ESP8266/WiFi_Link/Tx_Link/Release/Tx_Link.elf"
	@echo 'Finished building target: $@'
	@echo ' '

arduino.ar: $(AR_OBJ)
	@echo 'Starting archiver'
	"/opt/arduino-eclipse/eclipseArduino/arduinoPlugin/tools/arduino/avr-gcc/4.8.1-arduino5/bin/avr-ar" rcs  "/home/gsjy/src/embedded/Arduino/ESP8266/WiFi_Link/Tx_Link/Release/arduino.ar"    arduino.ar $(AR_OBJ)
	@echo 'Finished building: $@'
	@echo ' '

Tx_Link.elf: $(LINK_OBJ) $(AR)
	@echo 'Starting combiner'
	"/opt/arduino-eclipse/eclipseArduino/arduinoPlugin/tools/arduino/avr-gcc/4.8.1-arduino5/bin/avr-gcc" -Os -Wl,--gc-sections -mmcu=atmega328p  -o "/home/gsjy/src/embedded/Arduino/ESP8266/WiFi_Link/Tx_Link/Release/Tx_Link.elf"   $(LINK_OBJ) $(AR)    "-L/home/gsjy/src/embedded/Arduino/ESP8266/WiFi_Link/Tx_Link/Release" -lm
	@echo 'Finished building: $@'
	@echo ' '

Tx_Link.eep: $(ELF)
	@echo 'Create eeprom image'
	"/opt/arduino-eclipse/eclipseArduino/arduinoPlugin/tools/arduino/avr-gcc/4.8.1-arduino5/bin/avr-objcopy" -O ihex -j .eeprom --set-section-flags=.eeprom=alloc,load --no-change-warnings --change-section-lma .eeprom=0  "/home/gsjy/src/embedded/Arduino/ESP8266/WiFi_Link/Tx_Link/Release/Tx_Link.elf" "/home/gsjy/src/embedded/Arduino/ESP8266/WiFi_Link/Tx_Link/Release/Tx_Link.eep"
	@echo 'Finished building: $@'
	@echo ' '

Tx_Link.hex: $(EEP)
	@echo 'Create Flash image (ihex format)'
	"/opt/arduino-eclipse/eclipseArduino/arduinoPlugin/tools/arduino/avr-gcc/4.8.1-arduino5/bin/avr-objcopy" -O ihex -R .eeprom  "/home/gsjy/src/embedded/Arduino/ESP8266/WiFi_Link/Tx_Link/Release/Tx_Link.elf" "/home/gsjy/src/embedded/Arduino/ESP8266/WiFi_Link/Tx_Link/Release/Tx_Link.hex"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(C_UPPER_DEPS)$(PDE_DEPS)$(C_DEPS)$(AR)$(EEP)$(FLASH_IMAGE)$(CC_DEPS)$(AR_OBJ)$(C++_DEPS)$(LINK_OBJ)$(CXX_DEPS)$(ASM_DEPS)$(INO_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(ELF)$(CPP_DEPS) Tx_Link
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
