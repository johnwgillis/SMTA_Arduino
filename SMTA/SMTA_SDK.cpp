/*
Smart Motion Trend Anaylizer (SMTA)
Software Development Kit
Board Version: REV A
Author: Grant Hilgert
Date Created: October 25, 2017

*/
#include "SMTA_SDK.h"
#include "Arduino.h"

SMTA::SMTA(){}

int SMTA::greenLed(){
  return 1;}

int SMTA::amberLed(){
  return 1;}

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

int SMTA::powerDown(){
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



