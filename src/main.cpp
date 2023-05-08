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
#include "screens/TimeSettingScreen.h"
#include "screens/DebugScreen.h"
#include "screens/RegisterBookMarkScreen.h"
#include "screens/SettingHomeScreen.h"

LGFX Llcd;                       // LGFXのインスタンスを作成（クラスLGFXを使ってlcdコマンドでいろいろできるようにする）
LGFX_Sprite canvas(&Llcd);       // スプライトを使う場合はLGFX_Spriteのインスタンスを作成
Setting setting;                 // 設定を保持するクラスのインスタンスを作成
bool isEnableWifiConnect = true; // Wi-Fiに接続されているかどうかのフラグ
BookData readingBook;            // 現在読んでいる本の情報を保持するクラスのインスタンスを作成

static ReadingScreen readingScreen;
static SettingTimeIntervalScreen settingTimeScreen;
static SelectBookScreen selectBookScreen;
static TimeSettingScreen timeSettingScreen;
static DebugScreen debugScreen;
static RegisterBookMarkScreen registerBookMarkScreen;
static SettingHomeScreen settingHomeScreen;

// 画面一覧をまとめた配列。 ScreenBaseの型で基本的な処理のみ実行可能
static ScreenBase *screens[Screen_NUM];
static Screen currentScreenNumber = Screen::Screen_SettingHome;

// ボタンを長押ししたときに1回だけ実行するためのフラグ
static bool buttonB_longPress_flag = false;
static bool buttonC_longPress_flag = false;

/**
 * M5Stackの初期化関数
 * システムによって自動的に呼び出される
 */
void setup()
{
  M5.begin();
  Serial.begin(9600);
  M5.lcd.begin();
  Llcd.init(); // LCD初期化
  screens[Screen_Reading] = &readingScreen;
  screens[Screen_SettingTimeInterval] = &settingTimeScreen;
  screens[Screen_RegisterBookMark] = &registerBookMarkScreen;
  screens[Screen_SelectBook] = &selectBookScreen;
  screens[Screen_DateTimeSetting] = &timeSettingScreen;
  screens[Screen_Debug] = &debugScreen;
  screens[Screen_SettingHome] = &settingHomeScreen;
  setting.readIni();

  bool isWifiConnectSuccess;

  Llcd.setCursor(0, 0);
  Llcd.setFont(&fonts::lgfxJapanGothic_16);

#ifndef DEBUG_WITHOUT_WIFI
#ifndef DEBUG_SSID_WITHOUT_SETTINGFILE

  if (setting.getSSID().equals("NULL") || setting.getWifiPass().equals("NULL"))
  {
    isWifiConnectSuccess = connectingWifi(String(WIFI_SSID), String(WIFI_PASSWORD));
  }
  else
    isWifiConnectSuccess = connectingWifi(setting.getSSID(), setting.getWifiPass());
#else
  isWifiConnectSuccess = connectingWifi(String(WIFI_SSID), String(WIFI_PASSWORD));
#endif
#else
  isWifiConnectSuccess = false;
  isEnableWifiConnect = false;
#endif
  if (isWifiConnectSuccess)
  {
    Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
    Firebase.reconnectWiFi(true);
    setRTC();
  }
  else
  {
    auto time = setting.getTime();
    auto date = setting.getDate();
    M5.Rtc.SetTime(&time);
    M5.Rtc.SetDate(&date);
  }

  screens[(int)currentScreenNumber]->initScreen();
}

/**
 * M5Stackのメインループ関数
 * システムによって自動的に呼び出される
 */
void loop()
{
  M5.update();
  screens[(int)currentScreenNumber]->screenUpdate();

  if (!buttonB_longPress_flag && M5.BtnB.pressedFor(3000))
  {
    togglePowerLcd();
    buttonB_longPress_flag = true;
  }
  else if (buttonB_longPress_flag && !M5.BtnB.isPressed())
  {
    buttonB_longPress_flag = false;
  }

  if (!buttonC_longPress_flag && M5.BtnC.pressedFor(3000))
  {
    screenTransitionHandler(Screen::Screen_Debug);
  }
  else if (buttonC_longPress_flag && !M5.BtnC.isPressed())
  {
    buttonC_longPress_flag = false;
  }

  if (M5.BtnB.pressedFor(5000))
  {
    wakeupLcd();
    Llcd.fillScreen(BLACK);
    Llcd.setCursor(20, 100);
    Llcd.setFont(&fonts::lgfxJapanGothic_40);
    Llcd.print("ShutDown");
    delay(4500);
    M5.shutdown();
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
  if (screenList == Screen::Screen_Reading)
  {
    readingScreen.setCurrentBookData(readingBook);
  }

  screens[(int)currentScreenNumber]->deleteScreen();
  currentScreenNumber = screenList;
  screens[(int)currentScreenNumber]->initScreen();
}