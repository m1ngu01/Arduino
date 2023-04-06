#define LED 8
#define DETECT 5

int movement = 0;

void setup() {
  Serial.begin(9600);
  pinMode(DETECT, INPUT);
  pinMode(LED,OUTPUT);

}

void loop() {
  int state = digitalRead(DETECT);
  Serial.println(state);
  if(state == 1){
    movement = !movement;
  }
  if(movement == 1){
    digitalWrite(LED,HIGH);
  }
  else{
    digitalWrite(LED,LOW);
  }
}
