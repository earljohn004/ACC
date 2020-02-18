// Project TipidBox
//
// Project Name:			Centralized Coinslot 
// Author:					Earl John P. Abaquita
// File name:				Panel.h 
// Version:					0.1
// Description:				This file contains all the functions related to Screen display
//
// Copyright Abaquitronics 2020

#ifndef Panel_h
#define Panel_h

#define LCDMAX 16
#define LCDROW1 0
#define LCDROW2 1

#include <LiquidCrystal_I2C.h>
#include <millisDelay.h>

class Panel{

  private:
    struct panel_{
      char * message1;
      char * message2;
      int delay;
    }; 

	public:
        typedef struct panel_ PANEL;

    private:
        PANEL *privatePanel_;
        int size_;
        bool *displayEnable_;
        
    private:
		// -------------------------------------------------------------------------
		// Function name:				setEnablePermission
		// Function description: 		TODO:
		// Input:						TODO:
		// return type:					TODO:
		// -------------------------------------------------------------------------
        void setEnablePermission(int &currentIndex);

		// -------------------------------------------------------------------------
		// Function name:				initDisplayEnable
		// Function description: 		initialize the panel display:
		// Input:						none
		// return type:					void
		// -------------------------------------------------------------------------
        void initDisplayEnable();

		// -------------------------------------------------------------------------
		// Function name:				setDisplay
		// Function description: 		Centralize the text on the lcd
		// Input:						message
		// Input:						row
		// Input:						LiquidCryts_I2C lcd object
		// return type:					void
		// -------------------------------------------------------------------------
        void setDisplay(char* message, int row, LiquidCrystal_I2C &lcd);

    public:
		// -------------------------------------------------------------------------
		// Function name:				Panel
		// Function description: 		Panel constructor
		// Input:						size ( create an array of input size )
		// return type:					Panel
		// -------------------------------------------------------------------------
        Panel(int size);

		// -------------------------------------------------------------------------
		// Function name:				add
		// Function description: 		Add Panel display text to the object
		// Input:						row1 Message
		// Input:						row2 Message
		// Input:						delay
		// Input:						index
		// return type:					void
		// -------------------------------------------------------------------------
        void add(char* row1message, char* row2message, int delay, int index);

		// -------------------------------------------------------------------------
		// Function name:				run
		// Function description: 		Call function in arduino loop to display the text on the LCD
		// Input:						lcd ( LiquidCrystal_I2C object )
		// Input:						mdelay ( millisDelay object )
		// return type:					void
		// -------------------------------------------------------------------------
        void run(LiquidCrystal_I2C &lcd, millisDelay &mdelay);

		// -------------------------------------------------------------------------
		// Function name:				add
		// Function description: 		On multiple screens, sets other screen to the display state
		// Input:						none
		// return type:					void
		// -------------------------------------------------------------------------
        void initialize();
};

#endif
