#include <AFMotor.h>  
#include <Servo.h> // подключаем библиотеку для работы с сервоприводом

#define FORWARDH 85
#define FORWARDV 105
#define DELTA_VIEW 20
#define SPEED 255
#define TIME 500

Servo servo1; // объявляем переменную servo типа "servo1"
Servo servo2;

AF_DCMotor motorR(2);
AF_DCMotor motorL(4);
 
bool quit = false;

enum Command {
    kNeedCommand,  // 0x00
    kForward,      // 0x01
    kBack,         // 0x02
    kLeft,         // 0x03
    kRight,        // 0x04
    kStop,         // 0x05
    kAbort,        // 0x06
    kForwardView,  // 0x07
    kLeftView,     // 0x08
    kRightView,    // 0x09
    kUpView,       // 0x0A
    kDownView      // 0x0B
  };


void moveit(int L, int R, int speed, int time)
{
  if(R != -1)
  {
    motorR.run(R);
    motorR.setSpeed(speed);
  }
  if(L != -1)
  {
    motorL.run(L); 
    motorL.setSpeed(speed);
  } 
  delay(time);
  stop(L != -1, R != -1);
}

void stop(bool L, bool R)
{
  if(R)
    motorR.run(RELEASE);
  if(L)
    motorL.run(RELEASE);
  delay(500);
}

void forward(int speed, int time)
{
  moveit(FORWARD, FORWARD, speed, time);
}

void backward(int speed, int time)
{
  moveit(BACKWARD, BACKWARD, speed, time);
}

void left(int speed, int time)
{
  moveit(-1, FORWARD, speed, time);
}

void right(int speed, int time)
{
  moveit(FORWARD, -1, speed, time);
}

void leftward(int speed, int time)
{
  moveit(BACKWARD, FORWARD, speed, time);
}

void rightward(int speed, int time)
{
  moveit(FORWARD, BACKWARD, speed, time);
}

void forwardView()
{
  servo1.write(FORWARDH);
  servo2.write(FORWARDV); 
}

void leftView(int delta)
{
   servo1.write(FORWARDH + delta); 
}

void rightView(int delta)
{
   servo1.write(FORWARDH - delta); 
}

void upView(int delta)
{
   servo2.write(FORWARDV + delta); 
}

void downView(int delta)
{
   servo2.write(FORWARDV - delta); 
}

void setup() { 
  
  Serial.begin(9600);

  servo1.attach(9);
  servo2.attach(10);
  forwardView();
  
  motorR.setSpeed(255);
  motorL.run(RELEASE);
  motorR.setSpeed(255);
  motorL.run(RELEASE);
}

int i;

void loop() {
  if(quit)
    return;
  if (Serial.available() > 0) {
    int incomingByte = 0;  
    incomingByte = Serial.read();
    switch(incomingByte){
      case kNeedCommand:
        printf("Need a command!\n");
        break;
      case kForward:
        forward(SPEED, 2 * TIME);
        break;
      case kBack: 
        backward(SPEED, 2 * TIME);
        break;
      case kLeft: 
        left(SPEED, TIME);
        break;
      case kRight: 
        right(SPEED, TIME);
        break;
      case kStop: 
        stop(true, true);
        break;
      case kAbort: 
        quit = true;
        break;
      case kForwardView: 
        forwardView();
        break;
      case kLeftView: 
        leftView(DELTA_VIEW);   
        break;
      case kRightView: 
        rightView(DELTA_VIEW); 
        break;
      case kUpView: 
        upView(DELTA_VIEW);     
        break;
      case kDownView: 
        downView(DELTA_VIEW); 
        break;
    }
    Serial.write(kNeedCommand);
  }
    forward(SPEED, 3 * TIME);
    delay(2000);
  leftView(3 * DELTA_VIEW);
  delay(2000);
  rightView(3 * DELTA_VIEW);  
  delay(2000);
  upView(3 * DELTA_VIEW);
  delay(2000);
  forwardView();
  leftward(SPEED, TIME);
  delay(2000);
  forward(SPEED,3 * TIME);
  delay(2000);
delay(2000);
}

