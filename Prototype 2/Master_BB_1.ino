

void setup() {
  Serial.begin(9600); // Default communication rate of the Bluetooth module
}
void loop() {
 Serial.write('1');
 delay(1000);
 Serial.write('0');
 delay(1000);
}





