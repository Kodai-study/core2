#include <Arduino.h>
#include <FirebaseESP32.h>
#include <M5Core2.h>
#define LGFX_AUTODETECT          // 自動認識(D-duino-32 XS, PyBadgeはパネルID読取れないため自動認識の対象から外れているそうです)
#define LGFX_USE_V1              // v1.0.0を有効に(v0からの移行期間の特別措置とのこと。書かない場合は旧v0系で動作)
#include <LovyanGFX.hpp>         // lovyanGFXのヘッダを準備
#include <LGFX_AUTODETECT.hpp>   // クラス"LGFX"を準備
static LGFX lcd;                 // LGFXのインスタンスを作成（クラスLGFXを使ってlcdコマンドでいろいろできるようにする）
static LGFX_Sprite canvas(&lcd); // スプライトを使う場合はLGFX_Spriteのインスタンスを作成

#define FIREBASE_HOST "modular-source-342310-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "yx1PO3FwKiYzo1wN5NedZAYqN2S26TH57kVmE4ZW"
#define WIFI_SSID "aterm-b9044b-g"
#define WIFI_PASSWORD "1ca1af621dff7"

FirebaseData firebaseData;

bool statusA = true;
bool statusB = true;
bool statusC = true;

bool buttonProcess(String buttonName, bool status)
{
    lcd.fillScreen(BLACK);
    if (Firebase.setBool(firebaseData, "/" + buttonName + "/", status))
    {
        // Success
        lcd.setCursor(0, 0);
        lcd.print("Set bool data success やった!\n"); // 表示内容をcanvasに準備

        lcd.println("液晶表示 明朝体"); // 表示内容をcanvasに準備
        lcd.println("液晶表示 明朝体");
        FirebaseData data;
        if (!Firebase.get(data, "/readDatas/0"))
            return false;
        lcd.setCursor(0, 0);
        lcd.fillScreen(BLACK);
        delay(2000);
        lcd.println(data.stringData());
        lcd.println(data.jsonString());

        delay(2000);
        lcd.setCursor(0, 0);
        lcd.fillScreen(BLACK);
        Firebase.getArray(data, "/readDatas/0");
        lcd.print(data.dataType());

        FirebaseJsonArray array;
        array = data.jsonArray();
        lcd.println(array.size());
        FirebaseJsonData jsonData;
        if(! array.get(jsonData, 1)){
            lcd.println("配列取得失敗");
        }
        FirebaseJson json;
        lcd.println(jsonData.stringValue);
        jsonData.get(json);
        json.get(jsonData,"dateTime");
        lcd.println(jsonData.stringValue);
    }
    else
    {
        lcd.setCursor(0, 0);
        lcd.println("Error in setInt, ");
        lcd.print(firebaseData.errorReason());
    }
    lcd.setCursor(0, 20);
    lcd.print(buttonName + " was pressed!");
    return status = !status;
}

void setup()
{
    M5.begin();
    Serial.begin(115200);
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

    lcd.init(); // LCD初期化
    int _cursorX = 0;
    lcd.setTextFont(4);
    lcd.setTextColor(WHITE);
    lcd.setCursor(0, 0);
    lcd.setTextColor(WHITE);
    lcd.setCursor(0, 0);
    // WiFiに接続
    lcd.print("Connecting to Wi-Fi");
    while (WiFi.status() != WL_CONNECTED)
    {
        Serial.print(".");
        lcd.setCursor(0 + 5 * _cursorX, 30);
        lcd.print(".");
        delay(300);
        _cursorX++;
        if (_cursorX > 320)
        {
            _cursorX = 0;
        }
    }

    lcd.fillScreen(BLACK);
    lcd.setCursor(0, 0);
    lcd.print("Connected with IP:");
    lcd.print(WiFi.localIP());
    lcd.setTextFont(&fonts::lgfxJapanMinchoP_32); // 明朝体（8,12,16,20,24,28,32,36,40）
    lcd.println("液晶表示 明朝体");               // 表示内容をcanvasに準備
    lcd.println("M5のメソッドで日本語表示");
    delay(1000);
    // Firebase関連
    Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
    Firebase.reconnectWiFi(true);
}

void loop()
{
    M5.update();
    if (M5.BtnA.wasPressed())
    {
        statusA = buttonProcess("BtnA", statusA);
    }
    if (M5.BtnB.wasPressed())
    {
        statusB = buttonProcess("BtnB", statusB);
    }
    if (M5.BtnC.wasPressed())
    {
        statusC = buttonProcess("BtnC", statusC);
    }
}