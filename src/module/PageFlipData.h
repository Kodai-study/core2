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
    /**
     * @brief ページをめくった時刻。 フォーマットは、YYYY-MM-DD hh:mm:ss
     */
    String dateTime;
    /**
     * @brief ページをめくったときの読書モード
     */
    int mode;
    int page;

    // empty constructor
    pageFlipHistory()
    {
        // 変数の初期値を設定 データを持たない、空を表す値に設定する
        this.dateTime = "";
        this.mode = -1;
        this.page = -1;
    }

    // 引数から変数を初期化するコンストラクタ
    pageFlipHistory(string dateTime, int mode, int page)
    {
        this.dateTime = dateTime;
        this.mode = mode;
        this.page = page;
    }
}

#endif