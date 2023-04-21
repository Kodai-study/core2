/**
 * @file ReadingScreen.h
 * @author Kodai-study (anchor.kou@softbank.ne.jp)
 * @brief 読書中の画面の制御を行うReadingScreenクラスの宣言
 * @date 2023-04-06
 *
 */
#include "header.h"
#include "ScreenBase.h"
#include "ObjectFromCsvFactory.h"
#include "module/PageFlipData.h"
#include "CsvManager.h"
#include "../module/BookData.h"

/**
 * @brief 現在の時刻を手動で設定する画面の制御を行うクラス
 */
class TimeSettingScreen : public ScreenBase
{
private:
   const RTC_DateTypeDef DEFAULT_TIME = {0, 4, 21, 2023};
   const RTC_TimeTypeDef DEFAULT_DATE = {12, 0, 0};

   RTC_TimeTypeDef settingTime;
   RTC_DateTypeDef settingDate;

   String getDateTimeString();
   Button sampleButton;
   const Point btnPos[4] = {Point(250, 0), Point(250, 55), Point(250, 110), Point(250, 165)};

   // 共通のボタンサイズ
   const Point btnSize = Point(70, 40);

   // 以下の効果を持つボタンを定義する。
   /* 日にちを1増やす。 日にちを10増やす。 時刻(分)を1増やす。 時刻を10増やす。 */

public:
   void initScreen() override;
   void deleteScreen() override;
   void scereenUpdate() override;
   void setRTC();
};