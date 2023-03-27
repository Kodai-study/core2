#include "header.h"

class SettingTimeIntervalScreen
{
private:
   int index;
   int currentPage;
   String bookName;
   ButtonColors cl_on = {CYAN, WHITE, WHITE};      // タップした時の色 (背景, 文字列, ボーダー)
   ButtonColors cl_off = {DARKCYAN, WHITE, WHITE}; //
   /*
   Button btn_plus1;
   Button btn_minus1;
   Button btn_minus5;*/
public:
   void initScreen();
   SettingTimeIntervalScreen(int index, int currentPage, String bookName);
   SettingTimeIntervalScreen();
   Button btn_plus5;
};