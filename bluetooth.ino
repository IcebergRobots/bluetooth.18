#define DEBUG true
#define debug(_str_); if(DEBUG){Serial.print(_str_);}
#define debugln(_str_); if(DEBUG){Serial.println(_str_);}

#define LED 13
#define BUTTON A8

String bluetooth;
enum ROLE {MASTER, SLAVE};
ROLE r;
bool isLed = false;
bool gotMes = false;
unsigned long lastMes = 0;

void setup() {
  r = MASTER;   //==============================================00
  pinMode(LED, OUTPUT);
  pinMode(BUTTON, INPUT_PULLUP);
  Serial.begin(9600);
  if (r == MASTER) {
    debugln("RESTART as MASTER");
  } else {
    debugln("RESTART as SLAVE");
  }
  Serial3.begin(38400);
  Serial3.println("IR:available");
}
void loop() {
  analogWrite(LED, 200 * !digitalRead(BUTTON));
  switch (r)
  {
    case MASTER:
      if (millis() - lastMes > 3000) {
        lastMes = millis();
        analogWrite(LED, 100);
        delay(10);
        analogWrite(LED, 0);
        if (isLed) {
          char mes[] = "42";
          debugln("sent: " + (String)mes);
          Serial3.print(mes);
        } else {
          char mes[] = "IR:on";
          debugln("sent: " + (String)mes);
          Serial3.write(mes);
        }
        isLed = !isLed;
      }
      delay(100);
      break;
    case SLAVE:
      if (Serial3.available() > 0) {
        gotMes = true;
        bluetooth = Serial3.readString();
        Serial.print((String)bluetooth+" ");
        /*if (bluetooth == "IR:on") {
          digitalWrite(LED, 1);
          Serial3.println("turned on");
        } else if (bluetooth == "IR:off") {
          digitalWrite(LED, 0);
          Serial3.println("turned off");
        }*/
      } else {
        if(gotMes) {
          Serial.println();
        }
        gotMes = false;
      }
      delay(20);
      break;
    default: break;
  }
}
