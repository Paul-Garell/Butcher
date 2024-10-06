# include <Wire.h>
# include <Adafruit_ADS1X15.h>
# include <Adafruit_MCP4725.h>
#include "AD5933.h"

Adafruit_MCP4725 dac;
Adafruit_ADS1015 ads1015;

# define DAC_RESOLUTION (9)

// AD5933 Constants

#define START_FREQ (5000)
#define FREQ_INCR (1000)
#define NUM_INCR (9)
#define REF_RESIST (300)

double gain[NUM_INCR + 1];
int phase[NUM_INCR + 1];

int i;
int sL[3] = { 8, 9, 10 };
int MUXtable[8][3] = { { 1, 0, 1 }, { 0, 1, 1 }, { 0, 0, 0 }, { 0, 0, 1 }, { 0, 1, 0 }, { 1, 0, 0 }, { 1, 1, 0 }, { 1, 1, 1 } };

// Board Constants

const int yellowLED = 5;
const int greenLED = 6;
const int startbuttonPin = 7;
int startbuttonState = 0;

// PID Control Constants

int mytime1;
int mytime2;

double dt;
double integral, derivative = 0;
double previous, out, lasttime = 0;
double kp, ki, kd;

bool was_holding = false;
double cur = 0;

void setup(void)
{
  Serial.begin(9600);
  Wire.begin();

  // LEDs
  startbuttonState = digitalRead(startbuttonPin);
  pinMode(greenLED, OUTPUT);
  pinMode(yellowLED, OUTPUT);
  
  // Pull pin A2 to ground
  pinMode(A2, OUTPUT);
  digitalWrite(A2, LOW);

  // Initialize Probe Board

  // Initialize MUX
  for (i = 0; i < 3; i++) {
    pinMode(sL[i], OUTPUT);
  }


  // Perform initial configuration. Fail if any one of these fail.
  if (!(AD5933::reset() && AD5933::setInternalClock(true) && AD5933::setStartFrequency(START_FREQ) && AD5933::setIncrementFrequency(FREQ_INCR) && AD5933::setNumberIncrements(NUM_INCR) && AD5933::setPGAGain(PGA_GAIN_X1))) {
    Serial.println("FAILED in initialization!");
    while (true)
      ;
  }

  Serial.println("Initialized!");

  // Select 300 OHM resistor
  digitalWrite(sL[0], MUXtable[0][0]);
  digitalWrite(sL[1], MUXtable[0][1]);
  digitalWrite(sL[2], MUXtable[0][2]);

  // Perform calibration sweep
  if (!AD5933::calibrate(gain, phase, REF_RESIST, NUM_INCR + 1)) {
    Serial.println("Calibration failed...");
    while (true)
      ;
  }
  Serial.println("Calibrated!");

  // Initialize ADC 
  // ADC range is +/- 6.144 V (1 bit = 3 mV)
  ads1015.begin(0x48);

  // Initialize DAC
  dac.begin(0x60);

  // Recalibrate DAC, use x instead of 4095 for exact voltage values
  // Start with no vacuum pressure, use PID control to find initial value
  //dac.setVoltage((5*4095)/5, false);
  
  kp = 0.5;
  ki = 0.2;
  kd = 0.05;
  
  out = 1;
}

void loop(void)
{
  double now = millis();
  dt = (now - lasttime)/1000.0;
  lasttime = now;

  controlPressure(false);

  // Lights for Ready to Test
  digitalWrite(greenLED, LOW);
  digitalWrite(yellowLED, HIGH);
  startbuttonState = digitalRead(startbuttonPin);
  if (startbuttonState == HIGH) {
    // Lights for Testing
    digitalWrite(yellowLED, LOW);
    digitalWrite(greenLED, HIGH);
    Serial.println(getPressure());
    frequencySweepEasy();
    Serial.println(getPressure());
  }

  
  Serial.print("L:");
  Serial.print(0);
  Serial.print(", ");

  Serial.print("H:");
  Serial.print(-10);
  Serial.print(", ");

  Serial.print("Holding Pressure:");
  Serial.print(cur);
  Serial.print(", ");
  
  Serial.print("Current Pressure:");
  Serial.println(getPressure());
  
}

// Easy way to do a frequency sweep. Does an entire frequency sweep at once and
// stores the data into arrays for processing afterwards. This is easy-to-use,
// but doesn't allow you to process data in real time.
void frequencySweepEasy() {
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
      Serial.println(impedance);
    }
    Serial.println("Frequency sweep complete!");
  } else {
    Serial.println("Frequency sweep failed...");
  }
}


void controlPressure(bool hold)
{
  /* 
  was_holding/cur logic: When the button is pressed, the first moment it is pressed contains the pressure
  value that should be held, similar to what would occur when a test is run.
  This value must be saved by the system, hence the logic system which tracks if the system has been holding.
  If the system hasn't been holding, then the button must have been recently pressed and the pressure value is saved.
  */
  if (hold){
    // Hold Pressure
    if (!was_holding) {
      cur = getPressure();
      was_holding = true;
    }
    PID(cur);
  }else{
    // Increase Pressure
    PID(getPressure()-1);
    was_holding = false;
  }
}

double PID(double setpoint)
{
  /*
    Controls the activity of the pressure transducer by setting the output voltage of the DAC

    Paramters: vin, voltage supplied to pressure transducer
    Returns: new voltage to be supplied to the vacuum regulator
  */
  double actual = getPressure();
  double error = setpoint-actual;
  // Calculate kp, ki values (Calibrate, fit to curve, place function here)

  integral += error * dt;
  derivative = (error-previous) / dt;
  previous = error;
  double output = -((kp*error) + (ki*integral) + (kd * derivative));
  
  if (output < 0) {output = 0;}
  if (output > 5) {output = 5;}
  if (actual > -1){
    integral = 0;
    derivative = 0;
    output = 1;
  }
  
  dac.setVoltage((output*4095)/5, false);
}

float getPressure(void)
{
  /*
    Returns pressure from the MPXV5050VC6T1 pressure sensor

    Paramters: None
    Returns: takes in voltage reading from sensor from the ADS1015 pressure sensor and returns kPa

    With testing from timing, function takes 2 milliseconds to run
  */

  // int16_t adc0; float vout; float pressure;
  // adc0 = ads1015.readADC_SingleEnded(0);         // output in bits, from A0
  // vout = ((adc0 * 3.0) / 1000);    // Convert bits to voltage, found on ADS1015 data sheet
  // pressure = (vout-(0.92*5))/(0.018*5);    // Convert voltage to pressure, found on MPXV5050VC6T1 data sheet

  return (((ads1015.readADC_SingleEnded(0) * 3.0) / 1000) - (0.92 * 5)) / (0.018 * 5);
}
