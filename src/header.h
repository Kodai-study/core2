/**
 * @file header.h
 * @author Kodai-study (anchor.kou@softbank.ne.jp)
 * @brief プロジェクト内で共通して使うライブラリのインクルードや定数、関数の宣言を行うヘッダファイル
 * @date 2023-04-06
 */

#ifndef HEADER_H
#define HEADER_H

#define LGFX_AUTODETECT
#define LGFX_USE_V1
#define FIREBASE_HOST "modular-source-342310-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "yx1PO3FwKiYzo1wN5NedZAYqN2S26TH57kVmE4ZW"

#define WIFI_SSID "aterm-b9044b-g"
#define WIFI_PASSWORD "1ca1af621dff7"

// #define WIFI_SSID "Buffalo-G-458A"
// #define WIFI_PASSWORD "hi6bmsk85557v"

// #define WIFI_SSID "Pixel_8000"
// #define WIFI_PASSWORD "45451919"

// #define WIFI_SSID "IODATA-298088-2G"
// #define WIFI_PASSWORD "Fx8EM83998089"

#include <Arduino.h>
#include <FirebaseESP32.h>
#include <M5Core2.h>
#include <LovyanGFX.hpp>       // lovyanGFXのヘッダを準備
#include <LGFX_AUTODETECT.hpp> // クラス"LGFX"を準備
#include "Setting.h"

extern LGFX Llcd; // LGFXのインスタンスを作成（クラスLGFXを使ってlcdコマンドでいろいろできるようにする）
extern Setting setting;

// 画面の一覧を定義する列挙型を作成
enum Screen
{
    SCREEN_NONE = -1,
    Screen_Reading,
    Screen_SettingTimeInterval,
    Screen_SelectBook,
    Screen_DateTimeSetting,
    Screen_NUM
};

/**
 * @brief sleepLcd関数でスリープモードとなったLcdを起床させる
 */
void wakeupLcd();
/**
 * @brief Lcdをスリープモードにする。
 * バックライトと液晶のコントラストを0にする。 画面を表示するには、wakeupLcd関数を呼び出す必要がある。
 */
void sleepLcd();
/**
 * @brief Lcdのスリープモードと起床モードを切り替える。
 */
void togglePowerLcd();
/**
 * @brief Firebaseの時刻をRTCにセットする
 * ついでに、Firebaseのデータベースにも、セットした時刻をUNIX時間で保存する
 *
 * @return tm*
 */
tm *setRTC();
/**
 * @brief Wi-Fiへの接続を試みる
 *
 * @return true
 * @return false
 */
bool connectingWifi();

/**
 * @brief 画面遷移を行う関数
 *
 * @param screenList 遷移先の画面を指定する列挙型の変数
 */
void screenTransitionHandler(Screen screenList);

// RTC_TimeTypeDef RTC_DateTypeDef の2つから、日付時刻の文字列を作成する関数
String getDateTimeString(RTC_DateTypeDef date, RTC_TimeTypeDef time);

#endif