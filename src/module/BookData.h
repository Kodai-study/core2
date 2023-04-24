#ifndef BOOK_DATA_H
#define BOOK_DATA_H

#include "header.h"

/**
 * @brief 本のデータを格納するデータクラス
 */
class BookData
{
private:
    /**
     * @brief この本の名前
     */
    String bookName;
    /**
     * @brief 現在のページ数
     * 最後に読まれたページ数を表すことになる
     */
    int currentPage;
    /**
     * @brief この本に付けられた番号
     * RealtimeDatabaseの配列におけるインデックスを表し、
     * このインデックスを使ってアクセスする
     */
    int bookIndex;
    /**
     * @brief 読了されたかどうかを表すフラグ
     */
    bool isReadEnd;
    /**
     * @brief 次に書き込むメモデータのインデックス
     * 初期値は現在のメモの個数になり、書き込むごとに増えていく
     */
    int memoDataIndex = -1;
    int memoDataSize = -1;

public:
    // ブックマークの配列の数を取得する関数の定義。
    // memoDataIndexの値を更新し、取得に成功したか否かを返す
    int getMemoDataSize() { return this->memoDataSize; }

    String getBookName() { return this->bookName; }
    int getCurrentPage() { return this->currentPage; }
    int getBookIndex() { return this->bookIndex; }
    bool getIsReadEnd() { return this->isReadEnd; }
    int getMemoDataIndex() { return this->memoDataIndex; }

    void setCurrentPage(int currentPage) { this->currentPage = currentPage; }
    void setMemoDataIndex(int memoDataIndex) { this->memoDataIndex = memoDataIndex; }

    // 全てのパラメータを初期化するコンストラクタ
    BookData(String bookName, int currentPage, int bookIndex, bool isReadEnd)
    {
        this->bookName = bookName;
        this->currentPage = currentPage;
        this->bookIndex = bookIndex;
        this->isReadEnd = isReadEnd;
    }
    // 全てのパラメータを初期化するコンストラクタ
    BookData(String bookName, int currentPage, int bookIndex, bool isReadEnd, int memoDataSize)
    {
        this->bookName = bookName;
        this->currentPage = currentPage;
        this->bookIndex = bookIndex;
        this->isReadEnd = isReadEnd;
        this->memoDataSize = memoDataSize;
    }
};

#endif