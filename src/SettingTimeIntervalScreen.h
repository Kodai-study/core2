#include "header.h"

class SettingTimeIntervalScreen
{
private:
   ButtonColors cl_on = {CYAN, WHITE, WHITE};      // タップした時の色 (背景, 文字列, ボーダー)
   ButtonColors cl_off = {DARKCYAN, WHITE, WHITE}; //

   Button btn_plus5;
   Button btn_plus1;
   Button btn_minus1;
   Button btn_minus5;

public:
   void initScreen();
   SettingTimeIntervalScreen();
   void deleteScreen();
};