/**
 * @file ReadingScreen.h
 * @author Kodai-study (anchor.kou@softbank.ne.jp)
 * @brief 読書中の画面の制御を行うReadingScreenクラスの宣言
 * @date 2023-04-06
 *
 */
#include "header.h"
#include "ScreenBase.h"

/**
 * @brief 読書中の画面の制御を行うクラス
 *
 */
class ReadingScreen : public ScreenBase
{
private:
   /**
    * @brief 読書モード_その他
    */
   const int OTHERS_MODE = 0;
   /**
    * @brief 読書モード_集中モード
    */
   const int FOCUS_MODE = 1;
   /**
    * @brief 自由モード
    */
   const int FREE_MODE = 2;

   /**
    * @brief 読書データ配列の数
    * イコールで、次に書き込む配列のインデックスになる
    */
   int readDataindex = -1;
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
   int currentMode = OTHERS_MODE;
   /**
    * @brief 現在読書中の本を表すインデックス
    * 本データの配列のインデックスを表す
    */
   int readingBookIndex = 0;
   /**
    * @brief ページめくりデータの配列にアクセスするパス
    */
   const String DATA_PAGEFLIP_PATH = String("readDatas/");

public:
   void initScreen() override;
   /**
    * @brief Construct a new Reading Screen object
    * 
    * @param readDataindex 
    * @param currentPage 
    * @param bookName 
    */
   ReadingScreen(int readDataindex, int currentPage, String bookName);
   void deleteScreen() override;
   void scereenUpdate() override;
   int getreadDataindex();
};