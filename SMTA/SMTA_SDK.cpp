#include "Arduino.h"

#define LED1 23
#define LED2 22
#define RESETSWITCH 21
#define POWERSWITCH 5
#define KILL 17
#define STAT1 18
#define STAT2 19
#define VEESENSE 27
#define VCCSENSE 25
#define ISENSE 26
#define GRIDEYEINT 32
#define GRIDEYESCL 35
#define GRIDEYESDA 34


class SMTA{
private: 

public:
int greenLed(); //Turn green LED on or off
int amberLed(); //Turn amber LED on or off

int getBatteryStatus(); //Return battery status (Full, Charging, Error)
int getIcharge();//Return battery charging current

int getVee();//Return (1/2)*Vee voltage
int getVcc(); //Return (1/2)*Vcc voltage
int powerdown(); //Tell supervisor to cut power

int networkReset(); //Function to run at resetSwitch interupt
int userInterupt(); //Function to run at powerSwitch interupt

};

