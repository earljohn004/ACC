#ifndef ScreenDisplayMaintenanceSettings_h
#define ScreenDisplayMaintenanceSettings_h

#include "Common.h"

char selectedMNT = '0';
String str1TransitionSetting_ = String( setting.getTransitionSetting() );

// KEY2 related variables start
String str2CafeNameSetting_ = setting.getCafeNameSetting();
String str_tmp_current;
String str_tmp_before;
bool key2Initial = true;
char tmpString;
int counter;
int columnCounter=0;
bool upperCaseFlag = true;
// End

String str3TriggerNum = "";
String str4MaxPCCount = String ( setting.getMaxPCCountSettings() );
String str5Passcode = setting.getPasscodeSettings();
String str7Timeout = String( setting.getTimeOutSettings() );
String str9FWVersion = setting.getFWVersion() ;

char stringMatrix[ 10 ][ 4 ] = {
	{ '.','_','-' },		// 1
	{ 'A','B','C' },		// 2
	{ 'D','E','F' },		// 3
	{ 'G','H','I' },		// 4   
	{ 'J','K','L' },		// 5
	{ 'M','N','O' },		// 6
	{ 'P','Q','R', 'S' },	// 7
	{ 'T','U','V' },		// 8
	{ 'W','X','Y', 'Z' },	// 9
	{ ' ' }					// 0
};

char stringMatrixLC[ 10 ][ 4 ] = {
	{ '.','_','-' },		// 1
	{ 'a','b','c' },		// 2
	{ 'd','e','f' },		// 3
	{ 'g','h','i' },		// 4   
	{ 'j','k','l' },		// 5
	{ 'm','n','o' },		// 6
	{ 'p','q','r', 's' },	// 7
	{ 't','u','v' },		// 8
	{ 'w','x','y', 'z' },	// 9
	{ ' ' }					// 0
};

int stringMatrixSize[]{
	3,					// 1
	3,					// 2
	3,					// 3
	3,					// 4
	3,					// 5
	3,					// 6
	4,					// 7
	3,					// 8
	4,					// 9
	1,					// 0
};

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
			isenableStateDisplay[ST_SETTINGS2][ENABLE_INDEX] = true;

			// Reset the string on initial open of Cafe name
			if( key2Initial == true){
				columnCounter = 0;
				str2CafeNameSetting_= CAFE_NAME_INIT;
				key2Initial = false;
			}

			getStringInput( str_tmp_current, 1 );

			// Check if current keypad input is same with before input
			// When current input is not equal to before, reset counter to 0
			if (str_tmp_current != str_tmp_before ){
				counter = 0;
			}

			if(upperCaseFlag == true){
				tmpString = stringMatrix[(str_tmp_current.toInt()-1)][counter];
			}else{
				tmpString = stringMatrixLC[(str_tmp_current.toInt()-1)][counter];
			}
			counter++;
			str_tmp_before = str_tmp_current;
			
			//Reset the counter when max is achieved
			if( counter > (stringMatrixSize[(str_tmp_current.toInt()-1)] - 1) ){
				counter = 0;
			}

			if( str_tmp_current == KEY_STRING_ACCEPT ){
				// Increment column Counter of the char array
				columnCounter++;
				str2CafeNameSetting_.setCharAt( columnCounter, '_' );

				// When there is white space, delete before character
				// Counter is incremented and not resetted to 0 when space key 0 is pressed
				if (counter > 1)
				{
					// Delete the _ character before when pressing 0 key multiple times
					str2CafeNameSetting_.setCharAt( columnCounter-1, ' ' );
				}

			}
			else{
				// If not key accept, concatenate the inputted character 
				// to the str2CafeNameSetting string
				str2CafeNameSetting_.setCharAt( columnCounter, tmpString );
			}

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
