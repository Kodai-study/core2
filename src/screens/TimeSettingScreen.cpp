/**
 * @file ReadingScreen.cpp
 * @author Kodai-study (anchor.kou@softbank.ne.jp)
 * @brief 読書中画面の制御を行うクラス、ReadingScreenの実装を記述するファイル
 * @date 2023-04-06
 */

#include "header.h"
#include "TimeSettingScreen.h"

// TimeSettingScreenクラスで定義した関数の実装
// 全て空の関数として実装

void TimeSettingScreen::initScreen()
{
    M5.Rtc.GetTime(&settingTime);
    M5.Rtc.GetDate(&settingDate);
    this->sampleButton = Button(100, 100, 100, 100, true, "-5", this->defaultColor_ButtonOff, this->defaultColor_ButtonOn);
}

void TimeSettingScreen::deleteScreen()
{
    setting.setDateTime(settingDate, settingTime);
}

void TimeSettingScreen::scereenUpdate()
{
    if (this->sampleButton.wasPressed())
    {
        sampleButton.setLabel("test");
    }
}

void TimeSettingScreen::setRTC()
{
    M5.Rtc.SetTime(&settingTime);
    M5.Rtc.SetDate(&settingDate);
}

String TimeSettingScreen::getDateTimeString()
{
    String timeString = "";
    timeString += String(settingDate.Year) + "/";
    timeString += String(settingDate.Month) + "/";
    timeString += String(settingDate.Date) + " ";
    timeString += String(settingTime.Hours) + ":";
    timeString += String(settingTime.Minutes) + ":";
    timeString += String(settingTime.Seconds);
    return timeString;
}