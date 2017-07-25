char  c;
void forward() {
  digitalWrite(10,HIGH);
  analogWrite(5,250);
  digitalWrite(11,HIGH);
  analogWrite(6,250);
}

void stop() {
  analogWrite(5,0);
  analogWrite(6,0);
}

void backward() {
  digitalWrite(10,LOW);
  analogWrite(5,250);
  digitalWrite(11,LOW);
  analogWrite(6,250);
}

void left() {
  digitalWrite(10,HIGH);
  analogWrite(5,250);
  digitalWrite(11,LOW);
  analogWrite(6,0);
}

void right() {
  digitalWrite(10,LOW);
  analogWrite(5,0);
  digitalWrite(11,HIGH);
  analogWrite(6,250);
}

void setup()
{
  Serial.begin(57600);
    c = '0';

  pinMode(10, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(6, OUTPUT);
}


void loop()
{
    if (Serial.available() > 0) {
      c = Serial.read();
      if (c == 'f') {
        forward();

      } else if (c == 'b') {
        backward();
      } else if (c == 'l') {
        left();
      } else if (c == 'r') {
        right();
      } else if (c == 's') {
        stop();
      }

    }

}
