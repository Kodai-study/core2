#include "header.h"
#include "SelectBookScreen.h"
#include "module/BookData.h"

void SelectBookScreen::initScreen()
{
}

void SelectBookScreen::deleteScreen()
{
}

void SelectBookScreen::scereenUpdate()
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
                uint32_t hoge;
                bool isGetSuccess = true;

                if (!arrayData.get(jsonData, i))
                    return false;
                jsonData.get(json);

                // json 変数のデータから、BookDataクラスのインスタンスを生成する

                isGetSuccess &= json.get(jsonData, "bookName");
                String bookName = jsonData.stringValue;

                isGetSuccess &= json.get(jsonData, "currentPage");
                int currentPage = jsonData.intValue;

                isGetSuccess &= json.get(jsonData, "readingTime");
                bool isReadEnd = jsonData.boolValue;

                if (!isGetSuccess)
                    return false;

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