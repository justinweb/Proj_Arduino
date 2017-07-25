//------------------------------------------------------
//使用 PS2 無線搖桿來控制 L298P 四輪小車
//------------------------------------------------------

#include <PS2X_lib.h>

#define PS2_DAT 2
#define PS2_CMD 3
#define PS2_SEL 5
#define PS2_CLK 6
#define E1 10
#define M1 12
#define E2 11
#define M2 13

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

  Serial.print( "Throttle=" );
  Serial.print( throttle );
  Serial.print( ",handler=");
  Serial.print( handler );
  Serial.println("");

   if(ps2x.Button(PSB_PAD_UP)) {         //will be TRUE as long as button is pressed
       Serial.print("Up held this hard: ");
       Serial.println(ps2x.Analog(PSAB_PAD_UP), DEC);
      }
      if(ps2x.Button(PSB_PAD_RIGHT)){
       Serial.print("Right held this hard: ");
        Serial.println(ps2x.Analog(PSAB_PAD_RIGHT), DEC);
      }
      if(ps2x.Button(PSB_PAD_LEFT)){
       Serial.print("LEFT held this hard: ");
        Serial.println(ps2x.Analog(PSAB_PAD_LEFT), DEC);
      }
      if(ps2x.Button(PSB_PAD_DOWN)){
       Serial.print("DOWN held this hard: ");
     Serial.println(ps2x.Analog(PSAB_PAD_DOWN), DEC);
      }   


   if (ps2x.NewButtonState())               //will be TRUE if any button changes state (on to off, or off to on)
    {
      if(ps2x.Button(PSB_L1))
         Serial.println("L1 pressed");
        if(ps2x.Button(PSB_R1))
         Serial.println("R1 pressed");
        if(ps2x.Button(PSB_L2))
         Serial.println("L2 pressed");
        if(ps2x.Button(PSB_R2))
         Serial.println("R2 pressed");
        if(ps2x.Button(PSB_GREEN))
         Serial.println("Triangle pressed");
         if(ps2x.ButtonPressed(PSB_RED))             //will be TRUE if button was JUST pressed
         Serial.println("Circle just pressed");
         
    if(ps2x.ButtonReleased(PSB_PINK))             //will be TRUE if button was JUST released
         Serial.println("Square just released");     
    
    if(ps2x.NewButtonState(PSB_BLUE))            //will be TRUE if button was JUST pressed OR released
         Serial.println("X just changed");     
    }   
  
  delay(500);
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

