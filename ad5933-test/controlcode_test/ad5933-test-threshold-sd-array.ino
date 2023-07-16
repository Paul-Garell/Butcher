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

int Signal = 5;
int i;
int sL[3] = {8, 9, 10};
int MUXtable[8][3] = {
  {0, 0, 0}, {1, 0, 0}, {0, 1, 0}, {1, 1, 0},
  {0, 0, 1}, {1, 0, 1}, {0, 1, 1}, {1, 1, 1}
};

int curChannel = 1;
Adafruit_MCP4725 dac;
double gain[NUM_INCR + 1];
int phase[NUM_INCR + 1];

const int pressureInput = A1;
const int pressureZ = 102;
const int pressureM = 921;
const int pressurePSI = 15;
float pressure;
int normalP = 0;

struct DataPoint {
  int pin;
  float pressure;
  unsigned long time;
  double impedance;
};

const int MAX_DATA_POINTS = 1000;
DataPoint dataPoints[MAX_DATA_POINTS];
int dataCount = 0;

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
        AD5933::setPGAGain(PGA_GAIN_X1))) {
    Serial.println("FAILED in initialization!");
    while (true);
  }

  digitalWrite(sL[0], MUXtable[0][0]);
  digitalWrite(sL[1], MUXtable[0][1]);
  digitalWrite(sL[2], MUXtable[0][2]);

  if (AD5933::calibrate(gain, phase, REF_RESIST, NUM_INCR + 1))
    Serial.println("Calibrated!");
  else
    Serial.println("Calibration failed...");

  if (SD.begin(4)) {
    Serial.println("SD card module is connected.");
  } else {
    Serial.println("SD card module is not detected. Check connections.");
  }

  dataCount = 0;
}

void loop(void) {
  dac.setVoltage((Curvoltage * 4095) / 5, false);
  for (curChannel - 1; curChannel <= 8; curChannel++) {
    selection(curChannel);
    if (frequencySweepEasy(curChannel)) break;
  }
  Curvoltage += .5;
  if (Curvoltage > 2.9) {
    Curvoltage = 0.5;
  }
}

bool frequencySweepEasy(int pin) {
  int real[NUM_INCR + 1], imag[NUM_INCR + 1];

  if (AD5933::frequencySweep(real, imag, NUM_INCR + 1)) {
    int cfreq = START_FREQ / 1000;

    for (int i = 0; i < NUM_INCR + 1; i++, cfreq += FREQ_INCR / 1000) {
      pressure = analogRead(pressureInput);
      pressure = (pressure - pressureZ) * 15 / (pressureM - pressureZ);
      normalP = abs((pressure * 6.89476) - 98);

      double magnitude = sqrt(pow(real[i], 2) + pow(imag[i], 2));
      double impedance = 1 / (magnitude * gain[i]);

      dataPoints[dataCount].pin = pin;
      dataPoints[dataCount].pressure = normalP;
      dataPoints[dataCount].time = millis();
      dataPoints[dataCount].impedance = impedance;
      dataCount++;

      if (dataCount >= MAX_DATA_POINTS) {
        exportData();
        dataCount = 0;
        return true; // Indicate that data has been exported
      }
    }
  }
  return false; // Indicate that data has not been exported yet
}

void selection(int j) {
  digitalWrite(sL[0], MUXtable[j][0]);
  digitalWrite(sL[1], MUXtable[j][1]);
  digitalWrite(sL[2], MUXtable[j][2]);
}

void exportData() {
  dataFile = SD.open("data.csv", FILE_WRITE);
  if (dataFile) {
    for (int i = 0; i < dataCount; i++) {
      dataFile.print(dataPoints[i].time);
      dataFile.print(", ");
      dataFile.print(dataPoints[i].pin);
      dataFile.print(", ");
      dataFile.print(dataPoints[i].pressure, 1);
      dataFile.print(", ");
      dataFile.print(dataPoints[i].impedance);
      dataFile.println();
    }
    dataFile.close();
  }
}
