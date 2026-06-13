# Fahrwerk Simulator & Entwicklungsprojekt

Dieses Repository dokumentiert den Aufbau eines intelligenten,
regenerativen Fahrwerksystems — von ersten Arduino-Prototypen
bis zum späteren physischen Demonstrator.

## Vision

Ziel ist die Entwicklung eines aktiven Fahrwerksystems das drei
Dinge vereint die bisher niemand zusammen gelöst hat:

- **Prädiktive Sensorik** — erkennt Straßenunebenheiten bevor
  das Rad drüber fährt
- **KI-gestützte Regelung** — passt Dämpfung in Echtzeit
  automatisch an die Situation an
- **Energierekuperation** — gewinnt Energie aus jeder Dämpfung
  zurück statt sie als Wärme zu verlieren

Und das zu einem Bruchteil der Kosten bestehender Systeme —
damit nicht nur S-Klassen sondern alle Fahrzeuge davon profitieren.
Langfristig auch für Züge, Flugzeuge und Weltraum-Rover.

## Aktueller Stand

### Fertig
- HC-SR04 Ultraschallsensor + SG90 Servo Regelkreis
- PID-Regler mit manuellem Tuning
- Gleitender Mittelwert zur Signalglättung
- Automatisches Daten-Logging (CSV)
- Machine Learning Modell (Decision Tree, 88% Genauigkeit)
  erkennt Fahrsituationen: glatt / welle / schlagloch

### In Arbeit
- Zweiter Sensor für prädiktive Vorausschau
- DC-Motor als Generator für Rekuperation
- Energiemessung mit INA219

### Geplant
- CAD Gehäuse (Fusion 360)
- Physischer 1:5 Prototyp mit echter Feder
- Raspberry Pi + Kamera für Bildverarbeitung
- Vollständiger KI-gesteuerter Demonstrator

## Hardware

| Bauteil | Status |
|---|---|
| Elegoo Uno R3 | vorhanden |
| HC-SR04 Ultraschallsensor | vorhanden |
| SG90 Servo | vorhanden |
| NEMA 17 Schrittmotor | vorhanden |
| A4988 Motortreiber | bestellt |
| 2x HC-SR04 (prädiktiv) | bestellt |
| N20 DC-Motor (Generator) | bestellt |
| INA219 Stromsensor | bestellt |

## Hintergrund

Ich studiere Fahrzeugentwicklung an der TH Köln (2. Semester)
mit dem langfristigen Ziel eine eigene Firma zu gründen die
intelligente regenerative Fahrwerksysteme entwickelt und baut.

Dieses Projekt ist der erste praktische Schritt.

Entwicklungsbeginn: Juni 2026
