#include <Wire.h>
#include <Adafruit_MotorShield.h>

Adafruit_MotorShield MotorShield = Adafruit_MotorShield();
Adafruit_DCMotor *M[3];

const float R_lin[3][18] = { { 415, 440, 469, 502, 527, 555, 586, 613, 633,
                               651, 668, 686, 702, 715, 724, 732, 739, 859 },
                             { 320, 347, 375, 398, 425, 454, 474, 499, 520,
                               540, 561, 579, 600, 615, 623, 633, 639, 738 },
                             { 193, 215, 235, 253, 278, 298, 318, 338, 357,
                               377, 393, 406, 422, 431, 439, 446, 453, 595 } };

const float phi_lin[18] = { -1.0122, -0.9105, -0.8121, -0.7169, -0.6251, -0.5370,
                            -0.4530, -0.3736, -0.2991, -0.2303, -0.1674, -0.1110,
                            -0.0614, -0.0188, 0.0165, 0.0446, 0.0655, 0.5240 };

int R[3], R_soll[3];
float phi[3], phi_soll[3];             // Winkelwerte
float x, y, z;                         // kartesische Position des Effektors
float y0, z0, x1, y1, z1, x2, y2, z2;  // Ellenbogen
float x_soll, y_soll, z_soll;
float x_ziel, y_ziel, z_ziel;

const float s = 40.0;   // effektive Entfernung der Schultern vom Zentrum
const float l = 75.0;   // Länge der Oberarme
const float L = 195.0;  // Länge der Unterarmell
const float h = 215.5;

// mathematische Konstanten

const float sin120 = 0.866025;
const float cos120 = -0.5;
const float sin240 = -sin120;
const float cos240 = cos120;

float t, t0;

// Setup

void setup() {
  Serial.begin(115200);
  M[0] = MotorShield.getMotor(1);
  M[1] = MotorShield.getMotor(2);
  M[2] = MotorShield.getMotor(3);
  MotorShield.begin();
  M[0]->setSpeed(0);
  M[1]->setSpeed(0);
  M[2]->setSpeed(0);

  x_ziel = 0.0;
  y_ziel = 0.0;
  z_ziel = 40.0;
  while (ansteuern())
    ;
  z_ziel = 60.0;
  while (ansteuern())
    ;
  z_ziel = 40.0;
  while (ansteuern())
    ;
  x_ziel = 50.0;
  while (ansteuern())
    ;
  y_ziel = 50.0;
  while (ansteuern())
    ;
  x_ziel = -50.0;
  while (ansteuern())
    ;
  y_ziel = -50.0;
  while (ansteuern())
    ;
  x_ziel = 50.0;
  while (ansteuern())
    ;
  y_ziel = 0.0;
  while (ansteuern())
    ;

  t = t0 = float(millis());
  while (t < t0 + 3.0 * 3141.5) {
    t = float(millis());
    x_ziel = 50.0 * cos((t - t0) / 300);
    y_ziel = 50.0 * sin((t - t0) / 300);
    z_ziel = 50.0;
    ansteuern();
  }
  while (ansteuern())
    ;
}

void loop() {
}

boolean ansteuern() {

  float abstand, max_v, dphi[3], dx, dy, dz;
  const float Schrittweite = 5.0;

  R[0] = analogRead(0);
  R[1] = analogRead(1);
  R[2] = analogRead(2);
  widerstand_winkel();
  winkel_ellenbogen();
  ellenbogen_hand();
  dx = x_ziel - x;
  dy = y_ziel - y;
  dz = z_ziel - z;
  abstand = sqrt(dx * dx + dy * dy + dz * dz);
  max_v = 0;
  if (abstand > 3.0)
    max_v = 100;
  if (abstand > 6.0)
    max_v = 120;
  if (abstand > 10.0)
    max_v = 150;
  if (abstand > 15.0)
    max_v = 180;
  if (abstand > 20.0)
    max_v = 200;
  if (abstand > 30.0)
    max_v = 255;
  if (abstand > 0.0) {
    x_soll = x + Schrittweite * dx / abstand;
    y_soll = y + Schrittweite * dy / abstand;
    z_soll = z + Schrittweite * dz / abstand;
  } else {
    x_soll = x;
    y_soll = y;
    z_soll = z;
  }
  hand_winkel();
  for (byte i = 0; i < 3; i++) {
    dphi[i] = phi_soll[i] - phi[i];
  }
  setze_v(max_v, dphi);
  if (abstand > 3.0)
    return (true);
  else
    return (false);
}

void setze_v(int max_v, float *vf) {

  float max_vf;
  int v;

  max_vf = 0.0;
  for (byte i = 0; i < 3; i++) {
    if (abs(vf[i]) > max_vf)
      max_vf = abs(vf[i]);
  }
  for (byte i = 0; i < 3; i++) {
    if ((max_v == 0) && (max_vf == 0.0))
      v = 0;
    else
      v = vf[i] * (max_v / max_vf);
    if (v < 0) {
      M[i]->run(BACKWARD);
    } else
      M[i]->run(FORWARD);
    M[i]->setSpeed(abs(v));
  }
}

void widerstand_winkel() {

  for (byte i = 0; i < 3; i++) {
    byte j = 0;
    while ((R[i] > R_lin[i][j]) && (j < 16))
      j++;
    phi[i] = (phi_lin[j] - phi_lin[j - 1]) / (R_lin[i][j] - R_lin[i][j - 1]) * (R[i] - R_lin[i][j - 1]) + phi_lin[j - 1];
  }
}

void winkel_widerstand() {

  for (byte i = 0; i < 3; i++) {
    byte j = 0;
    while ((phi_soll[i] > phi_lin[j]) && (j < 16))
      j++;
    R_soll[i] = (R_lin[i][j] - R_lin[i][j - 1]) / (phi_lin[j] - phi_lin[j - 1]) * (phi_soll[i] - phi_lin[j - 1]) + R_lin[i][j - 1];
  }
}

void winkel_ellenbogen() {
  y0 = -(s + l * cos(phi[0]));
  z0 = h + l * sin(phi[0]);

  x1 = (s + l * cos(phi[1])) * sin120;
  y1 = -(s + l * cos(phi[1])) * cos120;
  z1 = h + l * sin(phi[1]);

  x2 = (s + l * cos(phi[2])) * sin240;
  y2 = -(s + l * cos(phi[2])) * cos240;
  z2 = h + l * sin(phi[2]);
}

void ellenbogen_hand() {
  float y10 = y1 - y0;
  float y20 = y2 - y0;
  float z10 = z1 - z0;
  float z20 = z2 - z0;
  float g1 = 0.5 * (x1 * x1 + y10 * (y1 + y0) + z10 * (z1 + z0));
  float g2 = 0.5 * (x2 * x2 + y20 * (y2 + y0) + z20 * (z2 + z0));
  float p = y20 * x1 - y10 * x2;
  float q = y20 * z10 - y10 * z20;
  float g = y20 * g1 - y10 * g2;
  float ax = -q / p;
  float bx = g / p;
  float ay = -(x2 * ax + z20) / y20;
  float by = (g2 - x2 * bx) / y20 - y0;
  float a = 1.0 + ax * ax + ay * ay;
  float b = 2.0 * (ax * bx + ay * by - z0);
  float c = bx * bx + by * by + z0 * z0 - L * L;
  z = 0.5 * (-b - sqrt(b * b - 4.0 * a * c)) / a;
  y = ay * z + by + y0;
  x = ax * z + bx;
}

void hand_winkel() {

  float a = x_soll * x_soll + (y_soll + s) * (y_soll + s) + (z_soll - h) * (z_soll - h) + l * l - L * L - 2 * (y_soll + s) * l;
  float b = 4.0 * (h - z_soll) * l;
  float c = a + 4.0 * (y_soll + s) * l;
  float t = 0.5 * (-b + sqrt(b * b - 4.0 * a * c)) / a;
  phi_soll[0] = 2.0 * atan(t);

  a = (x_soll - s * sin120) * (x_soll - s * sin120) + (y_soll + s * cos120) * (y_soll + s * cos120) + (z_soll - h) * (z_soll - h) + l * l - L * L - 2.0 * (-x_soll * sin120 + y_soll * cos120 + s) * l;
  c = a + 4.0 * (-x_soll * sin120 + y_soll * cos120 + s) * l;
  t = 0.5 * (-b + sqrt(b * b - 4.0 * a * c)) / a;
  phi_soll[1] = 2.0 * atan(t);

  a = (x_soll - s * sin240) * (x_soll - s * sin240) + (y_soll + s * cos240) * (y_soll + s * cos240) + (z_soll - h) * (z_soll - h) + l * l - L * L - 2.0 * (-x_soll * sin240 + y_soll * cos240 + s) * l;
  c = a + 4.0 * (-x_soll * sin240 + y_soll * cos240 + s) * l;
  t = 0.5 * (-b + sqrt(b * b - 4.0 * a * c)) / a;
  phi_soll[2] = 2.0 * atan(t);
}