/**
 * @file util.cpp
 * @author Kodai-study (anchor.kou@softbank.ne.jp)
 * @brief プロジェクト内で共通して使う関数の実装
 * @date 2023-04-06
 *
 */
#include "header.h"
#include <LinkedList.h>

/**
 * @brief SDカードが読み取り可能かどうかを確認する関数
 *
 * @param path
 * @param list
 * @return true
 * @return false
 */
bool sdCheck(const char *path, LinkedList<String> list)
{
    File fp = SD.open(path, FILE_READ);
    if (!fp)
    {
        Llcd.println("NO SD!!");
        return false;
    }
    while (fp.available())
    {
        list.add(fp.readStringUntil('\n'));
    }
    return true;
}

/**
 * @brief
 *
 * @param lineData
 * @param index
 * @return String
 */
String getCSVColum(String lineData, int index)
{
    static const char kugiri = ',';
    int firstIndex = 0;
    int last = lineData.indexOf(kugiri);
    if (index == 0)
    {
        return lineData.substring(last);
    }
    else
    {
        for (int i = 0; i < index; i++)
        {
            firstIndex = last + 1;
            last = lineData.indexOf(kugiri);
        }
        return lineData.substring(firstIndex, last);
    }
}

bool isLcdOn = true;

void wakeupLcd()
{
    isLcdOn = true;
    M5.Axp.SetLcdVoltage(3000);
    M5.Axp.SetDCDC3(true);
    M5.lcd.wakeup();
}

void sleepLcd()
{
    isLcdOn = false;
    M5.Axp.SetDCDC3(false);
    M5.Axp.SetLed(0);
    M5.Lcd.sleep();
}

void togglePowerLcd()
{
    isLcdOn = !isLcdOn;
    if (isLcdOn)
    {
        wakeupLcd();
    }
    else
    {
        sleepLcd();
    }
}

// ミリ秒のUNIXTIMEを引数で受け取って、その時間を表示する

tm *setRTC()
{
    FirebaseData data;
    Firebase.setTimestamp(data, "lastUpdateTime");
    time_t unixTime = (int)(data.doubleData());

    // ミリ秒単位のUNIX時間から、日本時間の tm 構造体を取得する

    auto currentTime = localtime(&unixTime);
    unixTime = data.intData();
    unixTime += (60 * 60 * 9);
    currentTime = localtime(&unixTime);
    RTC_TimeTypeDef tr;
    RTC_DateTypeDef dt;
    tr.Hours = (uint8_t)(currentTime->tm_hour);
    tr.Minutes = (uint8_t)(currentTime->tm_min);
    tr.Seconds = (uint8_t)(currentTime->tm_sec);

    dt.WeekDay = (uint8_t)(currentTime->tm_wday + 1);
    dt.Month = (uint8_t)(currentTime->tm_mon + 1);
    dt.Date = (uint8_t)(currentTime->tm_mday);
    dt.Year = (uint16_t)(currentTime->tm_year + 1900);

    setting.setDateTime(dt, tr);

    M5.Rtc.SetTime(&tr);
    M5.Rtc.SetDate(&dt);
    M5.Rtc.begin();
    return currentTime;
}

// ミリ秒のUNIXTIMEを引数で受け取って、その時間をRTCにセットする

bool connectingWifi(String wifiSSID, String wifiPassWord)
{
    M5.update();
    int _cursorX = 0;
    WiFi.begin(wifiSSID.c_str(), wifiPassWord.c_str());

    Serial.print("SSID: ");
    Serial.println(wifiSSID.c_str());
    Serial.print("PASS: ");
    Serial.println(wifiPassWord.c_str());
    Llcd.print("Connecting to Wi-Fi");
    while (WiFi.status() != WL_CONNECTED)
    {
        M5.update();
        Llcd.print(".");
        delay(300);
        _cursorX++;
        if (_cursorX > 15 || M5.BtnA.isPressed() || M5.BtnA.wasPressed())
        {
            isEnableWifiConnect = false;
            _cursorX = 0;
            Llcd.println("\nConnectionFailed");
            delay(1000);
            return false;
        }
    }
    Llcd.print(WiFi.localIP());
    Llcd.println("  Connected!!");
    setting.setSSID(wifiSSID);
    setting.setWifiPass(wifiPassWord);
    delay(1000);
    return true;
}

void printDirectory(File dir, int numTabs)
{
    while (true)
    {
        File entry = dir.openNextFile();
        if (!entry)
        {
            dir.rewindDirectory();
            break;
        }
        for (uint8_t i = 0; i < numTabs; i++)
        {
            Llcd.print('\t');
        }
        Llcd.print(entry.name());
        if (entry.isDirectory())
        {
            Llcd.println("/");
            printDirectory(entry, numTabs + 1);
        }
        else
        {
            Llcd.println("\t\t");
        }
    }
}

// ボタンを画面に設置して、対応するSSIDのWIFIに接続する。
// 接続に成功したかどうかをbooleanで返す
// 接続するSSID,WIFIパスワードは、配列に保存されている
// 3秒間接続できなかったら、falseを返す
// 引数は、ボタン番号の1つ
boolean connectWifi(int btn)
{
    boolean connect = false;
    Llcd.setTextSize(2);
    Llcd.setTextColor(WHITE);
    Llcd.println("接続中...");
    Llcd.println("接続先:");
    // Llcd.println(ssid[btn]);
    Llcd.println("パスワード:");
    // Llcd.println(pass[btn]);
    Llcd.println("接続中...");
    // WiFi.begin(ssid[btn], pass[btn]);
    int cnt = 0;
    while (WiFi.status() != WL_CONNECTED && cnt < 30)
    {
        delay(100);
        cnt++;
    }
    if (WiFi.status() == WL_CONNECTED)
    {
        connect = true;
    }
    return connect;
}

String getDateTimeString(RTC_DateTypeDef date, RTC_TimeTypeDef time)
{
    char buf[32];
    sprintf(buf, "%04d/%02d/%02d %02d:%02d:%02d", date.Year, date.Month, date.Date, time.Hours, time.Minutes, time.Seconds);
    return String(buf);
}

// 一つ上の関数とは逆に、日付の文字列から RTC_DateTypeDef date, RTC_TimeTypeDef time を取得する
void getDateTimeFromString(String str, RTC_DateTypeDef &date, RTC_TimeTypeDef &time)
{
    int year = str.substring(0, 4).toInt();
    int month = str.substring(5, 7).toInt();
    int day = str.substring(8, 10).toInt();
    int hour = str.substring(11, 13).toInt();
    int minute = str.substring(14, 16).toInt();
    int second = str.substring(17, 19).toInt();
    date.Year = year;
    date.Month = month;
    date.Date = day;
    time.Hours = hour;
    time.Minutes = minute;
    time.Seconds = second;
}