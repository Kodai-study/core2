/**
 * @file SettingTimeIntervalScreen.h
 * @author Kodai-study (anchor.kou@softbank.ne.jp)
 * @brief タイムインターバルの設定画面の制御を行うクラス、SettingTimeIntervalScreenの宣言を記述するファイル
 * @date 2023-04-06
 *
 */

#include "header.h"
#include "ScreenBase.h"
class SettingTimeIntervalScreen : public ScreenBase
{
private:
   Button btn_plus5;
   Button btn_plus1;
   Button btn_minus1;
   Button btn_minus5;

   int timeInterval = 0;
   int restTime = 0;
   int repeat = 0;

   // 今のカーソルの位置を示す変数
   int cursorPos = 0;

   // TODO カーソルが来る場所を指定する
   // Point クラスの配列で、カーソルのデフォルトの位置を指定する
   // 要素は5つで、すべて0,0 で初期化する
   const Point cursorDefaultPos[5] = {Point(0, 0), Point(0, 0), Point(0, 0), Point(0, 0), Point(0, 0)};

   // ボタンの位置を、Pointクラスの配列で指定する
   // 要素は4つで、次のルールで値が決まる。
   // x座標は、常に250  y座標は、0から始まり、55ずつ増える
   const Point btnPos[4] = {Point(250, 0), Point(250, 55), Point(250, 110), Point(250, 165)};

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
   void buttonPressed();

public:
   SettingTimeIntervalScreen();
   void initScreen() override;
   void deleteScreen() override;
   void scereenUpdate() override;
};