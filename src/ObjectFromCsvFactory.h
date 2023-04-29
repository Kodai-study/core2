/**
 * @file ObjectFromCsvFactory.h
 * @author Kodai-study (anchor.kou@softbank.ne.jp)
 * @brief CSV文字列からオブジェクトを作成するクラスCreateObjectFromCsvFactoryの宣言を記述するファイル
 * @date 2023-04-11
 */
#ifndef CREATE_OBJECT_FROM_CSV_FACTORY_H
#define CREATE_OBJECT_FROM_CSV_FACTORY_H

#include "header.h"
#include "module/PageFlipData.h"
#include "module/BookMarkData.h"
#include "module/BookData.h"

class CreateObjectFromCsvFactory
{
private:
    // csvLineの文字列を、 ',' で分割して、配列に格納する関数
    //  split関数は使用できない
    //  要素数は不定である
    static bool split(String csvLine, String array[])
    {
        String value;
        int index = 0;
        int startIndex = 0;
        int endIndex = 0;

        while (endIndex != -1)
        {
            endIndex = csvLine.indexOf(',', startIndex);
            String token = (endIndex == -1) ? csvLine.substring(startIndex)
                                            : csvLine.substring(startIndex, endIndex);
            array[index++] = token;
            startIndex = endIndex + 1;
        }
        return true;
    }

public:
    static PageFlipHistory CreateRealHistoryFromCsv(String csvLine)
    {
        String value;
        String array[3];

        PageFlipHistory readingHistory{
            array[0],
            (PageFlipHistory::ReadingMode)(array[1].toInt()),
            array[2].toInt()};

        value.toInt();

        return readingHistory;
    }

    static BookMarkData CreateMemoDataFromCsv(const String csvLine)
    {
        String array[4];
        split(csvLine, array);

        BookMarkData memoData{
            (BookMarkType)array[0].toInt(),
            array[1],
            array[2].toInt(),
            array[3].toInt()};

        return memoData;
    }

    static BookData *CreateBookDataFromCsv(const String csvLine)
    {
        String array[6];
        split(csvLine, array);

        return new BookData(
            array[0],
            array[1].toInt(),
            array[2].toInt(),
            array[3].toInt() != 0,
            array[4].toInt());
    }
};

#endif