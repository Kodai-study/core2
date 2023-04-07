/**
 * @file ReadingScreen.h
 * @author Kodai-study (anchor.kou@softbank.ne.jp)
 * @brief 読書中の画面の制御を行うReadingScreenクラスの宣言
 * @date 2023-04-06
 *
 */
#include "header.h"
#include "ScreenBase.h"
class ReadingScreen : public ScreenBase
{
private:
   const int OTHERS = 0;
   const int FOCUS_MODE = 1;
   const int FREE_MODE = 2;
   int index;
   int currentPage;
   String bookName;
   Button btn_x;
   bool isConnecitngWifi = false;
   int currentMode = OTHERS;
   int readingBookIndex = 0;
   const String DATA_PAGEFLIP_PATH = String("readDatas/");

public:
   void initScreen() override;
   ReadingScreen(int index, int currentPage, String bookName);
   void deleteScreen() override;
   void scereenUpdate() override;
};