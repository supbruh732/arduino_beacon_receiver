/*Version 3 Features: 
 Requires the Ultrasonic sensor to be triggered,
 as well as bluetooth receiver to be in range
 Allows for bluetooth range control
*/
#include <SoftwareSerial.h> 
#include <Adafruit_NeoPixel.h>
#include "NewPing.h"


#define ledPin 9
#define PIN 13 //LED strip connected to pin 13
#define NUM_LEDS 60
SoftwareSerial BTserial(2,3);//RX | TX (D2 = RX, D3 = TX)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, PIN, NEO_GRB + NEO_KHZ800);


// Hook up HC-SR04 with Trig to Arduino Pin 10, Echo to Arduino pin 13
// Maximum Distance is 400 cm

//ultrasound sensor 1
#define TRIGGER_PIN_1  11
#define ECHO_PIN_1     12

//ultrasound sensor 2
#define TRIGGER_PIN_2  9
#define ECHO_PIN_2     10

//ultrasound sensor 3
#define TRIGGER_PIN_3  7
#define ECHO_PIN_3     8

//ultrasound sensor 4
#define TRIGGER_PIN_4  5
#define ECHO_PIN_4     6

#define MAX_DISTANCE 400
 
NewPing sonar1(TRIGGER_PIN_1, ECHO_PIN_1, MAX_DISTANCE);
NewPing sonar2(TRIGGER_PIN_2, ECHO_PIN_2, MAX_DISTANCE);
NewPing sonar3(TRIGGER_PIN_3, ECHO_PIN_3, MAX_DISTANCE);
NewPing sonar4(TRIGGER_PIN_4, ECHO_PIN_4, MAX_DISTANCE);

float duration1, duration2, duration3, duration4, distance1, distance2, distance3, distance4;

const byte BTpin = 4; //State pin to D4
boolean BTConnected = false; //BTConnected = True
boolean inRange = false; //when in range = True


void setup() {
  strip.begin();
  strip.show();
  pinMode(BTpin, INPUT);
  pinMode(ledPin,OUTPUT);
  Serial.begin(9600); // Default communication rate of the Bluetooth module
  Serial.println("Ready to connect");
  Serial.println(" ");

   while(!BTConnected)
   {
    if(digitalRead(BTpin)==HIGH)
    {
      BTConnected = true; //Exit condition
    };
   }
   
Serial.println("COMS Established");
Serial.println(" ");

BTserial.begin(9600); //begin serial COMS 
}

//------------------------------------------//

void loop() {

  inRange = rangeFound();


  if( (digitalRead(BTpin) == HIGH) && inRange ){
    // chase(strip.Color(255, 0, 0)); // Red
    // chase(strip.Color(0, 0, 255)); // Blue
    chase(strip.Color(255,0,0)); //Turn on LEDS
    //chase(strip.Color(0,0,255));
    Serial.println("Range Found Triggered");
    // Serial.print(distance1);
    // Serial.println(" cm");
    delay(5);
  }
    
  else { 
    chase(strip.Color(0,0,0)); //LED OFF
    strip.show();
    Serial.println("Out of Range");
  }

  delay(5);
}

/* rangeFound() -- Type Boolean
 * Determines if the ultrasonic is out of range if so returns false
 *      else return true;
 *  
 */

boolean rangeFound() {

  // boolean localSetter = false;
  
  duration1 = sonar1.ping();
  duration2 = sonar2.ping();
 
  duration3 = sonar3.ping();
  duration4 = sonar4.ping();
  
  // Determine distance from duration
  // Use 343 metres per second as speed of sound
  distance1 = (duration1 / 2) * 0.0343;
  distance2 = (duration2 /2) * 0.0343;
  distance3 = (duration3 / 2) * 0.0343;
  distance4 = (duration4 /2) * 0.0343;

  if ( (distance1 >= 400 || distance1 <= 2) &&
       (distance2 >= 400 || distance2 <= 2) && 
       (distance3 >= 400 || distance3 <= 2) && 
       (distance4 >= 400 || distance4 <= 2) ) {

       return false;          // out of range
  }

  /*Serial.println("Distance1 = ");
  Serial.print(distance1);
  Serial.println(" cm");

  Serial.println("Distance2 = ");
  Serial.print(distance2);
  Serial.println(" cm");

  Serial.println("Distance3 = ");
  Serial.print(distance3);
  Serial.println(" cm");
  
  Serial.println("Distance4 = ");
  Serial.print(distance4);
  Serial.println(" cm");*/

  
  return true;
}


static void chase(uint32_t c) {
  for(uint16_t i=0; i<strip.numPixels()+4; i++) {
      strip.setPixelColor (i,c); // Draw new pixel
     // strip.setPixelColor(i-4, 0); // Erase pixel a few steps back
      strip.show();
      delay(2);
  }
}

