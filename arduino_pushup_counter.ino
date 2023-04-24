#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define BUZZER_PIN 8
#define SW_PIN 12
int echo = 6;
int trig = 7;

LiquidCrystal_I2C lcd(0x27, 20, 4); // I2C LCD 모듈의 주소와 크기를 입력합니다.

int pushupCnt=0;
int pushState=0;


void setup() {
  Serial.begin(9600);
  pinMode(trig,OUTPUT);
  pinMode(echo,INPUT);
  pinMode(BUZZER_PIN,OUTPUT);
  pinMode(SW_PIN,INPUT_PULLUP);
  
  

  lcd.init(); // LCD 초기화
  lcd.backlight(); // LCD 백라이트 활성화
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("PUSHUP COUNTER");

}

void loop() {
  float distance = ultraSonic();
  Serial.print(distance);
  Serial.println("cm");
  Serial.print("  switch");
  Serial.println(pushState);
  delay(100);
  if(distance <= 10 && pushState == 0){
    pushState = 1;
    pushupCnt++;
    lcd.setCursor(8,1);
    lcd.print(" ");
    lcd.setCursor(8,1);
    lcd.print(pushupCnt);
    digitalWrite(BUZZER_PIN, HIGH);
    delay(100);
    digitalWrite(BUZZER_PIN, LOW);
    delay(100);
  }
else if (distance >= 30 && pushState == 1){
  pushState = 0;
}

if( digitalRead(SW_PIN) == 0){
  pushupCnt = 0;
  lcd.setCursor(8,1);
  lcd.print(0,0);
  lcd.setCursor(8,1);
  lcd.print(pushupCnt);
  delay(100);
}
  
}

float ultraSonic(){
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig,LOW);

  unsigned long duration = pulseIn(echo, HIGH);

  float distanceCM= ((34000 * duration/1000000)/2);
  return distanceCM;
}