#include "MPU6000.h"

uint8_t divisor = 255; //possible that this must start from 254
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
  Serial.print("Sample rate divisor: "); Serial.print(divisor); Serial.println();

  accelerometer.setSampleRateDivisor(divisor);
  delay(1000);

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
  divisor--;
}
