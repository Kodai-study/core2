#include <Arduino.h>
#include <FirebaseESP32.h>
#include <M5Core2.h>
#define LGFX_AUTODETECT        // 自動認識(D-duino-32 XS, PyBadgeはパネルID読取れないため自動認識の対象から外れているそうです)
#define LGFX_USE_V1            // v1.0.0を有効に(v0からの移行期間の特別措置とのこと。書かない場合は旧v0系で動作)
#include <LovyanGFX.hpp>       // lovyanGFXのヘッダを準備
#include <LGFX_AUTODETECT.hpp> // クラス"LGFX"を準備
extern LGFX Llcd;              // LGFXのインスタンスを作成（クラスLGFXを使ってlcdコマンドでいろいろできるようにする）