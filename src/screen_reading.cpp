#include "header.h"
#include "ReadingScreen.h"

void push(Event &e)
{
    Llcd.setCursor(0, 0);
    Llcd.println("PUSHED");
}

void ReadingScreen::initScreen()
{
    Llcd.fillScreen(BLACK);
    Llcd.setCursor(16, 38);
    Llcd.setTextFont(&fonts::lgfxJapanMinchoP_24);
    Llcd.printf("読書中_%02d分", this->currentPage);
    Llcd.setCursor(20, 209);
    Llcd.println("戻る    前ページ  次ページ");

    Llcd.setCursor(64, 96);
    Llcd.setTextFont(&fonts::lgfxJapanMinchoP_40);
    Llcd.printf("ページ:%03d", this->currentPage);
    btn_x.addHandler(push, E_RELEASE);
    M5.Buttons.draw();
}

ReadingScreen::ReadingScreen(int index, int currentPage, String bookName) : currentPage(currentPage), btn_x(220, 10, 100, 60, true, "Start", this->cl_off, this->cl_on)
{
    this->bookName = bookName;
}