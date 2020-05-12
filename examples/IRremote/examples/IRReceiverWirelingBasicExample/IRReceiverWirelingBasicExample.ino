/************************************************************************
   IR Receiver Wireling Example
   This code shows how to use the IR Receiver Wireling to receive NEC
   IR codes(in this example, the codes used with TinyTV) and print the
   results to the Serial Monitor.

   Hardware by: TinyCircuits
   Written by: Ben Rose for TinyCircuits

   Initiated: 11/20/2019
   Updated: 05/06/2020
 ************************************************************************/

#include <IRremote.h>

#include <Wire.h>
#include <Wireling.h>

#if defined (ARDUINO_ARCH_AVR)
#define SerialMonitorInterface Serial
#elif defined(ARDUINO_ARCH_SAMD)
#define SerialMonitorInterface SerialUSB
#endif

// Define codes as 32 bit unsigned integers
uint32_t powerCode = 0x10AF8877;
uint32_t volUpCode = 0x10AF708F;
uint32_t volDownCode = 0x10AFB04F;
uint32_t chanUpCode = 0x10AF807F;
uint32_t chanDownCode = 0x10AF20DF;
uint32_t muteCode = 0x10AFF00F;

// Receive and transmit can be done on any IO pin. Pick A0-A3 for Wireling ports 0-3.
int RECV_PIN = A3;

IRrecv irrecv(RECV_PIN);

void setup(void) {
  SerialMonitorInterface.begin(9600);
  Wire.begin();
  Wireling.begin();
  while (!SerialMonitorInterface && millis() < 5000); //This will block for 5 seconds or until the Serial Monitor is opened on TinyScreen+/TinyZero platform!

  irrecv.enableIRIn(); // Start receiving data
}

void loop() {
  decode_results results;
  if (irrecv.decode(&results)) {
    irrecv.resume(); // Receive the next value
    if (results.decode_type = NEC && results.bits == 32) { //Check if there's a match for our expected protocol and bitcount
      if (results.value == powerCode) {
        SerialMonitorInterface.println("powerCode received!");
      } else if (results.value == volUpCode) {
        SerialMonitorInterface.println("volUpCode received!");
      } else if (results.value == volDownCode) {
        SerialMonitorInterface.println("volDownCode received!");
      } else if (results.value == chanUpCode) {
        SerialMonitorInterface.println("chanUpCode received!");
      } else if (results.value == chanDownCode) {
        SerialMonitorInterface.println("chanDownCode received!");
      } else if (results.value == muteCode) {
        SerialMonitorInterface.println("muteCode received!");
      } else {
        SerialMonitorInterface.print("Unrecognized code! ");
        SerialMonitorInterface.println(results.value, HEX);
      }
    } else {
      SerialMonitorInterface.print(results.decode_type);
      SerialMonitorInterface.print(" ");
      SerialMonitorInterface.print(results.bits);
      SerialMonitorInterface.print(" ");
      SerialMonitorInterface.println(results.value, HEX);
    }
  }
}
