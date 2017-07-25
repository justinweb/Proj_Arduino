#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);
char oString[] = "hello";
int g_RowIndex = 0;
void setup() {
  // put your setup code here, to run once:
  //lcd.init();
  lcd.begin();
  lcd.backlight();
  char oString[] = "hello";
  for( int i = 0; i < 5; ++i ){
    lcd.setCursor(i,0);
    lcd.print(oString[i]);  
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  lcd.clear();
  delay(2000);  
  for( int i = 0; i < 5; ++i ){
    lcd.setCursor(i,g_RowIndex);
    lcd.print(oString[i]);  
    delay(1000);
  }
  delay(2000);
  g_RowIndex = g_RowIndex + 1;
  g_RowIndex = g_RowIndex % 2;
}
