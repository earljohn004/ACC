#ifndef ScreenDisplayOutputState_h
#define ScreenDisplayOutputState_h

#include "Common.h"


void display_OutputState(){

    if( isenableStateDisplay[ST_OUTPUT][ENABLE_INDEX] && stateScreenDelay[ST_OUTPUT].justFinished()){
	  isenableStateDisplay[ST_OUTPUT][ENABLE_INDEX] = true;
      stateScreenDelay[ST_OUTPUT].repeat();
      setDisplay( MSG_NORMAL_OUTPUTSTATE_TOTAL, LCDROW1 );
      setDisplay( String( String(MSG_NORMAL_OUTPUTSTATE_PHP) + coinInserted ),LCDROW2);
	  isenableStateDisplay[ST_OUTPUT][ENABLE_INDEX] = true;
	  // coin_insert_timeout.restartTimer( coin_insert_timeout_id_ );
    }
}
#endif
