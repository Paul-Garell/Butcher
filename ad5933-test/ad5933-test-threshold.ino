#include <Wire.h>
#include "AD5933.h"
#include <Adafruit_MCP4725.h>

#define START_FREQ  (10000)
#define FREQ_INCR   (5000)
#define NUM_INCR    (18)
#define REF_RESIST  (300)
#define THRESHOLD   (100)  // Impedance threshold value

int muxChannels[8][3] = {
  {0, 0, 0}, {1, 0, 0}, {0, 1, 0}, {1, 1, 0},
  {0, 0, 1}, {1, 0, 1}, {0, 1, 1}, {1, 1, 1}
};

int lastChannel = 0;  // Last channel that had a full frequency sweep

Adafruit_MCP4725 dac;
double curVoltage = 0.5;

void setup() {
  pinMode(Signal, OUTPUT);  // Set the Signal pin as an output
  for (int i = 0; i < 3; i++)
    pinMode(sL[i], OUTPUT);  // Set the sL pins as outputs

  pinMode(A2, OUTPUT);
  digitalWrite(A2, LOW);  // Set A2 pin as an output and set it low
  dac.begin(0x60);  // Initialize the MCP4725 DAC with address 0x60

  Serial.begin(9600);  // Initialize serial communication
  Wire.begin();  // Initialize I2C communication

  Serial.println("AD5933 Test Started!");

  if (!(AD5933::reset() &&
        AD5933::setInternalClock(true) &&
        AD5933::setStartFrequency(START_FREQ) &&
        AD5933::setIncrementFrequency(FREQ_INCR) &&
        AD5933::setNumberIncrements(NUM_INCR) &&
        AD5933::setPGAGain(PGA_GAIN_X1))) {
    Serial.println("FAILED in initialization!");
    while (true) ;  // If initialization fails, enter an infinite loop
  }

  digitalWrite(sL[0], muxChannels[0][0]);  // Set the sL pins according to the first channel
  digitalWrite(sL[1], muxChannels[0][1]);
  digitalWrite(sL[2], muxChannels[0][2]);

  if (AD5933::calibrate(gain, phase, REF_RESIST, NUM_INCR + 1))
    Serial.println("Calibrated!");  
  else
    Serial.println("Calibration failed...");  
}

void loop() {
  dac.setVoltage((curVoltage * 4095) / 5, false);  // Set the DAC voltage based on curVoltage
  
  for (int channel = lastChannel; channel < 9; channel++) {
    lastChannel = selection(channel);  // Call the selection() function for each channel
  }

  Curvoltage = Curvoltage + .5; // Increment the voltage counter
  if (curVoltage > 2.9) {
    curVoltage = 0.5;  // Reset the voltage counter if it exceeds 2.9
  }
}

void frequencySweepEasy(int channel) {
  int real[NUM_INCR + 1], imag[NUM_INCR + 1];
  
  if (AD5933::frequencySweep(real, imag, NUM_INCR + 1)) {
    int cfreq = START_FREQ / 1000;
    Serial.print(channel);
    Serial.print(", ");
    Serial.print(normalP, 1);

    for (int i = 0; i < NUM_INCR + 1; i++, cfreq += FREQ_INCR / 1000) {
      // Calculate and print out the pressure information
      pressure = analogRead(pressureInput);
      pressure = (pressure - pressureZ) * 15 / (pressureM - pressureZ);
      normalP = abs((pressure * 6.89476) - 98);

      Serial.print(", ");
      double magnitude = sqrt(pow(real[i], 2) + pow(imag[i], 2));
      double impedance = 1 / (magnitude * gain[i]);
      Serial.print(impedance);

      if (impedance > THRESHOLD) {
        lastChannel = channel;  // Update lastChannel if impedance exceeds the threshold
        Serial.print("Impedance reached Threshold at channel ");
        Serial.print(lastChannel);
        return lastChannel;  // Return the updated lastChannel value
      }
    }
    Serial.println(" ");
  }
}

void selection(int channel) {
  digitalWrite(sL[0], muxChannels[channel][0]);  // Set the sL pins based on the selected channel
  digitalWrite(sL[1], muxChannels[channel][1]);
  digitalWrite(sL[2], muxChannels[channel][2]);
  lastChannel = frequencySweepEasy(channel);  // Call the frequencySweepEasy() function with the selected channel
  return lastChannel;  // Return the updated lastChannel value
}
