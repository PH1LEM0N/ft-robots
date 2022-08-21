// #include <SPI.h>
// #include <Wire.h>
// #include <Adafruit_MotorShield.h>

// Adafruit_MotorShield MotorShield = Adafruit_MotorShield();

// void setup() {
//     Serial.begin(115200);

//     MotorShield.begin();

//     // nur für die Kugeln die liegen...
//     Adafruit_DCMotor *magnet = MotorShield.getMotor(4);
//     magnet->setSpeed(255);
//     magnet->run(FORWARD);
    
//     byte i = 1;

//     do {   
//         while (Serial.available() == 0);
//         Serial.read();
//         Serial.print("{");
//         Serial.print(analogRead(0)); Serial.print(", ");
//         Serial.print(analogRead(1)); Serial.print(", ");
//         Serial.print(analogRead(2)); Serial.print("}, ");
//         if (i % 4 == 0) Serial.println();
//         i++;
//     } while(true);
// }

// void loop() {
// }
