
#include <Arduino.h>
/* 本代码适用于ESP8266 NodeMCU + 12864显示屏
 * 7pin SPI引脚，正面看，从左到右依次为GND、VCC、D0、D1、RES、DC、CS
 *    ESP8266 ---  OLED
 *      3V    ---  VCC
 *      G     ---  GND
 *      D7    ---  D1
 *      D5    ---  D0
 *      D2orD8---  CS
 *      D1    ---  DC
 *      RST   ---  RES
 * 4pin IIC引脚，正面看，从左到右依次为GND、VCC、SCL、SDA
 *      ESP8266  ---  OLED
 *      3.3V     ---  VCC
 *      G (GND)  ---  GND
 *      D1(GPIO5)---  SCL
 *      D2(GPIO4)---  SDA
 */

//#include <TimeLib.h>
//#include <ESP8266WiFi.h>
//#include <ESP8266WebServer.h>
//#include <DNSServer.h>
//#include <WiFiUdp.h>
#include <SPI.h>
//#include <EEPROM.h>
#include <U8g2lib.h>
#include <Wire.h>
//#include <OneButton.h>

//若屏幕使用SH1106，只需把SSD1306改为SH1106即可
//U8G2_SSD1306_128X64_NONAME_F_4W_HW_SPI u8g2(U8G2_R0, /* cs=*/4, /* dc=*/5, /* reset=*/3);
U8G2_SH1122_256X64_F_HW_I2C u8g2(U8G2_R0, /* reset=*/U8X8_PIN_NONE);
//U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE, /* clock=*/ 4, /* data=*/ 5); //D-duino

volatile int Zbushu;
volatile int Ybushu;
volatile int zm;
volatile int zs;
volatile int ym;
volatile int ys;
//U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0,U8X8_PIN_NONE);

void setup(){
  Zbushu = 0;
  Ybushu = 0;
  zm = 20;
  zs = 0;
  ym = 20;
  ys = 0;
  pinMode(14, OUTPUT);
  pinMode(0, OUTPUT);
  digitalWrite(14,HIGH);
  digitalWrite(0,HIGH);
   u8g2.begin();

  u8g2.enableUTF8Print();

  pinMode(16, INPUT);
  pinMode(13, OUTPUT);
  pinMode(4, INPUT);
}

void loop(){
  u8g2.firstPage();
  do
  {
  u8g2.setFont(u8g2_font_helvR24_tf);
    u8g2.setFontPosTop();
    u8g2.setCursor(0,16);
    u8g2.print(Zbushu);
    u8g2.setCursor(220,16);
    u8g2.print(Ybushu);
    u8g2.setFont(u8g2_font_helvR18_tf);
    u8g2.setFontPosTop();
    u8g2.setCursor(55,16);
    u8g2.print(String(String(zm)) + String(":") + String(String(zs)));
    u8g2.setCursor(140,16);
    u8g2.print(String(String(ym)) + String(":") + String(String(ys)));
    u8g2.setContrast(100);
  }
  while (u8g2.nextPage());

  if (digitalRead(14)) {
    if (!digitalRead(0)) {
      delay(1000);
      if (zs == 0) {
        zs = 60;
        zm--;

      }
      zs--;

    }
    if (!digitalRead(16)) {
      Zbushu++;
      digitalWrite(0,HIGH);
      tone(13,200,10);
      digitalWrite(14,LOW);

    }

  } else {
    if (!digitalRead(16)) {
      tone(13,300,100);

    }

  }

  if (digitalRead(0)) {
    if (!digitalRead(14)) {
      delay(1000);
      if (ys == 0) {
        ys = 60;
        ym--;

      }
      ys--;

    }
    if (!digitalRead(4)) {
      Ybushu++;
      digitalWrite(14,HIGH);
      tone(13,200,10);
      digitalWrite(0,LOW);

    }

  } else {
    if (!digitalRead(4)) {
      tone(13,300,100);

    }

  }

}
