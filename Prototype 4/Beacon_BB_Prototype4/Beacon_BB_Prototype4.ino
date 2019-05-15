//WORKING LED Strip
#include <SoftwareSerial.h> 
#define ledPin 9
#include <Adafruit_NeoPixel.h>
#define PIN 6 //LED strip connected to pin 6
#define NUM_LEDS 60
SoftwareSerial BTserial(2,3);//RX | TX (D2 = RX, D3 = TX)
const byte BTpin = 4; //State pin to D4
boolean BTConnected = false; //BTConnected = True
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, PIN, NEO_GRB + NEO_KHZ800);

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

if(digitalRead(BTpin) == HIGH){
  chase(strip.Color(255, 0, 0)); // Red
  chase(strip.Color(0, 0, 255)); // Blue
}
    
else { 
   chase(strip.Color(0,0,0)); //LED OFF
   strip.show();
   Serial.println("Disconnected");
}
}
static void chase(uint32_t c) {
  for(uint16_t i=0; i<strip.numPixels()+4; i++) {
      strip.setPixelColor (i,c); // Draw new pixel
      strip.setPixelColor(i-4, 0); // Erase pixel a few steps back
      strip.show();
      delay(2);
  }
}


  
  

 
 
 

 
