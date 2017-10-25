#include "Arduino.h"

#define LED1 23
#define LED2 22
#define resetSwitch 21
#define powerSwitch
#define kill 17
#define STAT1 18
#define STAT2 19
#define VeeSense 27
#define VccSense 25
#define ISense 26
#define gridEyeInt 32
#define gridEyeSCLv 35
#define gridEyeSDA 34

int greenLed(); //Turn green LED on or off
int amberLed(); //Turn amber LED on or off

int getBatteryStatus(); //Return battery status (Full, Charging, Error)
int getIcharge();//Return battery charging current

int getVee();//Return (1/2)*Vee voltage
int getVcc(); //Return (1/2)*Vcc voltage
int powerdown(); //Tell supervisor to cut power

int networkReset(); //Function to run at resetSwitch interupt
int userInterupt(); //Function to run at powerSwitch interupt



