#include <Stepper.h>
#include <Servo.h>
#include <LiquidCrystal_I2C.h>

//display 초깃ㄹ정
LiquidCrystal_I2C lcd(0x27, 20, 4); // I2C LCD 모듈의 주소와 크기를 입력합니다.

#define SERVO 12
#define SERVOH 13
//장전  노랑색 버튼
#define MODE_RELOAD 2
//발사 빨강색 버튼
#define FIRE_BUTTON 3

//서브모터 장전 판 막기 각도 여부
#define SHOTON 0
#define SHOTOFF 90

//발사 관련 변수
int reload=0;
int fire=1;
int mode = 0;
//센서 왼쪽
int echoleft = A0;
int trigleft = A1;
//센서 오른쪽
int echoright = A2;
int trigright = A3;

int width = 0;
int angle = 100;

//장전 파츠
Servo servo;
//높낮이 파츠
Servo servoh;

// 2048:한바퀴(360도), 1024:반바퀴(180도)... 512 256 128 64 32 16 8 4 2 
const int stepsPerRevolution = 2680; 
// 모터 드라이브에 연결된 핀 IN4, IN2, IN3, IN1
Stepper myStepper(stepsPerRevolution,11,9,10,8); 
Stepper mySteppertop(64,7,5,6,4); 

void setup() 
{
//기본 초기 설정
  Serial.begin(9600);
  myStepper.setSpeed(10); 
  mySteppertop.setSpeed(50); 
  servo.attach(SERVO);
  servoh.attach(SERVOH);

  pinMode(MODE_RELOAD, INPUT_PULLUP);
  pinMode(FIRE_BUTTON, INPUT_PULLUP);
  pinMode(trigleft, OUTPUT);
  pinMode(echoleft, INPUT);
  pinMode(trigright, OUTPUT);
  pinMode(echoright, INPUT);

//lcd 초기설정
  lcd.init(); // LCD 초기화
  lcd.backlight(); // LCD 백라이트 활성화
  lcd.clear();
  lcd.setCursor(3,0);
  lcd.print("SYSTEM START");


}
void loop() 
{

  /*mode change*/
  if(digitalRead(MODE_RELOAD) == 0)
  {
    mode++;
    mode = mode % 3;
    delay(500);
  }
  
  /*-----------------초음파 센서 함수 부분 좌우 부분---------------*/
  
  if(mode == 0)
  {

    //초음파 센서 왼쪽 회전
    digitalWrite(trigleft, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigleft, LOW);
    unsigned long durationleft = pulseIn(echoleft, HIGH);
    float disleft = ((34000 * durationleft) / 1000000 ) / 2;

    //처음파 센서 오른쪽 회전
    digitalWrite(trigright, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigright, LOW);
    unsigned long durationright = pulseIn(echoright, HIGH);
    float disright = ((34000 * durationright) / 1000000 ) / 2;

    if(reload == 1)
    {
      lcd.clear();
      lcd.setCursor(3,0);
      lcd.print("SHOT RESET");
      servo.write(SHOTOFF);
      myStepper.step(-stepsPerRevolution);
      reload = 0;
      fire = 1;

      if(digitalRead(FIRE_BUTTON) == 0)
      {
        lcd.clear();
        lcd.setCursor(3,0);
        lcd.print("MOVE RESET");

        width = -1 * width;
        mySteppertop.step(width);
        width = 0;
      }
    }
    else
    {
      lcd.clear();
      lcd.setCursor(2,0);
      lcd.print("MOVE SYSTEM!");
      delay(400);
      if(digitalRead(FIRE_BUTTON) == 0)
      {
        lcd.clear();
        lcd.setCursor(3,0);
        lcd.print("MOVE RESET");

        width = -1 * width;
        mySteppertop.step(width);
        width = 0;
      }
    }

    /* 좌우 각도조절 세부사항--------------------------------------*/
    if(disleft > 0 && disleft <= 3)
    {
      lcd.clear();
      lcd.setCursor(4,0);
      lcd.print("TURNING~");
      lcd.setCursor(4,1);
      lcd.print("LEFT <<<");
      //90이상 못 넘어가게 범위 한정
      if(width < 512)
      {
        mySteppertop.step(128);
        width += 128;
      }

    }
    
    if(disright > 0 && disright <= 3)
    {
      lcd.clear();
      lcd.setCursor(4,0);
      lcd.print("TURNING~");
      lcd.setCursor(4,1);
      lcd.print("RIGHT >>");
      if(width > -512)
      //-90이상 못 넘어가게 범위 한정
      {
        mySteppertop.step(-128);
        width -= 128;
      }
    }
  }

  /*-----------------초음파 센서 함수 부분 높낮이 부분-------------------*/
  else if(mode == 1)
  {
    //처음파 센서 왼쪾 회전
    digitalWrite(trigleft, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigleft, LOW);
    unsigned long durationleft = pulseIn(echoleft, HIGH);
    float disleft = ((34000 * durationleft) / 1000000 ) / 2;

    //처음파 센서 오른쪽 회전
    digitalWrite(trigright, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigright, LOW);
    unsigned long durationright = pulseIn(echoright, HIGH);
    float disright = ((34000 * durationright) / 1000000 ) / 2;

    if(disleft > 0 && disleft <= 3)
    {
      lcd.clear();
      lcd.setCursor(4,0);
      lcd.print("TURNING!");
      lcd.setCursor(6,1);
      lcd.print("UPUP");
      delay(400);

      //100도 이상 안올라가게 각도 조절
      angle += 10;
      if( angle > 100 )
      {
        angle = 100;
      }
      if(angle <= 100)
      {
        servoh.write(angle);
      }
    }
    else if(disright > 0 && disright <= 3)
    {
      lcd.clear();
      lcd.setCursor(4,0);
      lcd.print("TURNING!");
      lcd.setCursor(6,1);
      lcd.print("DOWN");
      delay(400);

      //0도 이하 안내려가고 각도 조절
      angle -= 10;
      if(angle < 30)
      {
        angle = 30;
      }
      if(angle >= 30)
      {
        servoh.write(angle);
      }
    }
    else if(reload == 1)
    {
      if(digitalRead(FIRE_BUTTON) == 0)
      {
        lcd.clear();
        lcd.setCursor(3,0);
        lcd.print("HIGH RESET");

        angle = 0;
        servoh.write(angle);
      }
    }
    else
    {
      lcd.clear();
      lcd.setCursor(2,0);
      lcd.print("HIGH SYSTEM!");
      delay(400);

      if(digitalRead(FIRE_BUTTON) == 0)
      {
        lcd.clear();
        lcd.setCursor(3,0);
        lcd.print("HIGH RESET");

        angle = 0;
        servoh.write(angle);
      }
    }
  }

  /*---------------------발사 부분------------------------------*/
  else if (mode == 2)
  {
    if(fire == 1)
    {
      lcd.clear();
      lcd.setCursor(3,0);
      lcd.print("RELOADING~");

      //열고 당기고
      myStepper.step(stepsPerRevolution);
      //닫고 당긴거 유지
      servo.write(SHOTON);

      //display 장전 완료 출력 부분
      lcd.clear();
      lcd.setCursor(3,0);
      lcd.print("RELOAD GOOD");


      //장전이 되면 활성화
      reload = 1;
      fire = 0;
    }
    else if(digitalRead(FIRE_BUTTON) == 0 && reload == 1)
    {
      lcd.clear();

      lcd.setCursor(7,0);
      lcd.print("4!");
      myStepper.step(-stepsPerRevolution / 5);
      delay(200);

      lcd.setCursor(7,0);
      lcd.print("3!");
      myStepper.step(-stepsPerRevolution / 5);
      delay(200);

      lcd.setCursor(7,0);
      lcd.print("2!");
      myStepper.step(-stepsPerRevolution / 5);
      delay(200);

      lcd.setCursor(7,0);
      lcd.print("1!");
      myStepper.step(-stepsPerRevolution / 5);
      delay(200);

      myStepper.step(-stepsPerRevolution / 5);
      lcd.clear();
      lcd.setCursor(4,0);
      lcd.print("!!FIRE!!");

      //닫고 풀고 (발사)
      
      //열고 안당기고
      servo.write(SHOTOFF);
      delay(3000);
      
      //장전 상태 해제
      reload = 0 ;
      fire = 1;
    }
    else
    {
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("READY TO LAUNCH!");
      lcd.setCursor(3,1);
      lcd.print("MODE FIRE!");
      delay(500);
    }
  }
  /*---------------------발사 부분------------------------------*/
}