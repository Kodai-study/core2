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

/**
 * @brief 読書中の画面の制御を行うクラス
 */
class ReadingScreen : public ScreenBase
{
private:
   BookData currentBookData;
   Button btn_x;
   int currentPage = -1;
   int memoIndex = -1;
   /**
    * @brief 現在の読書モード
    */
   PageFlipHistory::ReadingMode currentMode = PageFlipHistory::ReadingMode::OTHERS_MODE;

   /**
    * @brief ページめくりデータの配列にアクセスするパス
    */
   const String DATA_PAGEFLIP_PATH = String("readDatas/");

   CreateObjectFromCsvFactory factory;

   CsvManager csvManager = CsvManager("/readDatas.csv");

public:
   void initScreen() override;
   /**
    * @brief Construct a new Reading Screen object
    *
    * @param currentBookIndex
    * @param currentPage
    * @param bookName
    */
   ReadingScreen();
   // currentBookDataをセットする関数を定義
   // ページ数を取り出して、currentPageにセットする。
   void setCurrentBookData(BookData currentBookData);
   void deleteScreen() override;
   void scereenUpdate() override;
};