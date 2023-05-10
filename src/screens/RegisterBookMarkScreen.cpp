/**
 * @file ReadingScreen.cpp
 * @author Kodai-study (anchor.kou@softbank.ne.jp)
 * @brief 読書中画面の制御を行うクラス、ReadingScreenの実装を記述するファイル
 * @date 2023-04-06
 */

#include "header.h"
#include "RegisterBookMarkScreen.h"
#include "../module/BookMarkData.h"

// COLOR_LIST を初期化。  サイズはブックマークの種類だけ
const int RegisterBookMarkScreen::COLOR_LIST[] = {RED, ORANGE, YELLOW, GREEN};

void RegisterBookMarkScreen::initScreen()
{
    ScreenBase::initScreen();
    Llcd.setCursor(20, 209);
    Llcd.setFont(&fonts::lgfxJapanGothicP_24);
    Llcd.println("キャンセル    作成    モード切替");

    Llcd.setCursor(100, 10);
    Llcd.printf("%dページ目", readingBook.getCurrentPage());

    Llcd.setCursor(64, 96);
    Llcd.setFont(&fonts::lgfxJapanGothicP_32);

    // 現在選択されているブックマークの種類を表示する
    updateBookmarkType();

    drawBookmarkIcon(COLOR_LIST[(int)lastSelectedBookMarkType]);
}

void RegisterBookMarkScreen::deleteScreen()
{
    Llcd.fillScreen(BLACK);

    // 四角の描写と三角の描写を合わせてブックマークアイコンの描写を行う
}

void RegisterBookMarkScreen::screenUpdate()
{
    // ボタンAが押されたら、読書中画面に遷移する
    if (M5.BtnA.wasPressed())
    {
        screenTransitionHandler(Screen::Screen_Reading);
    }

    if (M5.BtnB.wasPressed())
    {
        // BookMarkData(int bookIndex, BookMarkType memoType, int pageNumber, String memo = "", bool resolved = false)
        BookMarkData bookMarkData(readingBook.getBookIndex(), this->lastSelectedBookMarkType, readingBook.getCurrentPage());
        // WIfiに接続されていたら、JSONデータを作成してFIrebaseに書き込む
        if (isWifiConnected)
        {
            FirebaseData firebaseData;
            // JSONデータを作成する
            FirebaseJson *jsonData = bookMarkData.getJson();
            int index = currentBookData.getMemoDataSize();

            String bookMarkDataPath = "/bookMarkList/";
            bookMarkDataPath += readingBook.getBookIndex();
            bookMarkDataPath += "/";
            bookMarkDataPath += index;

            if (!Firebase.setJSON(firebaseData, bookMarkDataPath, *jsonData))
                return;

            currentBookData.setMemoDataSize(index + 1);
            String bookDataPath = "/bookDatas/";
            bookDataPath += readingBook.getBookIndex();
            bookDataPath += "/bookMarkSize";
            Firebase.setInt(firebaseData, bookDataPath, currentBookData.getMemoDataSize());
        }
        else
        {
            CsvManager csvManager = CsvManager("/bookMarks.csv", true);
            csvManager.writeLine(bookMarkData.getCsvLine());
            Serial.println(bookMarkData.getCsvLine());
            csvManager.closeFile();
        }
        screenTransitionHandler(Screen::Screen_Reading);
    }

    // ボタンCが押されたら、ブックマークの種類を変更する
    if (M5.BtnC.wasPressed())
    {
        this->lastSelectedBookMarkType = (BookMarkType)((this->lastSelectedBookMarkType + 1) % BOOKMARK_TYPE_NUM);
        updateBookmarkType();
        drawBookmarkIcon(COLOR_LIST[(int)lastSelectedBookMarkType]);
    }
}

void RegisterBookMarkScreen::updateBookmarkType()
{
    Llcd.fillRect(0, 100, 320, 100, BLACK);
    Llcd.setCursor(20, 100);

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

void RegisterBookMarkScreen::drawBookmarkIcon(int color)
{
    // 適当に大きさと位置を決める
    const int32_t rectWidth = 40;
    const int32_t rectHeight = 40;
    const int32_t triangleHeight = 20;
    const int32_t triangleWidth = rectHeight / 2;

    // アイコンの描写する範囲を黒塗りにする。  大きさは上の定数を参照
    Llcd.fillRect(ICON_POSITION.x, ICON_POSITION.y, rectWidth + triangleWidth, rectHeight + triangleHeight, BLACK);

    // 描画する四角形
    Llcd.fillRect(ICON_POSITION.x, ICON_POSITION.y, rectWidth, rectHeight, color);
    // 描画する三角形
    Llcd.fillTriangle(ICON_POSITION.x, ICON_POSITION.y + rectHeight, ICON_POSITION.x, ICON_POSITION.y + rectHeight + triangleHeight,
                      ICON_POSITION.x + triangleWidth, ICON_POSITION.y + rectHeight, color);
    Llcd.fillTriangle(ICON_POSITION.x + rectWidth, ICON_POSITION.y + rectHeight, ICON_POSITION.x + rectWidth, ICON_POSITION.y + rectHeight + triangleHeight,
                      ICON_POSITION.x + triangleWidth, ICON_POSITION.y + rectHeight, color);
}