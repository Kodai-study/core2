/**
 * @file ReadingScreen.h
 * @author Kodai-study (anchor.kou@softbank.ne.jp)
 * @brief 読書中の画面の制御を行うReadingScreenクラスの宣言
 * @date 2023-04-06
 *
 */
#include "header.h"
#include "ScreenBase.h"
#include "ObjectFromCsvFactory.h"
#include "module/PageFlipData.h"
#include "CsvManager.h"
#include "../module/BookData.h"
#include "../module/BookMarkData.h"

/**
 * @brief 現在の時刻を手動で設定する画面の制御を行うクラス
 */
class RegisterBookMarkScreen : public ScreenBase
{
private:
   BookMarkType lastSelectedBookMarkType;
   // ブックマーク登録のための情報を表示する関数
   void updateBookmarkType();
   BookData currentBookData;

public:
   void initScreen() override;
   void deleteScreen() override;
   void screenUpdate() override;
   // ブックマークの種類の一覧を表した列挙型の宣言。  項目は以下の通り
   /* 大事なところ、分からなかったところ、分からなかった単語、その他 */
};