#ifndef ScreenDisplayCoinState_h
#define ScreenDisplayCoinState_h

#include "Common.h"


void display_CoinState(){

	if( isenableStateDisplay[ST_COINSLOT][ENABLE_INDEX] && stateScreenDelay[ST_COINSLOT].justFinished()){
		isenableStateDisplay[ST_COINSLOT][ENABLE_INDEX] = true;
		stateScreenDelay[ST_COINSLOT].repeat();
		setDisplay(MSG_NORMAL_COINSTATE_TOTAL,LCDROW1);
		setDisplay( String( String(MSG_NORMAL_COINSTATE_PHP) + entity.getSelectedPC()),LCDROW2);
		isenableStateDisplay[ST_COINSLOT][ENABLE_INDEX] = false;
	}
}
#endif
