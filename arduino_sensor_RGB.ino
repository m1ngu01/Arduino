#define R 10
#define G 9
#define B 8


int echo = 6;
int trig = 7;

void setup() {
  Serial.begin(9600);
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(R, OUTPUT);
  pinMode(G, OUTPUT);
  pinMode(B, OUTPUT);
  
}

void loop() {
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);

  unsigned long duration = pulseIn(echo, HIGH);

  float dis = ((34000 * duration) / 1000000 ) / 2;
  if ( dis > 0 && dis <= 10){
    digitalWrite(R, LOW);
    digitalWrite(G, HIGH);
    digitalWrite(B, HIGH);
  }
  else if ( dis > 10 && dis <= 20){
    digitalWrite(R, HIGH);
    digitalWrite(G, LOW);
    digitalWrite(B, HIGH);
  }
  else if ( dis > 20 && dis <= 30){
    digitalWrite(R, HIGH);
    digitalWrite(G, HIGH);
    digitalWrite(B, LOW);
  }
  else{
    digitalWrite(R, HIGH);
    digitalWrite(G, HIGH);
    digitalWrite(B, HIGH);    
  }

  Serial.println(dis);
  delay(100);

}
