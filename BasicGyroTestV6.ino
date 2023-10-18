/*
Author: Jack McDonald
Date: 10/17/2023
Description: For V6 LunaSat, simply setting up gyroscope and confirming we are able to read gyroscope output.

**NOTE** this code was written with the following addition to the MPU6000.h class

uint8_t MPU6000::getSampleRateDivisor() {
	uint8_t divisor;
	divisor = readByte(MPU6000_SMPLRT_DIV);
	return divisor;
}
*/

#include "MPU6000.h"

MPU6000 accelerometer(1, false); // Sets sensor ID to 1 and debugging to false
sensor_int16_vec_t rawGyro;
sensor_float_vec_t gyro;

void setup() {
  Serial.begin(9600);
  if (!accelerometer.begin()){
    Serial.println("MPU not found");
  }
  Serial.println("MPU found");

  accelerometer.initialize(); //sets sample rate divisor to 0
  accelerometer.setGyroRange(MPU6000_RANGE_500_DEG);
  
  Serial.print("Sample rate divisor: "); Serial.println(accelerometer.getSampleRateDivisor());
}

void loop() {
  rawGyro = accelerometer.getRawGyro();
  gyro = accelerometer.getGyro(rawGyro);

  Serial.print("Angular Velocity in Degrees per Second, X-Axis: "); Serial.print(gyro.x, 8);
  Serial.print(" Y-Axis: "); Serial.print(gyro.y, 8);
  Serial.print(" Z-Axis: "); Serial.print(gyro.z, 8);
  Serial.println();

  while (1) {
    delay(10000);
  }
}
