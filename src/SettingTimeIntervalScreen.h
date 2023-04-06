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

   // TODO カーソルが来る場所を指定する
   // Point クラスの配列で、カーソルのデフォルトの位置を指定する
   // 要素は5つで、すべて0,0 で初期化する
   const Point cursorDefaultPos[5] = {Point(0, 0), Point(0, 0), Point(0, 0), Point(0, 0), Point(0, 0)};

   // ボタンの位置を、Pointクラスの配列で指定する
   // 要素は4つで、次のルールで値が決まる。
   // x座標は、常に250  y座標は、0から始まり、55ずつ増える
   const Point btnPos[4] = {Point(250, 0), Point(250, 55), Point(250, 110), Point(250, 165)};
   
   const Point btnSize = Point(70, 40);

public:
   SettingTimeIntervalScreen();
   void initScreen() override;
   void deleteScreen() override;
   void scereenUpdate() override;
};