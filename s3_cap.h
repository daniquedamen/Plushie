/*
Last modified 08-11-23
Danique Damen (d.damen-1@studen.utwente.nl)

Summary file:
Capacity sensor header

library: https://github.com/sparkfun/SparkFun_CAP1203_Arduino_Library


*/

#include <Wire.h> // allows to communicate with I2C: SDA and SCL
#include "SparkFun_CAP1203.h" // Library for the capacity sensor


#ifndef S3_CAP_H
#define S3_CAP_H

class Cap_Class {
  public:

  Cap_Class();
  void cap_initialization();
  int cap_loop();

  private:
  CAP1203 sensor; 
  int cap_touched;

};


#endif