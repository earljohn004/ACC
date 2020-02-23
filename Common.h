// Project TipidBox
//
// Project Name:			Centralized Coinslot 
// Author:					Earl John P. Abaquita
// File name:				Common.h 
// Version:					0.1
// Description:				Contains all the definitions and helper functions
//
// Copyright Abaquitronics 2020
#ifndef Common_h
#define Common_h

#include <LiquidCrystal_I2C.h>
#include <Keypad.h>
#include "Settings.h"
#include "Entity.h"
#include <WString.h>

// LCD related definitions 
#define ROWS	4
#define COLUMN  4

#define LCDMAX	16
#define LCDROW1 0
#define LCDROW2 1

// Keypad related definitions 
#define ENABLE_INDEX 0
#define KEY_ACCEPT '#'
#define KEY_MAINTENANCE '*'
#define KEY1 '1'
#define KEY2 '2'
#define KEY3 '3'
#define KEY4 '4'
#define KEY5 '5'
#define KEY6 '6'
#define KEY7 '7'
#define KEY8 '8'
#define KEY9 '9'

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

// COINSLOT related definitions 
#define PIN_COINSLOT 18
#define DUMMY_OUT 52

// DELAY and TRANSITIONS
#define SERIAL_BAUD 115200
#define THREAD_INTERVAL_INPUT 50
#define THREAD_INTERVAL_STM 50
#define OUTPUT_DELAY 50

// MAXIMUM VALUES
#define STR1_TRANSITION 4
#define STR2_PCNAME_MAX 16
#define STR_TWODIGIT 2
#define STR5_PASSCODE_MAX 4
#define STR7_TIMEOUT_MAX 5

// --------------------------------------------------------------
// GPIO RELATED FUNCTIONS
// START
	bool isAccept = false;
	int input_pins[] = { PIN_COINSLOT };
	int output_pins[] = { DUMMY_OUT, 53, 51, 49, 47, 45, 43, 41, 39 };
//  END
// --------------------------------------------------------------
//

// --------------------------------------------------------------
// VARIABLES FOR STATE MACHINE
// START
	enum state_enum { ST_INIT, ST_INPUT, ST_COINSLOT, ST_OUTPUT, ST_SETTINGS1, ST_SETTINGS2, DUMMY_INPUT };
	typedef byte STATE;
	STATE state = ST_SETTINGS1;
//  END
// --------------------------------------------------------------

// --------------------------------------------------------------
// VARIABLES FOR DISPLAY AND MILLIS
// START
	millisDelay stateScreenDelay[6];
	bool isenableStateDisplay[6][3] = {
		{ true, false, false },         // Display for ST_INIT
		{ true },						// Display for ST_INPUT
		{ true },						// Display for ST_COINSLOT
		{ true },						// Display for ST_OUTPUT
		{ true, false },				// Display for ST_SETTINGS1
		{ true }						// Display for ST_SETTINGS2
	};
//  END
// --------------------------------------------------------------

// --------------------------------------------------------------
// VARIABLES for KEYPAD
// START
	char keyInput_;
	String strSelectedPC_ = "";

	const char keys [ROWS] [COLUMN] = {
	  {'1', '2', '3', 'A'},
	  {'4', '5', '6', 'B'},
	  {'7', '8', '9', 'C'},
	  {'*', '0', '#', 'D'},
	};

	const byte rowPins[ROWS]	= {ROW1P1, ROW1P2, ROW1P3, ROW1P4};
	const byte colPins[COLUMN]	= {ROW2P1, ROW2P2, ROW2P3, ROW2P4};
//  END
// --------------------------------------------------------------


// --------------------------------------------------------------
// LIBRARIES INSTANTIATION and VARIABLES
// START
	LiquidCrystal_I2C lcd (0x27, 20, 4); // LCD address to 0x27: 16 chars 2 rows
	Keypad keypad = Keypad ( makeKeymap(keys), rowPins, colPins, ROWS, COLUMN);
	SimpleTimer time_out;
	SimpleTimer coin_insert_timeout;
	int time_out_id_;
	int coin_insert_timeout_id_;
	volatile bool isTransition = false;
	volatile byte coinInserted = 0;
//  END
// --------------------------------------------------------------

// --------------------------------------------------------------
// MODEL INSTANTIATION and VARIABLES
// START
	Settings setting = Settings();
	Entity entity =  Entity();
//  END
// --------------------------------------------------------------

// --------------------------------------------------------------
// Thread related Instantiation
// START
	Thread displayInitThread = Thread();
	Thread stateThread = Thread();
	Thread inputThread = Thread();
	ThreadController control = ThreadController();
//  END
// --------------------------------------------------------------


// --------------------------------------------------------------
// Helper Functions
// -------------------------------------------------------------------------
// Function name:				setDisplay
// Function description: 		set text display centered on the LCD Module
// Input:						message (char*)
// Input:						row (int*)
// return type:					void
// -------------------------------------------------------------------------
void setDisplay(char* message, int row){
  // Compute the centerpoint of display in Row1
  
  int cursor = (LCDMAX - strlen(message))/2;
  lcd.setCursor(cursor,row);
  lcd.print(message);
}

// -------------------------------------------------------------------------
// Function name:				setDisplay
// Function description: 		set text display centered on the LCD Module
// Input:						message (String)
// Input:						row (int*)
// return type:					void
// -------------------------------------------------------------------------
void setDisplay(String message, int row){
  // Compute the centerpoint of display in Row1
  
  int cursor = (LCDMAX - message.length())/2;
  lcd.setCursor(cursor,row);
  lcd.print(message);
}


// -------------------------------------------------------------------------
// Function name:				initialize_outputs
// Function description: 		initialize the output pins
// Input:						N/A
// return type:					void
// -------------------------------------------------------------------------
void initialize_outputs(){
	int length = (sizeof(output_pins)/sizeof(output_pins[0]));
	for(int x=0; x<length; x++){
		pinMode(output_pins[x], OUTPUT);
		digitalWrite(output_pins[x], HIGH);
	}
}

// -------------------------------------------------------------------------
// Function name:				getKeypadInput
// Function description: 		get the keypad input run using thread
// Input:						N/A
// return type:					void
// -------------------------------------------------------------------------
void getKeypadInput(){
  keyInput_ = keypad.getKey();
}

// -------------------------------------------------------------------------
// Function name:				outputToPC
// Function description: 		this function sends signal to the corresponding PC
// Input:						N/A
// return type:					void
// -------------------------------------------------------------------------
void outputToPC(){
	detachInterrupt( INT5 );
	coin_insert_timeout.disable( coin_insert_timeout_id_ );
	for(int x=0; x < (coinInserted*2); x++){
		digitalWrite(output_pins[entity.getSelectedPC().toInt()],!digitalRead(output_pins[entity.getSelectedPC().toInt()]));
		delay( OUTPUT_DELAY );
	}
}

// -------------------------------------------------------------------------
// Function name:				getStringInput
// Function description: 		concatenate the string on key Input
// Input:						N/A
// return type:					void
// -------------------------------------------------------------------------
void getStringInput( String &str, int size ){
	//Concatenate string when key pressed is not "#"
	if(keyInput_!= KEY_ACCEPT){
		if( str.length() < size ){
			str += String(keyInput_);
		}
		else{
			str = String(keyInput_);
		}
	}else {/* Do nothing */}
}

#endif
