#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

Adafruit_MPU6050 mpu;
Adafruit_MPU6050_Gyro gyroObj(&mpu);
sensors_event_t g;

void setup() {
  Serial.begin(9600);
  if (!mpu.begin()){
    Serial.println("MPU not initialized");
  }
  // mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  // mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  // //mpu.setSampleRateDivisor(0);
  // mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
}

void loop() {
  //Serial.println(mpu.getSampleRateDivisor());
  // Adafruit_BusIO_Register sample_rate_div =
  // Adafruit_BusIO_Register(i2c_dev, MPU6050_SMPLRT_DIV, 1);
  // sample_rate_div.write(0);

  Serial.println(mpu.getSampleRateDivisor());

  gyroObj.getEvent(&g);
  Serial.println("Gyroscope reading: ");
  Serial.print(g.gyro.x); Serial.println();
  Serial.print(g.gyro.y); Serial.println();
  Serial.print(g.gyro.z); Serial.println();
  while (1) { //just want to verify it's working, don't need to read sensor more than once
    delay(10000);
  }
}
