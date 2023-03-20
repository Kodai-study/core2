#include <Arduino.h>
#include <FirebaseESP32.h>
#include <M5Core2.h>

#define FIREBASE_HOST "modular-source-342310-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "yx1PO3FwKiYzo1wN5NedZAYqN2S26TH57kVmE4ZW"
#define WIFI_SSID "aterm-b9044b-g"
#define WIFI_PASSWORD "1ca1af621dff7"

FirebaseData firebaseData;

bool statusA = true;
bool statusB = true;
bool statusC = true;

bool buttonProcess(String buttonName, bool status)
{
  M5.Lcd.fillScreen(BLACK);
    if (Firebase.setBool(firebaseData, "/" + buttonName + "/", status))
    {
      //Success
      M5.Lcd.setCursor(0, 0);
      M5.Lcd.print("Set bool data success");
    }
    else
    {
      M5.Lcd.setCursor(0, 0);
      M5.Lcd.println("Error in setInt, ");
      M5.Lcd.print(firebaseData.errorReason());
    }
    M5.Lcd.setCursor(0, 20);
    M5.Lcd.print(buttonName + " was pressed!");
    return status = !status;
}

void setup()
{
  M5.begin();
  Serial.begin(115200);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  int _cursorX = 0;
  M5.Lcd.setTextFont(4);
  M5.Lcd.setTextColor(WHITE);
  M5.Lcd.setCursor(0, 0);
  // WiFiに接続
  M5.Lcd.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    M5.Lcd.setCursor(0 + 5 * _cursorX, 30);
    M5.Lcd.print(".");
    delay(300);
    _cursorX++;
    if (_cursorX > 320)
    {
      _cursorX = 0;
    }
  }
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setCursor(0, 0);
  M5.Lcd.print("Connected with IP:");
  M5.Lcd.print(WiFi.localIP());
  delay(1000);
  // Firebase関連
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);
}

void loop()
{
  M5.update();
  if (M5.BtnA.wasPressed())
  {
    statusA = buttonProcess("BtnA", statusA);
  }
  if (M5.BtnB.wasPressed())
  {
    statusB = buttonProcess("BtnB", statusB);
  }
  if (M5.BtnC.wasPressed())
  {
    statusC = buttonProcess("BtnC", statusC);
  }
}