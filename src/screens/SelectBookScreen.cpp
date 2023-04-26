#include "header.h"
#include "SelectBookScreen.h"
#include "module/BookData.h"
#include "../CsvManager.h"
#include "../ObjectFromCsvFactory.h"

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

    cursorPosition = setting.getBookIndex();
    drawBookList();
}

void SelectBookScreen::drawBookList()
{
    // 一番下のボタンのプロンプト以外の部分を消す
    Llcd.fillRect(0, 0, 320, 190, BLACK);
    int yPosition = 5;
    Llcd.setFont(&fonts::lgfxJapanMinchoP_32);

    int firstIndex = (cursorPosition >= MAX_BOOK_NUM ? cursorPosition - 3 : 0);

    for (int i = firstIndex; i < firstIndex + MAX_BOOK_NUM && i < bookDataList.size(); i++)
    {
        BookData *bookData = bookDataList.get(i);
        Llcd.setCursor(20, yPosition);
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

    // Bボタンが押されたら、本の情報を表示する
    if (M5.BtnB.wasPressed())
    {
        BookData *bookData = bookDataList.get(cursorPosition);
        readingBook = *bookData;
        // 読書中画面に遷移する
        // 遷移処理はheader.hにある
        screenTransitionHandler(Screen::Screen_Reading);
    }
}

void SelectBookScreen::deleteScreen()
{
    Llcd.fillScreen(BLACK);
}

bool SelectBookScreen::getBookData()
{
    if (this->isWifiConnected)
    {
        CsvManager csvManager(BOOKDATA_FILE_NAME, true);
        FirebaseData data;
        FirebaseJsonArray arrayData;
        if (Firebase.getArray(data, BOOKDATA_PATH, &arrayData))
        {
            csvManager.resetFile(BookData::COLUM_CSV_LINE);
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

                isGetSuccess &= json.get(jsonData, "isReadEnd");
                bool isReadEnd = jsonData.boolValue;

                isGetSuccess &= json.get(jsonData, "memoList");
                isGetSuccess &= jsonData.getArray(bookMarkArray);
                BookData *bookData = new BookData(bookName, currentPage, i, isReadEnd, bookMarkArray.size());

                Serial.println(isGetSuccess ? "CSV Write Success" : "CSV Write Failed");
                this->bookDataList.add(bookData);
                csvManager.writeLine(bookData->getCsvLine());
                csvManager.closeFile();
            }
        }
    }
    else
    {
        auto csvManager = new CsvManager(BOOKDATA_FILE_NAME, false);
        Serial.println(BOOKDATA_FILE_NAME);
        LinkedList<String> lines = csvManager->readAllLines(true);
        lines.add("テスト本1,1,0,false,0");
        csvManager->closeFile();
        if (lines.size() == 0)
        {
            Serial.println("lines is null or size is 0");
            return false;
        }
        Serial.println(lines.size());
        CreateObjectFromCsvFactory *factory = new CreateObjectFromCsvFactory();
        // ObjectFromCsvFactoryのメソッドを使って、１行ずつBookDataを生成する
        for (int i = 0; i < lines.size(); i++)
        {
            String line = lines.get(i);
            BookData *bookData = factory->CreateBookDataFromCsv(line);

            if (bookData != nullptr)
            {
                this->bookDataList.add(bookData);
                Serial.println(bookData->getCsvLine());
            }
            else
                Serial.println("bookData is null. line:" + line);
        }
    }
    return true;
}

void SelectBookScreen::drawLine(int y)
{
    Llcd.drawLine(20, y, 200, y, WHITE);
}
