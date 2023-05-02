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
   Button sample;

public:
   void initScreen() override;
   void deleteScreen() override;
   void scereenUpdate() override;
   SettingHomeScreen();
};