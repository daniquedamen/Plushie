/*
Last modified 06-12-23
Danique Damen (d.damen-1@studen.utwente.nl)

Summary sketch:
This sketch is used for the Xiao Seeed NRF52840 microcontroller. The MC serves the Plushie that is used in the HELPER project https://www.ram.eemcs.utwente.nl/research/projects/helper
For more information, please contact me.


*/

#include "BLE.h"

BLE_Class ble;

void setup() {
  ble.BLE_initialisation();
}

unsigned long looptime;

void loop() {
  if(millis()>looptime + 500){
    looptime = millis();
    ble.BLE_loop();
  }

}

