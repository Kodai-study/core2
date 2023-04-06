/**
 * @file CsvManager.h
 * @author Kodai-study (anchor.kou@softbank.ne.jp)
 * @brief CsvManagerクラスの宣言
 * @date 2023-04-06
 * 
 */

#include "header.h"

// include guard
#ifndef CSV_MANAGER_H
#define CSV_MANAGER_H

/**
 * CSVファイルを扱うクラス。
 *
 */
class CsvManager
{
    // ファイル名を受け取って、ファイルアクセサを生成するコンストラクタ。
    // ファイルへのアクセスは、SD.open()で行う。
    // このとき、ファイルが存在しない場合は、ファイルを作成する。
    // ファイルが存在する場合は、ファイルの末尾に追記する。


    /**
     * @brief Construct a new Csv Manager object
     * 
     * @param fileName 
     */
    CsvManager(String fileName) : m_fileName(fileName)
    {
        File m_file = SD.open(m_fileName, FILE_WRITE, true);
    }

    // ファイルアクセサを開放するデストラクタ。
    ~CsvManager()
    {
        m_file.close();
    }

    void writeLine(String line)
    {
        m_file.println(line);
    }

    // CSVファイルから読み込む。
    // 読み込みには、File.readStringUntil()を使用する。
    // ファイルの末尾に改行を追加する。
    String readLine()
    {
        return m_file.readStringUntil('\n');
    }

    // m_file が今読み書き可能な状態かどうかを判断して、不可能な場合は、開きなおす関数
    void checkFile()
    {
        if (!m_file.available())
        {
            m_file.close();
            m_file = SD.open(m_fileName, FILE_WRITE, true);
        }
    }
};

#endif