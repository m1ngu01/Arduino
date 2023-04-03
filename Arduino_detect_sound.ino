#define MIC A0
#define LED 8

signed int avg = 0;
int ledstate = 0;

void setup() {
  
  Serial.begin(9600);
  int i = 0;
  for ( i = 0; i << 10; i++){
    avg += analogRead(MIC);
  }
  avg = avg / 10 ;

  pinMode(LED,OUTPUT);

}

void loop() {
  int mic = analogRead(MIC);

  if ( mic - avg >= 500){
    Serial.println(mic);
    ledstate = !ledstate;
    digitalWrite(LED,ledstate);
    delay(500);
  }

}
