#include <IRremote.h>
#define P1 8
#define P2 9
#define P3 10
#define P4 11

IRrecv irrecv(2);
decode_results signals;
void setup() {
  pinMode (P1, OUTPUT);
  pinMode (P2, OUTPUT);
  pinMode (P3, OUTPUT);
  pinMode (P4, OUTPUT);
  Serial.begin(9600);
  irrecv.enableIRIn();
}
bool on = false;
bool isup = false;
int speed = 2;
void loop() {
  if (irrecv.decode(&signals)) {
    Serial.println(signals.value, HEX);
    if (signals.value == 0xE85952E1){
      isup = true;
      on = true;
      speed = 2;
    }else if (signals.value == 0x78CDA4DD){
      isup = false;
      on = true;
      speed = 2;
    }else if (signals.value == 0xA2672345){
      on = false;
    }
    irrecv.resume();
  }
  if(on){
    if(isup){
      up(speed);
    }else{
      down(speed);
    }
  }
}

void down (int dly )
{
  digitalWrite (P1, HIGH);
  delay(dly);
  digitalWrite (P1, LOW);
  digitalWrite (P2, HIGH);
  delay(dly);
  digitalWrite (P2, LOW);
  digitalWrite (P3, HIGH);
  delay(dly);
  digitalWrite (P3, LOW);
  digitalWrite (P4, HIGH);
  delay(dly);
  digitalWrite (P4, LOW);
}

void up (int dly )
{
  digitalWrite (P4, HIGH);
  delay(dly);
  digitalWrite (P4, LOW);
  digitalWrite (P3, HIGH);
  delay(dly);
  digitalWrite (P3, LOW);
  digitalWrite (P2, HIGH);
  delay(dly);
  digitalWrite (P2, LOW);
  digitalWrite (P1, HIGH);
  delay(dly);
  digitalWrite (P1, LOW);
}
