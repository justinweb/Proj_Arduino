
/////////////////////////////////
//// 功能: WiFi手機無線遙控車 (ESP8266)    Station Mode
//// 日期: June 2016 
//// 作者: Dennis
//////////////////////////

#include <Wire.h>
#include <motoLiquidCrystal_I2C.h>
#include "motoESP8266.h"
#include <SoftwareSerial.h>
SoftwareSerial esp8266(3,2);  // use pins 3, 2 for software serial //S4A IO Board
LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display

#define AP_SSID  "xxxxxxxxx"      // change this to match your WiFi SSID
#define PASSWORD  "xxxxxxxxxxx"  // change this to match your WiFi password
#define PORT  80           // using port 8080 by default

ESP8266 wifi(esp8266);

const int Motor_E1 = 5;  // Speed Control pin 5 of Arduino (PWM)  
const int Motor_E2 = 6; // Speed Control pin 6 of Arduino (PWM)    
const int Motor_M1 = 10;    // Direction Control pin 10 of Arduino
const int Motor_M2 = 11;     // Direction Control pin 11 of Arduino

int LED_CONNECT_PIN = 13;

void setup() {
  
  lcd.init();      // initialize the lcd 
  lcd.backlight();
  lcd.print("Getting IP ...");
  pinMode(Motor_M1, OUTPUT);
  pinMode(Motor_M2, OUTPUT);
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
  
    if (wifi.enableMUX()) {
        Serial.print("multiple ok\r\n");
    } else {
        Serial.print("multiple err\r\n");
    }
    if (wifi.startTCPServer(PORT)) {
        Serial.print("start tcp server ok\r\n");
         Serial.print("Port: ");
         Serial.println(PORT);
           digitalWrite(LED_CONNECT_PIN, HIGH);
    } else {
        Serial.print("start tcp server err\r\n");
    }
 
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("IP:");
  lcd.setCursor(0,1);
  lcd.print(ipaddress);
  
}

void loop()
{
    uint8_t buffer[128] = {0};

    uint32_t len = wifi.recv(buffer, sizeof(buffer), 1000);
    if (len > 0) {
        for(uint32_t i = 0; i < len; i++) {
            Serial.print((char)buffer[i]);
        }
        MoveMotors(buffer[0]);
    }
}


void  MoveMotors(char data)
{    
    switch(data)
    {
        case 'f': 
            forward(255);
            break;
         case 'b': 
            backward(255);
            break;
        case 'l': 
            left(255);
            break;
        case 'r': 
            right(255);
            break;
        case 's': 
            motorstop();
            break;
        default:
        break;
    }
      
}

void motorstop()
{
  Serial.println("stop!");
  
  digitalWrite( Motor_M1, LOW);
  digitalWrite( Motor_M2, LOW);
  analogWrite( Motor_E1, 0);
  analogWrite( Motor_E2, 0);

}

void forward(int motorSpeed)
{
  Serial.println("forward!");
    
  digitalWrite( Motor_M1, HIGH);
  digitalWrite( Motor_M2, HIGH);
  analogWrite( Motor_E1, motorSpeed);
  analogWrite( Motor_E2, motorSpeed);
}

void backward(int motorSpeed)
{
  Serial.println("back!");
  
  digitalWrite( Motor_M1, LOW);
  digitalWrite( Motor_M2, LOW);
  analogWrite( Motor_E1, motorSpeed);
  analogWrite( Motor_E2, motorSpeed);

}

void right(int motorSpeed)
{
  Serial.println("right!");  
  
  digitalWrite( Motor_M1, HIGH);
  digitalWrite( Motor_M2, HIGH);
  analogWrite( Motor_E1, 0);
  analogWrite( Motor_E2, motorSpeed);
}

void left(int motorSpeed)
{
  Serial.println("left!");  
  
  digitalWrite( Motor_M1, HIGH);
  digitalWrite( Motor_M2, HIGH);
  analogWrite( Motor_E1, motorSpeed);
  analogWrite( Motor_E2, 0);

}


