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
        Llcd.setCursor(50, 50);
        Llcd.setFont(&fonts::lgfxJapanMinchoP_28);
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
    Llcd.fillRect(0, 0, 320, 210, BLACK);
    int yPosition = 2;
    Llcd.setFont(&fonts::lgfxJapanMinchoP_32);

    int firstIndex = (cursorPosition >= MAX_BOOK_NUM ? cursorPosition - 3 : 0);

    for (int i = firstIndex; i < firstIndex + MAX_BOOK_NUM && i < bookDataList.size(); i++)
    {
        BookData *bookData = bookDataList.get(i);
        Llcd.setCursor(20, yPosition + 15);
        if (bookData->getBookName().length() / 4 > MAX_BOOK_NAME_LENGTH)
        {
            Llcd.print(bookData->getBookName().substring(0, MAX_BOOK_NAME_LENGTH));
            Llcd.print("...");
        }
        else
        {
            Llcd.println(bookData->getBookName());
        }
        if (i == cursorPosition)
        {
            Llcd.setCursor(150, yPosition + 15);
            Llcd.setFont(&fonts::lgfxJapanMinchoP_16);
            Llcd.printf("ページ:%03d", bookData->getCurrentPage());
            Llcd.setFont(&fonts::lgfxJapanMinchoP_32);
        }
        drawLine(yPosition + 40);
        yPosition += 50;
    }

    if (cursorPosition - 3 > 0)
    {
        Llcd.setCursor(250, 10);
        Llcd.print("↑");
    }
    if (firstIndex + 3 < (bookDataList.size() - 1))
    {
        Llcd.setCursor(250, 160);
        Llcd.print("↓");
    }
}

void SelectBookScreen::scereenUpdate()
{
    // ボタンAを押すと、カーソルの値が1つ増えて、本のリストを再表示する
    if (M5.BtnA.wasPressed())
    {
        cursorPosition = (cursorPosition + 1) % bookDataList.size();
        drawBookList();
    }
    else if (M5.BtnC.wasPressed() && cursorPosition > 0)
    {
        cursorPosition--;
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

                delay(1000);

                isGetSuccess &= json.get(jsonData, "bookName");
                String bookName = jsonData.stringValue;

                isGetSuccess &= json.get(jsonData, "currentPage");
                int currentPage = jsonData.intValue;

                isGetSuccess &= json.get(jsonData, "readingTime");
                bool isReadEnd = jsonData.boolValue;

                isGetSuccess &= json.get(jsonData, "memoList");
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

        // bookDataListに、10個のデータを追加する
        // データは、"テスト(1～10)"、ページ数は1～10、IDは0～9、読了フラグはTrueとfalseを交互に設定する
        for (int i = 1; i <= 10; i++)
        {
            this->bookDataList.add(new BookData("テスト" + String(i), i, i - 1, i % 2 == 0));
        }
    }
    return true;
}

void SelectBookScreen::drawLine(int y)
{
    Llcd.drawLine(20, y, 200, y, WHITE);
}