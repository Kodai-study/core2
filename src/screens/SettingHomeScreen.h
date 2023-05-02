/**
 * @file SettingTimeIntervalScreen.h
 * @author Kodai-study (anchor.kou@softbank.ne.jp)
 * @brief タイムインターバルの設定画面の制御を行うクラス、SettingTimeIntervalScreenの宣言を記述するファイル
 * @date 2023-04-06
 *
 */

#include "header.h"
#include "ScreenBase.h"

/**
 * @brief 集中モードのタイムインターバルの設定画面の制御を行うクラス
 */
class SettingHomeScreen : public ScreenBase
{
private:
   Button moveDateTimeSettingButton;
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
   const Point btnPos[4] = {Point(5, 155), Point(85, 155), Point(170, 155), Point(250, 155)};

   // 共通のボタンサイズ
   const Point btnSize = Point(70, 50);

   const int DATETIME_Y_POSITION = 10;

   const int WIFI_INFO_Y_POSITION = 80;

public:
   void initScreen() override;
   void deleteScreen() override;
   void screenUpdate() override;
   SettingHomeScreen();
};