/**
 * @file ReadingScreen.cpp
 * @author Kodai-study (anchor.kou@softbank.ne.jp)
 * @brief 読書中画面の制御を行うクラス、ReadingScreenの実装を記述するファイル
 * @date 2023-04-06
 */

#include "header.h"
#include "ReadingScreen.h"
#include "module/PageFlipData.h"

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

    if (isWifiConnected && readDataindex == -1)
    {
        FirebaseData data;
        FirebaseJsonArray array;
        FirebaseJson json;
        Firebase.getArray(data, DATA_PAGEFLIP_PATH + readingBookIndex);
        array = data.jsonArray();
        readDataindex = array.size();
        FirebaseJsonData jsonData;
        if (!array.get(jsonData, 1))
        {
            Llcd.println("配列取得失敗");
            return;
        }
    }
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
    this->csvManager.closeFile();
}

void ReadingScreen::scereenUpdate()
{
    if (M5.BtnC.wasPressed())
    {
        FirebaseData writeData;
        char dateTimeStringBuffer[30];
        RTC_DateTypeDef date;
        RTC_TimeTypeDef time;
        M5.Rtc.GetDate(&date);
        M5.Rtc.GetTime(&time);

        sprintf(dateTimeStringBuffer, "%04d-%02d-%02d %02d:%02d:%02d", date.Year, date.Month, date.Date,
                time.Hours, time.Minutes, time.Seconds);
        PageFlipHistory pageFlipHistory(
            String(dateTimeStringBuffer), currentMode, currentPage);
        FirebaseJson *json = pageFlipHistory.getJson();

        if (isWifiConnected || readDataindex < 0)
        {
            this->csvManager.writeLine(pageFlipHistory.getCsvLine());
        }
        else
        {
            if (!Firebase.setJSON(writeData, DATA_PAGEFLIP_PATH + readingBookIndex + "/" + readDataindex++, *json))
                this->csvManager.writeLine(pageFlipHistory.getCsvLine());
        }
    }
}

int ReadingScreen::getreadDataindex()
{
    return this->readDataindex;
}
