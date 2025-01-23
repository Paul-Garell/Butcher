#include <Wire.h>
#include <Adafruit_ADS1X15.h>
#include <Adafruit_MCP4725.h>
#include "AD5933.h"
#include <SD.h>

Adafruit_MCP4725 dac;
Adafruit_ADS1015 ads1015;

#define DAC_RESOLUTION (9)

// AD5933 Constants

#define START_FREQ (5000)
#define FREQ_INCR (1000)
#define NUM_INCR (3)
#define REF_RESIST (300)

// Pressure Constants

#define PRES_START (-1)
#define PRES_INCR (-0.5)
#define PRES_NUM_INCR (30)

float pressure;
const float error = 0.1;

// Impedance Constants

double gain[NUM_INCR + 1];
int phase[NUM_INCR + 1];

int i;

// Mux Constants
int sL[3] = { 8, 9, 10 };
// First value corresponds to 300 ohm resistor
// int MUXtable[8][3] = { { 1, 0, 1 }, { 0, 1, 1 }, { 0, 0, 0 }, { 0, 0, 1 }, { 0, 1, 0 }, { 1, 0, 0 }, { 1, 1, 0 }, { 1, 1, 1 } }; // green board (old pad arrangement)
int MUXtable[8][3] = { { 1, 0, 1 }, { 1, 1, 1 }, { 0, 1, 1 }, { 0, 0, 1 }, { 0, 1, 0 }, { 1, 0, 0 }, { 0, 0, 0 }, { 1, 1, 0 } }; // new pad arrangement
// int MUXtable[8][3] = { { 1, 0, 1 }, { 1, 1, 0 }, { 0, 0, 0 }, { 1, 0, 0 }, { 0, 1, 0 }, { 0, 0, 1 }, { 0, 1, 1 }, { 1, 1, 1 } }; // Flipped new pad arrangement, if pads are flipped

//Stress Stain Test Global Variables
int curPad = 1;
float stressStrain[7] = {0,0,0,0,0,0,0};

// Board Constants
const int yellowLED = 5;
const int greenLED = 6;
const int startbuttonPin = 7;
int startbuttonState = 0;

// Pressure Control Constants
// y = mx where y is digital value to supply DAC and x is desired pressure (-kPa)
// slope and yint are calibrated before hand, determined with linear regression
const float slope = -87.87;
const float yint = 55.45;

// SD Card
File dataFile;
String filename = "Data.csv";
const int chipSelectPin = 4;

void setup(void) {
  Serial.begin(9600);
  Wire.begin();

  // LEDs
  startbuttonState = digitalRead(startbuttonPin);
  pinMode(greenLED, OUTPUT);
  pinMode(yellowLED, OUTPUT);

  // Pull pin A2 to ground
  pinMode(A2, OUTPUT);
  digitalWrite(A2, LOW);

  // Initialize SD Card
  if (SD.begin(chipSelectPin)) {
    Serial.println("SD card module is connected.");
  } else {
    Serial.println("SD card module is not detected. Check connections.");
  }

  // Open a new file for writing
  dataFile = SD.open(filename, FILE_WRITE);
  // SD.remove(filename); // Uncomment to wipe SD card reader files
  if (dataFile) {
    Serial.println("Created data.csv file.");
  } else {
    Serial.println("Failed to create data.csv file!");
  }

  dataFile.println(" ");
  dataFile.print("Freq (kHz): ");
  dataFile.print(", ");
  int cfreq = START_FREQ / 1000;
  for (int i = 0; i < NUM_INCR + 1; i++, cfreq += FREQ_INCR / 1000) {
    dataFile.print(cfreq);
    dataFile.print(", ");
  }

  dataFile.print(", ");
  dataFile.print("Pressure: ");
  dataFile.print(", ");
  dataFile.print("Duration: ");
  dataFile.close();

  // Initialize MUX
  for (i = 0; i < 3; i++) {
    pinMode(sL[i], OUTPUT);
  }

  Serial.print("Initializing... ");
  // Perform initial configuration. Fail if any one of these fail.
  if (!(AD5933::reset() && AD5933::setInternalClock(true) && AD5933::setStartFrequency(START_FREQ) && AD5933::setIncrementFrequency(FREQ_INCR) && AD5933::setNumberIncrements(NUM_INCR) && AD5933::setPGAGain(PGA_GAIN_X1) )) {
    Serial.println("FAILED in initialization!");
    while (true);
  }

  Serial.println("Initialized!");

  // Select 300 OHM resistor to Calibrate AD5933
  selectPad(0);

  Serial.print("Calibrating... ");
  // Perform calibration sweep
  if (!AD5933::calibrate(gain, phase, REF_RESIST, NUM_INCR + 1)) {
    Serial.println("Calibration failed...");
    while (true);
  }
  Serial.println("Calibrated!");

  // Initialize ADC
  // ADC range is +/- 6.144 V (1 bit = 3 mV)
  ads1015.begin(0x48);

  // Initialize DAC
  dac.begin(0x60);
}

void loop(void) {
  // Set pressure to 0 before test begins
  dac.setVoltage(0, false);
  digitalWrite(greenLED, LOW);
  digitalWrite(yellowLED, HIGH);
  startbuttonState = digitalRead(startbuttonPin);
  // Press button to start test
  if (startbuttonState == HIGH) {
    Serial.println("Stress Strain Determination Start!");
    pressureSweep();
    Serial.println("Done!");
    // Output data after sweep
    for (int i = 1; i < 8; i++) {
      Serial.print("Pad: ");
      Serial.print(i);
      Serial.print(" ");
      Serial.println(stressStrain[i-1]);
    } 
  }
}

void pressureSweep() {
  /*
    Paramters: Steps
    Returns: 
  */
  curPad = 1;
  pressure = PRES_START;
  for (int i = 0; i < PRES_NUM_INCR + 1; i++, pressure += PRES_INCR) {
    digitalWrite(greenLED, LOW);
    digitalWrite(yellowLED, HIGH);
    selectPressure(pressure);
    while (abs(getAveragePressure(6)-pressure) > error ){
      Serial.println("Getting Pressure");
      Serial.println(getPressure());
    }
    digitalWrite(greenLED, HIGH);
    digitalWrite(yellowLED, LOW);
    dataFile = SD.open(filename, FILE_WRITE);
    runTest(curPad);
    dataFile.close();
  }
}

void runSweep() {
  /*
    Paramters: None
    Returns: Runs a sweep on all 7 pads from the top most pad closest to tissue to the bottom
  */
  dataFile.println(" ");
  for (int i = 1; i < (sizeof(MUXtable) / sizeof(MUXtable[0])); i++) {
    dataFile.println(" ");
    dataFile.print("Pad ");
    dataFile.print(i);
    selectPad(i);

    int time1 = millis();
    frequencySweepEasy();
    int time2 = millis();

    dataFile.print(", ");
    dataFile.print(", ");
    dataFile.print(getPressure());
    dataFile.print(", ");
    dataFile.print(time2 - time1);
    Serial.print("Test time (ms): ");
    Serial.println(time2 - time1);
    Serial.print("Pressure (kPa): ");
    Serial.println(getPressure());
  }
}

void runTest(int padnum) {
  /*
    Paramters: Takes in pad number, runs a frequency sweep only on this pad
    Returns: None
  */
  dataFile.println(" ");
  dataFile.print("Pad ");
  dataFile.print(padnum);
  Serial.print("Pad ");
  Serial.print(padnum);
  Serial.println(" being tested");
  selectPad(padnum);

  int time1 = millis();
  frequencySweepEasy();
  int time2 = millis();

  dataFile.print(", ");
  dataFile.print(", ");
  dataFile.print(getPressure());
  dataFile.print(", ");
  dataFile.print(time2 - time1);
  Serial.print("Test time (ms): ");
  Serial.println(time2 - time1);
  Serial.print("Pressure (kPa): ");
  Serial.println(getPressure());
}

// Frequency Sweep
void frequencySweepEasy() {
  /*
    Paramters: None
    Returns: None, runs a frequency sweep with the AD5933 chip. Prints to serial monitor and SD card
    - Also checks if pad has been contacted yet based on first impedance value
  */
  // Create arrays to hold the data
  int real[NUM_INCR + 1], imag[NUM_INCR + 1];

  // Perform the frequency sweep
  if (AD5933::frequencySweep(real, imag, NUM_INCR + 1)) {
    // Print the frequency data
    int cfreq = START_FREQ / 1000;
    for (int i = 0; i < NUM_INCR + 1; i++, cfreq += FREQ_INCR / 1000) {
      // Print raw frequency data
      Serial.print(cfreq);
      Serial.print(": Impedance = ");
      // Serial.print(real[i]);
      // Serial.print("/I=");
      // Serial.print(imag[i]);

      // Compute impedance
      double magnitude = sqrt(pow(real[i], 2) + pow(imag[i], 2));
      double impedance = 1 / (magnitude * gain[i]);
      // Serial.print("  |Z|=");
      dataFile.print(", ");
      Serial.println(impedance);
      dataFile.print(impedance);
    }
    Serial.println("Frequency sweep complete!");
  } else {
    Serial.println("Frequency sweep failed...");
  }
  // Post Processing -> Test first value in array (lowest frequency)
  double magnitude = sqrt(pow(real[0], 2) + pow(imag[0], 2));
  double impedance = 1 / (magnitude * gain[0]);
  if ((impedance < 1000) && (curPad < 8)){
    stressStrain[curPad-1] = getPressure();
    Serial.print("Pad ");
    Serial.print(curPad);
    Serial.println(" has been contacted!");
    curPad++;
  }
}

// Mux Control Function
void selectPad(int p) {
  // Pad 0 is calibration resistor, Pad 1-7 are on flex pcb
  digitalWrite(sL[0], MUXtable[p][0]);
  digitalWrite(sL[1], MUXtable[p][1]);
  digitalWrite(sL[2], MUXtable[p][2]);
}

// Pressure Control Functions
float getPressure(void) {
  /*
    Paramters: None
    Returns: takes in voltage reading from sensor from the ADS1015 pressure sensor and returns kPa
    PRESSURE READING DEPENDS ON THE VOLTAGE SUPPLIED (I TESTED FOR LIKE 2 MONTHS WITHOUT REALIZING!!!)
    - Hence, second channel on the ADS1015 tracks the voltage supplied
  */

  // int16_t adc0; float vout; float pressure;
  // adc0 = ads1015.readADC_SingleEnded(0);         // output in bits, from A0
  // vout = ((adc0 * 3.0) / 1000);    // Convert bits to voltage, found on ADS1015 data sheet
  // pressure = (vout-(0.92*5))/(0.018*5);    // Convert voltage to pressure, found on MPXV5050VC6T1 data sheet
  // voltage supply changes when battery turns on! For 18V, 0.8A -> vs is 4.58 V, hence ADC also reads voltage going into pressure sensor

  return (((ads1015.readADC_SingleEnded(0) * 3.0) / 1000) - (0.92 * ((ads1015.readADC_SingleEnded(2) * 3.0) / 1000))) / (0.018 * ((ads1015.readADC_SingleEnded(2) * 3.0) / 1000));
}

float getAveragePressure(int steps) {
  /*
    Paramters: Steps, number of pressure values to average. Higher steps decreases chance of noise affecting system
    Returns: averaged pressure values, allows for smoothing of pressure values
  */
  float total = 0;
  for (int i = 0; i < steps; i++) {
    total += getPressure();
  }
  return total/steps;
}

void selectPressure(float p) {
  /*
    Paramters: pressure in kPa. If this number is positive, it will be assumed that it was negative (vacuum only makes negative pressure)
    Returns: None. Sets pressure on the pressure transducer based on the supplied voltage. Conversion from bits to kPa is done beforehand
  */
  if (p>0){
    p = p*-1;
  }
  dac.setVoltage(slope*p + yint, false);
}
