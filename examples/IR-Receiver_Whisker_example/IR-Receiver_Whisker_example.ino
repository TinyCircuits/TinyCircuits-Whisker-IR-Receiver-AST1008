/*
 * IRremote: IRrecvDemo - demonstrates receiving IR codes with IRrecv
 * An IR detector/demodulator must be connected to the input RECV_PIN.
 * Version 0.1 July, 2009
 * Copyright 2009 Ken Shirriff
 * http://arcfn.com
 */
#include "IRremote.h"
#include <SPI.h>
#include <Wire.h>
#include <TinyScreen.h>
int RECV_PIN = A0;
IRrecv irrecv(RECV_PIN);
decode_results results;
#if defined(ARDUINO_ARCH_SAMD)
#define SerialMonitorInterface SerialUSB
#else
#define SerialMonitorInterface Serial
#endif
// TinyScreen Global Variables
TinyScreen display = TinyScreen(TinyScreenPlus);
int background = TS_8b_Black; // sets the background color to black
void setup(){
  pinMode(4,OUTPUT);
  digitalWrite(4,HIGH);
  SerialMonitorInterface.begin(9600);
  // In case the interrupt driver crashes on setup, give a clue
  // to the user what's going on.
  SerialMonitorInterface.println("Enabling IRin");
  irrecv.enableIRIn(); // Start the receiver
  SerialMonitorInterface.println("Enabled IRin");
  Wire.begin();
  selectPort(0); // The adapter board has 4 different ports (0-3),
                 // make sure your software matches the setup!
  // This is the setup used to initialize the TinyScreen's appearance
  display.begin();
  display.setBrightness(15);
  display.setFlip(true);
  display.setFont(thinPixel7_10ptFontInfo); 
  display.fontColor(TS_8b_White, background);
    // Set the cursor to the following coordinates before it prints "BME280 Test" 
  display.setCursor(0, 0);
  display.print("IR Rev Test");
//  if (!irrev.begin()) {
//  display.setCursor(12, 12); 
//  display.print("No Sensor!");  // Printed to TinyScreen
//  SerialMonitor.println("Could not find a valid irrev sensor, check wiring!"); // Printed to SerialMonitor Monitor
//  while (1); // loop forever, because the rest of the program means nothing without the sensor
//  }
} //end of void setup
void loop() {
  if (irrecv.decode(&results)) {
    SerialMonitorInterface.println(results.value, HEX);
    irrecv.resume(); // Receive the next value
//  } else {
//    SerialMonitorInterface.println("Sensor not working");
  }
  delay(100);
}
////////////////////////////////////////Subroutines/////////////////////////////////////////////////////////////////
void selectPort(int port) {
  Wire.beginTransmission(0x70); //I2C
  Wire.write(0x04 + port);
  Wire.endTransmission();
}
