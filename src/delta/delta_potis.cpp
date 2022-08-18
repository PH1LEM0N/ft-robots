#include <Arduino.h>

void setup() {
  Serial.begin(115200);
}

void loop() {
  Serial.print(analogRead(0)); Serial.print(", ");
  Serial.print(analogRead(1)); Serial.print(", ");
  Serial.println(analogRead(2));
  Serial.println();
  delay(500);
}
  
  
