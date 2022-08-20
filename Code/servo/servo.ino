#include <Servo.h>
Servo servo;
int rain=1024;

void setup(){
  servo.attach(9);
  Serial.begin(9600);
}

void loop(){
  servo.write(0);
  rain=analogRead(A2);

  if(rain<700)
    servo.write(120);
  else
    servo.write(0);

    Serial.println(rain);

   delay(250);
  
}
