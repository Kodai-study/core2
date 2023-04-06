/**
 * @file util.cpp
 * @author Kodai-study (anchor.kou@softbank.ne.jp)
 * @brief プロジェクト内で共通して使う関数の実装
 * @date 2023-04-06
 * 
 */
#include "header.h"
#include <LinkedList.h>

bool sdCheck(const char *path, LinkedList<String> list)
{
    File fp = SD.open(path, "rw", false);
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
        if (_cursorX > 20)
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
