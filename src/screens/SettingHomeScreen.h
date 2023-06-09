/**
 * @file SettingTimeIntervalScreen.h
 * @author Kodai-study (anchor.kou@softbank.ne.jp)
 * @brief タイムインターバルの設定画面の制御を行うクラス、SettingTimeIntervalScreenの宣言を記述するファイル
 * @date 2023-04-06
 *
 */

#include "header.h"
#include "ScreenBase.h"
#include "../Setting.h"

/**
 * @brief 集中モードのタイムインターバルの設定画面の制御を行うクラス
 */
class SettingHomeScreen : public ScreenBase
{
private:
   // 接続するWifiのSSIDを選択するボタン
   Button selectWifiButton;

   // 選択したWifiに接続するボタン
   Button connectWifiButton;

   // 読み始めのページ数を増減するボタンを作成する
   // 増減する数は、 -10,-1,1,10の4つ
   // 配列で管理する
   Button changePageButton[4];

   // 現在のページ数を表示する
   int currentPage = 0;

   // ボタンの位置の一覧
   const Point btnPos[4] = {Point(5, 180), Point(85, 180), Point(170, 180), Point(250, 180)};

   // 共通のボタンサイズ
   const Point btnSize = Point(70, 35);

   const int DATETIME_Y_POSITION = 10;

   const int WIFI_INFO_Y_POSITION = 80;

   // 設定しているSSIDを表示する座標
   const Point SSID_POSITION = Point(40, 50);

   // ページ数を表示する座標
   const Point PAGE_NUM_POSITION = Point(110, 135);

   // 配列の中から、接続するWifiのSSIDを選択するインデックス
   int selectedWifiIndex = -1;

   RTC_TimeTypeDef settingTime;
   RTC_DateTypeDef settingDate;

public:
   void initScreen() override;
   void deleteScreen() override;
   void screenUpdate() override;
   SettingHomeScreen();

   // 時刻、SSID、ページ数の表示それぞれを書き換える関数をそれぞれ定義する
   void updateDateTimeText();
   void updateWifiInfoText();
   void updatePageNumText();
};