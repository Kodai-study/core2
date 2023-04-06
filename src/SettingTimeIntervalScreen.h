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

public:
   SettingTimeIntervalScreen();
   void initScreen() override;
   void deleteScreen() override;
   void scereenUpdate() override;
};