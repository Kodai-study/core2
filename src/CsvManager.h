/**
 * @file CsvManager.h
 * @author Kodai-study (anchor.kou@softbank.ne.jp)
 * @brief CsvManagerクラスの宣言
 * @date 2023-04-06
 *
 */

#include "header.h"
#include "LinkedList.h"

#ifndef CSV_MANAGER_H
#define CSV_MANAGER_H

/**
 * CSVファイルへの書き込みを管理するクラス
 */
class CsvManager
{
private:
    String m_fileName;
    File m_file;

    // ファイルが、読み取りモードで開かれているか、書き込みモードで開かれているかを判定するフラグ
    bool isWriteMode;

public:
    /**
     * @param openWriteMode 書き込みモードで開くかどうか
     */
    CsvManager(String fileName, bool openWriteMode = false)
    {
        m_fileName = fileName;
        isWriteMode = openWriteMode;
    }

    // ファイルアクセサを開放するデストラクタ。
    ~CsvManager()
    {
        closeFile();
    }

    /**
     * @brief 1行分の文字列を受け取って、CSVファイルに書き込む。
     *
     * @param line 書き込む文字列
     */
    void writeLine(String line)
    {
        if (!openFile())
            return;

        if (!isWriteMode)
        {

            m_file.close();
            m_file = SD.open(m_fileName, FILE_APPEND, true);
            isWriteMode = true;
        }
        m_file.println(line);
    }

    /**
     * @brief 1行分の文字列を読み込んで返す関数。
     *
     * @return String 読み込んだ文字列。改行文字を含む。
     */
    String readLine()
    {
        if (!openFile())
            return "";

        if (isWriteMode)
        {
            m_file.close();
            m_file = SD.open(m_fileName, FILE_READ, true);
            isWriteMode = false;
        }
        return m_file.readStringUntil('\n');
    }

    /**
     * @brief ファイルの全ての行を読み込み、LinkedListで返す関数。
     *
     * @return LinkedList<String> 1行の文字列を1つの要素としたLinkedList
     */
    LinkedList<String> readAllLines()
    {
        LinkedList<String> list;
        if (!openFile())
            return list;

        if (isWriteMode)
        {
            m_file.close();
            m_file = SD.open(m_fileName, FILE_READ, true);
            isWriteMode = false;
        }
        while (m_file.available())
        {
            list.add(m_file.readStringUntil('\n'));
        }
        return list;
    }

    // m_file が今読み書き可能な状態かどうかを判断して、不可能な場合は、開きなおす関数
    void checkFile()
    {
        if (!m_file.available())
        {
            m_file.close();
            m_file = SD.open(m_fileName, FILE_APPEND, true);
        }
    }

    // ファイルが閉じていたら開く関数。もともと開いていた場合と、開くことに成功したときはtrueを返す。
    bool openFile()
    {
        if (!m_file)
        {
            m_file = SD.open(m_fileName, isWriteMode ? FILE_APPEND : FILE_READ, true);
            if (!m_file)
            {
                return false;
            }
        }
        return true;
    }

    // ファイルを閉じる関数。もともと閉じていた場合と、閉じることに成功したときはtrueを返す。
    bool closeFile()
    {
        if (m_file)
        {
            m_file.close();
            if (m_file)
            {
                return false;
            }
        }
        return true;
    }

    // ファイルが開いているかどうかを返す関数。
    bool isFileOpen()
    {
        return m_file;
    }

    /**
     * @brief CSVファイルの中身をリセットする関数
     *
     * @param titleString 1行目に項目名として書き込む文字列。指定しなかった場合、元のファイルの1行目をそのまま書き込む。
     */
    void resetFile(String titleString = "")
    {
        m_file.close();
        m_file = SD.open(m_fileName, FILE_WRITE, true);
        isWriteMode = true;

        if (titleString != "")
        {
            m_file.println(titleString);
        }
        else
        {
            m_file.println(m_file.readStringUntil('\n'));
        }
        m_file.close();
        m_file = SD.open(m_fileName, FILE_WRITE, true);
        m_file.println();
        m_file.close();
    }

    // m_file でファイルにアクセスして、ファイルの最後の行を削除する関数
};

#endif