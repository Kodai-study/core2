#ifndef SELECT_BOOK_SCREEN_H
#define SELECT_BOOK_SCREEN_H

#include "header.h"
#include "ScreenBase.h"
// BookDataクラスをインクルード
#include "../module/BookData.h"
#include <LinkedList.h>

/**
 * @brief 読む本を選択する画面を制御するクラス
 */
class SelectBookScreen : public ScreenBase
{
private:
    const String BOOKDATA_PATH = String("/books");
    const int LINE_WIDTH = 2;
    const int LINE_LENGTH = 20;
    /**
     * @brief データベースに保存されている本のデータを格納するリスト
     */
    LinkedList<BookData *> bookDataList;

    void drawLine(int y);

    /**
     * @brief データベースから本のデータを取得して、bookDataListに格納する
     *
     * @return true 取得が成功して、bookDataListを利用できる
     * @return false 取得が失敗した
     */
    bool getBookData();

public:
    void initScreen() override;
    void deleteScreen() override;
    void scereenUpdate() override;
};

#endif