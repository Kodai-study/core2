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
    /**
     * @brief 接続するWi-Fiのパスワードの一覧
     */
    static const char *WIFI_PASS_COLUM[];

private:
    /**
     * @brief 設定情報をファイルに書き込む
     */
    void writeIni();
    String ssid = "NULL";
    String wifiPass = "NULL";
    int timeInterval = 10;
    int repeat = 5;

    RTC_TimeTypeDef time;
    RTC_DateTypeDef date;
};

#endif
