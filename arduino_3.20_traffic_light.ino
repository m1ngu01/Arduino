#define CAR_RED 13
#define CAR_YEL 12
#define CAR_GRE 11

#define MAN_RED 7
#define MAN_GRE 6

/*
case 1 turn car red
-man gre
case 2 turn car yel
-man red
case 3 turn car gre
-man gre

first : car gre ->(1s) car yel -> (5s) car red (5s)


*/

void setup() {
  pinMode(CAR_RED,OUTPUT);
  pinMode(CAR_YEL,OUTPUT);
  pinMode(CAR_GRE,OUTPUT);

  pinMode(MAN_RED,OUTPUT);
  pinMode(MAN_GRE,OUTPUT);
}

void loop() {
  //case 1 : turn on car gre, man red
 digitalWrite(CAR_RED,LOW);
 digitalWrite(CAR_YEL,LOW);
 digitalWrite(CAR_GRE,HIGH);

 digitalWrite(MAN_RED,HIGH);
 digitalWrite(MAN_GRE,LOW);
 delay(5000);
 // case 2 : turn on car yel, man red
 digitalWrite(CAR_RED,LOW);
 digitalWrite(CAR_YEL,HIGH);
 digitalWrite(CAR_GRE,LOW);

 digitalWrite(MAN_RED,HIGH);
 digitalWrite(MAN_GRE,LOW);
 delay(1000);
 // case 3 : turn on car red, man gre
  
 digitalWrite(CAR_RED,HIGH);
 digitalWrite(CAR_YEL,LOW);
 digitalWrite(CAR_GRE,LOW);

 digitalWrite(MAN_RED,LOW);
 digitalWrite(MAN_GRE,HIGH);

 delay(3000);
 //mean : warning, change traffic light (blink man_gre)
  for (int i = 0 ; i < 5; i++){
    digitalWrite(MAN_GRE,HIGH);
    delay(500);
    digitalWrite(MAN_GRE,LOW);
    delay(500);
  }
}
