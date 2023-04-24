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
   this->btn_plus5 = Button(btnPos[0].x, btnPos[0].y, btnSize.x, btnSize.y, true, "+5", this->defaultColor_ButtonOff, this->defaultColor_ButtonOn);
   this->btn_plus1 = Button(btnPos[1].x, btnPos[1].y, btnSize.x, btnSize.y, true, "+1", this->defaultColor_ButtonOff, this->defaultColor_ButtonOn);
   this->btn_minus1 = Button(btnPos[2].x, btnPos[2].y, btnSize.x, btnSize.y, true, "-1", this->defaultColor_ButtonOff, this->defaultColor_ButtonOn);
   this->btn_minus5 = Button(btnPos[3].x, btnPos[3].y, btnSize.x, btnSize.y, true, "-5", this->defaultColor_ButtonOff, this->defaultColor_ButtonOn);
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
   // ボタンCが押されていたら、cursorposを変更する
   if (M5.BtnC.isPressed())
   {
      cursorPos = (cursorPos + 1) % 3;
   }
   buttonPressed();
}

// ページ数、時刻、モード(数字)をcsvファイルに書き込む
// 今まで書き込まれた行に追加する
// 書き込み後は改行する
void writeCsv(int page, int time, int mode)
{
   File file = SD.open("data.csv", FILE_WRITE);
   if (file)
   {
      file.print(page);
      file.print(",");
      file.print(time);
      file.print(",");
      file.println(mode);
      file.close();
   }
}

void SettingTimeIntervalScreen::showTimeInterval()
{
   // TODO 文字列表示のカーソルと、フォントを設定

   // 指定した位置、幅、高さを黒で塗りつぶす
   Llcd.fillRect(0, 0, 320, 240, BLACK);

   Llcd.print(timeInterval);
   Llcd.print("分 休憩 ");
   Llcd.print(restTime);
   Llcd.print("分:");
   Llcd.print(repeat);
   Llcd.print("回");
}

// changeSettingValue関数を実装
// cursorPos に応じて、timeInterval, restTime, repeatの値を変更する
// 変化させる値は引数のvalueで指定し、負の数にはならない
void SettingTimeIntervalScreen::changeSettingValue(int value)
{
   switch (cursorPos)
   {
   case 0:
      timeInterval += value;
      if (timeInterval < 0)
      {
         timeInterval = 0;
      }
      break;
   case 1:
      restTime += value;
      if (restTime < 0)
      {
         restTime = 0;
      }
      break;
   case 2:
      repeat += value;
      if (repeat < 0)
      {
         repeat = 0;
      }
      break;
   default:
      break;
   }
}

// ボタンを押した時の処理を実装
// ボタンの種類に応じて、changeSettingValue関数を呼び出す
// ボタンの種類に応じて、cursorPosの値を変更する
void SettingTimeIntervalScreen::buttonPressed()
{
   if (btn_plus5.wasPressed())
   {
      changeSettingValue(5);
   }
   else if (btn_plus1.wasPressed())
   {
      changeSettingValue(1);
   }
   else if (btn_minus1.wasPressed())
   {
      changeSettingValue(-1);
   }
   else if (btn_minus5.wasPressed())
   {
      changeSettingValue(-5);
   }
}