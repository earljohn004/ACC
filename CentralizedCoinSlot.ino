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
	isenable_InitializeState = true;
}

void callback_CoinInsertTimeOut(){
	state = ST_INIT;
	isenable_InitializeState = true;
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
	display_InitializeStateEnableFlag[0] = true;
	display_InitializeStateEnableFlag[1] = false;
	display_InitializeStateEnableFlag[2] = false;
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
				isenable_InitializeState = false;
				break;
			case ST_INPUT:
				state = ST_COINSLOT;
				isenable_CoinState[ENABLE_INDEX] = true;
				isTransition = false;
				break;
			case ST_COINSLOT:
				state = ST_OUTPUT;
				isenable_OutputState[ENABLE_INDEX] = true;
				break;
			case ST_OUTPUT:
				state = ST_INIT;
				isenable_InitializeState = true;
				outputToPC();
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
			detachInterrupt( INT5 );
			time_out.disable( time_out_id_ );
			coin_insert_timeout.disable( coin_insert_timeout_id_ );
			/* isTransition = false;		//When there is coin insert in INIT STATE: force to false */
			/* coinInserted = 0; */

            if( keyInput_ == KEY_MAINTENANCE ){
				// Do something here for the transition to 
				// Maintenance mode
			}
            else if( keyInput_ ){
				init_variables();
				// Pressing any key will transition to next state
				// Set enable of next screen to true
                state = ST_INPUT;
				isenable_inputState[ENABLE_INDEX] = true;
				
				// Convert the keypad input to String
				getStringInput();
				
				//On Transition set time_out enable
				time_out.enable( time_out_id_ );
				lcd.clear();
            }

            display_InitializeState();
            break;
        case ST_INPUT:
			/* isTransition = false;		//When there is coin insert in INIT STATE: force to false */
			/* coinInserted = 0; */

			if(keyInput_){
				getStringInput();
				// Maximum of 2 character inputs only
				isenable_inputState[ENABLE_INDEX] = true;
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
				isenable_OutputState[ENABLE_INDEX] = true;
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
                state = ST_OUTPUT;
				isenable_OutputState[ENABLE_INDEX] = true;
				isTransition = false;
			}

			display_OutputState();
			transitionState(state);
            break;
    }
}


// Arduino commands
void setup() {
  Serial.begin( SERIAL_BAUD );
  lcd.init();
  lcd.backlight();

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
  initializeScreenDelay.start( setting.getTransitionSetting() );
  inputStateScreenDelay.start( setting.getTransitionSetting() );
  coinStateScreenDelay.start( setting.getTransitionSetting() );
  outputStateScreenDelay.start( setting.getTransitionSetting() );

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
