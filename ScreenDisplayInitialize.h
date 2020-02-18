#ifndef ScreenDisplayInitialize_h
#define ScreenDisplayInitialize_h

#include "Common.h"

millisDelay initializeScreenDelay;
bool display_InitializeStateEnableFlag[] = { true, false, false};
bool isenable_InitializeState = true;

void display_InitializeState(){

  if(isenable_InitializeState == true ){
    if( display_InitializeStateEnableFlag[0] && initializeScreenDelay.justFinished()){
	  display_InitializeStateEnableFlag[0] = false;
	  display_InitializeStateEnableFlag[1] = true;
	  display_InitializeStateEnableFlag[2] = false;
      initializeScreenDelay.repeat();
      lcd.clear();
      setDisplay(MSG_NORMAL_INITIALIZE_WELCOME,LCDROW1);
      setDisplay(setting.getCafeNameSetting(),LCDROW2);
    }
  
    if( display_InitializeStateEnableFlag[1] && initializeScreenDelay.justFinished()){
	  display_InitializeStateEnableFlag[0] = false;
	  display_InitializeStateEnableFlag[1] = false;
	  display_InitializeStateEnableFlag[2] = true;
      initializeScreenDelay.repeat();
      lcd.clear();
      setDisplay(MSG_NORMAL_INITIALIZE_SELECTPC,LCDROW1);
      setDisplay(MSG_NORMAL_INITIALIZE_KEYPAD,LCDROW2);
    }
  
    if( display_InitializeStateEnableFlag[2] && initializeScreenDelay.justFinished()){
	  display_InitializeStateEnableFlag[0] = true;
	  display_InitializeStateEnableFlag[1] = false;
	  display_InitializeStateEnableFlag[2] = false;
      initializeScreenDelay.repeat();
      lcd.clear();
      setDisplay(MSG_NORMAL_INITIALIZE_SELECT_TOP,LCDROW1);
      setDisplay(MSG_NORMAL_INITIALIZE_SELECT_BOT,LCDROW2);
    }
  }
}
#endif
