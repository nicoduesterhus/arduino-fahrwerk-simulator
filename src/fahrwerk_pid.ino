#include <Servo.h>

Servo daempfer;

const int trigPin = 9;
const int echoPin = 10;

// PID Parameter - hier experimentieren
float kP = 2.0;
float kI = 0.01;
float kD = 1.0;

float fehler = 0;
float letzterFehler = 0;
float integral = 0;
float ableitung = 0;

int aktuellerWinkel = 90;

void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  daempfer.attach(6);
  daempfer.write(90);
}

void loop() {
  // Abstand messen
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long dauer = pulseIn(echoPin, HIGH);
  long abstand = dauer * 0.034 / 2;
  abstand = constrain(abstand, 2, 30);

  // Zielwinkel berechnen
  int zielWinkel = map(abstand, 2, 30, 0, 180);

  // PID berechnen
  fehler = zielWinkel - aktuellerWinkel;
  integral = integral + fehler;
  ableitung = fehler - letzterFehler;

  float korrektur = (kP * fehler) + (kI * integral) + (kD * ableitung);

  aktuellerWinkel = aktuellerWinkel + korrektur;
  aktuellerWinkel = constrain(aktuellerWinkel, 0, 180);

  letzterFehler = fehler;

  daempfer.write(aktuellerWinkel);

  Serial.print("Ziel: ");
  Serial.print(zielWinkel);
  Serial.print("°  Aktuell: ");
  Serial.print(aktuellerWinkel);
  Serial.print("°  Fehler: ");
  Serial.println(fehler);

  delay(20);
}
