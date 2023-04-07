/**
 * @file ReadingScreen.cpp
 * @author Kodai-study (anchor.kou@softbank.ne.jp)
 * @brief 読書中画面の制御を行うクラス、ReadingScreenの実装を記述するファイル
 * @date 2023-04-06
 * 
 */

#include "header.h"
#include "ReadingScreen.h"

void push(Event &e)
{
    Llcd.setCursor(0, 0);
    Llcd.println("PUSHED");
}

void ReadingScreen::initScreen()
{
    ScreenBase::initScreen();
    Llcd.fillScreen(BLACK);
    Llcd.setCursor(16, 38);
    Llcd.setTextFont(&fonts::lgfxJapanMinchoP_24);
    Llcd.print(isWifiConnected);
    Llcd.printf("読書中_%02d分", this->currentPage);
    Llcd.setCursor(20, 209);
    Llcd.println("戻る    前ページ  次ページ");

    Llcd.setCursor(64, 96);
    Llcd.setTextFont(&fonts::lgfxJapanMinchoP_40);
    Llcd.printf("ページ:%03d", this->currentPage);
    btn_x = Button(220, 10, 100, 60, true, "Start", this->defaultColor_ButtonOff, this->defaultColor_ButtonOn);
    btn_x.addHandler(push, E_RELEASE);
    btn_x.draw();
    Llcd.setCursor(0, 0);
}

ReadingScreen::ReadingScreen(int index, int currentPage, String bookName)
    : currentPage(currentPage), btn_x(0, 0, 0, 0)
{
    this->bookName = bookName;
}

void ReadingScreen::deleteScreen()
{
    this->btn_x.erase(BLACK);
    this->btn_x.set(0, 0, 0, 0);
}

void ReadingScreen::scereenUpdate()
{
    if (M5.BtnC.wasPressed())
    {
        FirebaseData writeData;
        FirebaseJson pageFlipRecord;
        char dateTimeStringBuffer[30];
        RTC_DateTypeDef date;
        RTC_TimeTypeDef time;
        M5.Rtc.GetDate(&date);
        M5.Rtc.GetTime(&time);
        sprintf(dateTimeStringBuffer, "%04d-02d-02d %02d:%02d:%02d", date.Year, date.Month, date.Date,
                time.Hours, time.Minutes, time.Seconds);
        pageFlipRecord.set("dateTime", dateTimeStringBuffer);
        pageFlipRecord.set("page", this->currentPage);
        pageFlipRecord.set("mode", this->currentMode);
        if (isWifiConnected)
        {
            Firebase.pushJSON(writeData, DATA_PAGEFLIP_PATH + readingBookIndex, pageFlipRecord);
            Llcd.println("FirebaseWrite");
        }

        String JSONString;
        if (pageFlipRecord.toString(JSONString, true))
            Llcd.println(JSONString);
    }
}
