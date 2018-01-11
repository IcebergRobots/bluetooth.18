#define DEBUG true
#define debug(_str_); if(DEBUG){Serial.print(_str_);}
#define debugln(_str_); if(DEBUG){Serial.println(_str_);}

#define SEND true
#define LED 13
#define BUTTON A0

String bluetooth;
unsigned long lastMes = 0;
bool isButton = false;
bool lastButton = false;

void setup() {
  pinMode(LED, OUTPUT);
  pinMode(BUTTON, INPUT_PULLUP);
  Serial.begin(9600);
  debugln("RESTART");
  Serial3.begin(38400);
  Serial3.println("IR:available");
}
void loop() {
  isButton = !digitalRead(BUTTON);
  if (isButton != lastButton) {
    if (isButton) {
      Serial3.write("<set led on>");
    } else {
      Serial3.print("<set led off>");
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
