#include <Wire.h>
#include "AD5933.h"
#include <Adafruit_MCP4725.h>

#define START_FREQ  (10000)
#define FREQ_INCR   (5000)
#define NUM_INCR    (18)
#define REF_RESIST  (300)

// Threshold setup
int impedenceCheck; // Define a high resistance here

// Mux setup
int Signal = 5;
int i;
int sL[3] = {8, 9, 10};
int MUXtable[8][3] = {
  {0, 0, 0}, {1, 0, 0}, {0, 1, 0}, {1, 1, 0},
  {0, 0, 1}, {1, 0, 1}, {0, 1, 1}, {1, 1, 1}
};

// DAC setup for Pressure regulator
int DACp = 0;
double Curvoltage = 0.5;

Adafruit_MCP4725 dac;
#define DAC_RESOLUTION (9)

double gain[NUM_INCR + 1];
int phase[NUM_INCR + 1];

// Pressure variable for barometric sensor
const int pressureInput = A1;
const int pressureZ = 102;
const int pressureM = 921;
const int pressurePSI = 15;
float pressure;
int normalP = 0;

void setup(void) {
  pinMode(Signal, OUTPUT);
  for (i = 0; i < 4; i++) pinMode(sL[i], OUTPUT);

  pinMode(A2, OUTPUT);
  digitalWrite(A2, LOW);
  dac.begin(0x60);
  Serial.begin(9600);
  Wire.begin();
  Serial.println("AD5933 Test Started!");

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

  digitalWrite(sL[0], MUXtable[0][0]);
  digitalWrite(sL[1], MUXtable[0][1]);
  digitalWrite(sL[2], MUXtable[0][2]);

  if (AD5933::calibrate(gain, phase, REF_RESIST, NUM_INCR + 1)) {
    findImpedanceNoPressure(); // Call the function to determine the high resistance value
    Serial.println("Calibrated!");
  } else {
    Serial.println("Calibration failed...");
  }
}

int curChannel = 1;
void loop(void) {
  dac.setVoltage((Curvoltage * 4095) / 5, false);
  for (curChannel = 1; curChannel <= 8; curChannel++) {
    Serial.print(curChannel);
    selection(curChannel);
    if (frequencySweepEasy(curChannel)) break;
  }

  Curvoltage += 0.5; // Increment voltage counter
  if (Curvoltage > 2.9) {
    Curvoltage = 0.5;
  }
}

bool frequencySweepEasy(int pin) {
  // Create arrays to hold the data
  int real[NUM_INCR + 1], imag[NUM_INCR + 1];

  // Perform the frequency sweep
  if (AD5933::frequencySweep(real, imag, NUM_INCR + 1)) {
    // Print the frequency data
    int cfreq = START_FREQ / 1000;
    // Calculating and printing out the pressure information
    pressure = analogRead(pressureInput); // will read the value from the input pin
    pressure = (pressure - pressureZ) * 15 / (pressureM - pressureZ); // convert analog reading to psi
    normalP = abs((pressure * 6.89476) - 98); // normalize?
    
    Serial.print(millis());
    Serial.print(", ");
    Serial.print(pin);
    Serial.print(", ");
    Serial.print(normalP, 1); // converting to kPa while also printing (units kPa)

    for (int i = 0; i < NUM_INCR + 1; i++, cfreq += FREQ_INCR / 1000) {

      // Compute impedance
      double magnitude = sqrt(pow(real[i], 2) + pow(imag[i], 2));
      double impedance = 1 / (magnitude * gain[i]);
      Serial.print(", ");
      Serial.print(impedance);
      
      // Checker
      if (impedance > impedenceCheck) {
        Serial.println(" ");
        return true;
      }
    }
    Serial.println(" ");
  }
  return false;
}

void findImpedanceNoPressure() {
  selection(8);
  int real, imag;
  int cfreq = START_FREQ / 1000; // Starting frequency
  
  if (AD5933::frequencySweep(real, imag, 1)) {
    double magnitude = sqrt(pow(real, 2) + pow(imag, 2));
    double impedance = 1 / (magnitude * gain[0]);

    impedenceCheck = (int)impedance; // Set the high resistance value
  } else {
    impedenceCheck = 0; // Set default value to 0 if measurement fails
  }
}


void selection(int j) {
  digitalWrite(sL[0], MUXtable[j][0]);
  digitalWrite(sL[1], MUXtable[j][1]);
  digitalWrite(sL[2], MUXtable[j][2]);
}
