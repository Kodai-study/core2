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
    // "これはサンプルの表示です"
    Llcd.println("これはサンプルの表示です");
}

void RegisterBookMarkScreen::deleteScreen()
{
    Llcd.fillScreen(BLACK);
}

void RegisterBookMarkScreen::scereenUpdate()
{
}

void RegisterBookMarkScreen::showRegisterBookmarkDialog()
{
}