// /*
//   Delta-Roboter, 2. Sketch: Motor M Geschwindigkeitstest
//   Thomas Püttmann 2017
// */
// #include <SPI.h>
// #include <Wire.h>
// #include <Adafruit_MotorShield.h>

// Adafruit_MotorShield MotorShield = Adafruit_MotorShield();
// Adafruit_DCMotor *M = MotorShield.getMotor(3);

// void setup() {
//   Serial.begin(115200);
//   MotorShield.begin();
//   M->setSpeed(255);
//   Serial.flush();
// }

// void loop() {

//   if (Serial.available() > 0) {
//     int v = Serial.parseInt();
//     Serial.read();
//     Serial.println(v);
//     if (v >= 0) {
//       M->run(FORWARD);
//       M->setSpeed(v);
//     } else {
//       M->run(BACKWARD);
//       M->setSpeed(-v);
//     }
//   }
// }