/*
Last modified 07-11-23
Danique Damen (d.damen-1@studen.utwente.nl)

Summary file:
Using the FFT library of arduino, frequency spectral analysis of the microphone data is done. The peak frequency is obtained and eventually written to the characteristic.

*/

#include "s1_mic.h"

#define DEBUG 1                 // Enable pin pulse during ISR  
#define SAMPLES 1024

const uint16_t samples = 1024; // MUST BE POWER OF 2
const double signalFrequency = 1000;
const double samplingFrequency = 5000;
const uint8_t amplitude = 100;

double vReal[samples];
double vImag[samples];
 
mic_config_t mic_config{
  .channel_cnt = 1,
  .sampling_rate = 16000,
  .buf_size = 1600,
  .debug_pin = LED_BUILTIN                // Toggles each DAC ISR (if DEBUG is set to 1)
};

NRF52840_ADC_Class Mic(&mic_config);

int16_t recording_buf[SAMPLES];
volatile uint8_t recording = 0;
volatile static bool record_ready = false;


// Constructor
Mic_Class::Mic_Class(){

}

void Mic_Class::mic_initialization() {
 
  Mic.set_callback(audio_rec_callback);
 
  if (!Mic.begin()) {
    Serial.println("Mic initialization failed");
    while (1);
  }

  Serial.println("Mic initialization done.");
 
}

int Mic_Class::mic_peak(){
  if (record_ready)  
  {

  for (int i = 0; i < SAMPLES; i++) {
    vReal[i] = recording_buf[i];
    vImag[i] = 0; // Set to 0 since only magnitude applications will be used, simplification.
  }
  // weigh data
  FFT.Windowing(vReal, SAMPLES, FFT_WIN_TYP_HAMMING, FFT_FORWARD);

  // compute FFT
  FFT.Compute(vReal, vImag, SAMPLES, FFT_FORWARD);

  // compute magnitude
  FFT.ComplexToMagnitude(vReal, vImag, SAMPLES);  

  // Frequency with highest magnitude is obtained
  peak = FFT.MajorPeak(vReal, SAMPLES, samplingFrequency);
  peak = int(peak)

  record_ready = false; 
}

  return peak;
}
 
void Mic_Class::audio_rec_callback(uint16_t *buf, uint32_t buf_len) {
  
  static uint32_t idx = 0;
  // Copy samples from DMA buffer to inference buffer
  for (uint32_t i = 0; i < buf_len; i++) {
  
  // Convert 12-bit unsigned ADC value to 16-bit PCM (signed) audio value
  recording_buf[idx++] = buf[i];
 
      if (idx >= SAMPLES){ 
      idx = 0;
      recording = 0;
      record_ready = true;
      break;
     } 
    }
}

// print Amplitude of sound if 
int Mic_Class::mic_amplitude(){
    for (int i = 0; i < SAMPLES/2; i++) {
    Serial.println(vReal[i], 1);
  }
}

int Mic_Class::mic_interaction(){
  /*
  child voice 250-400 Hz
  child cry = 300-600hz
  */
  int micpeak = int(mic_peak());
  return micpeak;

}