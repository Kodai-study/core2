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
    M5.Rtc.SetTime(&tr);
    M5.Rtc.SetDate(&dt);
    M5.Rtc.begin();
    return currentTime;
}

// ミリ秒のUNIXTIMEを引数で受け取って、その時間をRTCにセットする

bool connectingWifi()
{
    Llcd.setCursor(0, 0);
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
        if (_cursorX > 5)
        {
            _cursorX = 0;
            Llcd.println("\nConnectionFailed");
            delay(1000);
            return false;
        }
    }
    Llcd.fillScreen(BLACK);
    Llcd.setCursor(0, 0);
    Llcd.print("Connected with IP:");
    Llcd.print(WiFi.localIP());
    Llcd.println("\nConnected!!");
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
    Llcd.fillScreen(BLACK);
    Llcd.setCursor(0, 0);
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
    String timeString = "";
    timeString += String(date.Year) + "/";
    timeString += String(date.Month) + "/";
    timeString += String(date.Date) + " ";
    timeString += String(time.Hours) + ":";
    timeString += String(time.Minutes) + ":";
    timeString += String(time.Seconds);
    return timeString;
}