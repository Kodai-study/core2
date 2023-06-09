/**
 * @file Setting.h
 * @author Kodai-study (anchor.kou@softbank.ne.jp)
 * @brief 設定情報をファイルに読み書きする処理を管理するSettingクラスの宣言
 * @date 2023-04-10
 *
 */
#ifndef SETTING_H
#define SETTING_H

#include "header.h"

/**
 * @brief 設定情報をファイルに読み書きして、保存や設定情報の反映をおこなう
 */
class Setting
{
public:
    Setting();
    /**
     * @brief 最後に接続が成功したWi-FiのSSIDをファイルに保存する。
     *
     * @param ssid SSIDの文字列
     */
    void setSSID(String ssid);
    /**
     * @brief 最後に接続が成功したWi-Fiのパスワードをファイルに保存する
     *
     * @param pass パスワードの文字列
     */
    void setWifiPass(String pass);
    /**
     * @brief 集中モードのタイムインターバルの時間を設定する
     *
     * @param timeInterval
     */
    void setTimeInterval(int timeInterval);
    /**
     * @brief 集中モードの繰り返し回数を設定する
     *
     * @param rep
     */
    void setRepeat(int rep);
    String getSSID();
    String getWifiPass();
    int getTimeInterval();
    int getRepeat();
    int getBookIndex();
    RTC_DateTypeDef getDate();
    RTC_TimeTypeDef getTime();
    /**
     * @brief 設定情報をファイルから読み込む
     */
    void readIni();

    // 日付と時刻を引数にとって、設定ファイルに書き込む関数の定義
    void setDateTime(RTC_DateTypeDef date, RTC_TimeTypeDef time);

    String getDateTime();

    /**
     * @brief 接続するWi-FiのSSIDの一覧
     * 設定画面で、Wi-Fiの接続を行うときに、この配列の中から選択する
     */
    static const char *SSID_COLUM[];

    static const int SSID_COLUM_SIZE = 5;

    /**
     * @brief 接続するWi-Fiのパスワードの一覧
     */
    static const char *WIFI_PASS_COLUM[];

    static constexpr const char *SETTING_FILE_NAME = "/setting.ini";

    // 設定情報の一覧をデバッグ出力する関数
    void printAllSetting();

private:
    /**
     * @brief 設定情報をファイルに書き込む
     */
    void writeIni();
    String ssid = DATA_NULL;
    String wifiPass = DATA_NULL;
    int timeInterval = 10;
    int repeat = 5;
    int bookIndex = 0;

    RTC_TimeTypeDef time =
        {
            .Hours = 12,
            .Minutes = 0,
            .Seconds = 0,
    };

    RTC_DateTypeDef date =
        {
            .WeekDay = 6,
            .Month = 4,
            .Date = 22,
            .Year = 23,
    };
};

#endif
