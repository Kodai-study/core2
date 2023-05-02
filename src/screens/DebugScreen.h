/**
 * @file ReadingScreen.h
 * @author Kodai-study (anchor.kou@softbank.ne.jp)
 * @brief 読書中の画面の制御を行うReadingScreenクラスの宣言
 * @date 2023-04-06
 *
 */

#ifndef DEBUGSCREEN_H
#define DEBUGSCREEN_H

#include "header.h"
#include "ScreenBase.h"
#include "ObjectFromCsvFactory.h"
#include "module/PageFlipData.h"
#include "CsvManager.h"
#include "../module/BookData.h"

/**
 * @brief 設定情報や、SDカードに保存されているデータを見ることができるデバッグ画面を制御するクラス
 */
class DebugScreen : public ScreenBase
{
private:
   LinkedList<String> fileNames;
   int cursor = 0;
   void printDirectory(File dir, int numTabs = 1);
   void updateCursor()
   {
      // x250 より右側の画面を黒塗りにする。
      Llcd.fillRect(250, 0, SCREEN_WIDTH - 250, 240, BLACK);
      for (int i = 0; i < cursor; i++)
      {
         Llcd.setCursor(250, i * 20);
      }
      Llcd.print("←");
   }

public:
   // ScreenBaseクラスのinitScreenをオーバーライドし、その実装を空で記述する。
   void initScreen() override
   {
      Llcd.setCursor(0, 0);
      Llcd.setTextFont(&fonts::lgfxJapanMinchoP_16);
      setting.printAllSetting();
      printDirectory(SD.open("/"));
      // '←'のカーソルを表示する。  カーソルは、printDirectory関数で表示されたファイルの一覧の中で移動する。
      Llcd.setCursor(250, 0);
      Llcd.print("←");
   }

   // SDカードの直下に入っているファイルの一覧を表示する関数

   // 設定情報を表示する関数
   void printSetting()
   {
      Llcd.fillScreen(BLACK);
      setting.readIni();
      Llcd.setCursor(0, 0);
      Llcd.println("repeat: " + setting.getRepeat());
      Llcd.println("timeInterval: " + setting.getTimeInterval());
      Llcd.println("SSID: " + setting.getSSID());
      Llcd.println("WifiPass: " + setting.getWifiPass());
      Llcd.println("DateTime: " + setting.getDateTime());
   }

   void deleteScreen() override {}
   void screenUpdate() override
   {
      /* Cボタンが押されたら、カーソル位置を一つ下に移動する。
      Bボタンが押されたら、画面を全て黒塗りにして、カーソルが指しているファイルの中身を表示する。
      */
      if (M5.BtnC.wasPressed())
      {
         cursor = (cursor + 1) % fileNames.size();
         updateCursor();
      }
      else if (M5.BtnB.wasPressed())
      {
         Llcd.fillScreen(BLACK);
         File file = SD.open("/" + fileNames.get(cursor));
         Llcd.setCursor(0, 0);
         while (file.available())
         {
            Llcd.println(file.readStringUntil('\n'));
         }
         file.close();
      }
      // ボタンAが押されたら、リストのデータをもとにファイル名一覧を表示する
      else if (M5.BtnA.wasPressed())
      {
         Llcd.fillScreen(BLACK);
         Llcd.setCursor(0, 0);
         for (int i = 0; i < fileNames.size(); i++)
         {
            Llcd.println(fileNames.get(i));
         }
      }
   }
};

void DebugScreen::printDirectory(File dir, int numTabs)
{
   while (true)
   {
      File entry = dir.openNextFile();
      if (!entry)
      {
         // no more files
         break;
      }
      for (uint8_t i = 0; i < numTabs; i++)
      {
         Llcd.print('\t');
      }
      Llcd.print(entry.name());

      if (numTabs == 1)
         fileNames.add(entry.name());

      if (entry.isDirectory())
      {
         Llcd.println("/");
         // printDirectory(entry, numTabs + 1);
      }
      else
      {
         // files have sizes, directories do not
         Llcd.print("\t    ");
         Llcd.println(entry.size());
      }
      entry.close();
   }
}

#endif // DEBUGSCREEN_H