#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>
  
Adafruit_BNO055 bno = Adafruit_BNO055(55);
 
void setup(void) 
{
  Serial.begin(115200);
  Serial1.begin(115200);
      while (!Serial) {
      ; // wait for serial port to connect. Needed for Leonardo only
     }
          while (!Serial1) {
      ; // wait for serial port to connect. Needed for Leonardo only
     }
  Serial.println("Orientation Sensor Test"); Serial.println("");
  
  /* Initialise the sensor */
  if(!bno.begin())
  {
    /* There was a problem detecting the BNO055 ... check your connections */
    Serial.print("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
    while(1);
  }
  
  delay(1000);
    
  bno.setExtCrystalUse(true);
  //bno.setSleepEnabled(false); 
}
 
void loop(void) 
{
  /* Get a new sensor event */ 
  sensors_event_t event; 
  bno.getEvent(&event);
  
  /* Display the floating point data */
  
  Serial.print("y:");
  Serial.print(event.orientation.y, 0);

  Serial1.print("y:");
  Serial1.print(event.orientation.y, 0);
  
  Serial.print(",z:");
  Serial.print(event.orientation.z, 0);
  Serial1.print(",z:");
  Serial1.print(event.orientation.z, 0);
  
  Serial.print(", x:");
  Serial.print(round(event.orientation.x), 0);

  
  //Serial.println("");
  Serial.print("\n");
  Serial1.print("\n");

    if (Serial1.peek() != -1) {
    Serial1.print("Read: ");
    do {
      Serial1.print((char) Serial1.read());
    } while (Serial1.peek() != -1);
    Serial1.print("\n");
  }
  
  delay(5);
}
