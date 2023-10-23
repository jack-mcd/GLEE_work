#ifndef HEALTHSCRIPT_H
#define HEALTHSCRIPT_H

#include <Arduino.h>
#include "Adafruit_TMP117.h"
#include "MPU6000.h" //this can be improved to only having to include one per sensor and could possibly
//bundle all of the new ones together since GLEE2023 includes lots of things we won't be using
#include <SparkFun_MMC5983MA_Arduino_Library.h>
#include "TPIS1385.h"
#include "LoRaFi.h"

class HealthScript {
    public:
        HealthScript(); //default constructor sets all sensors to "off" (logically)

        // void readBitString() TO-DO

        bool isInitialized(); //verifies our constructor has initialized private vars
        bool isTMP117Connected(Adafruit_TMP117 tmp); //checks if TMP117 sensor is connected
        bool isMPU6000Connected(MPU6000 acc); //checks if MPU6000 sensor is connected
        bool isMMC5983MAConnected(SFE_MMC5983MA mag); //checks if MMC5983MA sensor is connected
        bool isTPiS1S1385Connected(TPIS1385 therm); //checks if TPIS1S1385 sensor is connected
        bool isSX1272Connected(LoRaFi lora); //checks if SX1272 LoRa module is on

    private:
        /*
        sensors[0] = TMP117 status
        sensors[1] = MPU6000 status
        sensors[2] = MMC5983MA status
        sensors[3] = TPiS1S1385 status
        sensors[4] = SX1272 status
        */
        bool sensors[5];
};

#endif
