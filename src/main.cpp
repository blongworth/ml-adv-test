/** Read Nortec Vector ADV serial packets */

#include <Arduino.h>
#include "adv.h"

#define ADV_SERIAL Serial3

ADV adv(ADV_SERIAL);

elapsedMillis loopTimer;
unsigned long loopCount = 0;

void setup() {
  Serial.begin(9600);
  ADV_SERIAL.begin(115200);
  delay(3000);
  Serial.println("Teensy ready");
  Serial.println("Starting ADV...");
  adv.begin();
}

void loop() {
  loopCount++;
  if (loopTimer >= 1000) {
    Serial.print("Loop rate: ");
    float loopRate = (float)loopCount / (loopTimer / 1000.0);
    Serial.print(loopRate);
    Serial.println(" loops per second");
    loopCount = 0;
    loopTimer = 0;
  }
  
  adv.read();
  adv.getVVDPacket();
  adv.getVSDPacket();
}