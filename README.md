# Fahrwerk-Simulator

Ein selbstgebauter Versuchsaufbau, der eine Fahrbahnanregung erzeugt, die Systemantwort misst und daraus den Fahrbahnzustand klassifiziert. Entstanden als Eigenprojekt neben dem Studium (Fahrzeugentwicklung B.Eng., TH Köln).

<!-- Foto hier einfügen: ![Aufbau](docs/aufbau.jpg) -->

---

## Worum es geht

Ein Fahrwerk ist im Kern eine Regelstrecke: Ein Sensor misst eine Störgröße, ein Regler verarbeitet sie, ein Aktor reagiert. Ich wollte diese Kette einmal vollständig selbst aufbauen — vom Rohsignal bis zur ausgewerteten Messreihe — statt nur darüber zu lesen.

Der Aufbau ist bewusst einfach gehalten. Es geht nicht um ein realistisches Fahrwerksmodell, sondern darum, die Signalkette zu verstehen und sauber zu implementieren.

---

## Aktueller Stand

**Phase 1 — abgeschlossen**

- Abstandsmessung mit Ultraschallsensor (HC-SR04)
- Signalglättung über gleitenden Mittelwert
- PID-Regler mit definierter Abtastzeit, Ansteuerung eines Servos (SG90)
- Aufzeichnung der Messwerte als CSV über die serielle Schnittstelle
- Auswertung in Python: Klassifikation des Fahrbahnzustands (glatt / Welle / Schlagloch) mit einem Entscheidungsbaum, **91,2 % Trefferquote** auf chronologisch getrennten Testdaten

**Phase 2 — in Arbeit**

Umbau zu einem Ein-Freiheitsgrad-Viertelfahrzeug-Aufbau:

- Wegmessung über Time-of-Flight-Sensoren (VL53L1X) statt Ultraschall
- Beschleunigungsmessung am Aufbau (MPU-6050)
- Basispunktanregung über Schrittmotor (NEMA 17, A4988)
- Erfassung der rückgewonnenen elektrischen Leistung über einen rückgetriebenen DC-Motor (INA219)

---

## Aufbau der Signalkette

```
Sensor  →  Filterung  →  Regler  →  Aktor
   ↓
 Logging (CSV)  →  Auswertung (Python)  →  Klassifikation
```

---

## Verwendete Hardware

| Komponente | Typ | Funktion |
|---|---|---|
| Mikrocontroller | Arduino Uno R3 | Regelung, Datenerfassung |
| Abstandssensor | HC-SR04 | Phase 1 |
| Abstandssensor | VL53L1X (ToF) | Phase 2 |
| Beschleunigungssensor | MPU-6050 | Phase 2 |
| Aktor | SG90 Servo | Phase 1 |
| Anregung | NEMA 17 + A4988 | Phase 2 |
| Strommessung | INA219 | Phase 2 |

---

## Repository

<!-- Diese Struktur an dein Repo anpassen -->

src/fahrwerk_pid.ino     Arduino-Sketch (C++): Sensorauslesung, Filterung, PID-Regler
fahrwerk_ml.py           Auswertung und Klassifikation (Python, scikit-learn)
daten.csv                Aufgezeichnete Messreihe
docs/                    Fotos und Notizen

---

## Was ich dabei gelernt habe

- **Abtastzeit ist keine Nebensache.** Ein PID-Regler ohne definierte Abtastzeit liefert je nach Schleifenlaufzeit unterschiedliche Ergebnisse. Das war der Punkt, an dem der erste Aufbau nicht reproduzierbar war.
- **Filterung kostet Phase.** Ein gleitender Mittelwert glättet das Signal, verzögert es aber auch — und diese Verzögerung wirkt direkt im Regelkreis.
- **Die Sensorwahl begrenzt das Messbare.** Der Ultraschallsensor ist für langsame Bewegungen ausreichend, für schnellere Vorgänge nicht. Das war der Grund für den Wechsel auf ToF-Sensorik.
- **Zufälliges Mischen verfälscht die Bewertung.** Bei Messreihen sind aufeinanderfolgende Samples stark korreliert. Ein zufälliger Train-Test-Split lässt das Modell Werte "sehen", die es schon kennt, und überschätzt die Genauigkeit. Ich trenne stattdessen chronologisch je Klasse.

---

## Grenzen des Aufbaus

Der Aufbau ist ein Lernprojekt, kein Prüfstand im technischen Sinne:

- Der Arduino Uno ist keine Echtzeitplattform. Die Schleifenlaufzeit schwankt, was die erreichbare Regelgüte begrenzt.
- Die verwendeten Aktoren sind für dynamische Regelung im relevanten Frequenzbereich zu langsam.
- Die Messwerte sind nicht kalibriert und daher nicht absolut belastbar.

Diese Punkte sind bekannt und bewusst in Kauf genommen — es geht um die Methode, nicht um die absolute Genauigkeit.

---

## Nächste Schritte

- Aufbau der Mechanik (Masse, Feder, Linearführung)
- Auslegung von Eigenfrequenz und Anregungsbereich
- Portierung auf eine echtzeitfähige Plattform (STM32 oder Teensy)
- Erweiterung der Auswertung um Sprungantwort und Frequenzgang

---

**Nico Düsterhus** · Fahrzeugentwicklung B.Eng., TH Köln
