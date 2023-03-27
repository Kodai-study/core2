#include <Arduino.h>
#include <FirebaseESP32.h>
#include <M5Core2.h>
#define LGFX_AUTODETECT        // 自動認識(D-duino-32 XS, PyBadgeはパネルID読取れないため自動認識の対象から外れているそうです)
#define LGFX_USE_V1            // v1.0.0を有効に(v0からの移行期間の特別措置とのこと。書かない場合は旧v0系で動作)
#include <LovyanGFX.hpp>       // lovyanGFXのヘッダを準備
#include <LGFX_AUTODETECT.hpp> // クラス"LGFX"を準備
LGFX Llcd;                     // LGFXのインスタンスを作成（クラスLGFXを使ってlcdコマンドでいろいろできるようにする）
LGFX_Sprite canvas(&Llcd);     // スプライトを使う場合はLGFX_Spriteのインスタンスを作成
#define FIREBASE_HOST "modular-source-342310-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "yx1PO3FwKiYzo1wN5NedZAYqN2S26TH57kVmE4ZW"
#define WIFI_SSID "aterm-b9044b-g"
#define WIFI_PASSWORD "1ca1af621dff7"

void event_btn_x(Event &e)
{
    M5.Axp.SetLDOEnable(3, true);
    delay(500);
    M5.Axp.SetLDOEnable(3, false);
    M5.Buttons.draw();
}
class SampleTest
{
public:
    FirebaseData firebaseData;

    bool statusA = true;
    bool statusB = true;
    bool statusC = true;
    ButtonColors cl_on = {CYAN, WHITE, WHITE};      // タップした時の色 (背景, 文字列, ボーダー)
    ButtonColors cl_off = {DARKCYAN, WHITE, WHITE}; // 指を離した時の色 (背景, 文字列, ボーダー)
    // ボタン定義名( X軸, Y軸, 横幅, 高さ, 回転, ボタンのラベル, 指を離した時の色指定, タッチした時の色指定）
    Button btn_x;
    Button btn_y;

    bool buttonProcess(String buttonName, bool status)
    {
        Llcd.fillScreen(BLACK);
        if (Firebase.setBool(firebaseData, "/" + buttonName + "/", status))
        {
            tm *currentTime;
            getJson();
            delay(2000);
            getJsonArray();
            delay(2000);
            currentTime = setRTC();
            delay(2000);
            printCurrentTime();
            Llcd.print(currentTime);
        }
        else
        {
            Llcd.setCursor(0, 0);
            Llcd.println("Error in setInt, ");
            Llcd.print(firebaseData.errorReason());
        }
        Llcd.setCursor(0, 20);
        Llcd.print(buttonName + " was pressed!");
        return status = !status;
    }

    void beginSample()
    {
        M5.begin();
        Serial.begin(115200);

        Llcd.init(); // LCD初期化
        Llcd.setTextFont(4);
        Llcd.setTextColor(WHITE);
        Llcd.setCursor(0, 0);
        // WiFiに接続
        Llcd.setTextFont(&fonts::lgfxJapanMinchoP_32); // 明朝体（8,12,16,20,24,28,32,36,40）
        Llcd.println("液晶表示 明朝体");               // 表示内容をcanvasに準備
        Llcd.println("M5のメソッドで日本語表示");
        delay(1000);
        // Firebase関連
        Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
        Firebase.reconnectWiFi(true);

        M5.Buttons.setFreeFont(2);
        this->btn_x.setFreeFont(2);
        this->btn_y.setFreeFont(1);
        this->btn_y.addHandler(event_btn_x, E_TOUCH);
        this->btn_x.addHandler(event_btn_x, E_RELEASE);

        M5.Buttons.draw();
    }

    void loopSample()
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

    void getJson()
    {
        FirebaseData data;
        if (!Firebase.get(data, "/readDatas/0"))
            return;
        Llcd.setCursor(0, 0);
        Llcd.fillScreen(BLACK);
        Llcd.println(data.jsonString());
        data.jsonString();
    }

    void getJsonArray()
    {
        FirebaseData data;
        FirebaseJsonArray array;
        FirebaseJson json;
        Llcd.setCursor(0, 0);
        Llcd.fillScreen(BLACK);
        Firebase.getArray(data, "/readDatas/0");

        array = data.jsonArray();
        Llcd.println(array.size());
        FirebaseJsonData jsonData;
        if (!array.get(jsonData, 1))
        {
            Llcd.println("配列取得失敗");
            return;
        }
        Llcd.println(jsonData.stringValue);
        jsonData.get(json);
        json.get(jsonData, "dateTime");
        Llcd.println(jsonData.stringValue);
    }

    tm *setRTC()
    {
        FirebaseData data;
        Firebase.setTimestamp(data, "lastUpdateTime");
        const time_t unixTime = data.intData() + (1000 * 3600 * 9);
        auto currentTime = localtime(&unixTime);
        RTC_TimeTypeDef tr = {0, 0, 0};
        RTC_DateTypeDef dt = {0, 0, 0};
        tr.Hours = (uint8_t)(currentTime->tm_hour);
        tr.Minutes = (uint8_t)(currentTime->tm_min);
        tr.Seconds = (uint8_t)(currentTime->tm_sec);
        dt.Year = (uint16_t)(currentTime->tm_year + 1900);
        dt.Month = (uint8_t)(currentTime->tm_mon + 1);
        dt.Date = (uint8_t)(currentTime->tm_mday);
        M5.Rtc.SetTime(&tr);
        M5.Rtc.SetDate(&dt);
        M5.Rtc.begin();
        return currentTime;
    }

    void printCurrentTime()
    {
        RTC_TimeTypeDef tr = {0, 0, 0};
        RTC_DateTypeDef dt = {0, 0, 0};
        Llcd.setCursor(0, 0);
        Llcd.fillScreen(BLACK);
        M5.Rtc.GetTime(&tr);
        M5.Rtc.GetDate(&dt); // Get the date of the real-time clock.
        M5.Lcd.setCursor(0, 15);
        Llcd.printf("Data: %04d-%02d-%02d\n", dt.Year, dt.Month, dt.Date); // Output the date of the current real-time clock on the screen.
        Llcd.printf("Week: %d\n", dt.WeekDay);
        Llcd.printf("Time: %02d : %02d : %02d\n", tr.Hours, tr.Minutes, tr.Seconds);
    }

    bool connectingWifi()
    {
        int _cursorX = 0;
        WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
        Llcd.print("Connecting to Wi-Fi");
        while (WiFi.status() != WL_CONNECTED)
        {
            Serial.print(".");
            Llcd.setCursor(0 + 5 * _cursorX, 30);
            Llcd.print(".");
            delay(300);
            _cursorX++;
            if (_cursorX > 320)
            {
                _cursorX = 0;
                return false;
            }
        }
        Llcd.fillScreen(BLACK);
        Llcd.setCursor(0, 0);
        Llcd.print("Connected with IP:");
        Llcd.print(WiFi.localIP());
        return true;
    }
};
