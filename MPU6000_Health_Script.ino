/*
  Description: Accelerometer sample rate test
  Author: Jack McDonald
  Date: 9/27/23
*/

#include "MPU6000.h"

uint8_t divisor = 255; //possible that this must start from 254
int idx;

MPU6000 accelerometer(1, false); // Sets sensor ID to 1 and debugging to false
sensor_float_vec_t acc; // Saves acceleration readings in a vector structure

unsigned long startSampleLoop;
unsigned long endSampleLoop;
unsigned long sampleLoopTotal[17];

unsigned long loopTime;

int numSamples;


void setup() {

  Serial.begin(9600); // Sets baud rate to 9600 bits per second for serial transmission 
                        // and starts serial communication

  accelerometer.begin(); // Begins transmission to the I2C slave device
  accelerometer.initialize(); // Set-up for MPU 
  accelerometer.setAccelRange(MPU6000_RANGE_2_G); // Sets range of acccelrometer 
                                                    // Range options: 2_G, 4_G, 8_G, 16_G   
  
  /*
  Find out time loop takes and time it takes to iterate numSamples as this needs to be subtracted from the actual
  sample rate time that we calculate in loop(). An example to portray the logic behind this:

  while (numSamples < 100) { <--- 2-3 operations: it's a while loop, check condition, continue or break
    acc = accelerometer.getSample(); <---- ? operations: this is what we want to measure the time of
    numSamples++; <----- ~2 operations: read current value, iterate this value and save it... we don't want this to be measured
  }

  Therefore, measure the time of the loop without the accelerometer readings, so we can subtract the time that takes below
  to just get the time it takes to measure the accelerometer 100 times
  */
  int numSamples = 0;
  startSampleLoop = micros();
  while (numSamples < 100) {
    numSamples++;
  }
  endSampleLoop = micros();
  loopTime = endSampleLoop - startSampleLoop;
  Serial.print("Loop time: "); Serial.print(loopTime); Serial.println();

}

void loop() {
  numSamples = 0;

  Serial.print("Sample rate divisor: "); Serial.print(divisor); Serial.println();

  accelerometer.setSampleRateDivisor(divisor);

  startSampleLoop = micros();
  while (numSamples < 100) {
    acc = accelerometer.getSample();
    numSamples++;
    /*
    Do we need to account for time it takes to increment numSamples? May not be necessary since presumably the differences
    in time will be the same where the increments are an added constant no matter what sample rate is
    */
  }
  endSampleLoop = micros();
  /*
  Design decision to trade memory for a more accurate time stamp of time it takes to complete while loop.
  Possible that it is better to not have endSampleLoop variable and compute sampleLoopTotal as
  sampleLoopTotal = micros() - startSampleLoop, but it was hypothesized that this micros() reading would
  be less accurate than the way we are doing it above.
  */
  idx = (divisor/15) % 17;
  Serial.print("For index "); Serial.print(idx); Serial.println();
  sampleLoopTotal[idx] = (endSampleLoop - startSampleLoop) - loopTime;
  Serial.print("Time in microseconds: "); Serial.print(sampleLoopTotal[idx]); Serial.println();

  if (divisor == 0) {
    Serial.println("Highest sample rate reached");
    /*
    Making program stick in while loop so output doesn't become cluttered and we
    don't set sample divisor rates that aren't valid (i.e. < 0). This health script
    assumes it is being run manually with an operator monitoring the serial
    output. This can be modified on V6 LunaSat with EEPROM.
    */
    while (1) {
      delay(10000);
    }
  }
  divisor -= 15;
}
