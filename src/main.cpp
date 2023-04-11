/**
 * @file main.cpp
 * @author Kodai-study (anchor.kou@softbank.ne.jp)
 * @brief メイン関数、ループ関数など、主処理を実装するファイル
 * @date 2023-04-06
 *
 */

#include "header.h"
#include "screens/ReadingScreen.h"
#include "screens/SettingTimeIntervalScreen.h"
#include "screens/ScreenBase.h"

LGFX Llcd;                 // LGFXのインスタンスを作成（クラスLGFXを使ってlcdコマンドでいろいろできるようにする）
LGFX_Sprite canvas(&Llcd); // スプライトを使う場合はLGFX_Spriteのインスタンスを作成
FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

static ReadingScreen readingScreen(0, 1, "bookName");
static SettingTimeIntervalScreen settingTimeScreen;
static ScreenBase *screens[2];
static int currentScreenNumber = 0;

/**
 * M5Stackの初期化関数
 * システムによって自動的に呼び出される
 */
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

/**
 * M5Stackのメインループ関数
 * システムによって自動的に呼び出される
 */
void loop()
{
  M5.update();
  screens[currentScreenNumber]->scereenUpdate();

  // Bボタンを3秒間ホールドするとtogglePowerLcd()を呼び出す.
  // さらに5秒間ホールドすると、シャットダウン
  if (M5.BtnB.pressedFor(3000))
  {
    togglePowerLcd();
    if (M5.BtnB.pressedFor(5000))
    {
      M5.shutdown();
    }
  }

  if (M5.BtnA.wasPressed())
  {
    togglePowerLcd();
  }
}

/**
 * 画面遷移のテストの時に、メインループで呼び出す関数
 * ボタンによって画面遷移を行う
 */
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
