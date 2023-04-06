#include <Servo.h>

#define SERVO_PIN 9
#define SENSOR A0

Servo myservo;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  myservo.attach(SERVO_PIN);
  myservo.write(0);

}

int motorpoint = 0;
void loop() {
  // put your main code here, to run repeatedly:

  int rainvalue = analogRead(SENSOR);
  Serial.println(rainvalue);

  if(rainvalue >= 900){
    //rain
    myservo.write(motorpoint%181);
    delay(1000);
  }
  else{
    myservo.write(motorpoint++%181);
  }
}
