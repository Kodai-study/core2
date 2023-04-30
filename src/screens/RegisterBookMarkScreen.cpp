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
    ScreenBase::initScreen();
    Llcd.setCursor(20, 209);
    Llcd.setFont(&fonts::lgfxJapanGothicP_24);
    Llcd.println("キャンセル    作成    モード切替");

    Llcd.setCursor(64, 96);
    Llcd.setFont(&fonts::lgfxJapanGothicP_32);
    Llcd.println("これはサンプルの表示です");
}

void RegisterBookMarkScreen::deleteScreen()
{
    Llcd.fillScreen(BLACK);

    // 四角の描写と三角の描写を合わせてブックマークアイコンの描写を行う
    Llcd.fillTriangle(0, 0, 0, 20, 20, 0, WHITE);
    Llcd.fillTriangle(0, 0, 20, 0, 0, 20, WHITE);
    Llcd.fillRect(0, 20, 20, 20, WHITE);
}

void RegisterBookMarkScreen::scereenUpdate()
{
    // ボタンAが押されたら、読書中画面に遷移する
    if (M5.BtnA.wasPressed())
    {
        screenTransitionHandler(Screen::Screen_Reading);
    }

    if (M5.BtnB.wasPressed())
    {
        //   BookMarkData(int bookIndex, BookMarkType memoType, int pageNumber, String memo = "", bool resolved = false)
        BookMarkData bookMarkData(readingBook.getBookIndex(), this->lastSelectedBookMarkType, readingBook.getCurrentPage());
        // WIfiに接続されていたら、JSONデータを作成してFIrebaseに書き込む
        if (isWifiConnected)
        {
            FirebaseData firebaseData;
            // JSONデータを作成する
            FirebaseJson *jsonData = bookMarkData.getJson();
            int index = currentBookData.getMemoDataIndex() + 1;
            // Firebaseにデータを書き込む

            Firebase.setJSON(firebaseData, "/bookMarkList/" + String(readingBook.getBookIndex()), *jsonData);
        }
        else
        {
            csvManager.writeLine(bookMarkData.getCsvLine());
            screenTransitionHandler(Screen::Screen_Reading);
        }
    }

    // ボタンCが押されたら、ブックマークの種類を変更する
    if (M5.BtnC.wasPressed())
    {
        this->lastSelectedBookMarkType = (BookMarkType)((this->lastSelectedBookMarkType + 1) % BOOKMARK_TYPE_NUM);
        updateBookmarkType();
    }
}

void RegisterBookMarkScreen::updateBookmarkType()
{
    Llcd.fillRect(0, 100, 240, 80, BLACK);
    Llcd.setCursor(50, 100);

    // ブックマークの種類によって、表示する文字列を変更する
    switch (this->lastSelectedBookMarkType)
    {
    case BookMarkType::IMPORTANT:
        Llcd.println("大事なところ");
        break;
    case BookMarkType::DONT_UNDERSTAND:
        Llcd.println("分からなかったところ");
        break;
    case BookMarkType::DONT_UNDERSTAND_WORD:
        Llcd.println("分からなかった単語");
        break;
    case BookMarkType::OTHERS:
        Llcd.println("その他");
        break;
    }
}