#include "header.h"
#include "SelectBookScreen.h"
#include "module/BookData.h"

void SelectBookScreen::initScreen()
{
    ScreenBase::initScreen();
    Llcd.fillScreen(BLACK);
    Llcd.setCursor(55, 217);
    Llcd.setTextFont(&fonts::lgfxJapanMinchoP_24);
    Llcd.print("前      決定        次");

    if (!getBookData())
    {
        Llcd.println("データ取得失敗");
        return;
    }

    // TODO 本を選択するカーソルを設定ファイルから初期化する
    cursorPosition = 0;
    drawBookList();
}

void SelectBookScreen::drawBookList()
{
    // 一番下のボタンのプロンプト以外の部分を消す
    Llcd.fillRect(0, 0, 320, 200, BLACK);
    int yPosition = 10;

    Llcd.setCursor(20, yPosition);
    Llcd.setFont(&fonts::lgfxJapanMinchoP_32);

    int firstIndex = (cursorPosition >= MAX_BOOK_NUM ? cursorPosition - 3 : 0);
    for (int i = firstIndex; i < firstIndex + MAX_BOOK_NUM && i < bookDataList.size(); i++)
    {
        BookData *bookData = bookDataList.get(i);
        if (bookData->getBookName().length() > MAX_BOOK_NAME_LENGTH)
        {
            Llcd.print(bookData->getBookName().substring(0, MAX_BOOK_NAME_LENGTH));
            Llcd.println("...");
        }
        else
        {
            Llcd.println(bookData->getBookName());
        }
        drawLine(yPosition + 40);
        yPosition += 50;
        if (i == cursorPosition)
        {
            Llcd.setCursor(150, yPosition + 15);
            Llcd.setFont(&fonts::lgfxJapanMinchoP_16);
            Llcd.printf("ページ:%03d", bookData->getCurrentPage());
            Llcd.setFont(&fonts::lgfxJapanMinchoP_32);
        }
    }

    if (cursorPosition - 3 > 0)
    {
        Llcd.setCursor(220, 10);
        Llcd.print("↑");
    }
    if (firstIndex + 3 < (bookDataList.size() - 1))
    {
        Llcd.setCursor(220, 160);
        Llcd.print("↓");
    }
}

void SelectBookScreen::scereenUpdate()
{
    // ボタンAを押すと、カーソルの値が1つ増えて、本のリストを再表示する
    if (M5.BtnA)
    {
        cursorPosition++;
        drawBookList();
    }
}

void SelectBookScreen::deleteScreen()
{
}

bool SelectBookScreen::getBookData()
{
    if (isWifiConnected)
    {
        FirebaseData data;
        FirebaseJsonArray arrayData;

        if (Firebase.getArray(data, BOOKDATA_PATH, &arrayData))
            // 取得したデータをbookDataListに格納する
            for (int i = 0; i < arrayData.size(); i++)
            {
                FirebaseJson json;
                FirebaseJsonData jsonData;
                FirebaseJsonArray bookMarkArray;
                bool isGetSuccess = true;

                if (!arrayData.get(jsonData, i))
                    return false;
                jsonData.get(json);

                isGetSuccess &= json.get(jsonData, "bookName");
                String bookName = jsonData.stringValue;

                isGetSuccess &= json.get(jsonData, "currentPage");
                int currentPage = jsonData.intValue;

                isGetSuccess &= json.get(jsonData, "readingTime");
                bool isReadEnd = jsonData.boolValue;

                isGetSuccess &= json.get(jsonData, "MemoList");
                isGetSuccess &= jsonData.getArray(bookMarkArray);
                bookMarkArray.size();

                if (!isGetSuccess || isReadEnd)
                    continue;

                this->bookDataList.add(new BookData(bookName, currentPage, i, isReadEnd));
            }
    }
    else
    {
        // TODO ローカルのCSVファイルからデータを取得する
        // TODO 取得したデータをbookDataListに格納する
    }
    return true;
}

void SelectBookScreen::drawLine(int y)
{
    Llcd.drawLine(20, y, 300, y, WHITE);
}