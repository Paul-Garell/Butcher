#include <Wire.h>
#include "AD5933.h"
#include <Adafruit_MCP4725.h>

// Constants
#define START_FREQ  (10000)
#define FREQ_INCR   (5000)
#define NUM_INCR    (18)
#define REF_RESIST  (300)
#define IMPEDANCE_THRESHOLD 100

// Mux setup
int Signal = 5;
int sL[3] = {8, 9, 10};
int MUXtable[8][3] = {
  {0, 0, 0}, {1, 0, 0}, {0, 1, 0}, {1, 1, 0},
  {0, 0, 1}, {1, 0, 1}, {0, 1, 1}, {1, 1, 1}
};

// DAC setup for Pressure regulator
Adafruit_MCP4725 dac;
double Curvoltage = 0.5;

// Pressure variables for barometric sensor
const int pressureInput = A1;
const int pressureZ = 102;
const int pressureM = 921;
float pressure;
int normalP = 0;

void setup(void) {
  // Mux setup
  pinMode(Signal, OUTPUT);
  for (int i = 0; i < 3; i++) {
    pinMode(sL[i], OUTPUT);
  }

  // DAC setup (pressure regulator)
  pinMode(A2, OUTPUT);
  digitalWrite(A2, LOW);
  dac.begin(0x60);

  // Begin serial at 9600 baud for output
  Serial.begin(9600);

  // Begin I2C
  Wire.begin();

  Serial.println("AD5933 Test Started!");

  // Perform initial configuration
  if (!(AD5933::reset() &&
        AD5933::setInternalClock(true) &&
        AD5933::setStartFrequency(START_FREQ) &&
        AD5933::setIncrementFrequency(FREQ_INCR) &&
        AD5933::setNumberIncrements(NUM_INCR) &&
        AD5933::setPGAGain(PGA_GAIN_X1)))
  {
    Serial.println("FAILED in initialization!");
    while (true) ;
  }

  // Set mux to the calibration output (select Y0)
  digitalWrite(sL[0], MUXtable[0][0]);
  digitalWrite(sL[1], MUXtable[0][1]);
  digitalWrite(sL[2], MUXtable[0][2]);

  // Perform calibration sweep
  if (AD5933::calibrate(gain, phase, REF_RESIST, NUM_INCR + 1))
    Serial.println("Calibrated!");
  else
    Serial.println("Calibration failed...");
}

void loop(void) {
  dac.setVoltage((Curvoltage * 4095) / 5, false);

  for (int i = 0; i < 4; i++) {
    selection(i);
  }

  Curvoltage += 0.5;
  if (Curvoltage > 2.9) {
    Curvoltage = 0.5;
  }
}

void frequencySweepEasy(int pin) {
  int real[NUM_INCR + 1], imag[NUM_INCR + 1];
  bool impedanceReachedThreshold = false;

  if (AD5933::frequencySweep(real, imag, NUM_INCR + 1)) {
    int cfreq = START_FREQ / 1000;

    Serial.print(pin);
    Serial.print(", ");
    Serial.print(normalP, 1);

    for (int i = 0; i < NUM_INCR + 1; i++, cfreq += FREQ_INCR / 1000) {
      double magnitude = sqrt(pow(real[i], 2) + pow(imag[i], 2));
      double impedance = 1 / (magnitude * gain[i]);

      if (impedance < IMPEDANCE_THRESHOLD) {
        impedanceReachedThreshold = true;
        continue;
      }

      if (impedanceReachedThreshold) {
        Serial.print(", ");
        continue;
      }

      Serial.print(", ");
      Serial.print(impedance);
    }
    Serial.println(" ");
  } else {
    // Frequency sweep failed
  }
}

void selection(int pin) {
  for (int i = 0; i < 8; i++) {
    digitalWrite(Signal, LOW);
    digitalWrite(sL[0], MUXtable[i][0]);
    digitalWrite(sL[1], MUXtable[i][1]);
    digitalWrite(sL[2], MUXtable[i][2]);
    delay(1000);

    pressure = analogRead(pressureInput);
    normalP = map(pressure, pressureZ, pressureM, 0, 100);
    frequencySweepEasy(pin);
  }
}
