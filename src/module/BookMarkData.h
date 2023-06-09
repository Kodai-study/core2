/**
 * @file BookMarkData.h
 * @author Kodai-study (anchor.kou@softbank.ne.jp)
 * @brief 読書中のブックマークのデータを保持するクラスMemoDataの宣言を記述するファイル
 * @date 2023-04-10
 */
#ifndef BOOKMARK_DATA_H
#define BOOKMARK_DATA_H

// ブックマークの種類を表す変数
enum BookMarkType
{
    IMPORTANT,
    DONT_UNDERSTAND,
    DONT_UNDERSTAND_WORD,
    OTHERS,
    BOOKMARK_TYPE_NUM
};

/**
 * @brief 読書中のブックマークのデータを保持するクラス
 */
class BookMarkData
{
public:
    int bookIndex;
    BookMarkType memoType;
    String memo;
    int pageNumber;
    bool resolved;

    BookMarkData(int bookIndex, BookMarkType memoType, int pageNumber, String memo = DATA_NULL, bool resolved = false)
    {
        this->bookIndex = bookIndex;
        this->memoType = memoType;
        this->memo = memo;
        this->pageNumber = pageNumber;
        this->resolved = resolved;
    }

    // 全ての変数を引数の値に初期化するコンストラクタ
    BookMarkData(BookMarkType memoType, String memo, int pageNumber, bool resolved)
    {
        this->memoType = memoType;
        this->memo = memo;
        this->pageNumber = pageNumber;
        this->resolved = resolved;
    }
    // 全ての変数を引数の値に初期化するコンストラクタ
    BookMarkData(BookMarkType memoType, int pageNumber)
    {
        this->memoType = memoType;
        this->memo = DATA_NULL;
        this->pageNumber = pageNumber;
    }

    // デフォルトコンストラクタ
    BookMarkData()
    {
        this->memoType = IMPORTANT;
        this->memo = DATA_NULL;
        this->pageNumber = -1;
        this->resolved = false;
    }

    String getCsvLine()
    {
        String csvLine = "";
        csvLine += String(this->bookIndex) + ",";
        csvLine += String(this->memoType) + ",";
        csvLine += this->memo + ",";
        csvLine += String(this->pageNumber) + ",";
        csvLine += String(this->resolved);
        return csvLine;
    }

    // 以下は、読書データからJSONデータを作成する処理です。同じようにこのクラスのものも作成してください
    FirebaseJson *getJson()
    {
        FirebaseJson *memoRecord = new FirebaseJson();
        memoRecord->set("bookIndex", this->bookIndex);
        memoRecord->set("memoType", (int)this->memoType);
        memoRecord->set("memo", this->memo);
        memoRecord->set("pageNumber", this->pageNumber);
        memoRecord->set("resolved", this->resolved);
        return memoRecord;
    }
};

#endif