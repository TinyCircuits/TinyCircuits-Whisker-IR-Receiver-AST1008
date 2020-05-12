/************************************************************************
   IR Emitter Wireling Example
   This code shows how to use the IR Emitter Wireling to transmit NEC
   IR codes(in this example, the codes used with TinyTV).

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
int TX_PIN = A0;

IRsend irsend(TX_PIN);

void setup(void) {
  SerialMonitorInterface.begin(9600);
  Wire.begin();
  Wireling.begin();
  while (!SerialMonitorInterface && millis() < 5000); //This will block for 5 seconds or until the Serial Monitor is opened on TinyScreen+/TinyZero platform!
}


void loop() {
  SerialMonitorInterface.println("Sending powerCode!");
  noInterrupts();
  irsend.sendNEC(powerCode, 32);
  interrupts();
  delay(1000);
  SerialMonitorInterface.println("Sending muteCode!");
  noInterrupts();
  irsend.sendNEC(muteCode, 32);
  interrupts();
  delay(1000);
}
