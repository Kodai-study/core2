#ifndef SELECT_BOOK_SCREEN_H
#define SELECT_BOOK_SCREEN_H

#include "header.h"
#include "ScreenBase.h"
#include "../module/BookData.h"
#include <LinkedList.h>

/**
 * @brief 読む本を選択する画面を制御するクラス
 */
class SelectBookScreen : public ScreenBase
{
private:
    const String BOOKDATA_PATH = String("/bookDatas");
    const String BOOKDATA_FILE_NAME = String("/bookData.csv");
    const int LINE_WIDTH = 2;
    const int LINE_LENGTH = 20;
    const int MAX_BOOK_NUM = 4;
    const int MAX_BOOK_NAME_LENGTH = 8;

    // データベースに保存されている本のデータを格納するリスト
    LinkedList<BookData *> bookDataList;
    int cursorPosition = -1;

    /**
     * @brief 本のリストの区切り線を描画する
     *
     * @param y 区切り線のy座標
     */
    void drawLine(int y);
    /**
     * @brief Get the Book Data object
     *
     * @return true
     * @return false
     */
    bool getBookData();
    /**
     * @brief 本のリストを(再)描画する
     */
    void drawBookList();

public:
    void initScreen() override;
    void deleteScreen() override;
    void scereenUpdate() override;
    int selectBookIndex = -1;
};

#endif