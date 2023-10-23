#include <Arduino.h>
#include <EEPROM.h>
#include "HealthScript.h"

/*
Default constructor:
Initializes all sensors to false, meaning they are off
*/
HealthScript::HealthScript() {
    tmp = false;
}

/*
Verifies that default constructor initialized private variables
*/
bool HealthScript::isInitialized() {
    if (tmp == false) {
        return true;
    }
}

/*
Checks if TMP117 sensor is connected
*/
bool HealthScript::isTMP117Connected(Adafruit_TMP117 temp) {
    return temp.afterInitCheck();
}

bool HealthScript::isMPU6000Connected(MPU6000 acc) {
    return acc.isConnected();
}

bool HealthScript::isMMC5983MAConnected(SFE_MMC5983MA mag) {
    return mag.isConnected();
}

bool HealthScript::isTPiS1S1385Connected(TPIS1385 therm) {
    return therm.isConnected();
}

bool HealthScript::isSX1272Connected(LoRaFi lora) {
    return lora.isOn();
}
