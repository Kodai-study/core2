#ifndef HEADER
#define HEADER

#define LGFX_AUTODETECT // 自動認識(D-duino-32 XS, PyBadgeはパネルID読取れないため自動認識の対象から外れているそうです)
#define LGFX_USE_V1     // v1.0.0を有効に(v0からの移行期間の特別措置とのこと。書かない場合は旧v0系で動作)
#define FIREBASE_HOST "modular-source-342310-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "yx1PO3FwKiYzo1wN5NedZAYqN2S26TH57kVmE4ZW"
// #define WIFI_SSID "aterm-b9044b-g"
// #define WIFI_PASSWORD "1ca1af621dff7"
#define WIFI_SSID "Buffalo-G-9AD0"
#define WIFI_PASSWORD "icbdi657e6syp"

#include <Arduino.h>
#include <FirebaseESP32.h>
#include <M5Core2.h>
#include <LovyanGFX.hpp>       // lovyanGFXのヘッダを準備
#include <LGFX_AUTODETECT.hpp> // クラス"LGFX"を準備

extern LGFX Llcd; // LGFXのインスタンスを作成（クラスLGFXを使ってlcdコマンドでいろいろできるようにする）

void wakeupLcd();
void sleepLcd();
void togglePowerLcd();
tm *setRTC();
bool connectingWifi();
#endif