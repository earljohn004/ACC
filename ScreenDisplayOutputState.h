#ifndef ScreenDisplayOutputState_h
#define ScreenDisplayOutputState_h

#include "Common.h"

millisDelay outputStateScreenDelay;
bool isenable_OutputState[] = { true };

void display_OutputState(){

    if( isenable_OutputState[ENABLE_INDEX] && outputStateScreenDelay.justFinished()){
	  isenable_OutputState[ENABLE_INDEX] = true;
      outputStateScreenDelay.repeat();
      setDisplay(MSG_NORMAL_OUTPUTSTATE_TOTAL,LCDROW1);
      setDisplay( String( String(MSG_NORMAL_OUTPUTSTATE_PHP) + coinInserted ),LCDROW2);
	  isenable_OutputState[ENABLE_INDEX] = true;
    }
}
#endif
