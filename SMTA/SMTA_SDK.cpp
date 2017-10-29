/*
Smart Motion Trend Anaylizer (SMTA) - SDK Code
Software Development Kit
Board Version: REV A
Author: John Gillis and Grant Hilgert
Date Created: October 25, 2017

*/
#include "SMTA_SDK.h"
#include "Arduino.h"

// Don't init much until init method is called
SMTA::SMTA(){}

/* - - - - - - - - - - - - - -  *\
 *  START LED CODE              *
\* - - - - - - - - - - - - - -  */

// START GENERIC LED CODE

  // use 13 bit precission for LEDC timer
  #define LEDC_TIMER_13_BIT  13
  
  // use 5000 Hz as a LEDC base frequency
  #define LEDC_BASE_FREQ     5000

  void ledcSetup(uint8_t ledPin, uint8_t ledcChannel) {
    ledcSetup(ledcChannel, LEDC_BASE_FREQ, LEDC_TIMER_13_BIT);
    ledcAttachPin(ledPin, ledcChannel);
  }

  // Arduino like analogWrite
  // value has to be between 0 and valueMax
  void ledcAnalogWrite(uint8_t channel, uint32_t value, uint32_t valueMax = 100) {
    // calculate duty, 8191 from 2 ^ 13 - 1
    uint32_t duty = (8191 / valueMax) * min(value, valueMax);
  
    // write duty to LEDC
    ledcWrite(channel, duty);
  }

// END GENERIC LED CODE

// START GREEN LED CODE

  // Stores the current brightness level (0-100) of the green led
  int greenLedState = 0;

  // use first channel of 16 channels (started from zero)
  #define LED_GREEN_CHANNEL 0

  void setupGreenLed() {
    ledcSetup(LED_GREEN_PIN, LED_GREEN_CHANNEL);
  }
  
  // Sets the brightness level (0-100) of the green led
  void SMTA::setGreenLedBrightnessTo(int brightness) {
    greenLedState = min(100, max(0, brightness)); // Limit range to 0...100
  
    // set the brightness on LEDC channel 0
    ledcAnalogWrite(LED_GREEN_CHANNEL, brightness);
  }

  // Reads the brightness level (0-100) of the green led
  int SMTA::readGreenLedBrightness() {
    return greenLedState;
  }
  
// END GREEN LED CODE

// START AMBER LED CODE

  // Stores the current brightness level (0-100) of the green led
  int amberLedState = 0;

  // use second channel of 16 channels (started from zero)
  #define LED_AMBER_CHANNEL 1

  void setupAmberLed() {
    ledcSetup(LED_AMBER_PIN, LED_AMBER_CHANNEL);
  }
  
  // Sets the brightness level (0-100) of the amber led
  void SMTA::setAmberLedBrightnessTo(int brightness) {
    amberLedState = min(100, max(0, brightness)); // Limit range to 0...100
  
    // set the brightness on LEDC channel 0
    ledcAnalogWrite(LED_AMBER_CHANNEL, brightness);
  }

  // Reads the brightness level (0-100) of the amber led
  int SMTA::readAmberLedBrightness() {
    return amberLedState;
  }
  
// END AMBER LED CODE

// Setups up all of the LED channels
void setupLeds() {
  setupGreenLed();
  setupAmberLed();
}

/* - - - - - - - - - - - - - -  *\
 *  END LED CODE                *
\* - - - - - - - - - - - - - -  */



/* - - - - - - - - - - - - - -  *\
 *  START POWER CODE            *
\* - - - - - - - - - - - - - -  */

 // Gracefully cleanup and set the supervisor to cut power
void SMTA::powerDown() {
  // Cleanup ...

  // Tell the power supervisor to cut power
  digitalWrite(KILL_PIN, LOW);
}

// Setups up the IO for power management
void setupPower() {
  // Setup the power supervisor's kill line
  pinMode(KILL_PIN, OUTPUT);
  digitalWrite(KILL_PIN, HIGH);

  // Other power setup ...
}

/* - - - - - - - - - - - - - -  *\
 *  END POWER CODE              *
\* - - - - - - - - - - - - - -  */



/* - - - - - - - - - - - - - -  *\
 *  START SETUP AND SPIN CODE   *
\* - - - - - - - - - - - - - -  */

// Runs all of the setup code for GPIO and interfaces
void SMTA::init() {
  setupPower();
  setupLeds();
}

// Runs all of the loop code to maintain GPIO and interfaces
void SMTA::spinOnce() {
}

/* - - - - - - - - - - - - - -  *\
 *  END SETUP AND SPIN CODE     *
\* - - - - - - - - - - - - - -  */





int SMTA::getBatteryStatus(){
  return 1;
  }

int SMTA::getICharge(){
  return 1;
 }
int SMTA::getVee(){
  return 1;
}

int SMTA::getVcc(){
  return 1;
}

int SMTA::networkReset(){
  return 1;
}
int SMTA::userInterupt(){
  return 1;

}

char * thermalArray(){
  return "TEST DATA";
}



