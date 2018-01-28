#include <sbus.h>
#include <Servo.h>

//swAは下が2070上が970
//swHは下が970上が2070
// used pins
#define SBUS_PIN  2
#define FET1      3
#define FET2      4
#define FET3      5
#define FET4      8
#define SERVO1    6
#define SERVO2    9
#define SERVO3    10
#define LED       7
#define PSW       13

SBUS sbus;
Servo servo1;
Servo servo2;
Servo servo3;

uint16_t CH[19] = {0};//そのまま配列番号がCH番号
//なので
void updateSBUS(void) {
  if (!sbus.waitFrame()) {
    Serial.println("Timeout!");
  }
  else {
    if (sbus.signalLossActive()){}
    if (sbus.failsafeActive()){}
    
    for (int i = 1; i <= 18; ++i) {
      CH[i] = sbus.getChannel(i);
      Serial.print(CH[i]);
    }
    Serial.println("");
  }
}

void setup() {
  pinMode(FET1, OUTPUT);
  pinMode(FET2, OUTPUT);
  pinMode(FET3, OUTPUT);
  pinMode(FET4, OUTPUT);
  pinMode(LED,  OUTPUT);
  pinMode(PSW,  INPUT_PULLUP);
  sbus.begin(SBUS_PIN, sbusBlocking);
  servo1.attach(SERVO1);
  servo2.attach(SERVO2);
  servo3.attach(SERVO3);
  servo1.write(0);
  servo2.write(0);
  servo3.write(0);
  Serial.begin(115200);
}

void loop() {
  updateSBUS();
  if ( (CH[5] > 1300) && (CH[6] < 1300) || !digitalRead(PSW)){
    digitalWrite(FET1,HIGH);
    digitalWrite(LED,HIGH);
    servo1.write(30);
    servo2.write(30);
    servo3.write(30);
  }
  else{
    digitalWrite(FET1,LOW);
    digitalWrite(LED,LOW);
    servo1.write(180);
    servo2.write(180);
    servo3.write(180);
  }
}

