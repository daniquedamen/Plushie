/*

Library air pressure sensor : https://www.arduino.cc/reference/en/libraries/hx711/


*/

#ifndef S4_AIR_H
#define S4_AIR_H

#include <Arduino.h>
#include "HX711.h"


class Air_Class {
public:
    Air_Class();

    void air_initialization();
    int air_loop();
    
private:
    HX711 scale;
    int airp;

};

#endif