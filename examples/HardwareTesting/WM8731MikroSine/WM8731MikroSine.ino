// Simple sine wave & input level test for WM8731 Audio Codec Board
//
// Requires the MikroElektronika Audio Codec board or similar hardware
//   http://www.mikroe.com/add-on-boards/audio-voice/audio-codec-proto/
//
// Recommended connections:
//
//    Mikroe   Teensy 3.1
//    ------   ----------
//     SCK         9
//     MISO       13
//     MOSI       22
//     ADCL       23  (yes, ADCL & DACL connect together)
//     DACL       23
//     SDA        18
//     SCL        19
//     3.3V      +3.3V
//     GND        GND
//
// This example code is in the public domain.

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioSynthWaveform       waveform1;      //xy=245,160
AudioInputI2Sslave       i2sslave1;      //xy=265,252
AudioOutputI2Sslave      i2sslave2;      //xy=429,158
AudioAnalyzeRMS          rms2;           //xy=436,323
AudioAnalyzeRMS          rms1;           //xy=444,265
AudioConnection          patchCord1(waveform1, 0, i2sslave2, 0);
AudioConnection          patchCord2(waveform1, 0, i2sslave2, 1);
AudioConnection          patchCord3(i2sslave1, 0, rms1, 0);
AudioConnection          patchCord4(i2sslave1, 1, rms2, 0);
AudioControlWM8731master wm8731m1;       //xy=292,379
// GUItool: end automatically generated code


void setup() {
  wm8731m1.enable();

  AudioMemory(15);

  waveform1.begin(WAVEFORM_SINE);
  waveform1.frequency(440);
  waveform1.amplitude(0.9);

  wm8731m1.volume(0.50);
  wm8731m1.inputSelect(AUDIO_INPUT_MIC);
  // wm8731m1.inputSelect(AUDIO_INPUT_LINEIN); // not connected on MikroE-516
}

elapsedMillis msec;

// Print a simple level meter
void loop() {
  if (msec > 40) {
    if (rms1.available() && rms2.available()) {
      msec = 0;
      int level_left = rms1.read() * 30.0;
      int level_right = rms2.read() * 30.0;
      printchar(' ', 30 - level_left);
      printchar('<', level_left);
      Serial.print("||");
      printchar('>', level_right);
      Serial.println();
    }
  }
}

void printchar(char c, int num) {
  for (int i=0; i < num; i++) {
    Serial.write(c);
  }
}

