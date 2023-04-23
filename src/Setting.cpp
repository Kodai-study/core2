// Setting.cpp に書いてある内容を、Setting.h の宣言を実装する形に書き換える
#include "header.h"

Setting::Setting()
{
    readIni();
}

void Setting::setSSID(String ssid)
{
    this->ssid = ssid;
    writeIni();
}

void Setting::setDateTime(RTC_DateTypeDef date, RTC_TimeTypeDef time)
{
    this->date = date;
    this->time = time;
    writeIni();
}

void Setting::setWifiPass(String wifiPass)
{
    this->wifiPass = wifiPass;
    writeIni();
}

void Setting::setTimeInterval(int timeInterval)
{
    this->timeInterval = timeInterval;
    writeIni();
}

void Setting::setRepeat(int repeat)
{
    this->repeat = repeat;
    writeIni();
}

String Setting::getSSID()
{
    return ssid;
}
String Setting::getWifiPass()
{
    return wifiPass;
}
int Setting::getTimeInterval()
{
    return timeInterval;
}
int Setting::getRepeat()
{
    return repeat;
}

void Setting::writeIni() // write to SD card
{
    File file = SD.open(SETTING_FILE_NAME, FILE_WRITE, true); // open file
    if (file)
    {
        file.print("SSID="); // write SSID to file
        file.println(ssid);
        file.print("PASS="); // write password to file
        file.println(wifiPass);
        file.print("TIME="); // write time to file
        file.println(timeInterval);
        file.print("REPEAT="); // write repeat to file
        file.println(repeat);
        file.print("DATE="); // write date to file
        file.println(getDateTimeString(date, time));
        file.close(); // close file
    }
    else
    {
        Serial.println("file open failed");
    }
}

void Setting::readIni()
{
    File file = SD.open(SETTING_FILE_NAME, FILE_READ, true);
    if (file)
    {
        while (file.available())
        {
            String line = file.readStringUntil('\n');
            line.trim();
            if (line.startsWith("SSID="))
            {
                this->ssid = line.substring(5);
            }
            else if (line.startsWith("PASS="))
            {
                wifiPass = line.substring(5);
            }
            else if (line.startsWith("TIME="))
            {
                timeInterval = line.substring(5).toInt();
            }
            else if (line.startsWith("REPEAT="))
            {
                repeat = line.substring(7).toInt();
            }
            else if (line.startsWith("DATE="))
            {
                String dateStr = line.substring(5);
                // header.h で定義した、文字列から日付と時刻を取得する関数を呼び出す
                getDateTimeFromString(dateStr, date, time);
            }
        }
        file.close();
    }
    else
    {
        Serial.println("file open failed");
    }
}

String Setting::getDateTime()
{
    // header.h で定義した、日付と時刻から文字列を作成する関数を呼び出す
    return getDateTimeString(date, time);
}

// 日付、時刻の2つのローカル変数のゲッタを作成
RTC_DateTypeDef Setting::getDate()
{
    return date;
}

RTC_TimeTypeDef Setting::getTime()
{
    return time;
}

void Setting::printAllSetting()
{
    Serial.println("SSID: " + ssid);
    Serial.println("PASS: " + wifiPass);
    Serial.println("TIME: " + String(timeInterval));
    Serial.println("REPEAT: " + String(repeat));
    Serial.println("DATE: " + getDateTime());
}

String SSID_COLUM[] = {"aterm-b9044b-g", "Buffalo-G-458A", "Pixel_8000", "IODATA-298088-2G"};
String WIFI_PASS_COLUM[] = {"1ca1af621dff7", "hi6bmsk85557v", "45451919", "Fx8EM83998089"};
