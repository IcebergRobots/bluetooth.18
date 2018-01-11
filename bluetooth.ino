#define DEBUG true
#define debug(_str_); if(DEBUG){Serial.print(_str_);}
#define debugln(_str_); if(DEBUG){Serial.println(_str_);}

#define LED 13
#define BUTTON A8

String bluetooth;
enum ROLE {MASTER, SLAVE};
ROLE r;
unsigned long lastMes = 0;
bool isLed = false;

void setup() {
  r = SLAVE;   //==============================================00
  Serial.begin(9600);
  switch (r)
  {
    case MASTER:
      debugln("RESTART as MASTER");
      Serial3.begin(38400);
      Serial3.println("IR:available");
      break;
    case SLAVE:
      debugln("RESTART as SLAVE");
      Serial3.begin(9600);
      break;
    default: break;
  }
}
void loop() {
  switch (r)
  {
    case MASTER:
      if (millis() - lastMes > 2000) {
        lastMes = millis();
        analogWrite(LED, 200);
        delay(10);
        analogWrite(LED, 0);
        if (isLed) {
          char mes[] = "42";
          Serial3.print(mes);
        } else {
          Serial3.print("IR:on");
        }
        isLed = !isLed;
      }
      delay(100);
      break;
    case SLAVE:
      if (Serial3.available() > 0) {
        bluetooth = Serial3.readString();
        Serial.println(bluetooth);
      }
      break;
    default: break;
  }
}
