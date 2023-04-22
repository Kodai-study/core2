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
    Llcd.fillScreen(BLACK);
    M5.Rtc.GetTime(&settingTime);
    M5.Rtc.GetDate(&settingDate);

    btns[0] = Button(BTN_POSITIONS[0].x, BTN_POSITIONS[0].y, BTN_SIZE.x, BTN_SIZE.y, true, "+10", this->defaultColor_ButtonOff, this->defaultColor_ButtonOn);
    btns[1] = Button(BTN_POSITIONS[1].x, BTN_POSITIONS[1].y, BTN_SIZE.x, BTN_SIZE.y, true, "+1", this->defaultColor_ButtonOff, this->defaultColor_ButtonOn);
    btns[2] = Button(BTN_POSITIONS[2].x, BTN_POSITIONS[2].y, BTN_SIZE.x, BTN_SIZE.y, true, "-1", this->defaultColor_ButtonOff, this->defaultColor_ButtonOn);
    btns[3] = Button(BTN_POSITIONS[3].x, BTN_POSITIONS[3].y, BTN_SIZE.x, BTN_SIZE.y, true, "-10", this->defaultColor_ButtonOff, this->defaultColor_ButtonOn);

    Llcd.setCursor(55, 217);
    Llcd.setTextFont(&fonts::lgfxJapanMinchoP_24);
    Llcd.print("前      決定        次");
    this->sampleButton = Button(100, 100, 100, 100, true, "-5", this->defaultColor_ButtonOff, this->defaultColor_ButtonOn);

    Llcd.setCursor(DATETIME_SHOW_POSITION.x, DATETIME_SHOW_POSITION.y);
    Llcd.setFont(&fonts::lgfxJapanMinchoP_28);
    Llcd.print(getDateTimeString(settingDate, settingTime));
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
        // settingTime の値を、1時間文増やす
        settingTime.Hours++;
        correctDateTime();
        updateDateTimeView();
    }

    if (M5.BtnA.wasPressed())
    {
        // SetMode を切り替える
        SetMode = SetMode == SetMode::DATE ? SetMode::MINUTE : SetMode::DATE;
        updateDateTimeView();
    }

    // btns のボタンが、押されているかどうかを確認する
    for (int i = 0; i < 4; i++)
    {
        if (btns[i].wasPressed())
        {
            // 押されていたら、押されたボタンの種類によって、時刻の値を変更する
            switch (i)
            {
            case 0:

                settingTime.Minutes += 10;
                break;
            case 1:
                settingTime.Minutes++;
                break;
            case 2:
                settingTime.Minutes--;
                break;
            case 3:
                settingTime.Minutes -= 10;
                break;
            }
            correctDateTime();
            updateDateTimeView();
        }
    }
}

void TimeSettingScreen::setRTC()
{
    M5.Rtc.SetTime(&settingTime);
    M5.Rtc.SetDate(&settingDate);
}

void TimeSettingScreen::updateDateTimeView()
{
    Llcd.setCursor(0, 0);
    Llcd.print(getDateTimeString(settingDate, settingTime));
}

// 日付、時刻の誤りをただす関数
// 時刻の分が60以上になったら、時刻の時を1増やし、分の値を60減らす
// 時刻の時が24以上になったら、日付の日を1増やし、時の値を24減らす
// 日付の日が月の最大日数を超えたら、月を1増やし、日の値を月の最大日数減らす
// 月が12以上になったら、年を1増やし、月の値を12減らす
void TimeSettingScreen::correctDateTime()
{
    static const uint8_t monthMaxDay[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if (settingTime.Minutes >= 60)
    {
        settingTime.Hours++;
        settingTime.Minutes -= 60;
    }
    if (settingTime.Hours >= 24)
    {
        settingDate.Date++;
        settingTime.Hours -= 24;
    }
    if (settingDate.Date > monthMaxDay[settingDate.Month])
    {
        settingDate.Date -= monthMaxDay[settingDate.Month];
        settingDate.Month++;
    }
    if (settingDate.Month > 12)
    {
        settingDate.Year++;
        settingDate.Month -= 12;
    }
}