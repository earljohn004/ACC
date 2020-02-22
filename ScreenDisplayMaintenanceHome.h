#ifndef ScreenDisplayMaintenanceHome_h
#define ScreenDisplayMaintenanceHome_h

#include "Common.h"

// millisDelay stateScreenDelay[ST_SETTINGS1];
// bool isenableStateDisplay[ST_SETTINGS1][] = { true, false };

void display_MaintenanceHomeState(){

    if( isenableStateDisplay[ST_SETTINGS1][0] && stateScreenDelay[ST_SETTINGS1].justFinished()){
	  isenableStateDisplay[ST_SETTINGS1][0] = false;
	  isenableStateDisplay[ST_SETTINGS1][1] = true;
      stateScreenDelay[ST_SETTINGS1].repeat();
      lcd.clear();
      setDisplay(MSG_NORMAL_MAINTENANCEHOME_MODE, LCDROW1);
      setDisplay(MSG_NORMAL_MAINTENANCEHOME_NUM, LCDROW2);
    }
  
    if( isenableStateDisplay[ST_SETTINGS1][1] && stateScreenDelay[ST_SETTINGS1].justFinished()){
	  isenableStateDisplay[ST_SETTINGS1][0] = true;
	  isenableStateDisplay[ST_SETTINGS1][1] = false;
      stateScreenDelay[ST_SETTINGS1].repeat();
      lcd.clear();
      setDisplay(MSG_NORMAL_MAINTENANCEHOME_CHANGEVALUE, LCDROW1);
      setDisplay(MSG_NORMAL_MAINTENANCEHOME_ACCEPTVALUE, LCDROW2);
    }
  
}
#endif
