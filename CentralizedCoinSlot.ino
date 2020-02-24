#include <Thread.h>
#include <ThreadController.h>
#include <millisDelay.h>
#include <SimpleTimer.h>

#include "Message.h"
#include "Common.h"
#include "ScreenDisplayInitialize.h"
#include "ScreenDisplayInputState.h"
#include "ScreenDisplayCoinState.h"
#include "ScreenDisplayOutputState.h"
#include "ScreenDisplayMaintenanceHome.h"
#include "ScreenDisplayMaintenanceSettings.h"


void ISR_coinInsert(){
	if( state == ST_COINSLOT || state == ST_OUTPUT ){
		isTransition = true;
		coinInserted += 1;
	}else{
		isTransition = false;
		coinInserted = 0;
	}
}

void callback_Timeout(){
	state = ST_INIT;
	isenableStateDisplay[ST_INIT][ ENABLE_INDEX ] = true;
}

void callback_CoinInsertTimeOut(){
	state = ST_INIT;
	isenableStateDisplay[ST_INIT][ ENABLE_INDEX ] = true;
	outputToPC();
}

// -------------------------------------------------------------------------
// Function name:				init_variables
// Function description: 		initialize the variables
// Input:						N/A
// return type:					void
// -------------------------------------------------------------------------
void init_variables(){
	strSelectedPC_ = "";
	isAccept  = false;
	isenableStateDisplay[ST_INIT][0] = true;
	isenableStateDisplay[ST_INIT][1] = false;
	isenableStateDisplay[ST_INIT][2] = false;
    isenableStateDisplay[ST_SETTINGS1][0] = true;
    isenableStateDisplay[ST_SETTINGS1][1] = false;
	coinInserted = 0;
	isTransition = false;
}

bool transitionState( STATE &state ){
	bool ret = false;
	//Transition Logic
	if( keyInput_== KEY_ACCEPT ){
		switch(state){
			case ST_INIT: 
				state =  ST_INPUT;
				isenableStateDisplay[ST_INIT][ ENABLE_INDEX ] = false;
				break;
			case ST_INPUT:
				state = ST_COINSLOT;
				isenableStateDisplay[ST_COINSLOT][ENABLE_INDEX] = true;
				isTransition = false;
				break;
			case ST_COINSLOT:
				state = ST_OUTPUT;
				isenableStateDisplay[ST_OUTPUT][ENABLE_INDEX] = true;
				break;
			case ST_OUTPUT:
				state = ST_INIT;
				isenableStateDisplay[ST_INIT][ ENABLE_INDEX ] = true;
				outputToPC();
				break;
			//TODO: transition to ST_INIT
			case ST_SETTINGS1:
				state = ST_INIT;
				isenableStateDisplay[ST_INIT][ENABLE_INDEX] = true;
				break;
			case ST_SETTINGS2:
				state = ST_INIT;
				isenableStateDisplay[ST_INIT][ENABLE_INDEX] = true;
				break;
			case DUMMY_INPUT:
				state = ST_SETTINGS2;
				isenableStateDisplay[ST_SETTINGS2][ENABLE_INDEX] = true;
				break;
			default: 
				break;

		};
		lcd.clear();
		ret = true;
	}else{ /* Do nothing */ }

	return ret;
}

void state_machine_run(){
    switch(state){
        case ST_INIT:
			time_out.disable( time_out_id_ );
			coin_insert_timeout.disable( coin_insert_timeout_id_ );

            if( keyInput_ == KEY_MAINTENANCE ){
				// Do something here for the transition to 
				// Maintenance mode
				isenableStateDisplay[ST_SETTINGS1][ENABLE_INDEX] = true;
				state = ST_SETTINGS1;
				/* time_out.disable( time_out_id_ ); */
			}
            else if( keyInput_ ){
				init_variables();
				// Pressing any key will transition to next state
				// Set enable of next screen to true
                state = ST_INPUT;
				isenableStateDisplay[ST_INPUT][ENABLE_INDEX] = true;
				
				// Convert the keypad input to String
				/* getStringInput(); */
				getStringInput(strSelectedPC_,STR_TWODIGIT);
				
				//On Transition set time_out enable
				time_out.enable( time_out_id_ );
				lcd.clear();
            }

            display_InitializeState();
            break;
        case ST_INPUT:
			if(keyInput_){
				/* getStringInput(); */
				getStringInput(strSelectedPC_,STR_TWODIGIT);
				// Maximum of 2 character inputs only
				isenableStateDisplay[ST_INPUT][ENABLE_INDEX] = true;
			}
			// Need to process reading of input before updating the display
			display_InputState();

			//Transition Logic
			isAccept = transitionState(state);
			if(isAccept == true){
				entity.setSelectedPC(strSelectedPC_);
				//Attach Interrupt
				attachInterrupt( INT5 , ISR_coinInsert, FALLING ); //Pin 18
				isTransition = false;		//Force the interrupt to transition to false
			}
            break;
        case ST_COINSLOT:
			//Transition thru interrupt
			if( isTransition == true ){
                state = ST_OUTPUT;
				isenableStateDisplay[ST_OUTPUT][ENABLE_INDEX] = true;
				isTransition == false;
				lcd.clear();

				// Disable main timeout on OUTPUT state
				// Enable coin_insert time out: automatically load to PC
				time_out.disable( time_out_id_ );
				coin_insert_timeout.enable( coin_insert_timeout_id_ );
			}
			display_CoinState();
            break;
        case ST_OUTPUT:
			//isTransition set in ISR
			if(isTransition == true){
				isenableStateDisplay[ST_OUTPUT][ENABLE_INDEX] = true;
                state = ST_OUTPUT;
				isTransition = false;
			}

			display_OutputState();
			transitionState(state);
            break;
		//TODO: version 3 added for Maintenance mode
		case ST_SETTINGS1:
            if( keyInput_ ){
                state = ST_SETTINGS2;
				isenableStateDisplay[ST_SETTINGS2][ENABLE_INDEX] = true;

				selectedMNT = keyInput_;

            }
			display_MaintenanceHomeState();
			transitionState(state);
			break;
		case ST_SETTINGS2:

			if ( keyInput_== KEY_MAINTENANCE ){

				state = DUMMY_INPUT;

			}else if ( keyInput_ ){

                state = ST_SETTINGS2;
				isenableStateDisplay[ST_SETTINGS2][ENABLE_INDEX] = true;

				selectedMNT = keyInput_;
			}

			display_MaintenanceSettingsState();
			transitionState(state);
			break;
		case DUMMY_INPUT:
			if (keyInput_ == KEY_ACCEPT){
				// Center the Cafe name on LCD Screen
				str2CafeNameSetting_.trim();
				// reset flag to true
				key2Initial = true;

			}else if ( keyInput_ == KEY_MAINTENANCE ){
				// Implement a change in Case
				// Toggle when key_maintenance is pressed
				upperCaseFlag = !upperCaseFlag;
			}
			 else if ( keyInput_ ){
				// Modify the string in Maintenance mode
				maintenanceSettingInputLogic();
				display_MaintenanceSettingsState();
			}

			isAccept = transitionState(state);
			if(isAccept == true){
				maintenanceSettingAcceptLogic();
				isAccept = false;
			}
			break;
    }
}

void initialize_delay(){
	for(int x =0; x < 6; x++){
		stateScreenDelay[x].start( setting.getTransitionSetting() );
	}
}


// Arduino commands
void setup() {
  Serial.begin( SERIAL_BAUD );
  lcd.init();
  lcd.backlight();

  init_variables();

  // Separate state machine logic on separate thread
  stateThread.onRun(state_machine_run);
  stateThread.setInterval( THREAD_INTERVAL_STM );
  control.add(&stateThread);

  // Initialize input thread
  // Add thread to control
  inputThread.onRun(getKeypadInput);
  inputThread.setInterval( THREAD_INTERVAL_INPUT );
  control.add(&inputThread);

  // Initialize screen delays
  // Add here when adding new screens
  initialize_delay();

  //Initialize inputs
  initialize_outputs();
  pinMode( PIN_COINSLOT , INPUT_PULLUP );

  //Timeout object
  time_out_id_ =		               time_out.setInterval( setting.getTimeOutSettings(), callback_Timeout );
  coin_insert_timeout_id_ = coin_insert_timeout.setInterval( setting.getTimeOutSettings(), callback_CoinInsertTimeOut );

}

void loop() {
  control.run();          //run the thread
  time_out.run();
  coin_insert_timeout.run();
}
