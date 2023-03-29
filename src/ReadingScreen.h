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
   const ButtonColors cl_on = {CYAN, WHITE, WHITE};      // タップした時の色 (背景, 文字列, ボーダー)
   const ButtonColors cl_off = {DARKCYAN, WHITE, WHITE}; //
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