#ifndef ScreenDisplayInitialize_h
#define ScreenDisplayInitialize_h

#include "Common.h"


void display_InitializeState(){

    if( isenableStateDisplay[ST_INIT][0] && stateScreenDelay[ST_INIT].justFinished()){
	  isenableStateDisplay[ST_INIT][0] = false;
	  isenableStateDisplay[ST_INIT][1] = true;
	  isenableStateDisplay[ST_INIT][2] = false;
      stateScreenDelay[ST_INIT].repeat();
      lcd.clear();
      setDisplay(MSG_NORMAL_INITIALIZE_WELCOME,LCDROW1);
      setDisplay(setting.getCafeNameSetting(),LCDROW2);
    }
  
    if( isenableStateDisplay[ST_INIT][1] && stateScreenDelay[ST_INIT].justFinished()){
	  isenableStateDisplay[ST_INIT][0] = false;
	  isenableStateDisplay[ST_INIT][1] = false;
	  isenableStateDisplay[ST_INIT][2] = true;
      stateScreenDelay[ST_INIT].repeat();
      lcd.clear();
      setDisplay(MSG_NORMAL_INITIALIZE_SELECTPC,LCDROW1);
      setDisplay(MSG_NORMAL_INITIALIZE_KEYPAD,LCDROW2);
    }
  
    if( isenableStateDisplay[ST_INIT][2] && stateScreenDelay[ST_INIT].justFinished()){
	  isenableStateDisplay[ST_INIT][0] = true;
	  isenableStateDisplay[ST_INIT][1] = false;
	  isenableStateDisplay[ST_INIT][2] = false;
      stateScreenDelay[ST_INIT].repeat();
      lcd.clear();
      setDisplay(MSG_NORMAL_INITIALIZE_SELECT_TOP,LCDROW1);
      setDisplay(MSG_NORMAL_INITIALIZE_SELECT_BOT,LCDROW2);
    }
}
#endif
