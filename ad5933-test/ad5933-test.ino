

/*
  ad5933-test
    Reads impedance values from the AD5933 over I2C and prints them serially.
*/
// 200, 1.1, 5.1 20000
#include <Wire.h>
#include "AD5933.h"
#define START_FREQ  (10000)
#define FREQ_INCR   (5000)
#define NUM_INCR    (18)
#define REF_RESIST  (300)
bool setter = true;
int follow = 0;

//Mux setup
int Signal = 5; int i; //int n;
int sL[3] = {8, 9, 10}; //int sU[4] = {13,10,11,12};
int MUXtable[8][3] = {{0, 0, 0}, {1, 0, 0}, {0, 1, 0}, {1, 1, 0},
  {0, 0, 1}, {1, 0, 1}, {0, 1, 1}, {1, 1, 1}
};


//DAC setup for Pressure regulator
int DACp = 0;
double Curvoltage = .5;
#include <Adafruit_MCP4725.h>
Adafruit_MCP4725 dac;
#define DAC_RESOLUTION (9)



double gain[NUM_INCR + 1];
int phase[NUM_INCR + 1];

//Pressure variable for barometric sensor
const int pressureInput = A1;  // where the pressure will be sensed
const int pressureZ = 102;    // the minimum voltage for 0 pressure
const int pressureM = 921;    // the maxium voltage for 15psi
const int pressurePSI = 15;
float pressure;  // where we want to store the value from the incoming pressure transducer
int normalP = 0; //placeholder


void setup(void)
{

  //Mux setup
  pinMode(Signal, OUTPUT);
  for (i = 0; i < 4; i++) pinMode(sL[i], OUTPUT);
  //for(n=0; n<4; n++) pinMode(sU[n], OUTPUT);


  //DAC setup (pressure regulator)
  //pinMode(DAC1, OUTPUT); /*this is for the arduino DUE
  //analogWriteResolution(12);   //** I think this is messing with the setup
  pinMode(A2, OUTPUT);
  digitalWrite(A2, LOW);
  dac.begin(0x60);


// Begin serial at 9600 baud for output
  Serial.begin(9600);

  // Begin I2C
  Wire.begin();

  
  Serial.println("AD5933 Test Started!");


  // Perform initial configuration. Fail if any one of these fail.
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

  /** //Debugging tool
    if (!AD5933::reset()) follow = 1; setter = false;
    if (setter && !AD5933::setInternalClock(true))  follow = 2; setter = false;
    if (setter && !AD5933::setStartFrequency(START_FREQ)) follow = 3; setter = false;
    if (setter && !AD5933::setIncrementFrequency(FREQ_INCR)) follow = 4; setter = false;
    if (setter && !AD5933::setNumberIncrements(NUM_INCR)) follow = 5; setter = false;
    if (setter && !AD5933::setPGAGain(PGA_GAIN_X1)) follow = 6; setter = false;
    while(!setter) {
    Serial.println(follow);
    }
  */



  //Set mux to the calibration output (select Y0) (300 ohm resistor installed on baord)
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
  
  
  //Setup delay in between cycles NOT IN USE
  for (i = 0; i < 0; i++) {
    Serial.println("Delay");
    delay(1000);
  }


  //Set select for Mux
  //int i = 4; selection(i);
  //for (DACp = .3; DACp < 3; DACp = DACp + .2) {
    
    //analogWrite(DAC1, DACp);
    //delay(1000);

    
    dac.setVoltage((Curvoltage*4095)/5, false);
    for (i = 0; i < 4; i++) {
      selection(i);
    }

    
    Curvoltage = Curvoltage + .5; // voltage counter
    if (Curvoltage > 2.9) {
      Curvoltage = 0.5;
    }
  //}


  // Easy to use method for frequency sweep
  //frequencySweepEasy();

  // Delay
  //delay(10000);

  // Complex but more robust method for frequency sweep
  //frequencySweepRaw();

  // Delay
  //delay(5000);
}

// Easy way to do a frequency sweep. Does an entire frequency sweep at once and
// stores the data into arrays for processing afterwards. This is easy-to-use,
// but doesn't allow you to process data in real time.
void frequencySweepEasy(int pin) {





  // Create arrays to hold the data
  int real[NUM_INCR + 1], imag[NUM_INCR + 1];

  // Perform the frequency sweep
  if (AD5933::frequencySweep(real, imag, NUM_INCR + 1)) {
    // Print the frequency data
    int cfreq = START_FREQ / 1000;

    Serial.print(pin);
    Serial.print(", ");
    Serial.print(normalP, 1); // converting to kPa while also printing (units kPa)

    for (int i = 0; i < NUM_INCR + 1; i++, cfreq += FREQ_INCR / 1000) {

      //claculating and printing out the pressure information
      pressure = analogRead(pressureInput); // will read the value from the input pin
      pressure = (pressure - pressureZ) * 15 / (pressureM - pressureZ); // convert analog reading to psi
      normalP = abs((pressure * 6.89476) - 98); // normalize?
      //Serial.print("pin: ");


      //Serial.print("  "); // label to the number
      //Serial.print(cfreq);
      //Serial.print(": R=");
      //Serial.print(",");
      //Serial.print(real[i]);
      //Serial.print("/I=");
      Serial.print(", ");
      //Serial.print(imag[i]);

      // Compute impedance
      double magnitude = sqrt(pow(real[i], 2) + pow(imag[i], 2));
      double impedance = 1 / (magnitude * gain[i]);
      //Serial.print("  |Z|=");
      //Serial.print(",");
      Serial.print(impedance);
    }
    Serial.println(" ");
  } else {
    //Serial.println("Frequency sweep failed...");
  }
}


//Not using this method of frequency sweeps currently, but it may be useful to switch to at some point for efficiency purposes
/*
  // Removes the frequencySweep abstraction from above. This saves memory and
  // allows for data to be processed in real time. However, it's more complex.
  void frequencySweepRaw() {
    // Create variables to hold the impedance data and track frequency
    int real, imag, i = 0, cfreq = START_FREQ/1000;

    // Initialize the frequency sweep
    if (!(AD5933::setPowerMode(POWER_STANDBY) &&          // place in standby
          AD5933::setControlMode(CTRL_INIT_START_FREQ) && // init start freq
          AD5933::setControlMode(CTRL_START_FREQ_SWEEP))) // begin frequency sweep
         {
             Serial.println("Could not initialize frequency sweep...");
         }

    // Perform the actual sweep
    while ((AD5933::readStatusRegister() & STATUS_SWEEP_DONE) != STATUS_SWEEP_DONE) {
        // Get the frequency data for this frequency point
        if (!AD5933::getComplexData(&real, &imag)) {
            Serial.println("Could not get raw frequency data...");
        }

        // Print out the frequency data
        Serial.print(cfreq);
        Serial.print(": R=");
        Serial.print(real);
        Serial.print("/I=");
        Serial.print(imag);

        // Compute impedance
        double magnitude = sqrt(pow(real, 2) + pow(imag, 2));
        double impedance = 1/(magnitude*gain[i]);
        Serial.print("  |Z|=");
        Serial.println(impedance);

        // Increment the frequency
        i++;
        cfreq += FREQ_INCR/1000;
        AD5933::setControlMode(CTRL_INCREMENT_FREQ);
    }

    Serial.println("Frequency sweep complete!");

    // Set AD5933 power mode to standby when finished
    if (!AD5933::setPowerMode(POWER_STANDBY))
        Serial.println("Could not set to standby...");
  }
*/



void selection(int j) {
  digitalWrite(sL[0], MUXtable[j][0]);
  digitalWrite(sL[1], MUXtable[j][1]);
  digitalWrite(sL[2], MUXtable[j][2]);
  frequencySweepEasy(j);
}
