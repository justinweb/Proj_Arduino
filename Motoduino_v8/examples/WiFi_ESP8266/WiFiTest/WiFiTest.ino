
/////////////////////////////////
//// 功能: WiFi ESP8266 Testing
//// 日期: June 2016 
//// 作者: Dennis
//////////////////////////

#include <Wire.h>
#include <motoLiquidCrystal_I2C.h>
#include "motoESP8266.h"
#include <SoftwareSerial.h>
SoftwareSerial esp8266(3,2);  // use pins 3, 2 for software serial //S4A IO Board
LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display

#define AP_SSID  "xxxxxxxxxx"      // change this to match your WiFi SSID
#define PASSWORD  "xxxxxxxxx"  // change this to match your WiFi password

ESP8266 wifi(esp8266);

int LED_CONNECT_PIN = 13;

void setup() {
  
  lcd.init();      // initialize the lcd 
  lcd.backlight();
  lcd.print("Getting IP ...");

 pinMode(LED_CONNECT_PIN, OUTPUT);
   digitalWrite(LED_CONNECT_PIN, LOW); 
  // change if necessary to match your modules' baud rate
  esp8266.begin(9600);
  
  Serial.begin(9600);
  Serial.println("begin.");

    wifi.restart();
  
    if (wifi.setOprToStation()) {
        Serial.print("set to STATION mode ok\r\n");
    } else {
        Serial.print("set to STATION mode err\r\n");
    }
    
   wifi.joinAP(AP_SSID, PASSWORD);
    delay(8000);
     Serial.print("IP: ");
        String ipaddress = wifi.getLocalIP();
       Serial.println(ipaddress);
  
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("IP:");
  lcd.setCursor(0,1);
  lcd.print(ipaddress);
  
}

void loop()
{

}



