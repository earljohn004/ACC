#ifndef ScreenDisplayInputState_h
#define ScreenDisplayInputState_h

#include "Common.h"


void display_InputState(){

	if( isenableStateDisplay[ST_INPUT][ENABLE_INDEX] && stateScreenDelay[ST_INPUT].justFinished()){
		isenableStateDisplay[ST_INPUT][ENABLE_INDEX] = true;
		stateScreenDelay[ST_INPUT].repeat();
		lcd.clear();
		setDisplay(MSG_NORMAL_INPUTSTATE_INPUTHERE, LCDROW1);
		setDisplay(strSelectedPC_, LCDROW2);
		isenableStateDisplay[ST_INPUT][ENABLE_INDEX] = false;
		time_out.restartTimer( time_out_id_ );
	}
}
#endif
