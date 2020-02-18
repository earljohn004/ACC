#ifndef Common_h
#define Common_h

#include <LiquidCrystal_I2C.h>
#include <Keypad.h>
#include "Settings.h"
#include "Entity.h"
#include <WString.h>

#define ROWS	4
#define COLUMN  4

#define LCDMAX	16
#define LCDROW1 0
#define LCDROW2 1

#define ENABLE_INDEX 0
#define KEY_ACCEPT '#'

// Keypad defines ROW Pins
#define ROW1P1 A8
#define ROW1P2 A9
#define ROW1P3 A10
#define ROW1P4 A11

// Keypad defines COLUMN Pins
#define ROW2P1 A12
#define ROW2P2 A13
#define ROW2P3 A14
#define ROW2P4 A15

char keyInput_;
String strSelectedPC_ = "";

enum state_enum { ST_INIT, ST_INPUT, ST_COINSLOT, ST_OUTPUT };
typedef byte STATE;
STATE state = ST_INIT;

const char keys [ROWS] [COLUMN] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'},
};

const byte rowPins[ROWS]	= {ROW1P1, ROW1P2, ROW1P3, ROW1P4};
const byte colPins[COLUMN]	= {ROW2P1, ROW2P2, ROW2P3, ROW2P4};

//TODO: transferredfrom .ino file to header file for readability
LiquidCrystal_I2C lcd (0x27, 20, 4); // LCD address to 0x27: 16 chars 2 rows
Keypad keypad = Keypad ( makeKeymap(keys), rowPins, colPins, ROWS, COLUMN);
Settings setting = Settings();
Entity entity =  Entity();

void setDisplay(char* message, int row){
  // Compute the centerpoint of display in Row1
  
  int cursor = (LCDMAX - strlen(message))/2;
  lcd.setCursor(cursor,row);
  lcd.print(message);
}

void setDisplay(String message, int row){
  // Compute the centerpoint of display in Row1
  
  int cursor = (LCDMAX - message.length())/2;
  lcd.setCursor(cursor,row);
  lcd.print(message);
}

void getStringInput(){
	//Concatenate string when key pressed is not "#"
	if(keyInput_!= KEY_ACCEPT){
		if( strSelectedPC_.length() <= 1 ){
			strSelectedPC_ += String(keyInput_);
		}
		else{
			strSelectedPC_ = String(keyInput_);
		}
	}else {/* Do nothing */}
}

#endif
