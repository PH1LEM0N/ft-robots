// #include <Wire.h>
// #include <SPI.h>
// #include <Adafruit_MotorShield.h>

// Adafruit_MotorShield MotorShield = Adafruit_MotorShield(); 
// Adafruit_DCMotor *M[3];
// Adafruit_DCMotor *magnet;

// boolean gehe_zu(int *R_soll) {
    
//   int v, R[3];
//   int toleranz = 5;
//   unsigned long start_zeit = millis();
//   boolean aktiv[3] = { true, true, true };
  
//   while ( (aktiv[0] || aktiv[1] || aktiv[2]) ) {
    
//     R[0] = analogRead(0);
//     R[1] = analogRead(1);
//     R[2] = analogRead(2);
    
//     for (byte i = 0; i <= 2; i++) {
      
//       if (aktiv[i]) {
//         if (R[i] > R_soll[i] + toleranz) {
//           v = 2*(R[i] - R_soll[i]);
//           if (v > 255) v = 255;
//           if (v < 90) v = 90;
//           M[i]->setSpeed(v);
//           M[i]->run(BACKWARD);
//          }
//          else if (R[i] < R_soll[i] - toleranz) {
//            v = 3*(R_soll[i] - R[i]);
//            if (v > 255) v = 255;
//            if (v < 120) v = 120;
//            M[i]->setSpeed(v);
//            M[i]->run(FORWARD);
//          }
//          else {
//            M[i]->setSpeed(0);
//            aktiv[i] = false;
//          }
//       }
//     }
    
//     if (millis() > start_zeit + 1000) {
//       M[0]->setSpeed(0);
//       M[1]->setSpeed(0);
//       M[2]->setSpeed(0);
//       return false;
//     }        
//   }
//   return true;
// }

// void home() {
//   M[0]->run(FORWARD); M[0]->setSpeed(100);
//   M[1]->run(FORWARD); M[1]->setSpeed(100);
//   M[2]->run(FORWARD); M[2]->setSpeed(100);
//   delay(3000);
//   M[0]->setSpeed(0);
//   M[1]->setSpeed(0);
//   M[2]->setSpeed(0);
// }

// void setup() {
//   M[0] = MotorShield.getMotor(1);
//   M[1] = MotorShield.getMotor(2);
//   M[2] = MotorShield.getMotor(3);
//   magnet = MotorShield.getMotor(4);
//   MotorShield.begin();
//   magnet->setSpeed(0);
//   magnet->run(FORWARD);
//   home(); 
//   delay(1000);
  
//   int unten[33][3] = 
//   { {450, 670, 524}, {490, 676, 457}, {521, 668, 433}, {491, 647, 509}, 
//     {534, 648, 471}, {568, 643, 424}, {422, 570, 605}, {475, 594, 578}, 
//     {528, 610, 556}, {567, 613, 536}, {607, 607, 502}, {634, 590, 460}, 
//     {650, 562, 413}, {439, 527, 629}, {500, 552, 605}, {552, 563, 569}, 
//     {596, 567, 544}, {635, 557, 490}, {662, 544, 468}, {677, 514, 371}, 
//     {456, 476, 646}, {516, 497, 628}, {569, 510, 596}, {617, 512, 555}, 
//     {655, 504, 504}, {678, 491, 459}, {694, 462, 409}, {580, 452, 610}, 
//     {624, 454, 525}, {662, 447, 497}, {580, 391, 543}, {626, 394, 525}, 
//     {663, 390, 522} };
//   int oben[33][3] = 
//   { {478, 726, 563}, {523, 730, 541}, {559, 724, 505}, {539, 724, 614}, 
//     {588, 729, 573}, {627, 723, 546}, {457, 639, 667}, {521, 668, 645}, 
//     {582, 686, 629}, {630, 688, 598}, {668, 679, 563}, {698, 660, 511}, 
//     {717, 629, 462}, {472, 569, 679}, {548, 614, 678}, {609, 627, 645}, 
//     {661, 633, 598}, {702, 625, 545}, {734, 603, 478}, {738, 556, 452}, 
//     {489, 512, 697}, {552, 535, 635}, {630, 564, 642}, {682, 569, 608}, 
//     {725, 559, 560}, {733, 527, 496}, {750, 501, 438}, {641, 497, 672}, 
//     {692, 497, 636}, {734, 493, 559}, {642, 427, 680}, {692, 431, 640}, 
//     {733, 422, 548} };
//   int ablage[4][3] = 
//   { {657, 707, 367}, {458, 718, 596}, {555, 385, 696}, {751, 473, 498} };
                 
 
//   for (byte i = 0; i < 32; i++) {
//     gehe_zu(oben[i]);
//     magnet->setSpeed(250);
//     gehe_zu(unten[i]);
//     delay(1000);
//     gehe_zu(oben[i]);
//     gehe_zu(ablage[0]);
//     magnet->setSpeed(0);
//   }
//   home();
// }

// void loop() {
// }
