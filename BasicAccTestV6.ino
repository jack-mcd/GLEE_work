/*
Author: Jack McDonald
Date: 10/16/2023
Description: For V6 LunaSat, simply setting up gyroscope and confirming we are able to change
the sample rate and read gyroscope output.

**NOTE** this code was written with the following addition to the MPU6000.h class

uint8_t MPU6000::getSampleRateDivisor() {
	uint8_t divisor;
	divisor = readByte(MPU6000_SMPLRT_DIV);
	return divisor;
}
*/

#include "MPU6000.h"

MPU6000 accelerometer(1, false); // Sets sensor ID to 1 and debugging to false
sensor_float_vec_t acc;

void setup() {
  Serial.begin(9600);
  if (!accelerometer.begin()){
    Serial.println("MPU not found");
  }
  Serial.println("MPU found");

  accelerometer.initialize();
  accelerometer.setGyroRange(MPU6000_RANGE_500_DEG);
  
  Serial.print("Sample rate divisor: "); Serial.println(accelerometer.getSampleRateDivisor());
}

void loop() {
  acc = accelerometer.getSample();

  Serial.print("Acceleration in Gs, X-Axis: "); Serial.print(acc.x, 8); // Prints out 3-axis acceleration (G)
  Serial.print(" Y-Axis: "); Serial.print(acc.y, 8);
  Serial.print(" Z-Axis: "); Serial.print(acc.z, 8);
  Serial.println();

  while (1) {
    delay(10000);
  }
}
