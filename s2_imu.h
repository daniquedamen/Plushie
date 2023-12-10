/*
Last modified 07-11-23
Danique Damen (d.damen-1@studen.utwente.nl)

*/
#include <string>
#include "LSM6DS3.h"
#include "Wire.h"

#ifndef SENSOR2_IMU_H
#define SENSOR2_IMU_H


class IMU_Class {
  public:

  IMU_Class();

  void IMU_initialization();
  float IMU_loop();
  int IMU_interaction();


  private:

  float gyr[3];
  int magnitude;

};


#endif