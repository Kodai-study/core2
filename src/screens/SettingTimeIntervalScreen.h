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
class SettingTimeIntervalScreen : public ScreenBase
{
private:
   /**
    * @brief 対象の設定項目の値を5分増加させるボタン
    */
   Button btn_plus5;
   /**
    * @brief 対象の設定項目の値を1分増加させるボタン
    */
   Button btn_plus1;
   /**
    * @brief 対象の設定項目の値を1分減少させるボタン
    */
   Button btn_minus1;
   /**
    * @brief 対象の設定項目の値を5分減少させるボタン
    */
   Button btn_minus5;

   /**
    * @brief タイムインターバルの値を保持する変数
    */
   int timeInterval = 0;
   /**
    * @brief 休憩時間の値を保持する変数
    */
   int restTime = 0;
   /**
    * @brief 繰り返し回数の値を保持する変数
    */
   int repeat = 0;

   /**
    * @brief 現在のカーソルの位置を保持する変数
    * 0:タイムインターバル 1:休憩時間 2:繰り返し回数
    */
   int cursorPos = 0;

   // TODO カーソルが来る場所を指定する
   const Point cursorDefaultPos[5] = {Point(0, 0), Point(0, 0), Point(0, 0), Point(0, 0), Point(0, 0)};

   // ボタンの位置の一覧
   const Point btnPos[4] = {Point(250, 0), Point(250, 55), Point(250, 110), Point(250, 165)};

   // 共通のボタンサイズ
   const Point btnSize = Point(70, 40);

   // カーソルの色を定数で指定する
   const int cursorColor = RED;

   // カーソルを描写する
   void drawCursor(int x, int y)
   {
      Llcd.fillRect(x, y, 10, 50, cursorColor);
   }
   // 設定したタイムインタ‐バルの値を表示する関数を宣言
   void showTimeInterval();

   // 設定項目の値を変化させる関数を宣言
   void changeSettingValue(int value);

   /**
    * @brief M5StackのボタンA~Cが押されたかどうかの判定と、押されたボタンに応じた処理を行う関数
    */
   void buttonPressed();

public:
   SettingTimeIntervalScreen();
   void initScreen() override;
   void deleteScreen() override;
   void screenUpdate() override;
};