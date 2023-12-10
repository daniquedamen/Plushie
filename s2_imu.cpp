/*
Last modified 07-11-23
Danique Damen (d.damen-1@studen.utwente.nl)

Summary file:
Using the library for the build-in IMU of the Xiao seeed NRF52480: LSM6DS3 to the magnitude of the gyroscope.

IMU library: https://github.com/Seeed-Studio/Seeed_Arduino_LSM6DS3


*/

#include "s2_imu.h"

LSM6DS3 myIMU(I2C_MODE, 0x6A);

IMU_Class::IMU_Class() {
  // Constructor
}

// Initialize class
void IMU_Class::IMU_initialization() 
{
    if (myIMU.begin() != 0) 
    {
        Serial.println("Device error");
    } 
    else 
    {
        Serial.println("IMU intialised!");
    }

}

// Within this function, the 3D values of the gyro are read.
int IMU_Class::IMU_loop(){
  gyr[0] = myIMU.readFloatGyroX();
  gyr[1] = myIMU.readFloatGyroY();
  gyr[2] = myIMU.readFloatGyroZ();

  // > 200 +- is interaction
  magnitude = sqrt(pow(gyr[0], 2) + pow(gyr[1],2) + pow(gyr[2],2)); 

  return magnitude;
}
