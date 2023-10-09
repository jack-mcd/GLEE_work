/*
Author: Jack McDonald
Date: 10/09/2023
Description: Testing the accelerometer / gyroscope sample rate
*/

/*
EEPROM key:
  - 0 means we tried the sample rate but LunaSat powered down
  - 1 means we successfully ran LunaSat at given sample rate
  - 2 means we powered down LunaSat for other reasons but last time we found a 1 for a given sample rate
  - 255 means nothing has been written to the EEPROM at a given position
*/

#include "MPU6000_Lunar.h"
#include <EEPROM.h>

unsigned int eepromSize = EEPROM.length(); //number of bytes in the EEPROM
int lastIdx = 0; //last index written to in EEPROM
uint8_t divisor = 0;
bool foundDiv = false;
bool firstTest = false;

//setup will be used when LunaSat powers on (or back on)
void setup() {
  
  for (int i = 0; i < eepromSize; i++ ) {
    if (EEPROM.read(i) == 255) { //find the first cell of EEPROM we have not written to
      if (i == 0) { //if this is first test
        firstTest = true;
        break;
      }
      lastIdx = i-1;
      if (EEPROM.read(lastIdx) == 1 || EEPROM.read(lastIdx) == 2) { //if we have already found a successful sample rate
        foundDiv = true;
        break;
      }
      else { //last sample rate was unsuccessful, try next one
        EEPROM.write(lastIdx+1, 0); //this will be updated to a 1 if we can successfully generate samples at this rate
        divisor = lastIdx+1 * 15; //need to implement control that divisor can only be between 0-255
        break;
      }
    }
    else {
      continue;
    }
  }

}

void loop() {
  if (foundDiv == true) {
    EEPROM.write(lastIdx+1, 2);
    while (1) {
      delay(10000);
    }
  }
  else {
    int numSamples = 0;
    while (numSamples < 500) {

    }
  }

}
