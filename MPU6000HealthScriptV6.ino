#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BusIO_Register.h>
#include <Adafruit_I2CDevice.h>
#include <Wire.h>

Adafruit_MPU6050 mpu;
Adafruit_MPU6050_Gyro gyroObj(&mpu);
sensors_event_t g;

uint8_t divisor = 0;
int idx;

unsigned long startSampleLoop;
unsigned long endSampleLoop;
unsigned long sampleLoopTotal[18];

int numSamples;

// TwoWire *wire;
// int32_t sensorID;
// uint8_t i2c_addr;

void setup() {
  Serial.begin(9600);
  //mpu.begin(MPU6050_I2CADDR_DEFAULT, wire, sensorID);
  //mpu.begin(i2c_addr = MPU6050_I2CADDR_DEFAULT, wire = &Wire, sensorID = 0x652);
  mpu.begin();
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
  //mpu.setSampleRateDivisor(divisor);
}

void loop() {
  numSamples = 0;

  Serial.print("Sample rate divisor (theoretical): "); Serial.print(divisor); Serial.println();
  //mpu.setSampleRateDivisor(divisor);
  // Wire.beginTransmission(MPU6050_SMPLRT_DIV);
  // Wire.write(0b00000000);
  // Wire.endTransmission();
  Serial.print("Sample rate divisor (actual): "); Serial.print(mpu.getSampleRateDivisor()); Serial.println();

  startSampleLoop = millis();
  while (numSamples < 500) {
    gyroObj.getEvent(&g);
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
