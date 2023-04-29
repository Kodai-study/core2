/**
 * @file ReadingScreen.cpp
 * @author Kodai-study (anchor.kou@softbank.ne.jp)
 * @brief 読書中画面の制御を行うクラス、ReadingScreenの実装を記述するファイル
 * @date 2023-04-06
 */

#include "header.h"
#include "RegisterBookMarkScreen.h"

void RegisterBookMarkScreen::initScreen()
{
    Llcd.setCursor(20, 209);
    Llcd.println("キャンセル    作成    モード切替");

    Llcd.setCursor(64, 96);
    Llcd.println("これはサンプルの表示です");
}

void RegisterBookMarkScreen::deleteScreen()
{
    Llcd.fillScreen(BLACK);
}

void RegisterBookMarkScreen::scereenUpdate()
{
    // ボタンAが押されたら、読書中画面に遷移する
    if (M5.BtnA.wasPressed())
    {
        screenTransitionHandler(Screen::Screen_Reading);
    }

    // ボタンBが押されたら、ブックマークを登録する
    // Wi-fiに接続されているときは、Firebaseにブックマークを登録する
    

    // ボタンCが押されたら、ブックマークの種類を変更する
    if (M5.BtnC.wasPressed())
    {
        this->lastSelectedBookMarkType = (BookMarkType)((this->lastSelectedBookMarkType + 1) % BOOKMARK_TYPE_NUM);
        showRegisterBookmarkDialog();
    }
}

void RegisterBookMarkScreen::showRegisterBookmarkDialog()
{
}