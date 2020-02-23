#ifndef ScreenDisplayMaintenanceSettings_h
#define ScreenDisplayMaintenanceSettings_h

#include "Common.h"

char selectedMNT = '0';
String str1TransitionSetting_ = String( setting.getTransitionSetting() );
String str2CafeNameSetting_ = "MPG Cafe";
String str3TriggerNum = "";
String str4MaxPCCount = String ( setting.getMaxPCCountSettings() );
String str5Passcode = setting.getPasscodeSettings();
String str7Timeout = String( setting.getTimeOutSettings() );
String str9FWVersion = setting.getFWVersion() ;

void display_MaintenanceSettingsState(){

    if( selectedMNT == KEY1 && isenableStateDisplay[ ST_SETTINGS2 ][ ENABLE_INDEX ] &&stateScreenDelay[ ST_SETTINGS2 ].justFinished()){
      stateScreenDelay[ ST_SETTINGS2 ].repeat();
      lcd.clear();
      setDisplay(MSG_NORMAL_MAINTENANCE_SET1, LCDROW1);
      setDisplay( str1TransitionSetting_, LCDROW2 );
	  isenableStateDisplay[ ST_SETTINGS2 ][ENABLE_INDEX] = false;
    }
  
    if( selectedMNT == KEY2 && isenableStateDisplay[ ST_SETTINGS2 ][ ENABLE_INDEX ] &&stateScreenDelay[ ST_SETTINGS2 ].justFinished()){
      stateScreenDelay[ ST_SETTINGS2 ].repeat();
      lcd.clear();
      setDisplay( MSG_NORMAL_MAINTENANCE_SET2A, LCDROW1 );
      setDisplay( str2CafeNameSetting_, LCDROW2 );
	  isenableStateDisplay[ ST_SETTINGS2 ][ENABLE_INDEX] = false;
    }

    if( selectedMNT == KEY3 && isenableStateDisplay[ ST_SETTINGS2 ][ ENABLE_INDEX ] &&stateScreenDelay[ ST_SETTINGS2 ].justFinished()){
      stateScreenDelay[ ST_SETTINGS2 ].repeat();
      lcd.clear();
      setDisplay( MSG_NORMAL_MAINTENANCE_SET3A, LCDROW1 );
      setDisplay( str3TriggerNum, LCDROW2 );
	  isenableStateDisplay[ ST_SETTINGS2 ][ENABLE_INDEX] = false;
    }

    if( selectedMNT == KEY4 && isenableStateDisplay[ ST_SETTINGS2 ][ ENABLE_INDEX ] &&stateScreenDelay[ ST_SETTINGS2 ].justFinished()){
      stateScreenDelay[ ST_SETTINGS2 ].repeat();
      lcd.clear();
      setDisplay( MSG_NORMAL_MAINTENANCE_SET4A, LCDROW1 );
      setDisplay( str4MaxPCCount, LCDROW2 );
	  isenableStateDisplay[ ST_SETTINGS2 ][ENABLE_INDEX] = false;
    }

    if( selectedMNT == KEY5 && isenableStateDisplay[ ST_SETTINGS2 ][ ENABLE_INDEX ] &&stateScreenDelay[ ST_SETTINGS2 ].justFinished()){
      stateScreenDelay[ ST_SETTINGS2 ].repeat();
      lcd.clear();
      setDisplay(MSG_NORMAL_MAINTENANCE_SET5, LCDROW1);
      setDisplay(str5Passcode, LCDROW2);
	  isenableStateDisplay[ ST_SETTINGS2 ][ENABLE_INDEX] = false;
    }

    if( selectedMNT == KEY6 && isenableStateDisplay[ ST_SETTINGS2 ][ ENABLE_INDEX ] &&stateScreenDelay[ ST_SETTINGS2 ].justFinished()){
      stateScreenDelay[ ST_SETTINGS2 ].repeat();
      lcd.clear();
      setDisplay(MSG_NORMAL_MAINTENANCE_SET6, LCDROW1);
	  isenableStateDisplay[ ST_SETTINGS2 ][ENABLE_INDEX] = false;
    }

    if( selectedMNT == KEY7 && isenableStateDisplay[ ST_SETTINGS2 ][ ENABLE_INDEX ] &&stateScreenDelay[ ST_SETTINGS2 ].justFinished()){
      stateScreenDelay[ ST_SETTINGS2 ].repeat();
      lcd.clear();
      setDisplay(MSG_NORMAL_MAINTENANCE_SET7, LCDROW1);
      setDisplay(str7Timeout, LCDROW2);
	  isenableStateDisplay[ ST_SETTINGS2 ][ENABLE_INDEX] = false;
    }

    if( selectedMNT == KEY8 && isenableStateDisplay[ ST_SETTINGS2 ][ ENABLE_INDEX ] &&stateScreenDelay[ ST_SETTINGS2 ].justFinished()){
      stateScreenDelay[ ST_SETTINGS2 ].repeat();
      lcd.clear();
      setDisplay(MSG_NORMAL_MAINTENANCE_SET8, LCDROW1);
	  isenableStateDisplay[ ST_SETTINGS2 ][ENABLE_INDEX] = false;
    }

    if( selectedMNT == KEY9 && isenableStateDisplay[ ST_SETTINGS2 ][ ENABLE_INDEX ] &&stateScreenDelay[ ST_SETTINGS2 ].justFinished()){
      stateScreenDelay[ ST_SETTINGS2 ].repeat();
      lcd.clear();
      setDisplay(MSG_NORMAL_MAINTENANCE_SET9, LCDROW1);
      setDisplay(str9FWVersion, LCDROW2);
	  isenableStateDisplay[ ST_SETTINGS2 ][ENABLE_INDEX] = false;
    }
  
}

void maintenanceSettingAcceptLogic(){
	switch(selectedMNT){
		case KEY1:
			setting.setTransitionSetting( str1TransitionSetting_.toInt() );
		break;
		case KEY2:
			setting.setCafeNameSetting( str2CafeNameSetting_ );
		break;
		case KEY3:
			// Do something for Trigger Test
		break;
		case KEY4:
			setting.setMaxPCCountSettings( str4MaxPCCount.toInt());
		break;
		case KEY5:
			setting.setPasscodeSettings( str5Passcode );
		break;
		case KEY6:
			// Do something for Reset key
		break;
		case KEY7:
			setting.setTimeOutSettings( str7Timeout.toInt());
		break;
		case KEY8:
			// Do something for Exit key
		break;
		case KEY9:
			// Do something for FW Version
		break;
		default:
		break;
	};
}

void maintenanceSettingInputLogic(){
	switch(selectedMNT){
		case KEY1:
			getStringInput( str1TransitionSetting_, STR1_TRANSITION );
			isenableStateDisplay[ST_SETTINGS2][ENABLE_INDEX] = true;
		break;
		case KEY2:
			getStringInput( str2CafeNameSetting_, STR2_PCNAME_MAX );
			isenableStateDisplay[ST_SETTINGS2][ENABLE_INDEX] = true;
		break;
		case KEY3:
			getStringInput( str3TriggerNum, STR_TWODIGIT );
			isenableStateDisplay[ST_SETTINGS2][ENABLE_INDEX] = true;
		break;
		case KEY4:
			getStringInput( str4MaxPCCount, STR_TWODIGIT );
			isenableStateDisplay[ST_SETTINGS2][ENABLE_INDEX] = true;
		break;
		case KEY5:
			getStringInput( str5Passcode, STR5_PASSCODE_MAX );
			isenableStateDisplay[ST_SETTINGS2][ENABLE_INDEX] = true;
		break;
		case KEY6:
			// Reset key
		break;
		case KEY7:
			getStringInput( str7Timeout, STR7_TIMEOUT_MAX );
			isenableStateDisplay[ST_SETTINGS2][ENABLE_INDEX] = true;
		break;
		case KEY8:
			//EXIT
		break;
		case KEY9:
			//FW VERSION
		break;
		default:
		break;
	};
}


#endif
