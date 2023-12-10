/*
Last modified 08-11-23
Danique Damen (d.damen-1@studen.utwente.nl)

Summary file:
Measuring the capacity pads (left (the lowest), middle, right (highest)) of the Plushie) Xiao seeed NRFCAP1203 (Sparkfun)
In the library, adjustment is done to allow multiple touch of the sensor.

*/

#include "s3_cap.h"



Cap_Class::Cap_Class(){

}

void Cap_Class::cap_initialization()
{
  Wire.begin();       // Join I2C bus  

  if (sensor.begin() == false)
  {
    Serial.println("Not connected. Please check connections and read the hookup guide.");
    while (1);
  }
  else
  {
    Serial.println("Cap initialised");
  }

  // sensor.setSensitivity(SENSITIVITY_4x); // Setup sensitivity if necessary. UP UNTILL 1X-128X 
}

int Cap_Class::cap_loop()
{
  cap_touched = 0;

  if (sensor.isMiddleTouched() == true)
  {
    cap_touched += 1;
  }

  if (sensor.isRightTouched() == true)
  {
    cap_touched += 10;
  }

  return cap_touched;
}
