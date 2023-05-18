/** Read Nortec Vector ADV serial packets */

#include <Arduino.h>

const byte numChars = 28; //max bytes for ADV packets
const char startMarker = '^'; //start byte of ADV packets
// const int startMarker = 165; //start byte of ADV packets
const char VVDChar = 'a'; //VVD packet designator
const int VVDLength = 3; //length of VVD packets
const int VSDLength = 6; //length of VSD packets
//const int VVDChar = 16; //VVD packet designator
//const int VVDLength = 24; //length of VVD packets
//const int VSDLength = 28; //length of VSD packets
char recievedChars[numChars];
boolean newData = false;

void recvADV() {
  static byte ndx = 0;
  static boolean recvInProgress = false;
  static int packetLength = 0;
  char rc;
  while (Serial.available() > 0 && newData == false) {
    rc = Serial.read();
    if (recvInProgress == true) {
      if (ndx == 1) {
        if (rc != VVDChar) {
          packetLength = VSDLength;
        } else {
          packetLength = VVDLength;
        }
        recievedChars[ndx] = rc;
        ndx++;
      } else if (ndx == packetLength) { // whole packet received
        //recievedChars[ndx] = '\0';
        ndx = 0;
        newData = true;
        recvInProgress = false;
      } else {
        recievedChars[ndx] = rc;
        ndx++;
        if (ndx >= numChars) {
          ndx = numChars - 1;
        }
      }
    } else if (rc == startMarker) {
      recievedChars[ndx] = rc;
      ndx++;
      recvInProgress = true;
    }
  }
}

void showNewData() {
  if (newData) {
    Serial.print("New char on serial: ");
    Serial.println(recievedChars);
    newData = false;
  }
}
void setup() {
  Serial.begin(9600);
  Serial.println("Teensy ready");
}

void loop() {
  recvADV();
  showNewData();
}