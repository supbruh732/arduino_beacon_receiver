/*Receiver V3
 * If Beacon is triggered and reciever is in range:
 * Receiver will light up and Speaker will sound
 */ 
#include <SoftwareSerial.h>
#define ledPin 9
SoftwareSerial BTserial(2, 3); // RX | TX   //USING DIGITAL PIN 2 & 3 as RX | TX
const byte BTpin = 4; //state pin connected to pin 4   //when State == HIGH (Connected) 
boolean BTConnected = false; //when BT connnected = True

void setup() {
  pinMode(BTpin, INPUT); //Setup State pin as an input 
  pinMode(ledPin,OUTPUT); //Setup LED as an output
  Serial.begin(9600); // Default communication rate of the Bluetooth module
  Serial.println("Ready to connect"); //Print to Serial Monitor
  Serial.println(" ");
  
  //Check to see if conneciton is established
  while(!BTConnected)
  {
    if ( digitalRead(BTpin)==HIGH)
    { 
      BTConnected = true; //Exit condition
    };   
  }

  Serial.println("Connection Established"); //print connection established
  Serial.println(" ");
  
  BTserial.begin(9600); //Begin Serial communication at 9600 Baud Rate
}
void loop() {
  
    if (digitalRead(BTpin)==HIGH){   //if State = HIGH, turn on LED
      digitalWrite(ledPin,HIGH);
    }
      else(digitalWrite(ledPin,LOW)); // otherwise turn off LED
  }
         
      
    
    
  

