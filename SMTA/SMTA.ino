// SMTA Code
// Create on: October 25, 2017
// Author: John Gillis (jgillis@jgillis.com) and Grant Hilgert
// Board: ESP32 Dev Module, DIO, 40MHz, 4MB (32Mb), 115200, None

#include "SMTA_SDK.h"

#include <Wire.h>

SMTA device;



#include "SMTA_AMG88xx.h"
SMTA_AMG88xx grideye;








void setup() {
  //device.init();

  test_grideye_setup();
}

void loop() {
  //test_led_loop();
  test_grideye_loop2();
  
  device.spinOnce();

  
}











void test_grideye_setup() {
  Serial.begin(115200);
  Serial.println(F("AMG88xx pixels"));

  bool status;
  
  // default settings
  status = grideye.begin();
  if (!status) {
      Serial.println("Could not find a valid AMG88xx sensor, check wiring!");
      while (1);
  }
  
  Serial.println("-- Pixels Test --");

  Serial.println();

  delay(100); // let sensor boot up
}

void test_grideye_loop() {
  Serial.print("Thermistor Temperature = ");
    Serial.print(grideye.readThermistor());
    Serial.println(" *C");
  
    Serial.println();


  
  float pixels[AMG88xx_PIXEL_ARRAY_SIZE];
  //read all the pixels
  grideye.readPixels(pixels);

  Serial.print("[");
  for(int i=1; i<=AMG88xx_PIXEL_ARRAY_SIZE; i++){
    Serial.print(pixels[i-1]);
    Serial.print(", ");
    if( i%8 == 0 ) Serial.println();
  }
  Serial.println("]");
  Serial.println();

  //delay a second
  delay(1000);
}





void test_grideye_loop2() {
  Serial.print("Thermistor Temperature = ");
    Serial.print(grideye.readThermistor());
    Serial.println(" *C");
  
    Serial.println();

    //delay a second
    delay(1000);
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
