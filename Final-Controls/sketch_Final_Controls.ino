//EVERYTHING COMBINED!!!

//LED

// LED RGB PWM pins 
const uint8_t blueLEDPin = 11;
const uint8_t redLEDPin = 10;

//const int blueLEDPotPin = A0;
//const int redLEDPotPin = A5;

// Potentiometer Value Variables
//int blueLEDPotVal;
//int redLEDPotVal;

// PWM Variables (values between 0-255) - leave as empty variable if using potentiometers
// CORRESPONDING COLOURS MUST BE THE SAME
// 'current' values must CORRESPOND WITH WHICH INTERVAL IS STARTING FIRST (DAY != 0, NIGHT = 0)
// To have only one colour of LED ON and the other OFF, set the bluePWM or the redPWM equal to 0 and the respective 'current' value equal to 0
const uint8_t bluePWM = 255;
const uint8_t redPWM = 0;
uint8_t currentbluePWM = 255;
uint8_t currentredPWM = 0;

// for testing purposes
//const uint64_t dayInterval = 3000;
//const uint64_t nightInterval = 2000;

// setting interval of time to determine when to toggle LEDs (milliseconds)
const uint32_t dayInterval = 6.48e+7;
const uint32_t nightInterval = 2.16e+7;
uint64_t interval = dayInterval;

// variable to save the current - now previous - time 
uint64_t previousMillis = 0; 

//TEMPERATURE + HUMIDITY SENSORS

// Time intervals to retrieve info from sensors (time between sensor calls)
const uint16_t interval2 = 3000;        
uint64_t previousMillis2 = 0; 

// ******************************** SPECIAL THANKS TO ADAFRUIT!!! ***************************** //
// DHT Temperature & Humidity Sensor
// Unified Sensor Library Example
// Written by Tony DiCola for Adafruit Industries
// Released under an MIT license.

// Depends on the following Arduino libraries:
// - Adafruit Unified Sensor Library: https://github.com/adafruit/Adafruit_Sensor
// - DHT Sensor Library: https://github.com/adafruit/DHT-sensor-library

#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

#define DHTPIN_ONE           13         // Arduino board pin which is connected to the DHT sensor.
#define DHTPIN_TWO           7
// Uncomment the type of sensor in use:
#define DHTTYPE           DHT11     // DHT 11 
//#define DHTTYPE           DHT22     // DHT 22 (AM2302)
//#define DHTTYPE           DHT21     // DHT 21 (AM2301)

// See guide for details on sensor wiring and usage:
//   https://learn.adafruit.com/dht/overview

DHT_Unified dht_one(DHTPIN_ONE, DHTTYPE);
DHT_Unified dht_two(DHTPIN_TWO, DHTTYPE);

//uint32_t delayMS_ONE;
//uint32_t delayMS_TWO;

/*
// variables used for printing sensor values 

//SENSOR ONE
sensors_event_t event_one; 

  // TEMPERATURE
  dht_one.temperature().getEvent(&event_one);
  float temp1 = event_one.temperature;

  // HUMIDITY
  dht_one.humidity().getEvent(&event_one);
  float hum1 = event_one.relative_humidity;

//SENSOR TWO
sensors_event_t event_two;  
  
  // TEMPERATURE 
  dht_two.temperature().getEvent(&event_two);
  float temp2 = event_two.temperature;

  // HUMIDITY 
  dht_two.humidity().getEvent(&event_two);
  float hum2 = event_two.relative_humidity;
*/
//FAN

// Pin information
const uint8_t fanPWMPin = 3;

// Fan speed settings using PWM, will vary based on average temperature value
uint8_t fanPWMHIGH = 255;
uint8_t fanPWMLOW = 0;

// temperatures specific to plant, manually set
uint8_t minTemp = 10;
uint8_t maxTemp = 28;
uint8_t marginTemp = 0;

//*********** END OF GLOBAL VARIABLES *************//

void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);

//LED

  // Assigning pin modes to the PWM LED pins
  pinMode(blueLEDPin, OUTPUT);
  pinMode(redLEDPin, OUTPUT);

  // Initial state of LEDs is for them to be OFF
  analogWrite(blueLEDPin, 0);
  analogWrite(redLEDPin, 0);

//Temperature and Humidity Sensors

  // Initialize device.
  dht_one.begin();
  dht_two.begin();

  // FIRST SENSOR
  Serial.println("DHT11 Unified Sensor One");
  // Print temperature sensor details.
  sensor_t sensor_one;
  dht_one.temperature().getSensor(&sensor_one);
  Serial.println("------------------------------------");
  Serial.println("Temperature");
  Serial.print  ("Sensor:       "); Serial.println(sensor_one.name);
  Serial.print  ("Driver Ver:   "); Serial.println(sensor_one.version);
  Serial.print  ("Unique ID:    "); Serial.println(sensor_one.sensor_id);
  Serial.print  ("Max Value:    "); Serial.print(sensor_one.max_value); Serial.println(" *C");
  Serial.print  ("Min Value:    "); Serial.print(sensor_one.min_value); Serial.println(" *C");
  Serial.print  ("Resolution:   "); Serial.print(sensor_one.resolution); Serial.println(" *C");  
  Serial.println("------------------------------------");
  // Print humidity sensor details.
  dht_one.humidity().getSensor(&sensor_one);
  Serial.println("------------------------------------");
  Serial.println("Humidity");
  Serial.print  ("Sensor:       "); Serial.println(sensor_one.name);
  Serial.print  ("Driver Ver:   "); Serial.println(sensor_one.version);
  Serial.print  ("Unique ID:    "); Serial.println(sensor_one.sensor_id);
  Serial.print  ("Max Value:    "); Serial.print(sensor_one.max_value); Serial.println("%");
  Serial.print  ("Min Value:    "); Serial.print(sensor_one.min_value); Serial.println("%");
  Serial.print  ("Resolution:   "); Serial.print(sensor_one.resolution); Serial.println("%");  
  Serial.println("------------------------------------");

  // SECOND SENSOR
  Serial.println("DHT11 Unified Sensor Two");
  // Print temperature sensor details.
  sensor_t sensor_two;
  dht_two.temperature().getSensor(&sensor_two);
  Serial.println("------------------------------------");
  Serial.println("Temperature");
  Serial.print  ("Sensor:       "); Serial.println(sensor_two.name);
  Serial.print  ("Driver Ver:   "); Serial.println(sensor_two.version);
  Serial.print  ("Unique ID:    "); Serial.println(sensor_two.sensor_id);
  Serial.print  ("Max Value:    "); Serial.print(sensor_two.max_value); Serial.println(" *C");
  Serial.print  ("Min Value:    "); Serial.print(sensor_two.min_value); Serial.println(" *C");
  Serial.print  ("Resolution:   "); Serial.print(sensor_two.resolution); Serial.println(" *C");  
  Serial.println("------------------------------------");
  // Print humidity sensor details.
  dht_two.humidity().getSensor(&sensor_two);
  Serial.println("------------------------------------");
  Serial.println("Humidity");
  Serial.print  ("Sensor:       "); Serial.println(sensor_two.name);
  Serial.print  ("Driver Ver:   "); Serial.println(sensor_two.version);
  Serial.print  ("Unique ID:    "); Serial.println(sensor_two.sensor_id);
  Serial.print  ("Max Value:    "); Serial.print(sensor_two.max_value); Serial.println("%");
  Serial.print  ("Min Value:    "); Serial.print(sensor_two.min_value); Serial.println("%");
  Serial.print  ("Resolution:   "); Serial.print(sensor_two.resolution); Serial.println("%");  
  Serial.println("------------------------------------");
  
  // Set delay between sensor readings based on sensor details.
  //delayMS_ONE = sensor_one.min_delay / 1000;
  //delayMS_TWO = sensor_two.min_delay / 1000;

//FAN

  // Setting the fan pin to be a PWM output pin
  pinMode(fanPWMPin, OUTPUT);
  digitalWrite(fanPWMPin, fanPWMHIGH);


}

void loop() {
  // put your main code here, to run repeatedly:

 

//LED

  // get data from potentiometers
  //blueLEDPotVal = analogRead(blueLEDPotPin);
  //redLEDPotVal = analogRead(redLEDPotPin);

  // map potentiometer value to PWM values
  //blueLEDPWM = map(blueLEDPotVal, 0, 1023, 0, 255);
  //redLEDPWM = map(redLEDPotVal, 0, 1023, 0, 255);
  
  // if state of LEDs has not changed
  analogWrite(blueLEDPin, currentbluePWM);
  analogWrite(redLEDPin, currentredPWM);
  
  // function for day/night cycle LED toggle - checks to see if LEDs are ON or OFF, will also determine function of other components 
  checkSYSTEM();


//Temperature and Humidity Sensors

  // function for retreiving sensor information and sending to the Arduino - without delay()
  //checkSensor();

//FAN

  // PWM will be used to control fan speed, but based on average tempature values measured from temp. sensors
  //toggleFAN();

} // end of program!
