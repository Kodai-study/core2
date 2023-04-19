/**
 * @file main.cpp
 * @author Kodai-study (anchor.kou@softbank.ne.jp)
 * @brief メイン関数、ループ関数など、主処理を実装するファイル
 * @date 2023-04-06
 */

#include "header.h"
#include "screens/ReadingScreen.h"
#include "screens/SettingTimeIntervalScreen.h"
#include "screens/ScreenBase.h"
#include "screens/SelectBookScreen.h"

LGFX Llcd;                 // LGFXのインスタンスを作成（クラスLGFXを使ってlcdコマンドでいろいろできるようにする）
LGFX_Sprite canvas(&Llcd); // スプライトを使う場合はLGFX_Spriteのインスタンスを作成

static ReadingScreen readingScreen(0, 1, "bookName");
static SettingTimeIntervalScreen settingTimeScreen;
static SelectBookScreen selectBookScreen;

// 画面一覧をまとめた配列。 ScreenBaseの型で基本的な処理のみ実行可能
static ScreenBase *screens[Screen_NUM];
static Screen currentScreenNumber = Screen_SelectBook;
static bool buttonInput = false;

/**
 * M5Stackの初期化関数
 * システムによって自動的に呼び出される
 */
void setup()
{
  M5.begin();
  M5.lcd.begin();
  Llcd.init(); // LCD初期化
  screens[Screen_Reading] = &readingScreen;
  screens[Screen_SettingTimeInterval] = &settingTimeScreen;
  screens[Screen_SelectBook] = &selectBookScreen;
  if (connectingWifi())
  {
    Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
    Firebase.reconnectWiFi(true);
    setRTC();
  }
  for (int i = 0; i < Screen_NUM; i++)
  {
    if (i != (int)currentScreenNumber)
      screens[i]->deleteScreen();
    else
      screens[i]->initScreen();
  }
  Serial.begin(9600);
}

/**
 * M5Stackのメインループ関数
 * システムによって自動的に呼び出される
 */
void loop()
{
  M5.update();
  screens[(int)currentScreenNumber]->scereenUpdate();

  if (!buttonInput && M5.BtnB.pressedFor(3000))
  {
    togglePowerLcd();
    buttonInput = true;
  }
  else if (buttonInput && !M5.BtnB.isPressed())
  {
    buttonInput = false;
  }

  if (M5.BtnB.pressedFor(5000))
  {
    M5.shutdown(5);
    wakeupLcd();
    Llcd.fillScreen(BLACK);
    Llcd.setCursor(200, 100);
    Llcd.setFont(&fonts::lgfxJapanGothic_40);
    Llcd.print("ShutDown");
    delay(4500);
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

/**
 * @brief 遷移先の画面を選択して、画面遷移を行う関数
 *
 * @param screenList Screen列挙型の中で、遷移先の画面を選択する
 */
void screenTransitionHandler(Screen screenList)
{
  screens[(int)currentScreenNumber]->deleteScreen();
  switch (screenList)
  {
  case Screen::Screen_Reading:
    readingScreen.initScreen();
    break;
  case Screen::Screen_SettingTimeInterval:
    settingTimeScreen.initScreen();
    break;
  case Screen::Screen_SelectBook:
    selectBookScreen.initScreen();
    break;
  default:
    break;
  }
}