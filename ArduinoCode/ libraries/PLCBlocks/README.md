# PLCBlocks

`PLCBlocks` stellt typische SPS-Bausteine für Arduino-kompatible Boards bereit.
Die Klassen werden wie Funktionsbaustein-Instanzen zyklisch in `loop()`
aufgerufen. Enthalten sind Speicher, Flankenerkennung, nichtblockierende Timer,
Zähler, Erstzyklus-Erkennung, Zykluszeit und Taktmerker.

Die Bedienung und Benennung orientieren sich an Siemens TIA Portal und
IEC 61131-3. Die Library ist eine unabhängige Implementierung und weder ein
Siemens-Produkt noch von Siemens geprüft oder freigegeben.

> **Wichtiger Hinweis:** Quellcode, Beispiele und Dokumentation wurden mit
> Unterstützung generativer KI (OpenAI ChatGPT/Codex) erstellt. Die Library
> wurde kompiliert und mit automatisierten Verhaltenstests geprüft, kann aber
> trotzdem Fehler enthalten. Sie ist nicht für ungeprüfte sicherheitskritische
> Anwendungen bestimmt. Weitere Informationen stehen in
> [`NOTICE.md`](NOTICE.md).

## Inhalt

- [Funktionsumfang](#funktionsumfang)
- [Installation](#installation)
- [Schnellstart](#schnellstart)
- [Das FB-Instanzprinzip](#das-fb-instanzprinzip)
- [API-Referenz](#api-referenz)
- [Typische Fehler](#typische-fehler)
- [Unterschiede zu einer Siemens-SPS](#unterschiede-zu-einer-siemens-sps)
- [Kompatibilität und Tests](#kompatibilität-und-tests)
- [Lizenz und KI-Hinweis](#lizenz-und-ki-hinweis)

## Funktionsumfang

| Baustein | Aufgabe | Wichtigstes Ergebnis |
|---|---|---|
| `SR` | Setzen und rücksetzen, Reset dominant | `Q` |
| `RS` | Rücksetzen und setzen, Set dominant | `Q` |
| `P_TRIG` | Positive Flanke erkennen | `Q` für einen oder mehrere Aufrufe |
| `N_TRIG` | Negative Flanke erkennen | `Q` für einen oder mehrere Aufrufe |
| `TON` | Einschaltverzögerung | `Q`, `ET` |
| `TOF` | Ausschaltverzögerung | `Q`, `ET` |
| `TP` | Nicht nachtriggerbarer Impuls | `Q`, `ET` |
| `CTU` | Aufwärts zählen | `Q`, `CV` |
| `CTD` | Abwärts zählen | `Q`, `CV` |
| `CTUD` | Auf- und abwärts zählen | `QU`, `QD`, `CV` |
| `FirstScan` | Ersten Programmdurchlauf erkennen | `Q` |
| `CycleTime` | Zeit zwischen zwei Aufrufen messen | `MS`, `Seconds` |
| `ClockMemory` | Acht Taktmerker erzeugen | `Q0` bis `Q7`, `Value` |

Die Timer verwenden `millis()` und blockieren das Programm nicht. Es wird kein
`delay()` innerhalb der Library aufgerufen.

### Aufrufübersicht

Vor der Verwendung muss für jeden benötigten Baustein eine eigene Instanz
angelegt werden. Die folgende Tabelle zeigt die vollständige Reihenfolge der
Parameter beim Aufruf. Die Kurzschreibweise setzt
`using namespace PLCBlocks;` voraus:

| Baustein | Instanz anlegen | Zyklischer Aufruf | Ausgänge lesen |
|---|---|---|---|
| `SR` | `SR speicher;` | `speicher.process(S, R1);` | `speicher.Q` |
| `RS` | `RS speicher;` | `speicher.process(S1, R);` | `speicher.Q` |
| `P_TRIG` | `P_TRIG flanke;` | `flanke.process(CLK);` | `flanke.Q` |
| `P_TRIG` verlängert | `P_TRIG flanke;` | `flanke.process(CLK, activeCycles);` | `flanke.Q` |
| `N_TRIG` | `N_TRIG flanke;` | `flanke.process(CLK);` | `flanke.Q` |
| `N_TRIG` verlängert | `N_TRIG flanke;` | `flanke.process(CLK, activeCycles);` | `flanke.Q` |
| `TON` | `TON timer(PT);` | `timer.process(IN);` | `timer.Q`, `timer.ET` |
| `TON` mit variablem `PT` | `TON timer;` | `timer.process(IN, PT);` | `timer.Q`, `timer.ET` |
| `TOF` | `TOF timer(PT);` | `timer.process(IN);` | `timer.Q`, `timer.ET` |
| `TOF` mit variablem `PT` | `TOF timer;` | `timer.process(IN, PT);` | `timer.Q`, `timer.ET` |
| `TP` | `TP impuls(PT);` | `impuls.process(IN);` | `impuls.Q`, `impuls.ET` |
| `TP` mit variablem `PT` | `TP impuls;` | `impuls.process(IN, PT);` | `impuls.Q`, `impuls.ET` |
| `CTU` | `CTU zaehler;` | `zaehler.process(CU, R, PV);` | `zaehler.Q`, `zaehler.CV` |
| `CTD` | `CTD zaehler;` | `zaehler.process(CD, LD, PV);` | `zaehler.Q`, `zaehler.CV` |
| `CTUD` | `CTUD zaehler;` | `zaehler.process(CU, CD, R, LD, PV);` | `zaehler.QU`, `zaehler.QD`, `zaehler.CV` |
| `FirstScan` | `FirstScan ersterZyklus;` | `ersterZyklus.process();` | `ersterZyklus.Q` |
| `CycleTime` | `CycleTime zykluszeit;` | `zykluszeit.process();` | `zykluszeit.MS`, `zykluszeit.Seconds` |
| `ClockMemory` | `ClockMemory takt;` | `takt.process();` | `takt.Q0` bis `takt.Q7`, `takt.Value` |

Dabei bedeuten die häufigsten Parameter:

| Parameter | Bedeutung |
|---|---|
| `IN` | Eingangssignal eines Timers |
| `PT` | Vorgegebene Zeit, zum Beispiel `T_SEC(2)` |
| `S` / `S1` | Set-Eingang |
| `R` / `R1` | Reset-Eingang |
| `CLK` | Signal für die Flankenerkennung |
| `activeCycles` | Anzahl der Aufrufe, für die ein Flankenausgang wahr bleibt |
| `CU` / `CD` | Aufwärts- beziehungsweise Abwärtszähleingang |
| `LD` | Vorgabewert in einen Abwärtszähler laden |
| `PV` | Vorgegebener Zählerwert |

## Installation

### Arduino IDE – ZIP-Datei

1. `PLCBlocks-1.0.0.zip` herunterladen.
2. In der Arduino IDE **Sketch > Bibliothek einbinden >
   ZIP-Bibliothek hinzufügen** auswählen.
3. Die ZIP-Datei öffnen.
4. Anschließend **Datei > Beispiele > PLCBlocks > BasicDemo** aufrufen.

### Manuelle Installation

Den vollständigen Ordner `PLCBlocks` in den persönlichen Arduino-Ordner unter
`libraries` kopieren. Danach die Arduino IDE neu starten.

Die Verzeichnisstruktur muss so aussehen:

```text
Arduino/
└── libraries/
    └── PLCBlocks/
        ├── library.properties
        ├── src/
        │   ├── PLCBlocks.h
        │   └── PLCBlocks.cpp
        └── examples/
```

## Schnellstart

Das folgende Beispiel schaltet eine LED zwei Sekunden nach dem Eingang ein:

```cpp
#include <PLCBlocks.h>

constexpr uint8_t INPUT_PIN = 4;
constexpr uint8_t LED_PIN = 2;

PLCBlocks::TON einschaltverzoegerung(PLCBlocks::T_SEC(2));

void setup() {
  pinMode(INPUT_PIN, INPUT_PULLUP);
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  const bool eingang = digitalRead(INPUT_PIN) == LOW;

  einschaltverzoegerung.process(eingang);
  digitalWrite(LED_PIN, einschaltverzoegerung.Q);
}
```

Alternativ kann der Namespace einmal eingebunden werden:

```cpp
using namespace PLCBlocks;

TON timer(T_SEC(2));
```

Bei größeren Projekten ist `PLCBlocks::TON` meist übersichtlicher und schützt
besser vor Namenskonflikten mit anderen Libraries.

## Das FB-Instanzprinzip

Jedes Objekt speichert seinen eigenen Zustand. Zwei unabhängige Verbraucher
benötigen deshalb zwei unabhängige Instanzen:

```cpp
PLCBlocks::TON motor1Delay(PLCBlocks::T_SEC(2));
PLCBlocks::TON motor2Delay(PLCBlocks::T_SEC(5));

void loop() {
  motor1Delay.process(motor1Request);
  motor2Delay.process(motor2Request);
}
```

Instanzen müssen außerhalb von `loop()` oder als `static` angelegt werden.
Andernfalls wird ihr gespeicherter Zustand bei jedem Durchlauf neu erzeugt:

```cpp
// Falsch: Der Timer beginnt in jedem Durchlauf wieder bei null.
void loop() {
  PLCBlocks::TON timer(PLCBlocks::T_SEC(2));
  timer.process(input);
}
```

Eine Instanz sollte in einem SPS-ähnlichen Zyklus genau einmal aufgerufen
werden. Das ist besonders bei Flankenbausteinen und Zählern wichtig.

## API-Referenz

Alle Klassen liegen im Namespace `PLCBlocks`.

### SR – Reset-dominanter Speicher

```cpp
PLCBlocks::SR speicher;
speicher.process(S, R1);
```

| `S` | `R1` | Neues `Q` |
|---:|---:|---:|
| 0 | 0 | vorheriger Zustand |
| 1 | 0 | 1 |
| 0 | 1 | 0 |
| 1 | 1 | 0 – Reset gewinnt |

`reset()` setzt `Q` unabhängig von den Eingängen auf `false`.

### RS – Set-dominanter Speicher

```cpp
PLCBlocks::RS speicher;
speicher.process(S1, R);
```

| `S1` | `R` | Neues `Q` |
|---:|---:|---:|
| 0 | 0 | vorheriger Zustand |
| 1 | 0 | 1 |
| 0 | 1 | 0 |
| 1 | 1 | 1 – Set gewinnt |

Die C++-Methoden verwenden bei beiden Speicherbausteinen die Reihenfolge
**Set-Eingang, Reset-Eingang**. Das ist besonders beim `RS`-Aufruf zu beachten.

### P_TRIG und N_TRIG – Flankenerkennung

```cpp
PLCBlocks::P_TRIG positiveFlanke;
PLCBlocks::N_TRIG negativeFlanke;

positiveFlanke.process(signal);  // false -> true
negativeFlanke.process(signal);  // true -> false
```

Ohne zweite Angabe ist `Q` wie bei einem klassischen Flankenbaustein nur für
den aktuellen `process()`-Aufruf wahr:

```cpp
positiveFlanke.process(signal);  // entspricht activeCycles = 1
```

Optional kann die Flanke auf mehrere Programmzyklen verlängert werden:

```cpp
positiveFlanke.process(signal, 3);  // Q ist für 3 Aufrufe wahr
negativeFlanke.process(signal, 5);  // Q ist für 5 Aufrufe wahr
```

Gezählt werden Aufrufe der jeweiligen Instanz, keine Millisekunden. Deshalb
sollte die Instanz genau einmal pro `loop()`-Durchlauf aufgerufen werden. Der
Zyklus, in dem die Flanke erkannt wird, zählt bereits als erster aktiver Zyklus.
Bei `activeCycles = 0` wird `Q` nicht gesetzt. Eine neue passende Flanke startet
die angegebene Zykluszahl erneut.

`reset()` beendet eine laufende Zyklusverlängerung und setzt `Q` auf `false`,
behält aber den zuletzt gesehenen Eingangszustand. Dadurch entsteht bei einem
unveränderten Eingang keine künstliche neue Flanke.

Mit `reset(false)` oder `reset(true)` kann der intern gespeicherte
Eingangszustand bewusst neu initialisiert werden. Meist sollte zum Abbrechen
einer laufenden Verlängerung nur `reset()` ohne Parameter verwendet werden.

### TON, TOF und TP – Timer

Ein fester Vorgabewert kann im Konstruktor gespeichert werden:

```cpp
PLCBlocks::TON timer(PLCBlocks::T_SEC(2));
timer.process(input);
```

Alternativ kann `PT` bei jedem Aufruf übergeben werden:

```cpp
PLCBlocks::TON timer;
timer.process(input, PLCBlocks::T_MS(500));
```

| Timer | Verhalten |
|---|---|
| `TON` | Bei `IN = true` läuft `ET` hoch. Nach `PT` wird `Q = true`. `IN = false` setzt `Q` und `ET` sofort zurück. |
| `TOF` | Bei `IN = true` ist `Q` sofort wahr. Eine fallende Flanke startet die Ausschaltzeit. Nach `PT` wird `Q = false`. |
| `TP` | Eine positive Flanke erzeugt einen Impuls der Länge `PT`. Änderungen von `IN` verlängern den laufenden Impuls nicht. |

Gemeinsame Ausgänge:

- `Q`: Timer-Ausgang
- `ET`: bisher abgelaufene Zeit in Millisekunden

Besonderheiten:

- Beim `TOF` bleibt `ET` nach Ablauf auf `PT`, bis `IN` wieder wahr wird.
- Beim `TP` läuft der Impuls weiter, wenn `IN` vor Ablauf wieder falsch wird.
- `PT = 0` schaltet einen `TON` sofort durch, beendet einen `TOF` sofort und
  erzeugt beim `TP` keinen Impuls.
- `reset()` beendet den Timer und setzt `Q` und `ET` auf null.
- `setPT(...)` ändert den gespeicherten Vorgabewert; `preset()` liest ihn aus.

Für Tests oder eine kontrollierte eigene Millisekunden-Zeitquelle steht
`processAt(IN, PT, now)` zur Verfügung. Im normalen Sketch sollte
`process(...)` verwendet werden.

Die Zeitdifferenzen werden über vorzeichenlose Subtraktion bestimmt und
sättigend aufsummiert. Dadurch wird ein normaler `millis()`-Überlauf korrekt
behandelt. Eine laufende Instanz muss dafür mindestens einmal innerhalb von
rund 49,7 Tagen aufgerufen werden.

### CTU – Aufwärtszähler

```cpp
PLCBlocks::CTU zaehler;
zaehler.process(CU, R, PV);
```

- Eine positive Flanke an `CU` erhöht `CV` um eins.
- `R = true` setzt `CV` auf null und hat Vorrang vor `CU`.
- `Q` ist wahr, wenn `CV >= PV`.
- Bei `INT32_MAX` wird nicht weitergezählt.

### CTD – Abwärtszähler

```cpp
PLCBlocks::CTD zaehler;
zaehler.process(CD, LD, PV);
```

- `LD = true` lädt `PV` nach `CV` und hat Vorrang vor `CD`.
- Eine positive Flanke an `CD` verringert `CV` um eins.
- `Q` ist wahr, wenn `CV <= 0`.
- Bei `INT32_MIN` wird nicht weitergezählt.

Da `CV` anfangs null ist, startet `CTD.Q` mit `true`. Vor dem Herunterzählen
sollte der Vorgabewert deshalb einmal mit `LD = true` geladen werden.

### CTUD – Auf-/Abwärtszähler

```cpp
PLCBlocks::CTUD zaehler;
zaehler.process(CU, CD, R, LD, PV);
```

- `CU` zählt auf einer positiven Flanke hoch.
- `CD` zählt auf einer positiven Flanke herunter.
- Bei gleichzeitigen positiven Flanken bleibt `CV` unverändert.
- Die Priorität lautet `R` vor `LD` vor Zählen.
- `QU` ist wahr, wenn `CV >= PV`.
- `QD` ist wahr, wenn `CV <= 0`.

### FirstScan – erster Programmdurchlauf

```cpp
PLCBlocks::FirstScan firstScan;

void loop() {
  firstScan.process();
  if (firstScan.Q) {
    // Nur beim ersten Aufruf
  }
}
```

`reset()` sorgt dafür, dass der nächste `process()`-Aufruf erneut als erster
Aufruf behandelt wird.

### CycleTime – Zeit zwischen zwei Aufrufen

```cpp
PLCBlocks::CycleTime cycleTime;

void loop() {
  cycleTime.process();
  // cycleTime.MS
  // cycleTime.Seconds
}
```

Beim ersten Aufruf sind `MS` und `Seconds` null. Danach enthalten sie den
Abstand zum jeweils vorherigen Aufruf. `processAt(now)` und `resetAt(now)` sind
für Tests mit einer vorgegebenen Zeitquelle vorgesehen.

### ClockMemory – Taktmerkerbyte

```cpp
PLCBlocks::ClockMemory clockMemory;

void loop() {
  clockMemory.process();
  digitalWrite(LED_BUILTIN, clockMemory.Q5);
}
```

| Ausgang | Periodendauer | Frequenz |
|---|---:|---:|
| `Q0` | 100 ms | 10 Hz |
| `Q1` | 200 ms | 5 Hz |
| `Q2` | 400 ms | 2,5 Hz |
| `Q3` | 500 ms | 2 Hz |
| `Q4` | 800 ms | 1,25 Hz |
| `Q5` | 1000 ms | 1 Hz |
| `Q6` | 1600 ms | 0,625 Hz |
| `Q7` | 2000 ms | 0,5 Hz |

`Value` enthält alle acht Zustände als Byte. Mit `getBit(0)` bis `getBit(7)`
kann ein einzelner Zustand über seinen Index gelesen werden. Ein ungültiger
Index liefert `false`.

Nach dem ersten Aufruf oder nach `reset()` beginnen alle Bits mit `false`.
Die Ausgänge ändern sich nur, wenn `process()` aufgerufen wird; Arduino stellt
hier keinen unabhängig laufenden SPS-Systemmerker bereit.

### Zeithelfer

```cpp
PLCBlocks::T_MS(250)    // 250 ms
PLCBlocks::T_SEC(5)     // 5 s
PLCBlocks::T_MIN(2)     // 2 min
PLCBlocks::T_HOUR(1)    // 1 h
```

Alle Helfer liefern Millisekunden als `uint32_t`. Ergebnisse oberhalb von
`UINT32_MAX` werden auf `UINT32_MAX` begrenzt.

## Typische Fehler

### Zuweisung statt Übergabe

```cpp
// Falsch: überschreibt latch.Q und übergibt anschließend false.
delayTimer.process(latch.Q = false);

// Richtig: aktuellen Zustand übergeben.
delayTimer.process(latch.Q);

// Richtig: invertierten Zustand übergeben.
delayTimer.process(!latch.Q);
```

Die öffentlichen Ausgänge `Q`, `ET`, `CV`, `QU` und `QD` sollten nur gelesen
werden. Zum definierten Zurücksetzen dient die jeweilige `reset()`-Methode.

### Instanz innerhalb von loop()

Ein lokal ohne `static` angelegter Baustein verliert bei jedem Durchlauf seinen
Zustand. Timer, Flanken und Zähler deshalb global oder statisch anlegen.

### Mehrfacher Aufruf derselben Instanz

Mehrere Aufrufe im selben Programmdurchlauf verändern den internen Zustand
mehrfach. Eine Instanz nach Möglichkeit genau einmal pro Zyklus aufrufen und
anschließend ihre Ausgänge verwenden.

### Blockierende Gerätefunktionen

Die Library selbst blockiert nicht. Lange `delay()`-Aufrufe oder blockierende
Display-, LED- oder IR-Funktionen im eigenen Programm vergrößern aber die
Zykluszeit und verzögern dadurch Flankenerkennung und Ausgangsaktualisierung.

### Mehrere ESP32-Tasks oder CPU-Kerne

Die Instanzen sind nicht threadsicher. Dieselbe Instanz nicht gleichzeitig aus
mehreren FreeRTOS-Tasks, Interrupts oder CPU-Kernen aufrufen.

## Unterschiede zu einer Siemens-SPS

- Arduino besitzt keine Organisationsbausteine, Instanz-Datenbausteine oder
  garantierte SPS-Zykluszeit.
- `FirstScan`, `CycleTime` und `ClockMemory` müssen ausdrücklich aufgerufen
  werden.
- Ausgänge werden nur bei einem Methodenaufruf aktualisiert.
- Zustände sind ohne zusätzliche Speicherung nach Neustart oder Stromausfall
  nicht remanent.
- Zähler verwenden fest `int32_t`, entsprechend einem vorzeichenbehafteten
  32-Bit-Wert.
- Die Bausteine sind nicht sicherheitszertifiziert und ersetzen keine
  Sicherheits-SPS.

## Kompatibilität und Tests

Die Library benötigt nur `Arduino.h`, `millis()` und Standard-C++11.

Geprüfter Stand von Version `1.0.0`:

| Ziel | Ergebnis |
|---|---|
| ESP32 Dev Module, Arduino Framework | Erfolgreich kompiliert und gelinkt |
| Arduino Uno / ATmega328P | Erfolgreich kompiliert und gelinkt |
| Native C++-Verhaltenstests | Erfolgreich, einschließlich `millis()`-Überlauf |

Getestet wurden unter anderem Dominanzen, Flanken, Timerabbrüche, `PT = 0`,
Zählerprioritäten, Wertebegrenzungen, FirstScan, CycleTime und ClockMemory.

## Projektstruktur

```text
PLCBlocks/
├── library.properties
├── keywords.txt
├── CHANGELOG.md
├── LICENSE
├── NOTICE.md
├── README.md
├── src/
│   ├── PLCBlocks.h
│   └── PLCBlocks.cpp
└── examples/
    └── BasicDemo/
        └── BasicDemo.ino
```

Für eine Veröffentlichung im Arduino Library Manager muss diese Struktur im
Stammverzeichnis des öffentlichen Git-Repositorys liegen. Releases benötigen
eine zur Version in `library.properties` passende Git-Markierung.

## Lizenz und KI-Hinweis

Das Projekt wird unter der [Unlicense](LICENSE) soweit rechtlich möglich der
Gemeinfreiheit übergeben und ohne Gewährleistung bereitgestellt.

Der Herkunftshinweis in [`NOTICE.md`](NOTICE.md) dokumentiert die Unterstützung
durch generative KI. Er fügt der Unlicense keine zusätzliche Bedingung hinzu.
