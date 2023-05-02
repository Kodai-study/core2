/**
 * @file SettingTimeIntervalScreen.cpp
 * @author Kodai-study (anchor.kou@softbank.ne.jp)
 * @brief タイムインターバルの設定画面の制御を行うクラス、SettingTimeIntervalScreenの実装を記述するファイル
 * @date 2023-04-06
 *
 */
#include "header.h"
#include "SettingHomeScreen.h"

// SettingHomeScreenクラスで、ベースクラスのメソッドを実装
// 中身は空
void SettingHomeScreen::initScreen()
{
   ScreenBase::initScreen();
   this->sample = Button(100, 100, 100, 100, true, "sample", this->defaultColor_ButtonOff, this->defaultColor_ButtonOn);
}

void SettingHomeScreen::deleteScreen()
{
}

void SettingHomeScreen::scereenUpdate()
{
}

// ボタンを0,0,0,0  で初期化するコンストラクタ
SettingHomeScreen::SettingHomeScreen()
    : sample(0, 0, 0, 0)
{
}