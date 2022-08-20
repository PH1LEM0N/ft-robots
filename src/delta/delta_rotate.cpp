// #include "Arduino.h"
// #include <SPI.h>
// #include <Wire.h>
// #include <Adafruit_MotorShield.h>

// Adafruit_MotorShield MotorShield = Adafruit_MotorShield();
// Adafruit_DCMotor *M[3];

// void setup()
// {
//   Serial.begin(115200);
//   MotorShield.begin();
//   for (byte i = 0; i <= 2; i++)
//   {
//     M[i] = MotorShield.getMotor(i + 1);
//     M[i]->setSpeed(0);
//   }
// }

// boolean gehe_zu(int *R_soll)
// {

//   int v, R[3];
//   int toleranz = 5;
//   unsigned long start_zeit = millis();
//   boolean aktiv[3] = {true, true, true};

//   while ((aktiv[0] || aktiv[1] || aktiv[2]))
//   {

//     R[0] = analogRead(0);
//     R[1] = analogRead(1);
//     R[2] = analogRead(2);

//     for (byte i = 0; i <=2; i++)
//     {
//       //byte i = 2;

//       if (aktiv[i])
//       {
//         // Serial.print("R[i]: ");
//         // Serial.print(R[i]);
//         // Serial.print(" R_soll[i]: ");
//         // Serial.println(R_soll[i] + toleranz);
//         // Serial.println(R[i] > R_soll[i] + toleranz);
//         if (R[i] > R_soll[i] + toleranz)
//         {
//           v = 2 * (R[i] - R_soll[i]);
//           if (v > 255)
//             v = 255;
//           if (v < 90)
//             v = 90;
//           // Serial.println("  v: ");
//           // Serial.println(v);
//           // Serial.println("   ");
//           M[i]->setSpeed(v);
//           M[i]->run(BACKWARD);
//         }
//         else if (R[i] < R_soll[i] - toleranz)
//         {
//           v = 3 * (R_soll[i] - R[i]);
//           if (v > 255)
//             v = 255;
//           if (v < 120)
//             v = 120;
//           M[i]->setSpeed(v);
//           M[i]->run(FORWARD);
//         }
//         else
//         {
//           M[i]->setSpeed(0);
//           aktiv[i] = false;
//         }
//       }
//     }

//     if (millis() > start_zeit + 1000)
//     {
//       M[0]->setSpeed(0);
//       M[1]->setSpeed(0);
//       M[2]->setSpeed(0);
//       return false;
//     }
//   }
//   return true;
// }


// void loop()
// {

//     // Serial.println("hello");
//     // M[2]->run(FORWARD);
//     // M[2]->setSpeed(200);


//   // delay(5000);
  
//   int R_soll[3];
//   Serial.print("R_soll = ");
//   while (Serial.available() == 0);
//   R_soll[0] = Serial.parseInt();
//   R_soll[1] = Serial.parseInt();
//   R_soll[2] = Serial.parseInt();
//   Serial.read();
//   Serial.print(R_soll[0]);
//   Serial.print(", ");
//   Serial.print(R_soll[1]);
//   Serial.print(", ");
//   Serial.print(R_soll[2]);
//   Serial.print(",  ");

//   unsigned long start = millis();
//   boolean erfolgreich = gehe_zu(R_soll);
//   unsigned long dauer = millis() - start;

//   Serial.print("R = ");
//   Serial.print(analogRead(0));
//   Serial.print(", ");
//   Serial.print(analogRead(1));
//   Serial.print(", ");
//   Serial.print(analogRead(2));
//   Serial.print(", ");
//   Serial.print("t = ");
//   Serial.print(dauer);
//   Serial.print(" ms");
//   delay(300);
//   Serial.print(", R (300 ms) = ");
//   Serial.print(analogRead(0));
//   Serial.print(", ");
//   Serial.print(analogRead(1));
//   Serial.print(", ");
//   Serial.print(analogRead(2));
//   Serial.print(", ");
//   Serial.println(erfolgreich);
// }

