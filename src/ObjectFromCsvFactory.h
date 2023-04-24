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
#include "module/MemoData.h"

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

    static MemoData CreateMemoDataFromCsv(const String csvLine)
    {
        String array[4];
        split(csvLine, array);

        MemoData memoData{
            (MemoData::MemoType)array[0].toInt(),
            array[1],
            array[2].toInt(),
            array[3].toInt()};

        return memoData;
    }
};

#endif