/*
Last modified 07-11-23
Danique Damen (d.damen-1@studen.utwente.nl)

BLE library: https://github.com/arduino-libraries/ArduinoBLE


*/

#ifndef BLE_H
#define BLE_H

#include <ArduinoBLE.h>
#include "s1_mic.h"
#include "s2_imu.h"
#include "s3_cap.h"
#include "s4_air.h"

class BLE_Class {

  public:

  BLE_Class();

  void BLE_initialization();
  void BLE_loop();
  void WriteInteract();
  void ByteFunc(int value, byte BArray[2]);

  // Private members can only be accessed inside the BLE class
  private:
  // Sensor classes

  Mic_Class mic;
  IMU_Class imu;
  Cap_Class cap;
  Air_Class air;


  byte BArrayMic[2];
  byte BArrayIMU[2];
  byte BArrayAir[2];

  BLEService Plushie_service;

  BLECharacteristic mic_char;
  BLECharacteristic imu_char;
  BLEIntCharacteristic cap_char;
  BLECharacteristic air_char;

  byte value;

};

#endif