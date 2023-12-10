
/*
Last modified 08-11-23
Danique Damen (d.damen-1@studen.utwente.nl)

Summary file:
Test if Plushie is squeezed with air pressure sensor. Library HX711 is used for pressure sensor HX710B for the Xiao seeed NRF52480.

*/

#include "s4_air.h"


Air_Class::Air_Class(){

}

void Air_Class::air_initialization() {
    scale.begin(A1, SCK);
    scale.set_scale(2280);
    scale.tare();
}

// average of 5 readings
int Air_Class::air_loop() {

  airp = int(scale.get_units(5)/10000);

  return airp;
}

