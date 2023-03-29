#include "header.h"
#include "ReadingScreen.h"
#include "SettingTimeIntervalScreen.h"
#include "ScreenBase.h"

LGFX Llcd;                 // LGFXのインスタンスを作成（クラスLGFXを使ってlcdコマンドでいろいろできるようにする）
LGFX_Sprite canvas(&Llcd); // スプライトを使う場合はLGFX_Spriteのインスタンスを作成
FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

static ReadingScreen readingScreen(0, 1, "bookName");
static SettingTimeIntervalScreen settingTimeScreen;
static ScreenBase *screens[2];
static int currentScreenNumber = 0;

void setup()
{
  M5.begin();
  M5.lcd.begin();
  Llcd.init(); // LCD初期化
  screens[0] = &readingScreen;
  screens[1] = &settingTimeScreen;
  if (connectingWifi())
  {
    Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
    Firebase.reconnectWiFi(true);
    setRTC();
  }
  readingScreen.initScreen();
  settingTimeScreen.deleteScreen();
  Serial.begin(9600);
}

void loop()
{
  M5.update();
  screens[currentScreenNumber]->scereenUpdate();
  if (M5.BtnA.wasPressed())
  {
    togglePowerLcd();
  }
}

void test_screenTransition()
{
  if (M5.BtnA.wasPressed())
  {
    togglePowerLcd();
  }

  if (M5.BtnB.wasPressed())
  {
    readingScreen.deleteScreen();
    settingTimeScreen.initScreen();
  }

  if (M5.BtnC.wasPressed())
  {
    settingTimeScreen.deleteScreen();
    readingScreen.initScreen();
  }
}