/** Read Nortec Vector ADV serial packets */

#include <Arduino.h>

const byte numChars = 28; //max bytes for ADV packets
const char startMarker = '^'; //start byte of ADV packets
// const int startMarker = 165; //start byte of ADV packets
const char VVDChar = 'a'; //VVD packet designator
const byte VVDLength = 3; //length of VVD packets
const byte VSDLength = 6; //length of VSD packets
//const int VVDChar = 16; //VVD packet designator
//const int VVDLength = 24; //length of VVD packets
//const int VSDLength = 28; //length of VSD packets
char ADVpacket[numChars];
boolean newData = false;

void recvADV() {
  static byte ndx = 0;
  static boolean recvInProgress = false;
  static byte packetLength;
  char rc;
  while (Serial.available() > 0 && newData == false) {
    rc = Serial.read();
    if (recvInProgress == true) {
      if (ndx == 1) {
        if (rc == VVDChar) {
          packetLength = VVDLength;
        } else {
          packetLength = VSDLength;
        }
        ADVpacket[ndx] = rc;
        ndx++;
      } else if (ndx == packetLength - 1) { // whole packet received
        ADVpacket[ndx] = rc;
        ndx++;
        ADVpacket[ndx] = '\0';
        ndx = 0;
        newData = true;
        recvInProgress = false;
      } else {
        ADVpacket[ndx] = rc;
        ndx++;
      }
    } else if (rc == startMarker) {
      ADVpacket[ndx] = rc;
      ndx++;
      recvInProgress = true;
    }
  }
}

void parseVVD() {
  Serial.print("New VVD: ");
  Serial.println(ADVpacket);
}

void parseVSD() {
  Serial.print("New VSD: ");
  Serial.println(ADVpacket);
}

void parseADV() {
  if (newData) {
    if (ADVpacket[1] == VVDChar) {
      parseVVD();
    } else {
      parseVSD();
    }
    newData = false;
  }
}

void setup() {
  Serial.begin(9600);
  Serial.println("Teensy ready");
}

void loop() {
  recvADV();
  parseADV();
}