/*
   Read pressure data via shift register & angle from gyro
   Based on: https://www.arduino.cc/en/Tutorial/ShftOut11
        and: https://learn.adafruit.com/adafruit-bno055-absolute-orientation-sensor/wiring-and-test


   @author wbock

*/

#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>
#include <math.h>

Adafruit_BNO055 bno = Adafruit_BNO055(55);

// Pin connected to ST_CP of 74HC595
int latchPin = 8;
// Pin connected to SH_CP of 74HC595
int clockPin = 10;
// Pin connected to DS of 74HC595
int dataPin = 9;

// Multiplexer channel select bits
int muxPin0 = 14;
int muxPin1 = 15;
int muxPin2 = 16;


int r0 = 0;      //value of select pin at the 4051 (s0)
int r1 = 0;      //value of select pin at the 4051 (s1)
int r2 = 0;      //value of select pin at the 4051 (s2)

// Analog pins for reading input
int muxPinData = 6;

int chanels[] = {1, 2, 4, 8, 16, 32, 64};

// Temp vars
int value = 0; //Current read value
String values = ""; //Set of all values

void setup() {
  //set pins to output so you can control the shift register
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);

  digitalWrite(muxPin0, 0);
  digitalWrite(muxPin1, 0);
  digitalWrite(muxPin2, 0);

  digitalWrite(latchPin, LOW);
      
  // shift out the bits:
  shiftOut(dataPin, clockPin, MSBFIRST, 1);

  //take the latch pin high so the LEDs will light up:
  digitalWrite(latchPin, HIGH);

  Serial.begin(9600);

//  /* Initialise the sensor */
//  if(!bno.begin())
//  {
//    /* There was a problem detecting the BNO055 ... check your connections */
//    Serial.print("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
//    while(1);
//  }
//  
//  delay(1000);
//    
//  bno.setExtCrystalUse(true);
}

void loop () {

  
      
  delay(200);
  Serial.println(analogRead(muxPinData));

}

void loadGyroValues() {
  
  /* Get a new sensor event */ 
  sensors_event_t event; 
  bno.getEvent(&event);
  
  /* Display the floating point data */
  values = "3 ";
  values += roundf(event.orientation.x);
  values += " ";
  values += roundf(event.orientation.y);
  values += " ";
  values += roundf(event.orientation.z);
}

