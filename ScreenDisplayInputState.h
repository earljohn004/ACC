#ifndef ScreenDisplayInputState_h
#define ScreenDisplayInputState_h

#include "Common.h"

millisDelay inputStateScreenDelay;
bool isenable_inputState[] = { true };

void display_InputState(){

	if( isenable_inputState[ENABLE_INDEX] && inputStateScreenDelay.justFinished()){
		isenable_inputState[ENABLE_INDEX] = true;
		inputStateScreenDelay.repeat();
		lcd.clear();
		setDisplay(MSG_NORMAL_INPUTSTATE_INPUTHERE, LCDROW1);
		setDisplay(strSelectedPC_, LCDROW2);
		isenable_inputState[ENABLE_INDEX] = false;
		time_out.restartTimer( time_out_id_ );
	}
}
#endif
