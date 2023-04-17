#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define BUTTON_1P 10
#define BUTTON_2P 9
#define BUTTON_START 8

LiquidCrystal_I2C lcd(0x27, 20, 4); // I2C LCD 모듈의 주소와 크기를 입력합니다.

unsigned int buttonCnt1 = 0;
unsigned int buttonCnt2 = 0;

unsigned long currTime = 0;
unsigned long prevTime = 0;

unsigned int gameTime = 30;

void setup() {
  Serial.begin(9600);
  pinMode(BUTTON_1P, INPUT_PULLUP); // player1 스위치 핀을 입력으로 설정하고 풀업 저항을 사용합니다.
  pinMode(BUTTON_2P, INPUT_PULLUP); // player2 스위치 핀을 입력으로 설정하고 풀업 저항을 사용합니다.
  pinMode(BUTTON_START, INPUT_PULLUP); // 시작 버튼 스위치 핀을 입력으로 설정하고 풀업 저항을 사용합니다.

  lcd.init(); // LCD 초기화
  lcd.backlight(); // LCD 백라이트 활성화

}

void loop() {

  if ( button1P() == 1 ){
    if (gameTime > 0) buttonCnt1++;
    delay(50);
  }

  if ( button2P() == 1 ){
   if (gameTime > 0) buttonCnt2++;
   delay(50);
  }

  if ( buttonStart() == 1 ){
    gameTime = 30;
    buttonCnt1 = 0;
    buttonCnt2 = 0;
    delay(50);
  }

  currTime = millis();
  if(currTime - prevTime >= 1000){
    prevTime = currTime;
    if ( gameTime > 0 )
    {
      gameTime--;
    }
    Serial.println(gameTime);
    lcd.clear();
    lcd.setCursor(3,0);
    lcd.print("TIME : ");
    lcd.print(gameTime);
    lcd.setCursor(0,1);
    lcd.print(" 1P:");
    lcd.print(buttonCnt1);
    lcd.setCursor(8,1);
    lcd.print(" 2p:");
    lcd.print(buttonCnt2);
  }
  
}

int button1P()
{
  static int oldSw =1;
  static int newSw =1;
  
  newSw =digitalRead(BUTTON_1P);

  if (newSw != oldSw)
  {
    oldSw = newSw;
    if (newSw ==0) {
    return 1;
    }
  }
  return 0;
}

int button2P()
{
  static int oldSw =1;
  static int newSw =1;
  newSw =digitalRead(BUTTON_2P);
  if (newSw != oldSw)
  {
    oldSw = newSw;
    if (newSw = 0) {
    return 1;
    }
  }
  return 0;
}


int buttonStart (){
  static int oldSw =1;
  static int newSw =1;

  newSw =digitalRead (BUTTON_START);

  if (newSw != oldSw){
    oldSw = newSw;
    if (newSw ==0) {
    return 1;
    }
  }
  return 0;
}
































