#include <Wire.h>
#include "AD5933.h"
#include <Adafruit_MCP4725.h>
#include <SD.h>
#include <SPI.h>

#define START_FREQ  (10000)
#define FREQ_INCR   (5000)
#define NUM_INCR    (18)
#define REF_RESIST  (300)
#define DAC_RESOLUTION (9)

bool setter = true;
int follow = 0;

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
double Curvoltage = .5;

Adafruit_MCP4725 dac;

double gain[NUM_INCR + 1];
int phase[NUM_INCR + 1];

// Pressure variable for barometric sensor
const int pressureInput = A1;  // where the pressure will be sensed
const int pressureZ = 102;    // the minimum voltage for 0 pressure
const int pressureM = 921;    // the maxium voltage for 15psi
const int pressurePSI = 15;  
float pressure;  // where we want to store the value from the incoming pressure transducer
int normalP = 0; // placeholder

File dataFile;

String filename = "data.csv";