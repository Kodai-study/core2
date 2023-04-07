#ifndef SETTING_H
#define SETTING_H

#include "header.h"

class Setting
{
public:
    Setting();
    void setSSID(String ssid);
    void setWifiPass(String pass);
    void setTimeInterval(int timeInterval);
    void setRepeat(int rep);
    String getSSID();
    String getWifiPass();
    int getTime();
    int getRepeat();
    static const char *SSID_COLUM[];
    static const char *WIFI_PASS_COLUM[];

private:
    void writeIni();
    void readIni();
    String ssid = "SSID";
    String wifiPass = "PASS";
    int timeInterval = 10;
    int repeat = 5;
};

#endif
