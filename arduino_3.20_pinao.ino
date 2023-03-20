#define SOUND 3
#define SW1 13
#define SW2 12
#define SW3 11
#define SW4 10




void setup() {
  pinMode(SW1,INPUT_PULLUP);
  pinMode(SW2,INPUT_PULLUP);
  pinMode(SW3,INPUT_PULLUP);
  pinMode(SW4,INPUT_PULLUP);
}

void loop() {
  if (digitalRead(SW1) == 0) {tone(SOUND, 261.6);}
  else if (digitalRead(SW2) == 0) {tone(SOUND, 293.6);}
  else if (digitalRead(SW3) == 0) {tone(SOUND, 329.6);}
  else if (digitalRead(SW4) == 0) {tone(SOUND, 349.2);}
  else {noTone(SOUND);}
}
