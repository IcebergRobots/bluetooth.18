# Bluetooth-Kommunikation zwischen zwei Arduino Mega

Für Modul mit den Anschlüssen:

EN  VCC GND TXD RXD STATE


## 1. Bluetooth Modul konfigurieren

### 1. Leeres Programm auf den Arduino hochladen

```c++
void setup() {}
void loop() {}
```

### 2. Arduino vom Strom entfernen.
### 3. Arduino wie folgt verbinden:

|Arduino|BM (BlueoothModul)|
|:-----:|:-----:|
|5V|VCC|
|GND|GND|
|TX0|TXD|
|RX0|RXD|

### 4. Konfigurationsmodus des BM aktivieren

* Man betrachtet das BM mit der Antenne nach oben.
* An den obersten rechten Pin (Pin 34) des BM eine Krokodilklemme oder ein Kabel abschließen.
* Dieses über einen Taster an 3.3V des Arduinos anschließen.

|Arduino|Taster|BM (BlueoothModul)|
|:-----:|:-----:|:-----:|
|3.3V|↔|Pin 34|

### 5. Komandozeile aufbauen

* Taster gedrückt halten und Arduino an den Computer anschließen
* Wenn die rote LED am BM leuchtet, Taster loslassen
* Seriellen Monitor in der Arduino IDE öffnen
* `Sowohl NL als auch CR` auswählen
* `38400 Baus` auswählen
* `AT` 2mal senden
* Wenn spätenstens mein 2. Mal OK zurückkommt, ist die Kommunikation erfolgreich.

### 6. SLAVE konfigurieren

|Beschreibung|Befehl|erwartete<br>Rückgabe|
|:-----|:-----|:-----|
|Test|at|OK|
|Auf Standardwerte zurücksetzen|at+orgl|OK|
|Baudrate überprüfen|at+uart?|+UART:38400,0,0<br>OK|
|Ist die Baudrate verschieden,<br>diese korrigieren|at+uart=38400,0,0|OK|
|Modul-Addresse erfragen|at+addr?|+ADDR:????:??:??????<br>OK|

Diese Addresse notieren.

### 7. MASTER konfigurieren

|Beschreibung|Befehl|erwartete<br>Rückgabe|
|:-----|:-----|:-----|
|Test|at|OK|
|Auf Standardwerte zurücksetzen|at+orgl|OK|
|Baudrate überprüfen|at+uart?|+UART:38400,0,0<br>OK|
|Ist die Baudrate verschieden,<br>diese korrigieren|at+uart=38400,0,0|OK|
|Master Modus<br>aktivieren|at+role=1|OK|
|Verbindungsmodus auf<br>addressenspeziefisch setzen|at+cmode=0|OK|
|Slave-Addresse einstellen|at+bind=????,??,??????|OK|

Achtung: Beim einsetzen der Slave-Addresse Kommata statt Punkten verwenden!

[weitere Befehle](http://www.linotux.ch/arduino/HC-0305_serial_module_AT_commamd_set_201104_revised.pdf)

### 8. Fertig

Wenn beide Module eingeschalten sind sollten sie nach wenigen Sekunden 2mal hintereinander in zwei Sekunden rot und blau blinken.