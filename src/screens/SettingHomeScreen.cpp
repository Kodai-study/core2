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
   setting.readIni();
   Llcd.setFont(&fonts::lgfxJapanMinchoP_20);

   RTC_TimeTypeDef settingTime;
   RTC_DateTypeDef settingDate;
   M5.Rtc.GetTime(&settingTime);
   M5.Rtc.GetDate(&settingDate);

   // 時刻と日付から文字列を作成
   String settingDateTimeStr = getDateTimeString(settingDate, settingTime);
   Llcd.setCursor(0, DATETIME_Y_POSITION);
   Llcd.print("TIME : " + settingDateTimeStr);
   this->moveDateTimeSettingButton = Button(250, DATETIME_Y_POSITION, this->btnSize.x, this->btnSize.y, true, "SET", this->defaultColor_ButtonOff, this->defaultColor_ButtonOn);

   Llcd.setCursor(40, 50);
   Llcd.print("SSID:" + setting.getSSID());

   Llcd.setCursor(30, WIFI_INFO_Y_POSITION);
   Llcd.setFont(&fonts::lgfxJapanMinchoP_28);
   // wifiが接続されていれば緑色で接続中と表示
   // 接続されていなければ赤色で未接続と表示
   if (this->isWifiConnected)
   {
      Llcd.setTextColor(GREEN);
      Llcd.print("接続中");
   }
   else
   {
      Llcd.setTextColor(RED);
      Llcd.print("未接続");
   }
   Llcd.setTextColor(WHITE);
   Llcd.setFont(&fonts::lgfxJapanMinchoP_20);
   this->selectWifiButton = Button(125, WIFI_INFO_Y_POSITION, this->btnSize.x, this->btnSize.y, true, "SELECT", this->defaultColor_ButtonOff, this->defaultColor_ButtonOn);
   if (!this->isWifiConnected)
      this->connectWifiButton = Button(230, WIFI_INFO_Y_POSITION, this->btnSize.x + 30, this->btnSize.y, true, "CONNECT", this->defaultColor_ButtonOff, this->defaultColor_ButtonOn);

   // ボタン4つに割り当てる文字列を配列で宣言
   const char *changePageButtonStr[4] = {"-10", "-1", "+1", "+10"};

   // ボタンの配列の要素4つを、ボタンのサイズの配列からサイズを取ってきて初期化
   for (int i = 0; i < 4; i++)
   {
      this->changePageButton[i] = Button(this->btnPos[i].x, this->btnPos[i].y,
                                         this->btnSize.x, this->btnSize.y, true, changePageButtonStr[i], this->defaultColor_ButtonOff, this->defaultColor_ButtonOn);
   }
}

void SettingHomeScreen::deleteScreen()
{
   // 全てのボタンを、 0,0,0,0  で初期化
   this->moveDateTimeSettingButton = Button(0, 0, 0, 0);
   this->selectWifiButton = Button(0, 0, 0, 0);
   this->connectWifiButton = Button(0, 0, 0, 0);
   for (int i = 0; i < 4; i++)
   {
      this->changePageButton[i] = Button(0, 0, 0, 0);
   }
   Llcd.fillScreen(BLACK);
}

void SettingHomeScreen::screenUpdate()
{
   // 4つのボタンのうち、どれかが押されたら、currentPageを変更する
   for (int i = 0; i < 4; i++)
   {
      if (this->changePageButton[i].wasPressed())
      {
         // 押されたボタンによって、currentPageを変更する
         switch (i)
         {
         case 0:
            this->currentPage -= 10;
            break;
         case 1:
            this->currentPage -= 1;
            break;
         case 2:
            this->currentPage += 1;
            break;
         case 3:
            this->currentPage += 10;
            break;
         default:
            break;
         }
         // currentPageが0以下になったら、0にする
         if (this->currentPage < 0)
         {
            this->currentPage = 0;
         }
      }
   }
}

// ボタンを0,0,0,0  で初期化するコンストラクタ
SettingHomeScreen::SettingHomeScreen()
    : moveDateTimeSettingButton(0, 0, 0, 0),
      selectWifiButton(0, 0, 0, 0),
      connectWifiButton(0, 0, 0, 0),
      changePageButton{Button(0, 0, 0, 0),
                       Button(0, 0, 0, 0),
                       Button(0, 0, 0, 0),
                       Button(0, 0, 0, 0)}
{
}