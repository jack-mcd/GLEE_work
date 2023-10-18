/*
Author: Jack McDonald
Date: 10/16/2023
Updated: 10/17/2023
Description: Testing 17 sample rates of accelerometer on LunaSat V6, what I found is that sample rate time
does not change, indicating to me that we are not finding the sample rate correctly, I have verified that the
sample rate should change for accelerometer too.

**NOTE** this code was written with the following changes to the MPU6000 class (.cpp & .h)

uint8_t MPU6000::getSampleRateDivisor() {
	uint8_t divisor;
	divisor = readByte(MPU6000_SMPLRT_DIV);
	return divisor;
}

mpu6000_bandwidth_t MPU6000::getFilterBandwidth() {
	return readByte(MPU6000_CONFIG);
}
*/

#include "MPU6000.h"

MPU6000 accelerometer(1, false); // Sets sensor ID to 1 and debugging to false
sensor_float_vec_t acc;

uint8_t divisor = 0;
int idx;

unsigned long startSampleLoop;
unsigned long endSampleLoop;
unsigned long sampleLoopTotal[18];

int numSamples;

void setup() {
  Serial.begin(9600);
  accelerometer.begin();
  accelerometer.initialize();
  accelerometer.setFilterBandwidth(MPU6000_BAND_5_HZ); //set gyroscope output rate to 1 kHz
  Serial.println(accelerometer.getFilterBandwidth());
}

void loop() {
  numSamples = 0;

  accelerometer.setSampleRateDivisor(divisor);

  Serial.print("Sample rate divisor: "); Serial.println(accelerometer.getSampleRateDivisor());

  startSampleLoop = millis();
  while (numSamples < 1000) {
    acc = accelerometer.getSample();
    numSamples++;
  }
  endSampleLoop = millis();

  idx = divisor/15;
  Serial.print("For index "); Serial.print(idx); Serial.println();
  sampleLoopTotal[idx] = endSampleLoop - startSampleLoop;
  Serial.print("Time in milliseconds: "); Serial.print(sampleLoopTotal[idx]); Serial.println();

  if (divisor == 255) {
    Serial.println("Tested 17 Sample Rates");
    while (1) {
      delay(10000);
    }
  }

  divisor += 15;
}
