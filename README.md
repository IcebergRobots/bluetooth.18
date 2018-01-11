# Bluetooth-Kommunikation zwischen zwei Arduino Mega

Für Modul mit den Anschlüssen:

EN  VCC GND TXD RXD STATE


## 1. Bluetooth Modul konfigurieren

1. Leeres Programm auf den Arduino hochladen

```c++
void setup() {}
void loop() {}
```

2. Arduino vom Strom entfernen.
3. Arduino wie folgt verbinden:

|Arduino|BM (BlueoothModul)|
|:-----:|:-----:|
|5V|VCC|
|GND|GND|
|TX0|TXD|
|RX0|RXD|

4. Konfigurationsmodus des BM aktivieren

* Man betrachtet das BM mit der Antenne nach oben.
* An den obersten rechten Pin (Pin 34) des BM eine Krokodilklemme oder ein Kabel abschließen.
* Dieses über einen Taster an 3.3V des Arduinos anschließen.

|Arduino|Taster|BM (BlueoothModul)|
|:-----:|:-----:|:-----:|
|3.3V|↔|Pin 34|

5. Komandozeile aufbauen

* Taster gedrückt halten und Arduino an den Computer anschließen
* Wenn die rote LED am BM leuchtet, Taster loslassen
* Seriellen Monitor in der Arduino IDE öffnen
* `Sowohl NL als auch CR` auswählen
* `38400 Baus` auswählen
* `AT` 2mal senden
* Wenn spätenstens mein 2. Mal OK zurückkommt, ist die Kommunikation erfolgreich.

  
|Beschreibung|Befehl|Rückgabe|Parameter|
|:-----:|:-----:|:-----:|:-----|
|Test|AT|OK|None|
|Zurücksetzen|AT+RESET|OK|None|
|Softwareversion erfragen|AT+VERSION?|+VERSION:[Param]<br>OK|Param: Version number|
|Standardwerte|AT+ORGL|OK|Standardwerte:<br>Device type: 0<br>Inquire code: 0x009e8b33<br>Module work mode: Slave Mode<br>Connection mode: Connect to the Bluetooth device specified<br>Serial parameter: Baud rate: 38400 bits/s; Stop bit: 1 bit; Parity bit: None<br>Passkey: “1234”<br>Device name: “H-C-2010-06-01” |
|Bluetooth-Adresse erfragen|AT+ADDR?|+ADDR:[Param]<br>OK|Param: Bluetooth address|
|Modul-Modus setzen|AT+ROLE=[Param]|OK|
|Modul-Modus setzen|AT+ROLE?|+ROLE:[Param]<br>OK|Slave role: 0 (standard)<br>Master role: 1<br>Slave-Loop role: 2|

[weitere Befehle](http://www.linotux.ch/arduino/HC-0305_serial_module_AT_commamd_set_201104_revised.pdf)
