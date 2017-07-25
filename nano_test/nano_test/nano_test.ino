#define D2 2
void setup() {
  // put your setup code here, to run once:
   pinMode(D2, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(2000);
  digitalWrite( D2, HIGH );
  delay(2000);
  digitalWrite( D2, LOW );
}
