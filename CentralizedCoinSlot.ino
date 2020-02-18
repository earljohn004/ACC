#include <Thread.h>
#include <ThreadController.h>
#include <millisDelay.h>

#include "Message.h"
#include "Common.h"
#include "ScreenDisplayInitialize.h"
#include "ScreenDisplayInputState.h"
#include "ScreenDisplayCoinState.h"
#include "ScreenDisplayOutputState.h"


Thread displayInitThread = Thread();
Thread stateThread = Thread();
Thread inputThread = Thread();
ThreadController control = ThreadController();

bool isAccept = false;

void getKeypadInput(){
  keyInput_ = keypad.getKey();
}

void init_variables(){
	strSelectedPC_ = "";
	isAccept  = false;
	display_InitializeStateEnableFlag[0] = true;
	display_InitializeStateEnableFlag[1] = false;
	display_InitializeStateEnableFlag[2] = false;
}

bool transitionState( STATE &state ){
	//Transition Logic
	STATE temp;
	if( keyInput_== KEY_ACCEPT ){
		switch(state){
			case ST_INIT: 
				state =  ST_INPUT;
				isenable_InitializeState = false;
				break;
			case ST_INPUT:
				state = ST_COINSLOT;
				isenable_CoinState[ENABLE_INDEX] = true;
				break;
			case ST_COINSLOT:
				state = ST_OUTPUT;
				isenable_OutputState[ENABLE_INDEX] = true;
				break;
			case ST_OUTPUT:
				state = ST_INIT;
				isenable_InitializeState = true;
				break;
			default: 
				break;

		};
		lcd.clear();
		return true;
	}
	return false;
}

void state_machine_run(){
	Serial.println(state);
    switch(state){
        case ST_INIT:
            if(keyInput_){
				init_variables();
				// Pressing any key will transition to next state
				// Set enable of next screen to true
                state = ST_INPUT;
				isenable_inputState[ENABLE_INDEX] = true;
				
				// Convert the keypad input to String
				getStringInput();
				lcd.clear();
            }
            display_InitializeState();
            break;
        case ST_INPUT:
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
			}
            break;
        case ST_COINSLOT:
			transitionState(state);
			display_CoinState();
            break;
        case ST_OUTPUT:
			display_OutputState();
			transitionState(state);
            break;
    }
}



// Arduino commands
void setup() {
  Serial.begin(115200);
  lcd.init();
  lcd.backlight();

  // Separate state machine logic on separate thread
  stateThread.onRun(state_machine_run);
  stateThread.setInterval(50);
  control.add(&stateThread);

  // Initialize input thread
  // Add thread to control
  inputThread.onRun(getKeypadInput);
  inputThread.setInterval(50);
  control.add(&inputThread);

  // Initialize screen delays
  initializeScreenDelay.start(1000);
  inputStateScreenDelay.start(1000);
  coinStateScreenDelay.start(1000);
  outputStateScreenDelay.start(1000);

}

void loop() {
  control.run();          //run the thread
}
