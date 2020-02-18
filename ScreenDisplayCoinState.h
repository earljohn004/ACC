#ifndef ScreenDisplayCoinState_h
#define ScreenDisplayCoinState_h

#include "Common.h"

millisDelay coinStateScreenDelay;
bool isenable_CoinState[] = { true };

void display_CoinState(){

	if( isenable_CoinState[ENABLE_INDEX] && coinStateScreenDelay.justFinished()){
		isenable_CoinState[ENABLE_INDEX] = true;
		coinStateScreenDelay.repeat();
		setDisplay(MSG_NORMAL_COINSTATE_TOTAL,LCDROW1);
		setDisplay( String( String(MSG_NORMAL_COINSTATE_PHP) + entity.getSelectedPC()),LCDROW2);
		isenable_CoinState[ENABLE_INDEX] = false;
	}
}
#endif
