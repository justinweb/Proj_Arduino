int  L;
int  C;
int  R;
int SwitchStatus = 0;
int IsRunning = false;
int  Status;
int motoLevel = 200;
int Switch_Digital = 2;
int Left_Digital = 6;
int Right_Digital = 5;
void forward() {
  digitalWrite(10,HIGH);
  analogWrite(5,motoLevel);
  digitalWrite(11,HIGH);
  analogWrite(6,motoLevel);
}

void stop() {
  analogWrite(5,0);
  analogWrite(6,0);
}

void backward() {
  digitalWrite(10,LOW);
  analogWrite(5,motoLevel);
  digitalWrite(11,LOW);
  analogWrite(6,motoLevel);
}



void left() {
  digitalWrite(10,HIGH);
  analogWrite(5,motoLevel);
  digitalWrite(11,LOW);
  analogWrite(6,0);
}

void right() {
  digitalWrite(10,LOW);
  analogWrite(5,0);
  digitalWrite(11,HIGH);
  analogWrite(6,motoLevel);
}

void setup()
{
  Serial.begin(9600);
  pinMode(7, INPUT);
  pinMode(8, INPUT);
  pinMode(12, INPUT);
    L = '0';
  C = '0';
  R = '0';
  Status = '0';

  pinMode(10, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(6, OUTPUT);
}

void loop()
{
//    int crtSwitchStatus = digitalRead(Switch_Digital);
//    if( crtSwitchStatus != SwitchStatus ){
//      IsRunning = !IsRunning;
//    }
//    SwitchStatus = crtSwitchStatus;
//
//    if( IsRunning ){
//      digitalWrite(10, HIGH );
//    }else{
//      digitalWrite(10, LOW );
//    }
    
    
    L = digitalRead(7);
    C = digitalRead(8);
    R = digitalRead(12);
    Status = L * 4 + (C * 2 + R);
    Serial.println(Status);
    
    if (Status == 0) {
      forward();
    } else if (Status == 1) {
      right();
    } else if (Status == 2) {
      forward();
    } else if (Status == 3) {
      right();
    } else if (Status == 4) {
      left();
    } else if (Status == 5) {
      forward();
    } else if (Status == 6) {
      left();
    } else if (Status == 7) {
      stop();
    }
    

}
