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
class ScreenBase
{
protected:
    ButtonColors defaultColor_ButtonOn = {CYAN, WHITE, WHITE};
    ButtonColors defaultColor_ButtonOff = {DARKCYAN, WHITE, WHITE};
    bool isWifiConnected;

public:
    virtual void initScreen() { isWifiConnected = (WiFi.status() == WL_CONNECTED); };
    virtual void deleteScreen(){};
    virtual void scereenUpdate(){};
};

#endif