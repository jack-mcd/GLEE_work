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
bool HealthScript::isTMP117Connected() {
    Adafruit_TMP117 temp;
    return temp.afterInitCheck();
}