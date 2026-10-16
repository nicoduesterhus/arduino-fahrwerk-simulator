// Schritt 1 Pruefstand: MPU-6050 mit festem Abtasttakt als CSV loggen
// Verkabelung Uno:  VCC->5V   GND->GND   SDA->A4   SCL->A5   AD0->GND
// Serial Monitor auf 500000 Baud stellen.

#include <Wire.h>

const uint8_t  MPU   = 0x68;   // I2C-Adresse bei AD0 = GND
const uint32_t T_US  = 2000;   // Abtastperiode 2000 us = 500 Hz

// Kalibrierung z-Achse (Umdrehtest 16.10.2026):
//   flach: az = +14232   kopfueber: az = -18604
//   Nullpunkt = (14232 + -18604) / 2 = -2186
//   Empfindlichkeit = (14232 + 18604) / 2 = 16418 -> 0,2 % neben 16384, passt
const int32_t AZ_OFFSET = -2186;

uint32_t tNext;

// ein Register schreiben
void wr(uint8_t reg, uint8_t val) {
  Wire.beginTransmission(MPU);
  Wire.write(reg);
  Wire.write(val);
  Wire.endTransmission();
}

void setup() {
  Serial.begin(500000);
  Wire.begin();
  Wire.setClock(400000);       // I2C auf 400 kHz, sonst zu langsam fuer 500 Hz

  wr(0x6B, 0x00);   // PWR_MGMT_1: Sensor aufwecken
  wr(0x1A, 0x03);   // CONFIG: Tiefpass 44 Hz -> filtert Rauschen oberhalb unseres Messbereichs
  wr(0x19, 0x01);   // SMPLRT_DIV: interne Rate 1 kHz / (1+1) = 500 Hz
  wr(0x1C, 0x00);   // ACCEL_CONFIG: +/- 2 g  ->  16384 LSB pro g

  Serial.println(F("t_us,ax,ay,az"));
  tNext = micros();
}

void loop() {
  // --- Takt halten: warten bis der naechste Abtastzeitpunkt erreicht ist ---
  tNext += T_US;
  while ((int32_t)(micros() - tNext) < 0) { /* warten */ }

  // --- 6 Bytes ab Register 0x3B lesen: ax, ay, az ---
  Wire.beginTransmission(MPU);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU, (uint8_t)6);

  // WICHTIG: getrennt lesen. (Wire.read()<<8 | Wire.read()) hat in C++
  // keine definierte Auswertungsreihenfolge und liefert vertauschte Bytes.
  int16_t ax = Wire.read(); ax = (ax << 8) | Wire.read();
  int16_t ay = Wire.read(); ay = (ay << 8) | Wire.read();
  int16_t az = Wire.read(); az = (az << 8) | Wire.read();

  // Nullpunkt korrigieren. int32, damit nahe Messbereichsende nichts ueberlaeuft.
  int32_t azk = (int32_t)az - AZ_OFFSET;

  // --- als CSV ausgeben, Rohwerte (Umrechnung in g passiert spaeter in Python) ---
  Serial.print(micros()); Serial.print(',');
  Serial.print(ax);       Serial.print(',');
  Serial.print(ay);       Serial.print(',');
  Serial.println(azk);
}
