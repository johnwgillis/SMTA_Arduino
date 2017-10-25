#include "Arduino.h"

int greenLed(); //Turn green LED on or off
int amberLed(); //Turn amber LED on or off

int getBatteryStatus(); //Return battery status (Full, Charging, Error)
int getIcharge();//Return battery charging current

int getVee();//Return (1/2)*Vee voltage
int getVcc(); //Return (1/2)*Vcc voltage
int powerdown(); //Tell supervisor to cut power

int resetSwitch(); //Function to run at resetSwitch interupt
int powerSwitch(); //Function to run at powerSwitch interupt



