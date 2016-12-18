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

//Pin connected to ST_CP of 74HC595
int latchPin = 8;
//Pin connected to SH_CP of 74HC595
int clockPin = 10;
////Pin connected to DS of 74HC595
int dataPin = 9;

// Analog pins for reading input
int row1 = 0; // lower row (closest to output ports)
int row2 = 1; // middle row
int row3 = 2; // upper row

int chanels[] = {2, 4, 8, 16, 32, 64};

// Temp vars
int value = 0; //Current read value
String values = ""; //Set of all values

void setup() {
  //set pins to output so you can control the shift register
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);

   Serial.begin(115200);
  Serial1.begin(115200);
      
      //while (!Serial) {
      //; // wait for serial port to connect. Needed for Leonardo only
     //}
          while (!Serial1) {
      ; // wait for serial port to connect. Needed for Leonardo only
     }

  /* Initialise the sensor */
  if(!bno.begin())
  {
    /* There was a problem detecting the BNO055 ... check your connections */
    Serial.print("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
    while(1);
  }
  
  delay(1000);
    
  bno.setExtCrystalUse(true);
}

void loop () {

  for (int i = 0; i < 3; i++) {

    // First value = row number
    // values = "";
    // values += i;
    // values += " ";

    // Sum of all pressure values
    value = 0;

    for (int ii = 0; ii < 6; ii++) {
      // take the latchPin low so
      // the LEDs don't change while you're sending in bits:
      digitalWrite(latchPin, LOW);
      
      // shift out the bits:
      shiftOut(dataPin, clockPin, MSBFIRST, chanels[ii]);

      //take the latch pin high so the LEDs will light up:
      digitalWrite(latchPin, HIGH);
      // pause before next value:
      delay(20);
      value += (int) analogRead(i);

      // Spacing between values
      // if(ii < 5) {
      //   values +=  " ";
      // }
    }

     Serial1.print("p:");
     Serial1.print(value);
     
     Serial.print("p:");
     Serial.print(value);

     
    // Send values row-by-row
    // Serial.println(values);

    // Send gyro data in-between
     loadGyroValues();
    // Serial.println(values);
  delay(5);
    // Send sum of all pressure
  }
}

void loadGyroValues() {
  
  /* Get a new sensor event */ 
  sensors_event_t event; 
  bno.getEvent(&event);

  Serial.print(",x:");
  Serial.print(event.orientation.x, 0);
  
  Serial.print(",y:");
  Serial.print(event.orientation.y, 0);

  Serial1.print(",y:");
  Serial1.print(event.orientation.y, 0);
  
  Serial.print(",z:");
  Serial.print(event.orientation.z, 0);
  Serial1.print(",z:");
  Serial1.print(event.orientation.z, 0);
  
  //Serial.println("");

   Serial.print(",");
  Serial1.print(",");
  
  Serial.print("\n");
  Serial1.print("\n");

  if (Serial1.peek() != -1) {
    Serial1.print("Read: ");
    do {
      Serial1.print((char) Serial1.read());
    } while (Serial1.peek() != -1);
    Serial1.print("\n");
  }
}
