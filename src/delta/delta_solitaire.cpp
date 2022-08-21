#include <Wire.h>
#include <SPI.h>
#include <Adafruit_MotorShield.h>

Adafruit_MotorShield MotorShield = Adafruit_MotorShield(); 
Adafruit_DCMotor *M[3];
Adafruit_DCMotor *magnet;

boolean gehe_zu(int *R_soll) {
    
  int v, R[3];
  int toleranz = 5;
  unsigned long start_zeit = millis();
  boolean aktiv[3] = { true, true, true };
  
  while ( (aktiv[0] || aktiv[1] || aktiv[2]) ) {
    
    R[0] = analogRead(0);
    R[1] = analogRead(1);
    R[2] = analogRead(2);
    
    for (byte i = 0; i <= 2; i++) {
      
      if (aktiv[i]) {
        if (R[i] > R_soll[i] + toleranz) {
          v = 2*(R[i] - R_soll[i]);
          if (v > 255) v = 255;
          if (v < 90) v = 90;
          M[i]->setSpeed(v);
          M[i]->run(BACKWARD);
         }
         else if (R[i] < R_soll[i] - toleranz) {
           v = 3*(R_soll[i] - R[i]);
           if (v > 255) v = 255;
           if (v < 120) v = 120;
           M[i]->setSpeed(v);
           M[i]->run(FORWARD);
         }
         else {
           M[i]->setSpeed(0);
           aktiv[i] = false;
         }
      }
    }
    
    if (millis() > start_zeit + 1000) {
      M[0]->setSpeed(0);
      M[1]->setSpeed(0);
      M[2]->setSpeed(0);
      return false;
    }        
  }
  return true;
}

void home() {
  M[0]->run(FORWARD); M[0]->setSpeed(100);
  M[1]->run(FORWARD); M[1]->setSpeed(100);
  M[2]->run(FORWARD); M[2]->setSpeed(100);
  delay(3000);
  M[0]->setSpeed(0);
  M[1]->setSpeed(0);
  M[2]->setSpeed(0);
}

void setup() {
  M[0] = MotorShield.getMotor(1);
  M[1] = MotorShield.getMotor(2);
  M[2] = MotorShield.getMotor(3);
  magnet = MotorShield.getMotor(4);
  MotorShield.begin();
  magnet->setSpeed(0);
  magnet->run(FORWARD);
  home(); 
  delay(1000);
  
  int unten[33][3] = 
  { {445, 661, 450}, {488, 662, 412}, {521, 653, 369}, {491, 637, 497}, 
    {532, 638, 461}, {566, 632, 418}, {418, 561, 593}, {471, 585, 571}, 
    {521, 603, 543}, {566, 604, 499}, {606, 598, 447}, {632, 581, 396}, 
    {644, 557, 346}, {437, 521, 620}, {497, 546, 601}, {548, 558, 567}, 
    {594, 562, 528}, {628, 558, 479}, {656, 541, 430}, {672, 514, 368}, 
    {452, 473, 637}, {514, 493, 617}, {566, 505, 588}, {613, 508, 546}, 
    {648, 501, 499}, {674, 487, 445}, {689, 462, 383}, {571, 448, 600}, 
    {619, 451, 561}, {657, 443, 499}, {579, 388, 596}, {623, 390, 555}, 
    {658, 383, 508} };
  int oben[33][3] = 
  { {482, 729, 498}, {524, 732, 464}, {566, 728, 422}, {526, 700, 559}, 
    {580, 709, 515}, {618, 708, 470}, {452, 613, 650}, {505, 637, 630}, 
    {563, 665, 596}, {613, 673, 554}, {656, 669, 500}, {686, 656, 446}, 
    {710, 629, 386}, {465, 559, 669}, {524, 584, 653}, {591, 610, 620}, 
    {642, 616, 576}, {682, 609, 527}, {714, 587, 467}, {733, 566, 406}, 
    {474, 489, 646}, {564, 544, 683}, {618, 553, 651}, {668, 556, 604}, 
    {713, 551, 548}, {739, 532, 486}, {750, 510, 421}, {625, 494, 665}, 
    {682, 500, 618}, {724, 492, 556}, {630, 425, 665}, {683, 433, 595}, 
    {728, 424, 569} };
  int ablage[4][3] = 
  { {657, 707, 367}, {458, 718, 596}, {555, 385, 696}, {751, 473, 498} };

    // algorithm: https://en.wikipedia.org/wiki/Peg_solitaire
  byte zug[31][4] =
    { { 18,16,17, 0 }, {  5,17,10, 0 }, { 12,10,11, 0 }, { 17, 5,10, 0 },
      {  2,10, 5, 0 }, {  9,11,10, 0 }, { 26,12,19, 0 }, { 12,10,11, 0 },
      {  7, 9, 8, 1 }, {  9,11,10, 0 }, {  0, 2, 1, 1 }, {  3, 5, 4, 0 },
      {  2,10, 5, 0 }, { 11, 9,10, 1 }, { 22, 8,15, 1 }, {  9, 7, 8, 1 },
      {  6, 8, 7, 1 }, { 13,15,14, 1 }, {  8,22,15, 2 }, { 27,15,22, 2 },
      { 20,22,21, 2 }, { 15,27,22, 2 }, { 30,22,27, 2 }, { 23,21,22, 2 },
      { 31,23,28, 2 }, { 24,22,23, 2 }, { 32,24,29, 3 }, { 25,23,24, 2 },
      { 16,28,23, 2 }, { 21,23,22, 2 }, { 28,16,23, 2 } };
 
  for (byte i = 0; i < 31; i++) {
    gehe_zu( oben[zug[i][0]] );
    magnet->setSpeed(250);
    gehe_zu( unten[zug[i][0]] );
    gehe_zu( oben[zug[i][0]] );
    gehe_zu( oben[zug[i][1]] );
    gehe_zu( unten[zug[i][1]] );
    magnet->setSpeed(0);
    delay(50);
    gehe_zu( oben[zug[i][1]] );
    gehe_zu( oben[zug[i][2]] );
    magnet->setSpeed(250);
    gehe_zu( unten[zug[i][2]] );
    gehe_zu( oben[zug[i][2]] );
    gehe_zu( ablage[zug[i][3]] );
    magnet->setSpeed(0);
  }
  home();
}

void loop() {
}
