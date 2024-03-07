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
void setup(void)
{
  pinMode(Signal, OUTPUT);
  for (i = 0; i < 3; i++) pinMode(sL[i], OUTPUT);
  pinMode(A2, OUTPUT);
  digitalWrite(A2, LOW);
  dac.begin(0x60);
  
  // Begin serial at 9600 baud for output
  Serial.begin(9600);
  // Begin I2C
  Wire.begin();
  // Select SD card pin
  const int chipSelectPin = 4;
  // Perform initial configuration. Fail if any one of these fail.
  Serial.println("AD5933 Test Started!");

  if (!(AD5933::reset() &&
        AD5933::setInternalClock(true) &&
        AD5933::setStartFrequency(START_FREQ) &&
        AD5933::setIncrementFrequency(FREQ_INCR) &&
        AD5933::setNumberIncrements(NUM_INCR) &&
        AD5933::setPGAGain(PGA_GAIN_X1)))
  {
    Serial.println("FAILED in initialization!");
    while (true);
  }
  // Set mux to the calibration output (select Y0) (300 ohm resistor installed on board)
  digitalWrite(sL[0], MUXtable[0][0]);
  digitalWrite(sL[1], MUXtable[0][1]);
  digitalWrite(sL[2], MUXtable[0][2]);
  
  // Perform calibration sweep
  if (AD5933::calibrate(gain, phase, REF_RESIST, NUM_INCR + 1))
    Serial.println("Calibrated!");
  else
    Serial.println("Calibration failed...");

  // Initialize the SD card
  if (SD.begin(chipSelectPin)) {
    Serial.println("SD card module is connected.");
  } else {
    Serial.println("SD card module is not detected. Check connections.");
  }

  // Open a new file for writing
  dataFile = SD.open(filename, FILE_WRITE);
  if (dataFile) {
    Serial.println("Created data.csv file.");
  } else {
    Serial.println("Failed to create data.csv file!");
  }
  
  // Write the column headers to the file
  dataFile.println("Pin, Pressure, Time, Impedance");
  
  // Close the file
  dataFile.close();
}

void loop(void) {
  dac.setVoltage((Curvoltage * 4095) / 5, false);
  for (i = 0; i < 8; i++) {
    selection(i);
  }
  Curvoltage += .5;
  if (Curvoltage > 2.9) {
    Curvoltage = 0.5;
  }
}

void frequencySweepEasy(int pin) {
  // Create arrays to hold the data
  int real[NUM_INCR + 1], imag[NUM_INCR + 1];

  // Perform the frequency sweep
  if (AD5933::frequencySweep(real, imag, NUM_INCR + 1)) {
    // Open the data file in append mode
    dataFile = SD.open("data.csv", FILE_WRITE);
    if (dataFile) {
      // Calculating and printing out the pressure information
      int cfreq = START_FREQ / 1000;
      dataFile.print(pin);
      dataFile.print(", ");
      dataFile.print(normalP, 1);
      for (int i = 0; i < NUM_INCR + 1; i++, cfreq += FREQ_INCR / 1000) {
        pressure = analogRead(pressureInput);
        pressure = (pressure - pressureZ) * 15 / (pressureM - pressureZ);
        normalP = abs((pressure * 6.89476) - 98);
        dataFile.print(", ");

        // Time elapsed
        dataFile.print(millis());
        dataFile.print(", ");
        
        // Compute impedance
        double magnitude = sqrt(pow(real[i], 2) + pow(imag[i], 2));
        double impedance = 1 / (magnitude * gain[i]);
        dataFile.print(impedance);
      }
      dataFile.println(" ");
      
      // Close the file
      Serial.flush();
      dataFile.close();
    }
  }
}

void selection(int j) {
  digitalWrite(sL[0], MUXtable[j][0]);
  digitalWrite(sL[1], MUXtable[j][1]);
  digitalWrite(sL[2], MUXtable[j][2]);
  frequencySweepEasy(j);
}
