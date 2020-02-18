PROJECT_DIR       = ~/CentralizedCoinSlot
BOARD_TAG    = mega2560
#USER_LIB_PATH    =  $(PROJECT_DIR)/lib
ARDUINO_LIBS = ArduinoThread LiquidCrystal_I2C millisDelay Wire Keypad
MONITOR_PORT = /dev/ttyS4


include /usr/share/arduino/Arduino.mk

init_port:
	sudo chmod 666 /dev/ttyS4
	stty -F /dev/ttyS4 115200

