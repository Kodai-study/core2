/**
 * @file BookMarkData.h
 * @author Kodai-study (anchor.kou@softbank.ne.jp)
 * @brief 読書中のブックマークのデータを保持するクラスMemoDataの宣言を記述するファイル
 * @date 2023-04-10
 */
#ifndef MEMO_DATA_H
#define MEMO_DATA_H

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
    BookMarkType memoType;
    String memo;
    int pageNumber;
    bool resolved;

    // 全ての変数を引数の値に初期化するコンストラクタ
    BookMarkData(BookMarkType memoType, String memo, int pageNumber, bool resolved)
    {
        this->memoType = memoType;
        this->memo = memo;
        this->pageNumber = pageNumber;
        this->resolved = resolved;
    }

    // デフォルトコンストラクタ
    BookMarkData()
    {
        this->memoType = IMPORTANT;
        this->memo = "";
        this->pageNumber = -1;
        this->resolved = false;
    }

    String getCsvLine()
    {
        String csvLine = "";
        csvLine += String(this->memoType) + ",";
        csvLine += this->memo + ",";
        csvLine += String(this->pageNumber) + ",";
        csvLine += String(this->resolved) + ",";
        return csvLine;
    }
};

#endif