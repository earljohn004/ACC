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
int input_pins[] = { PIN_COINSLOT };
int output_pins[] = { DUMMY_OUT, 53, 51, 49, 47, 45, 43, 41, 39 };

void getKeypadInput(){
  keyInput_ = keypad.getKey();
}

void init_variables(){
	strSelectedPC_ = "";
	isAccept  = false;
	display_InitializeStateEnableFlag[0] = true;
	display_InitializeStateEnableFlag[1] = false;
	display_InitializeStateEnableFlag[2] = false;
	coinInserted = 0;
	isTransition = false;
}

void ISR_coinInsert(){
	isTransition = true;
	coinInserted += 1;
}

void outputToPC(){
	detachInterrupt(INT5);
	for(int x=0; x < (coinInserted*2); x++){
		digitalWrite(output_pins[entity.getSelectedPC().toInt()],!digitalRead(output_pins[entity.getSelectedPC().toInt()]));
		Serial.println(!digitalRead(output_pins[entity.getSelectedPC().toInt()]));
		delay(50);
	}
}

bool transitionState( STATE &state ){
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
		return true;
	}
	return false;
}


void state_machine_run(){
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
			// Attach interrupt on 18
			attachInterrupt( INT5 , ISR_coinInsert, FALLING ); //Pin 18

			//Transition thru interrupt
			if(isTransition == true){
                state = ST_OUTPUT;
				isenable_OutputState[ENABLE_INDEX] = true;
				isTransition == false;
				lcd.clear();
			}
			display_CoinState();
            break;
        case ST_OUTPUT:
			if(isTransition == true){
				isenable_OutputState[ENABLE_INDEX] = true;
				isTransition = false;
			}
			display_OutputState();
			transitionState(state);
            break;
    }
}

void initialize_outputs(){
	int length = (sizeof(output_pins)/sizeof(output_pins[0]));
	for(int x=0; x<length; x++){
		pinMode(output_pins[x], OUTPUT);
		digitalWrite(output_pins[x], HIGH);
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

  //Initialize inputs
  initialize_outputs();
  pinMode( PIN_COINSLOT , INPUT_PULLUP );

}

void loop() {
  control.run();          //run the thread
}
