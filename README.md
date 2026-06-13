# Arduino Fahrwerk Simulator

Simulation eines aktiven Dämpfersystems mit PID-Regler.
Gebaut mit Elegoo Uno R3, HC-SR04 Ultraschallsensor und SG90 Servo.

## Idee
Ein Ultraschallsensor misst den Abstand zu einem Objekt (= Straßenunebenheit).
Ein PID-Regler berechnet die optimale Reaktion.
Ein Servo stellt die Dämpfung in Echtzeit ein.

Sensor → Verarbeitung → Aktuator

Das ist das gleiche Grundprinzip wie bei Mercedes Magic Body Control —
nur mit zugänglicher Hardware nachgebaut.

## Hardware
- Elegoo Uno R3
- HC-SR04 Ultraschallsensor
- SG90 Servo Motor
- Breadboard + Jumperkabel

## Was ich dabei gelernt habe
- Sensor-Aktuator Regelkreise
- PID-Regler Theorie und praktisches Tuning
- Dämpfungsverhalten und dessen Auswirkung auf Systemstabilität

## Hintergrund
Ich studiere Fahrzeugentwicklung an der TH Köln (2. Semester)
und entwickle langfristig intelligente, regenerative Fahrwerksysteme.
Dieses Projekt ist der erste praktische Schritt in diese Richtung.
