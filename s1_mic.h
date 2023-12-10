/*
Last modified 07-11-23
Danique Damen (d.damen-1@studen.utwente.nl)

Library FFT: https://github.com/kosme/arduinoFFT

*/

// include libraries
#include <Arduino.h>
#include <mic.h>
#include "arduinoFFT.h"

#ifndef S1_MIC_H
#define S1_MIC_H

class Mic_Class{
  public:

  Mic_Class();

  void mic_initialization();
  int mic_interaction();
  int mic_peak();

  int mic_amplitude();
  static void audio_rec_callback(uint16_t *buf, uint32_t buf_len);

  private:
  arduinoFFT FFT;

  int peak;

  
};

#endif