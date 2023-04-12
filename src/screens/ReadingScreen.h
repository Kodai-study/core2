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

/**
 * @brief 読書中の画面の制御を行うクラス
 *
 */
class ReadingScreen : public ScreenBase
{
private:
   /**
    * @brief 読書データ配列の数
    * イコールで、次に書き込む配列のインデックスになる
    */
   int currentBookIndex = -1;
   /**
    * @brief 現在読んでいるページ数
    */
   int currentPage;
   /**
    * @brief 本の名前
    */
   String bookName;
   Button btn_x;

   /**
    * @brief 現在の読書モード
    */
   PageFlipHistory::ReadingMode currentMode = PageFlipHistory::ReadingMode::OTHERS_MODE;
   /**
    * @brief 現在読書中の本を表すインデックス
    * 本データの配列のインデックスを表す
    */
   int readingBookIndex = 0;
   /**
    * @brief ページめくりデータの配列にアクセスするパス
    */
   const String DATA_PAGEFLIP_PATH = String("readDatas/");

   CreateObjectFromCsvFactory factory;

   // TODO ページめくりのローカルデータを保存するCSVファイルのパスを定義する
   CsvManager csvManager = CsvManager("readDatas.csv");

public:
   void initScreen() override;
   /**
    * @brief Construct a new Reading Screen object
    *
    * @param currentBookIndex
    * @param currentPage
    * @param bookName
    */
   ReadingScreen(int currentBookIndex, int currentPage, String bookName);
   void deleteScreen() override;
   void scereenUpdate() override;
   int getreadDataindex();
   void setReadDataindex(int currentBookIndex);
};