#include "HealthScript.h"
#include "Adafruit_TMP117.h"

Adafruit_TMP117 temp;
HealthScript hs;

void setup() {
  Serial.begin(9600);
  temp.begin();
  Serial.println(hs.isInitialized());
  Serial.println(hs.isTMP117Connected());
}

void loop() {}
