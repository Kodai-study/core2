/**
 * @file CsvManager.h
 * @author Kodai-study (anchor.kou@softbank.ne.jp)
 * @brief CsvManagerクラスの宣言
 * @date 2023-04-06
 *
 */

#include "header.h"

#ifndef CSV_MANAGER_H
#define CSV_MANAGER_H

/**
 * CSVファイルを扱うクラス。
 *
 */
class CsvManager
{
private:
    // アクセスするファイル名をパラメータに持ち、コンストラクタで受け取った値に初期化する
    String m_fileName;
    File m_file;

    // ファイルが、読み取りモードで開かれているか、書き込みモードで開かれているかを判定するフラグ
    bool isWriteMode;

public:
    // 変数2つを初期化するコンストラクタ
    CsvManager(String fileName, openWriteMode = false)
    {
        m_fileName = fileName;
        isWriteMode = openWriteMode;
    }

    // ファイルアクセサを開放するデストラクタ。
    ~CsvManager()
    {
        closeFile();
    }

    // 1行分の文字列を受け取って、CSVファイルに書き込む。
    // isWriteMode = falseの時は、書き込みモードで開きなおす
    void writeLine(String line)
    {
        if !(openFile())
            return;

        if (!isWriteMode)
        {
            m_file.close();
            m_file = SD.open(m_fileName, FILE_WRITE, true);
            isWriteMode = true;
        }
        m_file.println(line);
    }


    // 1行分の文字列を読み込んで返す関数。
    // 現在書き込みモードで開いている場合は、読み込みモードで開きなおす。
    //  isWriteMode = trueの時は、読み込みモードで開きなおす
    String readLine()
    {
        if !(openFile())
            return "";

        if (isWriteMode)
        {
            m_file.close();
            m_file = SD.open(m_fileName, FILE_READ, true);
            isWriteMode = false;
        }
        return m_file.readStringUntil('\n');
    }

    // ファイルを1行ずつ読み取って、LinkedListに格納して返す関数。
    // 1行目は無視する。
    // 現在書き込みモードで開いている場合は、読み込みモードで開きなおす。
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

    // 指定した行数を読み込んで、LinkedListに格納して返す関数。
    // 現在書き込みモードで開いている場合は、読み込みモードで開きなおす。
    // 指定した行数がファイルの行数より多い場合は、全ての行を返す。
    LinkedList<String> readLines(int lineCount)
    {
        LinkedList<String> list;
        if !(openFile())
            return list;

        if (isWriteMode)
        {
            m_file.close();
            m_file = SD.open(m_fileName, FILE_READ, true);
            isWriteMode = false;
        }
        m_file.readStringUntil('\n');
        for (int i = 0; i < lineCount; i++)
        {
            list.add(m_file.readStringUntil('\n'));
        }
        return list;
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

    // ファイルが閉じていたら開く関数。もともと開いていた場合と、開くことに成功したときはtrueを返す。
    bool openFile()
    {
        if (!m_file)
        {
            m_file = SD.open(m_fileName, isWriteMode ? FILE_WRITE : FILE_READ, true);
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

            //CSVファイルの中身をリセットする関数
        //もし、titleString の変数が空文字列でなかったら、1行目にそれを書き込んで他はすべて削除する
        //空文字列であったら、ファイルの1行目だけを残して後は削除する
        void resetFile(String titleString = "")
        {
            if (!openFile())
                return;

            if (!isWriteMode)
            {
                m_file.close();
                m_file = SD.open(m_fileName, FILE_WRITE, true);
                isWriteMode = true;
            }
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

};

#endif