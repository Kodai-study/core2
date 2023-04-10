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
    int getTime();
    int getRepeat();
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
    /**
     * @brief 設定情報をファイルから読み込む
     */
    void readIni();
    String ssid = "SSID";
    String wifiPass = "PASS";
    int timeInterval = 10;
    int repeat = 5;
};

#endif
