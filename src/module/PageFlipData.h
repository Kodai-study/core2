/**
 * @file PageFlipData.h
 * @author Kodai-study (anchor.kou@softbank.ne.jp)
 * @brief ページめくりの履歴を保持するクラス、PageFlipHistoryの宣言を記述するファイル
 * @date 2023-04-10
 */
#ifndef PAGE_FLIP_DATA_H
#define PAGE_FLIP_DATA_H

/**
 * @brief ページめくりの履歴を保持するクラス
 */
class PageFlipHistory
{
public:
    // 現在の読書モードの一覧を作成
    enum ReadingMode
    {
        OTHERS_MODE = 0,
        FOCUS_MODE = 1,
        FREE_MODE = 2
    };
    /**
     * @brief ページをめくった時刻。 フォーマットは、YYYY-MM-DD hh:mm:ss
     */
    String dateTime;
    /**
     * @brief ページをめくったときの読書モード
     */
    ReadingMode mode;
    int page;

    // empty constructor
    PageFlipHistory()
    {
        // 変数の初期値を設定 データを持たない、空を表す値に設定する
        this->dateTime = "";
        this->mode = OTHERS_MODE;
        this->page = -1;
    }

    // 引数から変数を初期化するコンストラクタ
    PageFlipHistory(String dateTime, ReadingMode mode, int page)
    {
        this->dateTime = dateTime;
        this->mode = mode;
        this->page = page;
    }

    FirebaseJson *getJson()
    {
        FirebaseJson *pageFlipRecord = new FirebaseJson();
        pageFlipRecord->set("dateTime", this->dateTime);
        pageFlipRecord->set("page", this->page);
        pageFlipRecord->set("mode", (int)this->mode);
        return pageFlipRecord;
    }

    String getCsvLine()
    {
        String csvLine = "";
        csvLine += this->dateTime;
        csvLine += ",";
        csvLine += this->page;
        csvLine += ",";
        csvLine += this->mode;
        return csvLine;
    }
};

#endif