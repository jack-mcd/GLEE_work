#include <Arduino.h>
#include <EEPROM.h>
#include "HealthScript.h"

/*
bool sensors[5] logical layout:
sensors[0] = TMP117 status
sensors[1] = MPU6000 status
sensors[2] = MMC5983MA status
sensors[3] = TPiS1S1385 status
sensors[4] = SX1272 status

** NOTE **
Could be updated to bits or other more compact memory option

*/

/*
Default constructor:
Initializes all sensors to false, meaning they are off
*/
HealthScript::HealthScript() {
    memset(sensors, false, 5);
}

/*
Verifies that default constructor initialized private variables
*/
bool HealthScript::isInitialized() {
    for (bool x: sensors) {
        if (x == true) {
            return false;
        }
    }
    return true;
}

/*
Checks if TMP117 sensor is connected
sensors[0] = TMP117 status
*/
bool HealthScript::isTMP117Connected(Adafruit_TMP117 temp) {
    sensors[0] = temp.afterInitCheck();
    return sensors[0];
}

/*
Checks if MPU6000 sensor is connected
sensors[1] = MPU6000 status
*/
bool HealthScript::isMPU6000Connected(MPU6000 acc) {
    sensors[1] = acc.isConnected();
    return sensors[1];
}

/*
Checks if MMC5983MA sensor is connected
sensors[2] = MMC5983MA status
*/
bool HealthScript::isMMC5983MAConnected(SFE_MMC5983MA mag) {
    sensors[2] = mag.isConnected();
    return sensors[2];
}

/*
Checks if TPiS 1S 1385 sensor is connected
sensors[3] = TPiS 1S 1385 status
*/
bool HealthScript::isTPiS1S1385Connected(TPIS1385 therm) {
    sensors[3] = therm.isConnected();
    return sensors[3];
}


/*
Checks if SX1272 LoRa module is connected (on)
sensors[4] = SX1272 status
*/
bool HealthScript::isSX1272Connected(LoRaFi lora) {
    sensors[4] = lora.isOn();    
    return sensors[4];
}
