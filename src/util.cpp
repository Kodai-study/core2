#include "header.h"
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
            Llcd.print('\t');
        }
        Llcd.print(entry.name());
        if (entry.isDirectory())
        {
            Llcd.println("/");
            printDirectory(entry, numTabs + 1);
        }
        else
        {
            Llcd.println("\t\t");
        }
    }
}

bool split(char *str, char *buff)
{
    String input = String(str);
    int first = 0;
    int i = 0;
    int last = input.indexOf(',');
    while (first < input.length())
    {
       
        String subStr =  input.substring(first, last - first);
        buff[i++] = atoi(subStr.c_str());
        first = last + 1;
        last = input.indexOf(',', first);
        if (last == std::string::npos)
        {
            last = input.length();
        }
    }
    return false;
}

void sdCheck()
{
    auto wifiStat = WiFi.begin("aterm-b9044b-a", "1ca1af621dff7");
    Serial.printf("%d", (int)wifiStat);
    SD.begin();
    File root = SD.open("/");
    printDirectory(root, 0);
    delay(2000);
    root.close();
    File fp = SD.open("/test.csv");
    if (!fp)
    {
        Llcd.println("NO SD!!");
        return;
    }
    delay(2000);
    // Llcd.println(fp.read());
    fp.read();
    fp.read();
    Llcd.print((char)fp.read());
    delay(2000);
    while (fp.available())
    {
        // Llcd.print(fp.readString());
        Llcd.println(fp.readStringUntil('\n'));
        Llcd.write(99);
    }
    Llcd.println("done!");
}