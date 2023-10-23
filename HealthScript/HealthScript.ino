#include "HealthScript.h"

Adafruit_TMP117 temp;
MPU6000 acc(1, false);
SFE_MMC5983MA myMag;
TPIS1385 therm(1);
LoRaFi lora;
HealthScript hs;

void setup() {
  Serial.begin(9600);
  temp.begin();
  acc.begin();
  acc.initialize();
  acc.setAccelRange(MPU6000_RANGE_2_G);
  myMag.begin();
  therm.begin();
  lora.begin();
  if (hs.isInitialized()) {
    Serial.println("Health script initialized");
  }
  if (hs.isTMP117Connected(temp)) {
    Serial.println("TMP117 found");
  }
  if (hs.isMPU6000Connected(acc)) {
    Serial.println("MPU6000 found");
  }
  if (hs.isMMC5983MAConnected(myMag)) {
    Serial.println("MMC5983MA found");
  }
  if (hs.isTPiS1S1385Connected(therm)) {
    Serial.println("TPiS 1S 1385 found");
  }
  if (hs.isSX1272Connected(lora)) {
    Serial.println("SX1272 found");
  }

}

void loop() {}
