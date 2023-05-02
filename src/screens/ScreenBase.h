/**
 * @file ScreenBase.h
 * @author Kodai-study (anchor.kou@softbank.ne.jp)
 * @brief 様々な画面に共通する処理項目をまとめたクラス、ScreenBaseクラスの宣言
 * @date 2023-04-06
 *
 */

#include "header.h"

#ifndef SCREEN_BASE
#define SCREEN_BASE
/**
 * @brief 様々な画面に共通する処理項目をまとめたクラス
 * initScreen() で画面の初期化 ↓
 * screenUpdate() でマイフレームの画面の更新 ↓
 * deleteScreen() で画面の削除
 */
class ScreenBase
{
protected:
    /**
     * @brief
     */
    ButtonColors defaultColor_ButtonOn = {CYAN, WHITE, WHITE};
    ButtonColors defaultColor_ButtonOff = {DARKCYAN, WHITE, WHITE};
    /**
     * @brief 現在Wi-Fi、インターネットに接続されているか
     */

    bool isWifiConnected;

public:
    /**
     * @brief 画面の初期化を行う。画面遷移され、画面が表示される時に呼び出す。
     */
    virtual void initScreen() { isWifiConnected = isEnableWifiConnect && (WiFi.status() == WL_CONNECTED); };

    /**
     * @brief 画面の更新を行う。現在画面が有効な時に、ループ処理でこの処理を呼び出す。
     */
    virtual void screenUpdate(){};

    /**
     * @brief 画面の削除を行う。画面遷移の際に、次の画面に進む前に処理を行う。
     */
    virtual void deleteScreen(){};
};

#endif