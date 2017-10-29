// SMTA Code
// Create on: October 25, 2017
// Author: John Gillis (jgillis@jgillis.com) and Grant Hilgert
// Board: ESP32 Dev Module, DIO, 40MHz, 4MB (32Mb), 115200, None

#include "SMTA_SDK.h"

SMTA device;

void setup() {
  device.init();
}

void loop() {
  test_led_loop();
  
  device.spinOnce();
}






void test_led_loop() {
  static int brightness = 0;    // how bright the LED is
  static int fadeAmount = 2;    // how many points to fade the LED by
  
  // set the brightness for both LEDs
  device.setGreenLedBrightnessTo(brightness);
  device.setAmberLedBrightnessTo(brightness);

  // change the brightness for next time through the loop:
  brightness = brightness + fadeAmount;

  // reverse the direction of the fading at the ends of the fade:
  if (brightness <= 0 || brightness >= 100) {
    fadeAmount = -fadeAmount;
  }
  // wait for 30 milliseconds to see the dimming effect
  delay(30);
}
