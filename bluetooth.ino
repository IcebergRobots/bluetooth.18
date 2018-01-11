#define DEBUG true
#define debug(_str_); if(DEBUG){Serial.print(_str_);}
#define debugln(_str_); if(DEBUG){Serial.println(_str_);}

#define LED 13
#define BUTTON A8

String bluetooth;
enum ROLE {MASTER, SLAVE};
ROLE r;
bool isLed = false;
unsigned long lastMes = 0;

void setup() {
  r = MASTER;
  pinMode(LED, OUTPUT);
  pinMode(BUTTON, INPUT_PULLUP);
  Serial.begin(9600);
  if (r == MASTER) {
    debugln("RESTART as MASTER");
  } else {
    debugln("RESTART as SLAVE");
  }
  Serial3.begin(9600);
  Serial3.println("IR:available");
}
void loop() {
  analogWrite(LED,200*!digitalRead(BUTTON));
  switch (r)
  {
    case MASTER:
      if (millis() - lastMes > 1000) {
        lastMes = millis();
        if (isLed) {
          delay(10);
          debugln("sent: off");
          Serial3.println("IR:off");
        } else {
          debugln("sent: on");
          Serial3.println("IR:on");
        }
        isLed = !isLed;
      }
      break;
    case SLAVE:
      if (Serial3.available() > 0) {
        bluetooth = Serial3.read();
        debugln(bluetooth);
        if (bluetooth == "IR:on") {
          digitalWrite(LED, 1);
          Serial3.println("turned on");
        } else if (bluetooth == "IR:off") {
          digitalWrite(LED, 0);
          Serial3.println("turned off");
        }
      }
      break;
    default: break;
  }

  delay(100);
}
