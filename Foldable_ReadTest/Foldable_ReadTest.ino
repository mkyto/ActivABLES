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
int serialPin = 9;

// iterator and channels for addressing shift register
int currentShiftChan = 0;
int shiftChannels[] = {0, 1, 2, 4, 8, 16, 32, 64};

// Multiplexer channel select ports
int muxPin0 = 14;
int muxPin1 = 15;
int muxPin2 = 16;

// Multiplexer channel select bits
int muxBit0 = 0;
int muxBit1 = 0;
int muxBit2 = 0;

// Analog pins for reading input
int muxPinData = 7;

// iterator for addressing multiplexer
int currentMuxChan = 0;

// Temp vars
int value = 0; //Current read value
String values = ""; //Set of all values


void setup() {
  
  //set pins to output for shift register
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(serialPin, OUTPUT);

  updateShiftChannel();

  //set pins to output for multiplexer
  pinMode(muxPin0, OUTPUT);
  pinMode(muxPin1, OUTPUT);
  pinMode(muxPin2, OUTPUT);

  updateMuxChannel();

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

  values = "";
  values += i;
  values += " ";

  digitalWrite(muxPin0, HIGH);
  digitalWrite(muxPin1, LOW);
  digitalWrite(muxPin2, LOW);
  delay(200);
  Serial.println(analogRead(muxPinData));
}


void updateShiftChannel() {

  if(currentShiftChan < 8) {
    digitalWrite(latchPin, LOW);
    // shift out the bits:
    shiftOut(serialPin, clockPin, MSBFIRST, channels[currentShiftChan]);
    //take the latch pin high so the LEDs will light up:
    digitalWrite(latchPin, HIGH);
  } else if (currentShiftChan == 9) {
    // Extra DO pin, not implemented yet
  } else if (currentShiftChan == 10) {
    // Extra DO pin, not implemented yet
  }
}


void updateMuxChannel() {
  
  muxBit0 = bitRead(currentMuxChan, 0);
  muxBit1 = bitRead(currentMuxChan, 1); 
  muxBit2 = bitRead(currentMuxChan, 2);

  digitalWrite(muxPin0, muxBit0);
  digitalWrite(muxPin1, muxBit1);
  digitalWrite(muxPin2, muxBit2);
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

