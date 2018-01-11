#define DEBUG true
#define DEBUG_SERIAL Serial
#define BLUETOOTH true
#define BLUETOOTH_SERIAL Serial3

#define START_MARKER '<'
#define END_MARKER '>'

// Befehle für serielle Kommunikation (NICHT VERÄNDERN):
#define debug(_str_); if(DEBUG){DEBUG_SERIAL.print(_str_);}
#define debugln(_str_); if(DEBUG){DEBUG_SERIAL.println(_str_);}
#define bluetooth(_str_); if(BLUETOOTH){BLUETOOTH_SERIAL.print(START_MARKER);BLUETOOTH_SERIAL.print(_str_);BLUETOOTH_SERIAL.print(END_MARKER);}
// ---

#define LED 13
#define BUTTON A0

String bluetooth;
bool isButton = false;
bool lastButton = false;

void setup() {
  pinMode(LED, OUTPUT);
  pinMode(BUTTON, INPUT_PULLUP);
  DEBUG_SERIAL.begin(9600);
  debugln("RESTART");
  BLUETOOTH_SERIAL.begin(38400);
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
  if (Serial3.available() > 0) {
    bluetooth = Serial3.readString();
    debugln(bluetooth);
    if (bluetooth == "<set led on>") {
      analogWrite(LED, 250);
    } else if (bluetooth == "<set led off>") {
      analogWrite(LED, 0);
    }
  }
  lastButton = isButton;
}

