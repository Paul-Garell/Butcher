#include <Wire.h>
#include <Adafruit_ADS1X15.h>
#include <Adafruit_MCP4725.h>

Adafruit_ADS1015 ads1015;
Adafruit_MCP4725 dac;

#define DAC_RESOLUTION (9)

float data = 0;
char userInput;
bool initialized = false;

void setup() {
  Serial.begin(9600);
  
  // Wait for serial port to connect (needed for native USB boards)
  while (!Serial) {
    ; // wait for serial port to connect
  }
  
  // Pull pin A2 to ground
  pinMode(A2, OUTPUT);
  digitalWrite(A2, LOW);
  
  // Initialize I2C
  Wire.begin();
  delay(100); // Give I2C time to initialize
  
  // Initialize ADC
  if (!ads1015.begin(0x48)) {
    Serial.println("ERROR: Failed to initialize ADS1015!");
    while (1); // Halt if initialization fails
  }
  
  // Initialize DAC
  if (!dac.begin(0x60)) {
    Serial.println("ERROR: Failed to initialize MCP4725!");
    while (1); // Halt if initialization fails
  }
  
  // Set DAC voltage
  dac.setVoltage((1 * 4095) / 5, false);
  
  // Small delay to ensure everything is ready
  delay(100);
  
  // Send ready signal
  Serial.println("READY");
  initialized = true;
}

void loop() {
  // Serial.println(ads1015.readADC_SingleEnded(2));
  if (Serial.available() > 0) {
    userInput = Serial.read();
    
    // Clear any additional characters in buffer (like newline)
    while (Serial.available() > 0) {
      Serial.read();
    }
    
    if (userInput == 'g' && initialized) {
      // Read ADC value
      int16_t adc_value = ads1015.readADC_SingleEnded(2);
      
      // Convert to voltage (ADS1015 with default gain: 1 bit = 3mV)
      data = ((adc_value * 3.0) / 1000.0);
      
      // Send data with proper formatting
      Serial.print(data, 3); // 3 decimal places
      Serial.println(); // Ensure newline is sent
      Serial.flush(); // Ensure data is sent immediately
    }
  }
}





