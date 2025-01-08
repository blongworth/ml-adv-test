/** Read Nortec Vector ADV serial packets */

#include <Arduino.h>
#include "adv.h"

#define ADV_SERIAL Serial3

ADV adv(ADV_SERIAL);

void setup() {
  Serial.begin(9600);
  ADV_SERIAL.begin(115200);
  delay(3000);
  Serial.println("Teensy ready");
  Serial.println("Starting ADV...");
  adv.begin();
}

void loop() {
  adv.read();
  adv.getVVDPacket();
  adv.getVSDPacket();
}