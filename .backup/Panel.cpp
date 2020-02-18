// Project TipidBox
//
// Project Name:			Centralized Coinslot 
// Author:					Earl John P. Abaquita
// File name:				Setings.cpp 
// Version:					0.1
// Description:				This file contains the getter/setter functions of settings
//
// Copyright Abaquitronics 2020


#include "Panel.h"
#include <Arduino.h>

Panel::Panel(int size){
    // Create a new panel object
    PANEL newPanel[size];
    bool displayEnable[size];
     
    this->privatePanel_ = newPanel;
    this->size_ = size;
    this->displayEnable_ = displayEnable;
}

void Panel::initialize(){
    initDisplayEnable();
    this->displayEnable_[0] = true;
}

void Panel::initDisplayEnable(){
  for(int x=0; x < size_; x++){
    this->displayEnable_[x] = false;
  }
}

void Panel::add(char* row1message, char* row2message, int delay, int index){
    // Assign corresponding message to Panel
    this->privatePanel_[index].message1 = row1message;
    this->privatePanel_[index].message2 = row2message;
    this->privatePanel_[index].delay = delay;

	Serial.println(this->privatePanel_[index].message1);
	Serial.println(this->privatePanel_[index].message2);
}

void Panel::run(LiquidCrystal_I2C &lcd, millisDelay &mdelay){

    // for (int screenNum=0; screenNum < size_; screenNum++){
        // if( (displayEnable_[screenNum] == true) && (mdelay.justFinished())){
            //setEnablePermission(screenNum);
            // switch(screenNum){
            //     case 0:
            //         this->displayEnable_[0] = false;
            //         this->displayEnable_[1] = true;
            //         this->displayEnable_[2] = false;
            //         break;
            //     case 1:
            //         this->displayEnable_[0] = false;
            //         this->displayEnable_[1] = false;
            //         this->displayEnable_[2] = true;
            //         break;
            //     case 2:
            //         this->displayEnable_[0] = true;
            //         this->displayEnable_[1] = false;
            //         this->displayEnable_[2] = false;
            //         break;
            //     default:
            //         break;
            // }
            // mdelay.repeat();
            // lcd.clear();
            // setDisplay(this->privatePanel_[screenNum].message1,LCDROW1,lcd);
            // setDisplay(this->privatePanel_[screenNum].message2,LCDROW2,lcd);

            // Serial.println(this->privatePanel_[0].message1);
            // // Serial.println(this->privatePanel_[screenNum].message2);
            // Serial.println(screenNum);
        // }
    // }
}

void Panel::setEnablePermission(int &currentIndex){

    for(int x=0; x< this->size_; x++){
        if( x == (currentIndex + 1) ){
            this->displayEnable_[x] = true;
        }
        else {
            this->displayEnable_[x] = false;
        }
    }
    
     if(currentIndex+1 == this->size_){
        this->displayEnable_[0] = true;
     }
}

void Panel::setDisplay(char* message, int row, LiquidCrystal_I2C &lcd){
  // Compute the centerpoint of display in Row1
  int cursor = (LCDMAX - strlen(message))/2;

  lcd.setCursor(cursor,row);
  lcd.print(message);
}
