/*
  HC-SR04 NewPing Duration Demonstration
  HC-SR04-NewPing-Duration.ino
  Demonstrates using Duration function of NewPing Library for HC-SR04 Ultrasonic Range Finder
  Displays results on Serial Monitor
  DroneBot Workshop 2017
  http://dronebotworkshop.com
*/
//ULTRASONIC SENSOR
// This uses Serial Monitor to display Range Finder distance readings

// Include NewPing Library
#include "NewPing.h"

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
#define PIN 6 //LED Strip PIN
#define NUM_LEDS 60
#include <Adafruit_NeoPixel.h>
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  Serial.begin (9600);
  strip.begin();
  strip.show();
  
}

void loop() {
   
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
  
  // Send results to Serial Monitor=
  //Serial.print("Distance 1 = ");
  //Serial.print("Distance2 = ");

//Out of range turn off the LED Strip
  if (distance1 >= 400 || distance1 <= 2 ) {
    Serial.println("Distance1 = Out of range_1\n");
    chase(strip.Color(0,0,0)); //LED OFF
    strip.show();
  }
  if(distance2 >= 400 || distance2 <= 2){
    Serial.println("Distance2 = Out of range_2\n");
    chase(strip.Color(0,0,0)); //LED OFF
    strip.show();
  }
  if(distance3 >= 400 || distance3 <= 2){
   Serial.println("Distance3 = Out of range_3\n");
   chase(strip.Color(0,0,0)); //LED OFF
   strip.show();
  }
  if(distance4 >= 400 || distance4 <= 2){
    Serial.println("Distance4 = Out of range_4\n");
    chase(strip.Color(0,0,0)); //LED OFF
    strip.show();
    
  }
  
//When in range turn on the LED strip
    Serial.println("Distance1 = ");
    Serial.print(distance1);
    chase(strip.Color(255, 0, 0)); // Red
    chase(strip.Color(0, 0, 255)); // Blue
    Serial.println("");
    
    Serial.println("Distance2 = ");
    Serial.print(distance2);
    chase(strip.Color(255, 0, 0)); // Red
    chase(strip.Color(0, 0, 255)); // Blue
    Serial.println("");

    Serial.println("Distance3 = ");
    Serial.print(distance3);
    chase(strip.Color(255, 0, 0)); // Red
    chase(strip.Color(0, 0, 255)); // Blue
    Serial.println("");
    
    Serial.println("Distance4 = ");
    Serial.print(distance4);
    chase(strip.Color(255, 0, 0)); // Red
    chase(strip.Color(0, 0, 255)); // Blue
    Serial.println("");
    

   
  delay(500);

}
static void chase(uint32_t c) {
  for(uint16_t i=0; i<strip.numPixels()+4; i++) {
      strip.setPixelColor (i,c); // Draw new pixel
      strip.setPixelColor(i-4, 0); // Erase pixel a few steps back
      strip.show();
      delay(2);
  }

}

  

