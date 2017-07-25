//------------------------------------------------------
//使用 PS2 無線搖桿來控制 L298P 四輪小車
//------------------------------------------------------

#include <PS2X_lib.h>

#define PS2_DAT 2
#define PS2_CMD 3
#define PS2_SEL 5
#define PS2_CLK 6
#define E1 10
#define M1 13
#define E2 11
#define M2 12

const int motor_speed = 200;

byte vibrate = 0;
PS2X ps2x;

void setup()
{
  Serial.begin(9600);
  
  delay(1000);

  initial();
}

void initial()
{
  ps2x.config_gamepad(PS2_CLK, PS2_CMD, PS2_SEL, PS2_DAT, true, false);
  
  pinMode(M1, OUTPUT);
  pinMode(M2, OUTPUT);
  
  carStop();
}

void loop()
{
  ps2x.read_gamepad(false, vibrate);

  int throttle = ps2x.Analog(PSS_LY);
  int handler = ps2x.Analog(PSS_RX);
  
  if (throttle < 123)
  {
    if (handler > 133)
    {
      forwardRight();
    }
    else if (handler < 123)
    {
      forwardLeft();
    }
    else
    {
      forward();
    }
  }
  else if (throttle > 133)
  {
    if (handler > 133)
    {
      backwardLeft();
    }
    else if (handler < 123)
    {
      backwardRight();
    }
    else
    {
      backward();
    }
  }
  else
  {
    carStop();
  }
    
  delay(50);
}

void forward()
{
  digitalWrite(M1, HIGH);
  digitalWrite(M2, HIGH);
  analogWrite(E1, motor_speed);
  analogWrite(E2, motor_speed);
}

void forwardLeft()
{
  digitalWrite(M1, HIGH);
  digitalWrite(M2, LOW);
  analogWrite(E1, motor_speed + 40);
  analogWrite(E2, motor_speed + 40);
}

void forwardRight()
{
  digitalWrite(M1, LOW);
  digitalWrite(M2, HIGH);
  analogWrite(E1, motor_speed + 40);
  analogWrite(E2, motor_speed + 40);
}

void backward()
{
  digitalWrite(M1, LOW);
  digitalWrite(M2, LOW);
  analogWrite(E1, motor_speed);
  analogWrite(E2, motor_speed);
}

void backwardLeft()
{
  digitalWrite(M1, HIGH);
  digitalWrite(M2, LOW);
  analogWrite(E1, motor_speed);
  analogWrite(E2, motor_speed);
}

void backwardRight()
{
  digitalWrite(M1, LOW);
  digitalWrite(M2, HIGH);
  analogWrite(E1, motor_speed);
  analogWrite(E2, motor_speed);
}

void carStop()
{
  digitalWrite(M1, LOW);
  digitalWrite(M2, LOW);
  analogWrite(E1, 0);
  analogWrite(E2, 0);
}

