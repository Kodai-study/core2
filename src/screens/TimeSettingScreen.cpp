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

    settingTime.Minutes -= settingTime.Minutes % 10;
    settingTime.Seconds = 0;

    btns[0] = Button(BTN_POSITIONS[0].x, BTN_POSITIONS[0].y, BTN_SIZE.x, BTN_SIZE.y, true, "+10", this->defaultColor_ButtonOff, this->defaultColor_ButtonOn);
    btns[1] = Button(BTN_POSITIONS[1].x, BTN_POSITIONS[1].y, BTN_SIZE.x, BTN_SIZE.y, true, "+1", this->defaultColor_ButtonOff, this->defaultColor_ButtonOn);
    btns[2] = Button(BTN_POSITIONS[2].x, BTN_POSITIONS[2].y, BTN_SIZE.x, BTN_SIZE.y, true, "-1", this->defaultColor_ButtonOff, this->defaultColor_ButtonOn);
    btns[3] = Button(BTN_POSITIONS[3].x, BTN_POSITIONS[3].y, BTN_SIZE.x, BTN_SIZE.y, true, "-10", this->defaultColor_ButtonOff, this->defaultColor_ButtonOn);

    Llcd.setCursor(30, 217);
    Llcd.setTextFont(&fonts::lgfxJapanMinchoP_24);
    Llcd.print("切り替え      決定         次");

    Llcd.setFont(&fonts::lgfxJapanMinchoP_28);
    Llcd.setCursor(30, 20);
    Llcd.print("時刻設定");

    Llcd.setCursor(DATETIME_SHOW_POSITION.x, DATETIME_SHOW_POSITION.y);
    Llcd.print(getDateTimeString(settingDate, settingTime));
}

void TimeSettingScreen::deleteScreen()
{
    setting.setDateTime(settingDate, settingTime);
    Llcd.fillScreen(BLACK);
    // ボタンのサイズを全て0にする
    for (int i = 0; i < 4; i++)
    {
        btns[i] = Button(0, 0, 0, 0);
    }
}

void TimeSettingScreen::scereenUpdate()
{
    if (M5.BtnA.wasPressed())
    {
        Llcd.fillRect(0, 0, 100, 40, BLACK);
        Llcd.setCursor(30, 20);
        switch (SetMode)
        {
        case SetMode::DATE:
            SetMode = SetMode::MINUTE;
            btns[0].setLabel("+30");
            btns[1].setLabel("+10");
            btns[2].setLabel("-10");
            btns[3].setLabel("-30");
            Llcd.print("時刻設定:(分)");
            break;
        case SetMode::MINUTE:
            SetMode = SetMode::DATE;
            btns[0].setLabel("+10");
            btns[1].setLabel("+1");
            btns[2].setLabel("-1");
            btns[3].setLabel("-10");
            Llcd.print("日付設定:(日)");
            break;
        }
        M5.Buttons.draw();
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
                if (SetMode == SetMode::DATE)
                    settingDate.Date += 10;
                else if (SetMode == SetMode::MINUTE)
                    settingTime.Minutes += 30;
                break;
            case 1:
                if (SetMode == SetMode::DATE)
                    settingDate.Date++;
                else if (SetMode == SetMode::MINUTE)
                    settingTime.Minutes += 10;
                break;
            case 2:
                if (SetMode == SetMode::DATE)
                    settingDate.Date--;
                else if (SetMode == SetMode::MINUTE)
                    settingTime.Minutes -= 10;
                break;
            case 3:
                if (SetMode == SetMode::DATE)
                    settingDate.Date -= 10;
                else if (SetMode == SetMode::MINUTE)
                    settingTime.Minutes -= 30;
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
    // 画面の指定した範囲を、黒で塗りつぶす
    Llcd.fillRect(0, 70, 320, 75, BLACK);
    Llcd.setCursor(DATETIME_SHOW_POSITION.x, DATETIME_SHOW_POSITION.y);
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

    // uint_8型のため、200を超えている値は負の数と考え、調節を行う。
    //  例えば、分の値が-nになったら、時の値を1減らし、分の値を60-nにする
    if (settingTime.Minutes > 200)
    {
        settingTime.Hours--;
        settingTime.Minutes += 60;
    }
    if (settingTime.Hours > 200)
    {
        settingDate.Date--;
        settingTime.Hours += 24;
    }
    if (settingDate.Date == 0 || settingDate.Date > 200)
    {
        settingDate.Date += monthMaxDay[settingDate.Month];
        settingDate.Month--;
    }
    if (settingDate.Month == 0 || settingDate.Month > 200)
    {
        settingDate.Year--;
        settingDate.Month += 12;
    }

    // 0~60の範囲に収まるように、値を調節する

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
    if (settingDate.Date > monthMaxDay[settingDate.Month - 1])
    {
        settingDate.Date -= monthMaxDay[settingDate.Month - 1];
        settingDate.Month++;
    }
    if (settingDate.Month > 12)
    {
        settingDate.Year++;
        settingDate.Month -= 12;
    }
}