#include <Arduino.h>
#include "MPU6000_Lunar.h"
#include "TMP117_Lunar.h"
#include "BM1422AGMV_Lunar.h"
#include "TPIS1385_Lunar.h"
#include "CAP_Lunar.h"

/*
IMPORTANT NOTE!!!!

The way that we sample sensors based on the bitstring is not finalized, this script is a proof of concept that
we are able to switch between bistrings for the length of their duration, and take samples.
*/

#define BITSTRING1 0b01000000100000000000000011000000010ULL  // Bit string for sensor mode configurations, currently defaulted to Thermopile sensor only
#define BITSTRING2 0b10000001010001010000000000001110001ULL //second bitstring to switch to
#define BITSTRING3 0b11000000100001010000000001000000010ULL //third bitstring to switch to

const unsigned long DURATION1 = 5*1000;
const unsigned long DURATION2 = 10*1000;
const unsigned long DURATION3 = 3*1000;

unsigned long startConfig;

TPIS1385_Lunar thermo(1, true);
TPsample_t tpSample;
CAP_Lunar capLunar(1, true);
double dielectric;

float temp;
uint8_t tmp_buffer[2];

float acc[3];
float gyro[3];
uint8_t mpu_buffer[6];

float mag[3];
uint8_t mag_buffer[6];

void setup() {
  Wire.begin();
  Serial.begin(9600);
}

void loop() { 
  Serial.println("** STARTING BITSTRING1 **");
  setConfig(BITSTRING1);
  startConfig = millis();
  while (millis() - startConfig < DURATION1) {
    //NOTE: We are hardcoding sample retrieval since we know what will be turned on for each bitstring.
    //This method of sample retrieval does not reflect the way it will be implemented for flight.
    //This script is only focused on showing that mode switching will work.
    tpSample = thermo.getSample();
    Serial.print("TP Ambient: "); Serial.println(tpSample.ambient); 
    Serial.print("TP Object: "); Serial.println(tpSample.object);
  }
  Serial.println("** COMPLETED BITSTRING1 **");

  //BITSTRING PARTITION

  Serial.println("** STARTING BITSTRING2 **");
  setConfig(BITSTRING2);
  startConfig = millis();
  while (millis() - startConfig < DURATION2) {
    //CAP ON //TMP ONE_SHOT //MPU ACC MODE //MAG SINGLE
    //CAP DOESN'T WORK
    dielectric = capLunar.getDielectric();
    Serial.print("Dielectric: "); Serial.println(dielectric);
    
    //TMP117 DOES NOT WORK RIGHT NOW
    //TMP117_Lunar::getData(tmp_buffer);
    Lunar_I2C::readBytes(TMP117_TEMP_I2C, TMP117_TEMP_REG, 2, &tmp_buffer[0]);
    temp = (float)(tmp_buffer[0] << 8 | tmp_buffer[1]) * TMP117_RESOLUTION;
    //TMP117_Lunar::convertToTempC(tmp_buffer, &temp);
    Serial.print("Temperature C: "); Serial.println(temp);

    MPU6000_Lunar::readAccData(mpu_buffer);
    MPU6000_Lunar::convertAccToFloat(mpu_buffer, acc);
    Serial.print("Acc. X: "); Serial.print(acc[0]); Serial.print(" Acc. Y: "); Serial.print(acc[1]); Serial.print(" Acc. Z: "); Serial.println(acc[2]);

    //DON'T THINK IT'S WORKING NEED TO VERIFY WITH SCIENCE
    BM1422AGMV_Lunar::getData(mag_buffer);
    BM1422AGMV_Lunar::convertToFloats(mag_buffer, mag);
    Serial.print("Mag readings: "); Serial.print(mag[0]); Serial.print(", "); Serial.print(mag[1]); Serial.print(", "); Serial.println(mag[2]);
  }
  Serial.println("** COMPLETED BITSTRING2 **");

  //BITSTRING PARTITION

  Serial.println("** STARTING BITSTRING3 **");
  setConfig(BITSTRING3);
  startConfig = millis();
  while (millis() - startConfig < DURATION3) {
    //GYRO on
    MPU6000_Lunar::readGyroData(mpu_buffer);
    MPU6000_Lunar::convertGyroToFloat(mpu_buffer, gyro);
    Serial.print("Gyro X: "); Serial.print(gyro[0]); Serial.print(" Gyro Y: "); Serial.print(gyro[1]); Serial.print(" Gyro Z: "); Serial.println(gyro[2]);
  }
  Serial.println("** COMPLETED BITSTRING3 **");
}

void setConfig(unsigned long long config){
  Serial.print("Config string passed into setConfig (hex): ");
  // Print upper 32 bits of config
  Serial.print((unsigned long)(config >> 32), HEX);
  // Print lower 32 bits of config
  Serial.println((unsigned long)config, HEX);

  //The following calls will print each mode/configuration that the specific sensor is set to.
  thermo.setConfig((config>>34) & 0x1); // call to setConfig from TPIS1385_Lunar in source code, sets the mode for the thermopile sensor
  thermo.readEEprom();

  capLunar.setConfig((config>>33) & 0x1); // call to setConfig from CAP_Lunar in source code, sets the mode for the capacitive sensor
  uint8_t capAdd = capLunar.getAddress();
  Serial.println(capAdd);

  TMP117_Lunar::setConfig((config>>25) & 0xFF); // call to setConfig from TMP117_Lunar in source code, sets the mode for the temperature sensor
  TMP117_Lunar::readConfig();

  MPU6000_Lunar::setConfig((config>>8) & 0x1FFFF); // call to setConfig from MPU60000_Lunar in source code, sets the mode for the accelerometer
  MPU6000_Lunar::readConfig();
  
  BM1422AGMV_Lunar::setConfig(config & 0xFF); // call to setConfig from BM1422AGMV_Lunar in source code, sets the mode for the magnetometers
  BM1422AGMV_Lunar::readConfig();
}