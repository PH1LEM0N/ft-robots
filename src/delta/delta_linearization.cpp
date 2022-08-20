// #include <Arduino.h>
// #include <SPI.h>
// #include <Wire.h>
// #include <Adafruit_MotorShield.h>

// void setup() {
//   Serial.begin(115200);
//   Serial.print("Poti: ");
//   while(Serial.available() == 0);
//   int poti = Serial.parseInt();
//   Serial.println(poti);
//   Serial.read();
 
//   byte i = 1;
  
//   do {   
//     while (Serial.available() == 0);
//     Serial.read();
//     Serial.print(analogRead(poti)); Serial.print(", ");
//     if (i % 10 == 0) Serial.println();
//     i++;
//   } while(true);
// }

// void loop() {
// }
