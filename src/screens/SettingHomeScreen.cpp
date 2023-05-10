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
   Llcd.fillScreen(BLACK);
   selectedWifiIndex = -1;

   Llcd.setFont(&fonts::lgfxJapanMinchoP_24);
   Llcd.setCursor(40, 220);
   Llcd.print("戻る        決定      時刻設定");

   M5.Rtc.GetTime(&settingTime);
   M5.Rtc.GetDate(&settingDate);

   // 時刻と日付から文字列を作成
   String settingDateTimeStr = getDateTimeString(settingDate, settingTime);
   Llcd.setCursor(0, DATETIME_Y_POSITION);
   // settingDateTimeStr の最後の3文字を省いた文字列
   // 例: 2021/04/06 12:34:56 -> 2021/04/06 12:34
   settingDateTimeStr = settingDateTimeStr.substring(0, settingDateTimeStr.length() - 3);
   Llcd.print("TIME:" + settingDateTimeStr);

   Llcd.setCursor(SSID_POSITION.x, SSID_POSITION.y);
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

   Llcd.setCursor(PAGE_NUM_POSITION.x, PAGE_NUM_POSITION.y);
   Llcd.printf("Page:%03d", this->currentPage);
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
   // selectedWifiIndexを変更して、選択中のWifiのSSIDを変更する
   if (this->selectWifiButton.wasPressed())
   {
      this->selectedWifiIndex++;
      if (this->selectedWifiIndex >= setting.SSID_COLUM_SIZE)
      {
         this->selectedWifiIndex = 0;
      }
      this->updateWifiInfoText();
   }
   else if (this->connectWifiButton.wasPressed())
   {
      Llcd.setCursor(0, WIFI_INFO_Y_POSITION + 40);
      // Wifiに接続する
      if (selectedWifiIndex == -1)
      {
         // settingの値をそのまま使用してWifiに接続すrう
         this->isWifiConnected = connectingWifi(setting.getSSID(), setting.getWifiPass());
      }
      else
      {
         this->isWifiConnected = connectingWifi(setting.SSID_COLUM[this->selectedWifiIndex], setting.WIFI_PASS_COLUM[this->selectedWifiIndex]);
      }
      updatePageNumText();
      if (isWifiConnected)
      {
         setRTC();
         settingTime = setting.getTime(); // 時刻表示を更新
         settingDate = setting.getDate(); // 日付表示を更新
         updateDateTimeText();
         updateWifiInfoText();
      }
   }

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
         updatePageNumText();
      }
   }

   if (M5.BtnC.wasPressed())
   {
      screenTransitionHandler(Screen::Screen_DateTimeSetting);
   }
}

// ボタンを0,0,0,0  で初期化するコンストラクタ
SettingHomeScreen::SettingHomeScreen()
    : selectWifiButton(0, 0, 0, 0),
      connectWifiButton(0, 0, 0, 0),
      changePageButton{Button(0, 0, 0, 0),
                       Button(0, 0, 0, 0),
                       Button(0, 0, 0, 0),
                       Button(0, 0, 0, 0)}
{
}
// 上の3つの関数を実装する。中身は、画面の1部を黒塗りして、カーソルをセット、変数の値を書き込む。
// 塗りつぶしの座標は仮に 0,0 とする。  表示する文字列は、initScreen() を参考にする
void SettingHomeScreen::updateDateTimeText()
{
   Llcd.fillRect(0, DATETIME_Y_POSITION, 320, 30, BLACK);
   Llcd.setCursor(0, DATETIME_Y_POSITION);
   Llcd.print("TIME:" + getDateTimeString(settingDate, settingTime));
}

void SettingHomeScreen::updateWifiInfoText()
{
   Llcd.fillRect(0, SSID_POSITION.y, 320, 40, BLACK);
   Llcd.setCursor(SSID_POSITION.x, SSID_POSITION.y);
   Llcd.print("SSID:");
   if (this->selectedWifiIndex == -1)
      Llcd.print(setting.getSSID());
   else
      Llcd.print(setting.SSID_COLUM[this->selectedWifiIndex]);

   // "接続中" か "未接続" の表示を塗りつぶす
   Llcd.fillRect(0, WIFI_INFO_Y_POSITION, 80, 40, BLACK);

   Llcd.setCursor(30, WIFI_INFO_Y_POSITION);
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
}

void SettingHomeScreen::updatePageNumText()
{
   Llcd.fillRect(0, PAGE_NUM_POSITION.y, 320, 30, BLACK);
   Llcd.setCursor(PAGE_NUM_POSITION.x, PAGE_NUM_POSITION.y);
   Llcd.printf("Page:%03d", this->currentPage);
}