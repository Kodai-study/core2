/**
 * @file ReadingScreen.cpp
 * @author Kodai-study (anchor.kou@softbank.ne.jp)
 * @brief 読書中画面の制御を行うクラス、ReadingScreenの実装を記述するファイル
 * @date 2023-04-06
 */

#include "header.h"
#include "ReadingScreen.h"
#include "module/PageFlipData.h"

// TODO 1分ごとにカウントダウンを減らし、0になったらバイブレーションを鳴らす
// TODO 設定ファイルから、集中モードと休憩モードの時間を取得して設定

void ReadingScreen::initScreen()
{
    ScreenBase::initScreen();
    Llcd.fillScreen(BLACK);
    Llcd.setCursor(16, 38);
    Llcd.setTextFont(&fonts::lgfxJapanMinchoP_24);
    Llcd.print(isEnableWifiConnect);
    Llcd.printf("読書中_%02d分", setting.getTimeInterval());
    Llcd.setCursor(20, 209);
    Llcd.println("戻る    前ページ  次ページ");

    Llcd.setCursor(64, 96);
    Llcd.setTextFont(&fonts::lgfxJapanMinchoP_40);
    Llcd.printf("ページ:%03d", this->currentPage);
    btn_x = Button(220, 10, 100, 60, true, "Start", this->defaultColor_ButtonOff, this->defaultColor_ButtonOn);
    btn_x.draw();
    Llcd.setCursor(0, 0);
}

ReadingScreen::ReadingScreen()
    : btn_x(0, 0, 0, 0)
{
}

/**
 * @brief 現在読んでいる本のデータをセットする
 *
 * @param currentBookData 現在読んでいる本のデータ
 */
void ReadingScreen::setCurrentBookData(BookData currentBookData)
{
    this->currentBookData = currentBookData;
    this->currentPage = currentBookData.getCurrentPage();
    this->memoIndex = currentBookData.getMemoDataSize();
}

void ReadingScreen::deleteScreen()
{
    this->btn_x.erase(BLACK);
    this->btn_x.set(0, 0, 0, 0);
    Llcd.fillScreen(BLACK);
}

void ReadingScreen::screenUpdate()
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
            String(dateTimeStringBuffer), currentMode, this->currentPage);
        FirebaseJson *json = pageFlipHistory.getJson();

        if (!isWifiConnected)
        {
            CsvManager csvManager = CsvManager(CSV_FILE_PATH, true);
            csvManager.writeLine(pageFlipHistory.getCsvLine());
            csvManager.closeFile();
        }
        else
        {
            if (!Firebase.setJSON(writeData, DATA_PAGEFLIP_PATH + currentBookData.getBookIndex() + "/" + memoIndex++, *json))
            {
                CsvManager csvManager = CsvManager(CSV_FILE_PATH, true);
                csvManager.writeLine(pageFlipHistory.getCsvLine());
                csvManager.closeFile();
            }
            String bookPageDataPath = String("/bookDatas/") + currentBookData.getBookIndex() + "/currentPage";
            Firebase.setInt(writeData, bookPageDataPath, this->currentPage);
        }
        currentPage++;
        updatePageView();
    }

    // ボタンBが押されたとき、グローバル変数の本データのページ数を更新し、画面遷移する
    if (M5.BtnB.wasPressed())
    {
        this->currentBookData.setCurrentPage(this->currentPage);
        readingBook.setCurrentPage(this->currentPage);
        screenTransitionHandler(Screen::Screen_RegisterBookMark);
    }

    if (btn_x.wasPressed())
    {
        screenTransitionHandler(Screen::Screen_SettingHome);
    }
}

/**
 * @brief ページ数の表示を更新する
 *
 */
void ReadingScreen::updatePageView()
{
    Llcd.fillRect(0, 0, 320, 40, BLACK);
    Llcd.setCursor(64, 96);
    Llcd.setTextFont(&fonts::lgfxJapanMinchoP_40);
    Llcd.printf("ページ:%03d", this->currentPage);
}

void ReadingScreen::updateTimeView()
{
    Llcd.fillRect(0, 50, 320, 60, BLACK);
    Llcd.setCursor(16, 38);
    Llcd.setTextFont(&fonts::lgfxJapanMinchoP_24);
    Llcd.printf("読書中_%02d分", setting.getTimeInterval());
}