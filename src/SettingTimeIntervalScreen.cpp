#include "header.h"
#include "SettingTimeIntervalScreen.h"

SettingTimeIntervalScreen::SettingTimeIntervalScreen()
    : btn_plus5(0, 0, 0, 0),
      btn_plus1(0, 0, 0, 0),
      btn_minus1(0, 0, 0, 0),
      btn_minus5(0, 0, 0, 0)
{
   this->btn_plus5.erase(BLACK);
   this->btn_plus1.erase(BLACK);
   this->btn_minus1.erase(BLACK);
   this->btn_minus5.erase(BLACK);
}
void pluc2(Event &e)
{
   Llcd.setCursor(0, 0);
   Llcd.println("PUSHED");
}
void SettingTimeIntervalScreen::initScreen()
{
   Llcd.fillScreen(BLACK);
   this->btn_plus5 = Button(250, 0, 70, 40, true, "+5", this->cl_off, this->cl_on);
   this->btn_plus1 = Button(250, 55, 70, 40, true, "+1", this->cl_off, this->cl_on);
   this->btn_minus1 = Button(250, 110, 70, 40, true, "-1", this->cl_off, this->cl_on);
   this->btn_minus5 = Button(250, 165, 70, 40, true, "-5", this->cl_off, this->cl_on);
   btn_plus5.addHandler(pluc2, E_RELEASE);
   btn_plus5.draw();
}

void SettingTimeIntervalScreen::deleteScreen()
{
   this->btn_plus5.erase(BLACK);
   this->btn_plus5.set(0, 0, 0, 0);
   this->btn_plus1.erase(BLACK);
   this->btn_plus1.set(0, 0, 0, 0);
   this->btn_minus1.erase(BLACK);
   this->btn_minus1.set(0, 0, 0, 0);
   this->btn_minus5.erase(BLACK);
   this->btn_minus5.set(0, 0, 0, 0);
}
