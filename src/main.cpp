#include "header.h"
#include "ReadingScreen.h"
#include "SettingTimeIntervalScreen.h"
#define PROGRESS_MAX 100
using namespace std;
FirebaseData fbdo;

FirebaseAuth auth;
FirebaseConfig config;

ReadingScreen readingScreen(0, 1, "bookName");
bool lcdOn = true;
SettingTimeIntervalScreen settingTimeScreen;
void setup()
{
  Serial.begin(9600);
  M5.begin();
  M5.lcd.begin();
  Llcd.init(); // LCD初期化
  readingScreen.initScreen();
  settingTimeScreen.btn_plus5.erase();
}

void loop()
{
  M5.update();

  if (M5.BtnA.wasPressed())
  {
    lcdOn = !lcdOn;

    if (lcdOn)
    {
      M5.Axp.SetLcdVoltage(3000);
      M5.Axp.SetDCDC3(true);
      M5.lcd.wakeup();
    }
    else
    {
      M5.Axp.SetDCDC3(false);
      M5.Axp.SetLed(0);
      M5.Lcd.sleep();
    }
  }

  if (M5.BtnB.wasPressed())
  {
    readingScreen.btn_x.erase(BLACK);
    readingScreen.btn_x.set(0,0,0,0);
    settingTimeScreen.initScreen();
  }

  if (M5.BtnC.wasPressed())
  {
    settingTimeScreen.btn_plus5.erase(BLACK);
    settingTimeScreen.btn_plus5.set(0,0,0,0);
    readingScreen.initScreen();
  }
}