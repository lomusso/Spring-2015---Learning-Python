#include "Arduino.h"
#include "Shield.h"
#include <Wire.h>
#include <Adafruit_MCP23017.h>
#include <Adafruit_RGBLCDShield.h>
Adafruit_RGBLCDShield lcd = Adafruit_RGBLCDShield();
#include "Testing.h"

void Shield::reset() {
  #define RED 0x1
  #define YELLOW 0x3
  #define GREEN 0x2
  #define TEAL 0x6
  #define BLUE 0x4
  #define VIOLET 0x5
  #define WHITE 0x7
  Serial.begin(9600); 
  lcd.begin(16,2);
  lcd.setBacklight(WHITE);
  lcd.setCursor(0,0);
  lcd.clear();
  lcd.print("Please Wait.");
}

void Shield::StartScreen() {
  lcd.clear();
  lcd.print("Ready to test?");
  lcd.setCursor(0,1);
  lcd.print("Press Select.");
  uint8_t buttons = lcd.readButtons(); 
  buttons = lcd.readButtons();
  while(buttons != BUTTON_SELECT){
    buttons = lcd.readButtons();
  }
  if (buttons == BUTTON_SELECT){
     lcd.clear();
     lcd.print("Testing");
  }
}

void Shield::RestScreen() {
  lcd.clear();
  lcd.print(pressureTrans.pressure);
  lcd.setCursor(6,0);
  lcd.print("kPa");
  lcd.setCursor(0,1)
  lcd.print("Please Rest.");
  _start_rest = (float)millis();
  while (_time_now < _start_rest + (_rest_time*1000)) {
    _time_now = millis();
  }
}

void DisplayResults() {
  lcd.clear
  lcd.print(pressureTrans.pressure);
  lcd.setCursor(6,0);
  lcd.print("+/-")
  lcd.setCursor(10,0);
  lcd.print(pressureTrans.standard_deviation);
  lcd.setCursor(0,1);
  lcd.print("kPa")
}
  
