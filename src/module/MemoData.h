/**
 * @file MemoData.h
 * @author Kodai-study (anchor.kou@softbank.ne.jp)
 * @brief 読書中のブックマークのデータを保持するクラスMemoDataの宣言を記述するファイル
 * @date 2023-04-10
 */
#ifndef MEMO_DATA_H
#define MEMO_DATA_H

/**
 * @brief 読書中のブックマークのデータを保持するクラス
 */
class MemoData
{
public:
    // ブックマークの種類を表す変数
    enum MemoType
    {
        MEMO_TYPE_BOOKMARK = 0,
        MEMO_TYPE_NOTE = 1,
        MEMO_TYPE_QUESTION = 2,
        MEMO_TYPE_ANSWER = 3,
        MEMO_TYPE_UNKNOWN = 4
    };

    MemoType memoType;
    String memo;
    int pageNumber;
    bool resolved;

    // 全ての変数を引数の値に初期化するコンストラクタ
    MemoData(MemoType memoType, String memo, int pageNumber, bool resolved)
    {
        this->memoType = memoType;
        this->memo = memo;
        this->pageNumber = pageNumber;
        this->resolved = resolved;
    }

    // デフォルトコンストラクタ
    MemoData()
    {
        this->memoType = MEMO_TYPE_UNKNOWN;
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