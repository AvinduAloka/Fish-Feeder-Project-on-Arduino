#include <Servo.h>

Servo s1;
int x = 2;

void setup() {
  // put your setup code here, to run once:
  s1.attach(7);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(x == 1){
    s1.detach();
    delay(4);
    s1.attach(7);
    s1.write(90);
    delay(900);
    s1.attach(7);
    s1.write(0);
    delay(200);
    exit(0);
  }
  else if(x == 2){
    s1.write(0);
    delay(200);
    exit(0);
  }
}
