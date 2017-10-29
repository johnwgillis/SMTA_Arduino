/*
Smart Motion Trend Anaylizer (SMTA) - SDK Header
Software Development Kit
Board Version: REV A
Author: John Gillis and Grant Hilgert
Date Created: October 25, 2017

*/
#ifndef SMTA_SDK
#define SMTA_SDK

#include "Arduino.h"

#define LED_AMBER_PIN 23
#define LED_GREEN_PIN 22

#define RESET_SWITCH_PIN  21
#define POWER_SWITCH_PIN  5

#define KILL_PIN  17

#define STAT1_PIN  18
#define STAT2_PIN  19

#define VEE_SENSE_PIN  27
#define VCC_SENSE_PIN  25
#define I_SENSE_PIN  26

#define GRIDEYE_INT_PIN  32
#define GRIDEYE_SCL_PIN  35
#define GRIDEYE_SDA_PIN  34


class SMTA{

  
  public:
  
    SMTA(void);
    
    void init(void); // Runs all of the setup code for GPIO and interfaces
    void spinOnce(void);// Runs all of the loop code to maintain GPIO and interfaces

    void setGreenLedBrightnessTo(int); // Sets the brightness level (0-100) of the green led
    int readGreenLedBrightness(void); // Reads the brightness level (0-100) of the green led
    void setAmberLedBrightnessTo(int); // Sets the brightness level (0-100) of the amber led
    int readAmberLedBrightness(void); // Reads the brightness level (0-100) of the amber led

    void powerDown(void); // Gracefully cleanup and set the supervisor to cut power

    
    
    int getBatteryStatus(); //Return battery status (Full, Charging, Error)
    int getICharge();//Return battery charging current
    
    int getVee();//Return (1/2)*Vee voltage
    int getVcc(); //Return (1/2)*Vcc voltage
    
    int networkReset(); //Function to run at resetSwitch interupt
    int userInterupt(); //Function to run at powerSwitch interupt
    
    char * thermalArray();

    private: 
    
};

#endif



