#include "header.h"
#include "SettingTimeIntervalScreen.h"

SettingTimeIntervalScreen::SettingTimeIntervalScreen()
    : btn_plus5(0, 0, 0, 0),
      btn_plus1(0, 0, 0, 0),
      btn_minus1(0, 0, 0, 0),
      btn_minus5(0, 0, 0, 0)
{
   this->btn_plus5.erase(BLACK);
   this->btn_plus1.erase(BLACK);
   this->btn_minus1.erase(BLACK);
   this->btn_minus5.erase(BLACK);
}
void pluc2(Event &e)
{
   Llcd.setCursor(0, 0);
   Llcd.println("PUSHED");
}
void SettingTimeIntervalScreen::initScreen()
{
   ScreenBase::initScreen();
   Llcd.fillScreen(BLACK);
   this->btn_plus5 = Button(250, 0, 70, 40, true, "+5", this->defaultColor_ButtonOff, this->defaultColor_ButtonOn);
   this->btn_plus1 = Button(250, 55, 70, 40, true, "+1", this->defaultColor_ButtonOff, this->defaultColor_ButtonOn);
   this->btn_minus1 = Button(250, 110, 70, 40, true, "-1", this->defaultColor_ButtonOff, this->defaultColor_ButtonOn);
   this->btn_minus5 = Button(250, 165, 70, 40, true, "-5", this->defaultColor_ButtonOff, this->defaultColor_ButtonOn);
   btn_plus5.addHandler(pluc2, E_RELEASE);
   btn_plus5.draw();
}

void SettingTimeIntervalScreen::deleteScreen()
{
   this->btn_plus5.erase(BLACK);
   this->btn_plus5.set(0, 0, 0, 0);
   this->btn_plus1.erase(BLACK);
   this->btn_plus1.set(0, 0, 0, 0);
   this->btn_minus1.erase(BLACK);
   this->btn_minus1.set(0, 0, 0, 0);
   this->btn_minus5.erase(BLACK);
   this->btn_minus5.set(0, 0, 0, 0);
}

void SettingTimeIntervalScreen::scereenUpdate()
{
}

// ページ数、時刻、モード(数字)をcsvファイルに書き込む
// 今まで書き込まれた行に追加する
// 書き込み後は改行する
void writeCsv(int page, int time, int mode)
{
   File file = SD.open("data.csv", FILE_WRITE);
   if (file)
   {
      file.print(page);
      file.print(",");
      file.print(time);
      file.print(",");
      file.println(mode);
      file.close();
   }
}

//.iniファイルに設定情報を書き込む。項目は、{SSID,パスワード,タイムインターバル、繰り返し回数}
void writeIni(String ssid, String pass, int time, int repeat) // write to SD card
{
   File file = SD.open("setting.ini", FILE_WRITE); // open file
   if (file)
   {
      file.print("SSID="); // write SSID to file
      file.println(ssid);
      file.print("PASS="); // write password to file
      file.println(pass);
      file.print("TIME="); // write time to file
      file.println(time);
      file.print("REPEAT="); // write repeat to file
      file.println(repeat);
      file.close(); // close file
   }
}

// ボタンを画面に設置して、対応するSSIDのWIFIに接続する。
// 接続に成功したかどうかをbooleanで返す
// 接続するSSID,WIFIパスワードは、配列に保存されている
// 3秒間接続できなかったら、falseを返す
// 引数は、ボタン番号の1つ
boolean connectWifi(int btn)
{
   boolean connect = false;
   Llcd.fillScreen(BLACK);
   Llcd.setCursor(0, 0);
   Llcd.setTextSize(2);
   Llcd.setTextColor(WHITE);
   Llcd.println("接続中...");
   Llcd.println("接続先:");
   // Llcd.println(ssid[btn]);
   Llcd.println("パスワード:");
   // Llcd.println(pass[btn]);
   Llcd.println("接続中...");
   // WiFi.begin(ssid[btn], pass[btn]);
   int cnt = 0;
   while (WiFi.status() != WL_CONNECTED && cnt < 30)
   {
      delay(100);
      cnt++;
   }
   if (WiFi.status() == WL_CONNECTED)
   {
      connect = true;
   }
   return connect;
}
