#include "header.h"

class ReadingScreen
{
private:
   int index;
   int currentPage;
   String bookName;
   ButtonColors cl_on = {CYAN, WHITE, WHITE};      // タップした時の色 (背景, 文字列, ボーダー)
   ButtonColors cl_off = {DARKCYAN, WHITE, WHITE}; //
   Button btn_x;
public:
   void initScreen();
   ReadingScreen(int index, int currentPage, String bookName);
};