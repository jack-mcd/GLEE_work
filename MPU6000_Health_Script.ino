#include "MPU6000.h"

uint8_t divisor = 0; //possible that this must start from 254
MPU6000 accelerometer(1, false); // Sets sensor ID to 1 and debugging to false
sensor_float_vec_t acc; // Saves acceleration readings in a vector structure

void setup() {

  Serial.begin(9600); // Sets baud rate to 9600 bits per second for serial transmission 
                        // and starts serial communication

  accelerometer.begin(); // Begins transmission to the I2C slave device
  accelerometer.initialize(); // Set-up for MPU 
  accelerometer.setAccelRange(MPU6000_RANGE_2_G); // Sets range of acccelrometer 
                                                    // Range options: 2_G, 4_G, 8_G, 16_G                      

}

void loop() {

  // Serial.print("Max. Sample Rate Divisor: "); Serial.print(ctr);
  // Serial.println();
  uint8_t divisor = uint8_t(ctr);
  //Serial.print("Binary equivalent: "); Serial.print(divisor);
  accelerometer.setSampleRateDivisor(ctr);
  //if we fail right here we won't write our current divisor to the eeprom
  //^^ meaning that the previous divisor value is our max sample rate
  //(when we update this code for V6 that has eeprom)

  delay(5000);
  ctr++;
}
