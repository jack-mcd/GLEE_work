#include <EEPROM.h>

int val;

void setup() {
  Serial.begin(9600);
  Serial.print("Size in bytes of EEPROM: "); Serial.println(EEPROM.length());

  val = EEPROM.read(0);
  if (val == 255) {
    EEPROM.write(0, 1);
    Serial.println("Wrote 1 to EEPROM[0]");
  }
  else {
    Serial.print("Reading from EEPROM[0]: "); Serial.println(val);
  }

}

void loop() {}
