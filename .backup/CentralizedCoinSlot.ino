#include <Thread.h>
#include <ThreadController.h>
#include <millisDelay.h>

#include "Message.h"
#include "Common.h"
#include "Panel.h"

char keyInput_;

Thread displayInitThread = Thread();
Thread stateThread = Thread();
Thread inputThread = Thread();
ThreadController control = ThreadController();

millisDelay testDelay;
millisDelay test2Delay;
millisDelay test3Delay;

bool display1 = true;
bool display2 = false;
bool display3 = false;
bool displayEnable = true;
bool display2Enable = true;

Panel initStateScreen = Panel(3);


/* void (*func_pointer)(LiquidCrystal_I2C&, millisDelay&) = &initStateScreen.run; */
/* func_pointer = &initStateScreen.run(lcd, millisDelay); */

void testThread(){
  initStateScreen.run(lcd, testDelay);
}

void getKeypadInput(){
  keyInput_ = keypad.getKey();
}

void state_machine_run(){
    switch(state){
        case ST_INIT:
            //displayInitState();
            displayEnable = true;
            if(keyInput_){
                state = ST_INPUT;
            }
            break;
        case ST_INPUT:
            if(display2Enable == true){
//              lcd.clear();
            }
            setDisplay(MSG_NORMAL_INPUTSTATE, LCDROW2);
            displayEnable = false;
            display2Enable = false;
            if(keyInput_ == 'A'){
                state = ST_INIT;
                display2Enable=true;
            }
            break;
        case ST_COINSLOT:
            break;
        case ST_OUTPUT:
            break;
    }
}

void testPanel(){
      display1 = false;
      display2 = true;
      display3 = false;
      testDelay.repeat();
      //lcd.clear();
      setDisplay(MSG_NORMAL_INITIALIZE_WELCOME,LCDROW1);
      setDisplay(setting.getCafeNameSetting(),LCDROW2);
      Serial.println("screen1");
}

void display_initialize_screen(){
    initStateScreen.add(  MSG_NORMAL_INITIALIZE_WELCOME,    setting.getCafeNameSetting(),     setting.getTransitionSetting(), 0 );
    initStateScreen.add(  MSG_NORMAL_INITIALIZE_SELECTPC,   MSG_NORMAL_INITIALIZE_KEYPAD,     setting.getTransitionSetting(), 1 );
    initStateScreen.add(  MSG_NORMAL_INITIALIZE_SELECT_TOP, MSG_NORMAL_INITIALIZE_SELECT_BOT, setting.getTransitionSetting(), 2 );
};

void displayInitState(){

  if(displayEnable == true ){
    if( display1 && testDelay.justFinished()){
      display1 = false;
      display2 = true;
      display3 = false;
      testDelay.repeat();
      //lcd.clear();
      setDisplay(MSG_NORMAL_INITIALIZE_WELCOME,LCDROW1);
      setDisplay(setting.getCafeNameSetting(),LCDROW2);
      Serial.println("screen1");
    }
  
    if( display2 && testDelay.justFinished()){
      display1 = false;
      display2 = false;
      display3 = true;
      testDelay.repeat();
      //lcd.clear();
      setDisplay(MSG_NORMAL_INITIALIZE_SELECTPC,LCDROW1);
      setDisplay(MSG_NORMAL_INITIALIZE_KEYPAD,LCDROW2);
      Serial.println("screen2");
    }
  
    if( display3 && testDelay.justFinished()){
      display1 = true;
      display2 = false;
      display3 = false;
      testDelay.repeat();
      //lcd.clear();
      setDisplay(MSG_NORMAL_INITIALIZE_SELECT_TOP,LCDROW1);
      setDisplay(MSG_NORMAL_INITIALIZE_SELECT_BOT,LCDROW2);
      Serial.println("screen3");
    }
  }
}



// Arduino commands
void setup() {
  Serial.begin(115200);
  lcd.init();
  lcd.backlight();

  // Separate state machine logic on separate thread
  /* stateThread.onRun(state_machine_run); */
  /* stateThread.setInterval(200); */
  /* inputThread.onRun(getKeypadInput); */
  /* inputThread.setInterval(300); */
  /* displayInitThread.onRun(displayInitState); */
  /* displayInitThread.setInterval(100); */

  /* control.add(&inputThread); */
  /* control.add(&displayInitThread); */

  stateThread.onRun(testThread);
  stateThread.setInterval(100);
  control.add(&stateThread);

  testDelay.start(1000);
  /* test2Delay.start(2000); */
  /* test3Delay.start(3000); */

  initStateScreen.initialize(); 
  display_initialize_screen();

}

void loop() {
  /* initStateScreen.run(lcd, testDelay); */
  /* control.run();          //run the thread */
  /* setDisplay("earL",LCDROW1); */
  /* Serial.println("earl"); */
  /* state_machine_run(); */
  /* func_pointer(lcd, testDelay); */
}
