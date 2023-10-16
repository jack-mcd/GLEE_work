/*
Author: Jack McDonald
Date: 10/16/2023
Description: Testing 17 sample rates of accelerometer on LunaSat V6, what I foound is that sample rate time
does not change, indicating that it is possible that only gyroscope can change sample rate. Basing this off of
datasheet that states that sample rate = gyroscope output (kHz) / (1 + sample rate divisor). See datasheet
about sample rate divisor if curious about why this was inferred, note that this was inferred and not yet verified
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
