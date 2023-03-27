#include "header.h"
#include "SettingTimeIntervalScreen.h"

SettingTimeIntervalScreen::SettingTimeIntervalScreen()
    : btn_plus5(0, 0, 0, 0)

{
   this->btn_plus5.erase(BLACK);
}
void pluc2(Event &e)
{
   Llcd.setCursor(0, 0);
   Llcd.println("PUSHED");
}
void SettingTimeIntervalScreen::initScreen()
{
   Llcd.fillScreen(BLACK);
   this->btn_plus5 = Button(0, 0, 199, 100, true, "+5", this->cl_off, this->cl_on);
   btn_plus5.addHandler(pluc2, E_RELEASE);
   btn_plus5.draw();
   M5.Buttons.draw();
}
