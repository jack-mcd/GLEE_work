#ifndef HEALTHSCRIPT_H
#define HEALTHSCRIPT_H

#include <Arduino.h>
#include "Adafruit_TMP117.h"

class HealthScript {
    public:
        HealthScript(); //default constructor sets all sensors to "off" (logically)
        bool isInitialized(); //verifies our constructor has initialized private vars
        bool isTMP117Connected(); //checks if TMP117 sensor is connected

    private:
        bool tmp; //false = off, true = on
};

#endif