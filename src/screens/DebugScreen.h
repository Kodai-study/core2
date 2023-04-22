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
class DebugScreen : public ScreenBase
{
private:
public:
   // ScreenBaseクラスのinitScreenをオーバーライドし、その実装を空で記述する。
   void initScreen() override
   {
      Llcd.setCursor(0, 0);
      Llcd.setTextFont(&fonts::lgfxJapanMinchoP_16);
      setting.readIni();
      Llcd.println(setting.getRepeat());
      Llcd.println(setting.getTime());
      Llcd.println(setting.getSSID());
      Llcd.println(setting.getWifiPass());
      Llcd.println(setting.getDateTime());
   }
   // ScreenBaseクラスのdeleteScreenをオーバーライドし、その実装を空で記述する。

   void deleteScreen() override {}
   void scereenUpdate() override {}
};
