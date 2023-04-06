/**
 * @file SettingTimeIntervalScreen.cpp
 * @author Kodai-study (anchor.kou@softbank.ne.jp)
 * @brief タイムインターバルの設定画面の制御を行うクラス、SettingTimeIntervalScreenの実装を記述するファイル
 * @date 2023-04-06
 * 
 */
#include "header.h"
#include "SettingTimeIntervalScreen.h"

SettingTimeIntervalScreen::SettingTimeIntervalScreen()
    : btn_plus5(0, 0, 0, 0),
      btn_plus1(0, 0, 0, 0),
      btn_minus1(0, 0, 0, 0),
      btn_minus5(0, 0, 0, 0)
{
   this->btn_plus5.erase(BLACK);
   this->btn_plus1.erase(BLACK);
   this->btn_minus1.erase(BLACK);
   this->btn_minus5.erase(BLACK);
}
void pluc2(Event &e)
{
   Llcd.setCursor(0, 0);
   Llcd.println("PUSHED");
}
void SettingTimeIntervalScreen::initScreen()
{
   ScreenBase::initScreen();
   Llcd.fillScreen(BLACK);
   this->btn_plus5 = Button(250, 0, 70, 40, true, "+5", this->defaultColor_ButtonOff, this->defaultColor_ButtonOn);
   this->btn_plus1 = Button(250, 55, 70, 40, true, "+1", this->defaultColor_ButtonOff, this->defaultColor_ButtonOn);
   this->btn_minus1 = Button(250, 110, 70, 40, true, "-1", this->defaultColor_ButtonOff, this->defaultColor_ButtonOn);
   this->btn_minus5 = Button(250, 165, 70, 40, true, "-5", this->defaultColor_ButtonOff, this->defaultColor_ButtonOn);
   btn_plus5.addHandler(pluc2, E_RELEASE);
   btn_plus5.draw();
}

void SettingTimeIntervalScreen::deleteScreen()
{
   this->btn_plus5.erase(BLACK);
   this->btn_plus5.set(0, 0, 0, 0);
   this->btn_plus1.erase(BLACK);
   this->btn_plus1.set(0, 0, 0, 0);
   this->btn_minus1.erase(BLACK);
   this->btn_minus1.set(0, 0, 0, 0);
   this->btn_minus5.erase(BLACK);
   this->btn_minus5.set(0, 0, 0, 0);
}

void SettingTimeIntervalScreen::scereenUpdate()
{
}
