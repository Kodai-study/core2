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
   const Point DATETIME_SHOW_POSITION = Point(10, 100);
   const Point BTN_POSITIONS[4] = {Point(5, 145), Point(85, 145), Point(170, 145), Point(240, 145)};
   const Point BTN_SIZE = Point(70, 40);

   RTC_TimeTypeDef settingTime;
   RTC_DateTypeDef settingDate;

   enum SetMode
   {
      DATE,
      MINUTE
   };

   // 4つのボタンを宣言する。
   // 足し算で、大きく値が増える。 足し算で、小さく値が増える。  引き算で、大きく値が減る。  引き算で、小さく値が減る。
   Button btns[4] = {
       Button(0, 0, 0, 0),
       Button(0, 0, 0, 0),
       Button(0, 0, 0, 0),
       Button(0, 0, 0, 0)};

   SetMode SetMode = DATE;

public:
   void initScreen() override;
   void deleteScreen() override;
   void scereenUpdate() override;
   void setRTC();
   // 日付時刻を再表示する関数
   void updateDateTimeView();
   // 日付、時刻の誤りをただす関数
   void correctDateTime();
};