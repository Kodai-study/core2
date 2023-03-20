#include <string>
#include <M5Core2.h>
#include "header.h"
#include <LinkedList.h>
#include <FirebaseESP32.h>
#define PROGRESS_MAX 100
using namespace std;

#define WIDTH 144
#define HEIGHT 205

void printDirectory(File dir, int numTabs);

static unsigned char gucProgress = 0;
static unsigned char gucOpenFlg = 0;
fs::File fp;
int x = 0;
int y = 0;
char c[HEIGHT][WIDTH];
char vec[10];

FirebaseData fbdo;

FirebaseAuth auth;
FirebaseConfig config;


bool split(char *str, char *buff)
{
  String s;
  LinkedList<int> linkedList;

  string input = string(str);
  int first = 0;
  int i = 0;
  int last = input.find_first_of(',');
  while (first < input.size())
  {
    std::string subStr(input, first, last - first);
    buff[i++] = atoi(subStr.c_str());
    first = last + 1;
    last = input.find_first_of(',', first);
    if (last == std::string::npos)
    {
      last = input.size();
    }
  }
  return false;
}

/*
void setup() {
  M5.begin();
  M5.Lcd.println("start");
  std::string line;
  fp = SD.open("/degu.csv");
  auto st = fp.readStringUntil('\n');
  // M5Stackの初期化
  M5.Lcd.println(fp.name());
  bool isNext = true;
  M5.Lcd.print(st);
  fp.read();
}
*/

File root;
/*
void setup()
{
  M5.begin();
  pinMode(10, OUTPUT);
  Firebase.begin(&config, &auth);
  
  auto wifiStat = WiFi.begin("aterm-b9044b-a", "1ca1af621dff7");
  Serial.printf("%d",(int)wifiStat);
  SD.begin();
  root = SD.open("/");
  printDirectory(root, 0);
  delay(2000);
  root.close();
  File fp = SD.open("/test.csv");
  if (!fp)
  {
    M5.Lcd.println("NO SD!!");
    return;
  }
  delay(2000);
  // M5.Lcd.println(fp.read());
  fp.read();
  fp.read();
  M5.Lcd.print((char)fp.read());
  delay(2000);
  while (fp.available())
  {
    // M5.Lcd.print(fp.readString());
    M5.Lcd.println(fp.readStringUntil('\n'));
    M5.lcd.write(99);
  }
  M5.Lcd.println("done!");
}
*/
void printDirectory(File dir, int numTabs)
{
  while (true)
  {
    File entry = dir.openNextFile();
    if (!entry)
    {
      dir.rewindDirectory();
      break;
    }
    for (uint8_t i = 0; i < numTabs; i++)
    {
      M5.Lcd.print('\t');
    }
    M5.Lcd.print(entry.name());
    if (entry.isDirectory())
    {
      M5.Lcd.println("/");
      printDirectory(entry, numTabs + 1);
    }
    else
    {
      M5.Lcd.println("\t\t");
    }
  }
}
