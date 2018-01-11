#define DEBUG true
#define DEBUG_SERIAL Serial
#define BLUETOOTH true
#define BLUETOOTH_SERIAL Serial3

#define START_MARKER '<'
#define END_MARKER '>'

// Befehle für serielle Kommunikation (NICHT VERÄNDERN):
#define debug(_str_); if(DEBUG){Serial.print(_str_);}
#define debugln(_str_); if(DEBUG){Serial.println(_str_);}
#define bluetooth(_str_); Serial3.print(START_MARKER);Serial3.print(_str_);Serial3.print(END_MARKER);
// ---

#define LED 13
#define BUTTON A0

String message = "";
String command = "";
bool isButton = false;
bool lastButton = false;
bool isReceiving = false;

void setup() {
  pinMode(LED, OUTPUT);
  pinMode(BUTTON, INPUT_PULLUP);
  Serial.begin(9600);
  debugln("RESTART");
  Serial3.begin(38400);
  bluetooth("IR:available");
}
void loop() {
  isButton = !digitalRead(BUTTON);
  if (isButton != lastButton) {
    if (isButton) {
      bluetooth("IR:on");
    } else {
      bluetooth("IR:off");
    }
  }
  command = receiveBluetooth();
  if (command != "") {
    debugln(command);
    if (command == "IR:on") {
      analogWrite(LED, 250);
    } else if (command == "IR:off") {
      analogWrite(LED, 0);
    }
  }
  lastButton = isButton;
  delay(1);
}

String receiveBluetooth() {
  char c;
  while (Serial3.available() > 0) {
    c = Serial3.read();
    debugln(c);
    if (isReceiving) {
      if (c == START_MARKER) {
        message = "";
      } else if (c == END_MARKER) {
        isReceiving = false;
        return (message);
      } else {
        message += c;
        debugln("mes=" + (String)message);
      }
    } else {
      if (c == START_MARKER) {
        message = "";
        isReceiving = true;
      }
    }
    return ("");
  }
}

  }
  return ("");
}

