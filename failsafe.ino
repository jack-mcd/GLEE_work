#include <EEPROM.h>
#include "Adafruit_TMP117.h"
#include "MPU6000.h"

/*
EEPROM reference:
https://docs.arduino.cc/learn/programming/eeprom-guide

EEPROM partitions
| byte 0 = uint8_t val  | byte 1 = uint8_t ???   |
| val shows us how many | no variable name used  |
| times the lunaSat has | if == 64 then we don't |
| powered off           | have enough power for  |
|                       | any sensors            |

*/
uint8_t val;

Adafruit_TMP117  tmp117;
MPU6000 acc(1, false);

void setup() {
  Serial.begin(9600);

  val = EEPROM.read(0);

  if (val == 255) {
    EEPROM.write(0, 0);
    Serial.println(F("Wrote 0 to EEPROM, 255 read at position 0"));
    tmp117.begin();
    acc.begin();
    acc.initialize();
    //init all sensors
  }
  else {
    EEPROM[0] += 1;
    Serial.println(F("EEPROM ITERATED AT POS 0, we have turned off before"));
  }

  if (val == 1) { //we have turned off once, don't initialize TMP117 (lower priority)
    acc.begin();
    acc.initialize();
  }
  else {
    //don't turn on anything (just for testing purposes)
    //write some stuff to eeprom
    EEPROM.write(1, 64); //64 at pos 1 indicates that we don't have enough power to run anything
  }


}

void loop() { }
